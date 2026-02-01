#include "arm_driver/hjarm_engineer.h"

LibSerial::SerialPort HjarmEngineer::serial_port_;
rclcpp::Publisher<std_msgs::msg::String>::SharedPtr HjarmEngineer::pub_stm32_raw_;
rclcpp::Time send_start_time;
HjarmEngineer::HjarmEngineer(const rclcpp::NodeOptions & options)
: Node("hjarm_engineer", options), manipulator_()
{
    // 串口初始化
    try {

        serial_port_.Open("/dev/ttyACM0");               
        serial_port_.SetBaudRate(LibSerial::BaudRate::BAUD_115200);
        serial_port_.SetCharacterSize(LibSerial::CharacterSize::CHAR_SIZE_8);
        serial_port_.SetParity(LibSerial::Parity::PARITY_NONE);
        serial_port_.SetStopBits(LibSerial::StopBits::STOP_BITS_1);

        RCLCPP_INFO(this->get_logger(), "Serial port opened succeed"); 
        // 启动串口读取线程
        thread(&HjarmEngineer::serial_read_thread, this).detach();

    } catch (const LibSerial::OpenFailed& e) {
        RCLCPP_ERROR(this->get_logger(), "Failed to open serial port: %s", e.what());
    }


    this->declare_parameter<vector<string>>("joint_names", {"joint1", "joint2", "joint3","joint4", "joint5", "joint6"});

    this->get_parameter("joint_names", joint_names_);
    manipulator_.dof = joint_names_.size();

    for (const auto & name : joint_names_) {
        HjarmJoint joint;
        joint.name = name;
        joint.position = 0.0;
        joint.velocity = 0.0;
        joint.effort = 0.0;
        manipulator_.joints.push_back(joint);
    }
    
    pub_joint_state_ = this->create_publisher<sensor_msgs::msg::JointState>("/joint_states", 10);

    action_server_ = rclcpp_action::create_server<FollowJointTrajectory>(
        this,
        "test_group_controller/follow_joint_trajectory",
        bind(&HjarmEngineer::handle_goal, this, placeholders::_1, placeholders::_2),
        bind(&HjarmEngineer::handle_cancel, this, placeholders::_1),
        bind(&HjarmEngineer::handle_accepted, this, placeholders::_1));

    timer_ = this->create_wall_timer(
        chrono::milliseconds(100),
        bind(&HjarmEngineer::joint_state_update, this));
}

// 串口读取线程函数
void HjarmEngineer::serial_read_thread()
{
    // string data_str;
    // serial_port_.Read(data_str);
    // RCLCPP_INFO(this->get_logger(), "Received: %s ", data_str.c_str());      
    // const uint8_t FRAME_END[] = {0x55}; 
    // const size_t FRAME_END_LEN = sizeof(FRAME_END)/sizeof(FRAME_END[0]);
    
    vector<uint8_t> buffer;
    uint8_t byte; 

    serial_port_.SetVTime(1);
    serial_port_.SetVMin(0);
    while (rclcpp::ok() && serial_port_.IsOpen())
    {

            //RCLCPP_INFO(this->get_logger(), "Time: %f",send_start_time-this.now());
            serial_port_.ReadByte(byte); 
            uint8_t ubyte = static_cast<uint8_t>(byte);
            buffer.push_back(ubyte);

            // 检测完整帧：包含帧头0xAA且以帧尾0x55结尾
            if (buffer.size() >= 2) // 至少包含帧头+帧尾
            {
                // 查找帧头位置（从后往前找，避免旧帧头干扰）
                auto head_pos = find(buffer.rbegin(), buffer.rend(), 0xAA);
                if (head_pos != buffer.rend())
                {
                    size_t head_idx = distance(buffer.begin(), head_pos.base()) - 1;
                    size_t tail_idx = buffer.size() - 1;

                    // 验证帧尾：帧头之后存在帧尾0x55
                    if (tail_idx > head_idx && buffer[tail_idx] == 0x55)
                    {
                        // 提取完整帧（帧头到帧尾）
                        vector<uint8_t> frame(buffer.begin() + head_idx, buffer.end());
                        
                        // 打印完整帧数据
                        RCLCPP_INFO(this->get_logger(), "收到完整帧（长度：%zu）：", frame.size());
                        //for (uint8_t b : frame) printf("%02X ", b);

                        vector<uint8_t> data_bytes(frame.begin() + 1, frame.end() - 2);
                             for (size_t i = 0; i < data_bytes.size(); i += 4)
                                {
                                    if (i + 4 <= data_bytes.size())
                                    {
                                        float value;
                                        memcpy(&value, &data_bytes[i], sizeof(float));
                                        //RCLCPP_INFO(this->get_logger(), "%.4f ", value);
                                        printf("%.4f ",value);
                                    }
                                }        
                        
                        printf("\n");

                        // 清空已处理的帧数据，保留未匹配的部分（防止新帧头被截断）
                        buffer.erase(buffer.begin(), buffer.begin() + tail_idx + 1);
                    }
                }
            }

            if (buffer.size() > 1024)
            {
                RCLCPP_WARN(this->get_logger(), "缓存溢出，清空无效数据");
                buffer.clear();
            }
        this_thread::sleep_for(chrono::milliseconds(20));
    }    
}

HjarmEngineer::~HjarmEngineer() {}

rclcpp_action::GoalResponse HjarmEngineer::handle_goal(
    const rclcpp_action::GoalUUID & uuid,
    shared_ptr<const FollowJointTrajectory::Goal> goal)
{
    (void)uuid;
    if (goal->trajectory.joint_names != joint_names_) {
        RCLCPP_WARN(this->get_logger(), "Joint names mismatch!");
        return rclcpp_action::GoalResponse::REJECT;
    }
    if (goal->trajectory.points.empty()) {
        RCLCPP_WARN(this->get_logger(), "Empty trajectory goal");
        return rclcpp_action::GoalResponse::REJECT;
    }
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

rclcpp_action::CancelResponse HjarmEngineer::handle_cancel(
    const shared_ptr<GoalHandleFollowJointTrajectory> goal_handle)
{
    (void)goal_handle;
    return rclcpp_action::CancelResponse::ACCEPT;
}

void HjarmEngineer::handle_accepted(const shared_ptr<GoalHandleFollowJointTrajectory> goal_handle)
{
    thread{bind(&HjarmEngineer::execute_trajectory, this, placeholders::_1), goal_handle}.detach();
}

// 发布关节指令给下位机的函数
void HjarmEngineer::send_joint_command_to_stm32()
{
    arm_driver::msg::JointCommand cmd_msg;

    // 关节名称
    cmd_msg.joint_names = joint_names_;

    JointCommandPacket send_package;
    
    for (size_t j = 0; j < manipulator_.dof && j < 6; ++j) {
        send_package.joint_positions[j] = manipulator_.joints[j].position;    // 弧度
        send_package.joint_velocities[j] = manipulator_.joints[j].velocity;   // 弧度/秒单位
    }

    uint8_t* data_ptr = reinterpret_cast<uint8_t*>(&send_package);
    send_package.checksum = 0;
    for (size_t i = 1; i < sizeof(JointCommandPacket) - 2; i++) {
        send_package.checksum ^= data_ptr[i];
    
    }

    // serial_port_.Write(cmd_msg);
    try {
        string data_str(reinterpret_cast<const char*>(&send_package), sizeof(JointCommandPacket));
        serial_port_.Write(data_str);
        
        send_start_time=this->now();
        RCLCPP_INFO(this->get_logger(), "Send binary packet to STM32: j1=%.3f, j2=%.3f, j3=%.3f, j4=%.3f, j5=%.3f, j6=%.3f ",
                    send_package.joint_positions[0], 
                    send_package.joint_positions[1], 
                    send_package.joint_positions[2],
                    send_package.joint_positions[3],
                    send_package.joint_positions[4],
                    send_package.joint_positions[5]   );
                    
        //serial_read_thread();                   
    } catch (const exception& e) {
        RCLCPP_ERROR(this->get_logger(), "Failed to send binary packet: %s", e.what());
    }
}

void HjarmEngineer::execute_trajectory(const shared_ptr<GoalHandleFollowJointTrajectory> goal_handle)
{
    const auto goal = goal_handle->get_goal();
    auto feedback = std::make_shared<FollowJointTrajectory::Feedback>();
    auto result = std::make_shared<FollowJointTrajectory::Result>();

    rclcpp::Rate rate(100.0);

    rclcpp::Time trajectory_start_time;
    if (rclcpp::Time(goal->trajectory.header.stamp).nanoseconds() == 0) {
        trajectory_start_time = this->now();
    } else {
        trajectory_start_time = rclcpp::Time(goal->trajectory.header.stamp);
    }

    for (size_t i = 1; i < goal->trajectory.points.size(); ++i) {
        if (goal_handle->is_canceling()) {
            result->error_code = FollowJointTrajectory::Result::SUCCESSFUL;
            goal_handle->canceled(result);
            return;
        }

        const auto& target_point = goal->trajectory.points[i];

        for (size_t j = 0; j < target_point.positions.size() && j < manipulator_.dof; ++j) {
            manipulator_.joints[j].position = target_point.positions[j];  // 目标位置
            manipulator_.joints[j].velocity = 0.5;  
        }
        // 发送目标点到STM32
        this->send_joint_command_to_stm32();

            feedback->joint_names = joint_names_;
            feedback->actual.positions = {manipulator_.joints[0].position, manipulator_.joints[1].position, manipulator_.joints[2].position};
            feedback->actual.velocities = {manipulator_.joints[0].velocity, manipulator_.joints[1].velocity, manipulator_.joints[2].velocity};

            goal_handle->publish_feedback(feedback);

            rate.sleep();
        
    }

    if (rclcpp::ok()) {
        result->error_code = FollowJointTrajectory::Result::SUCCESSFUL;
        goal_handle->succeed(result);
    }
}

void HjarmEngineer::joint_state_update()
{
    auto msg = sensor_msgs::msg::JointState();
    msg.header.stamp = this->now();
    msg.name = joint_names_;
    msg.position.resize(manipulator_.dof);
    msg.velocity.resize(manipulator_.dof);
    
    for (size_t i = 0; i < manipulator_.dof; ++i) {
        msg.position[i] = manipulator_.joints[i].position;
        msg.velocity[i] = manipulator_.joints[i].velocity;
    }
    
    pub_joint_state_->publish(msg);
}


int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(make_shared<HjarmEngineer>());
    rclcpp::shutdown();
    return 0;
}