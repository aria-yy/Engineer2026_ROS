#ifndef ARM_DRIVER_HJARM_ENGINEER_H
#define ARM_DRIVER_HJARM_ENGINEER_H

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "std_msgs/msg/string.hpp"
#include "control_msgs/action/follow_joint_trajectory.hpp"
#include "arm_driver/msg/joint_command.hpp"

#include <vector>
#include <string>
#include <chrono>
#include <functional>
#include <memory>
#include <sstream>
#include <libserial/SerialPort.h>
#include <libserial/SerialStream.h>
#include <thread>

using namespace std;

struct JointCommandPacket {
    uint8_t header = 0xAA;
    float joint_positions[3];
    float joint_velocities[3]; 
    uint8_t checksum;
    uint8_t footer = 0x55;
} __attribute__((packed));

// 关节和机械臂结构体
struct HjarmJoint {
    string name;
    float position;
    float velocity;
    float effort;
};

struct HjarmManipulator {
    vector<HjarmJoint> joints;
    size_t dof;
};

// 动作类型别名
using FollowJointTrajectory = control_msgs::action::FollowJointTrajectory;
using GoalHandleFollowJointTrajectory = rclcpp_action::ServerGoalHandle<FollowJointTrajectory>;

class HjarmEngineer : public rclcpp::Node
{
public:
    HjarmEngineer(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());
    ~HjarmEngineer();

private:
    static LibSerial::SerialPort serial_port_;
    static rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_stm32_raw_;

    vector<string> joint_names_;
    rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr pub_joint_state_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_stm32_;
    rclcpp_action::Server<FollowJointTrajectory>::SharedPtr action_server_;
    rclcpp::TimerBase::SharedPtr timer_;
    HjarmManipulator manipulator_;
    rclcpp::Publisher<arm_driver::msg::JointCommand>::SharedPtr pub_joint_cmd_;

    // 成员函数
    void serial_read_thread();
    void sub_stm32_callback(const std_msgs::msg::String::SharedPtr msg);
    void joint_state_update();
    void send_joint_command_to_stm32();
    void execute_trajectory(const shared_ptr<GoalHandleFollowJointTrajectory> goal_handle);
    
    // 动作服务器回调
    rclcpp_action::GoalResponse handle_goal(
        const rclcpp_action::GoalUUID & uuid,
        shared_ptr<const FollowJointTrajectory::Goal> goal);
    rclcpp_action::CancelResponse handle_cancel(
        const shared_ptr<GoalHandleFollowJointTrajectory> goal_handle);
    void handle_accepted(const shared_ptr<GoalHandleFollowJointTrajectory> goal_handle);
};

#endif