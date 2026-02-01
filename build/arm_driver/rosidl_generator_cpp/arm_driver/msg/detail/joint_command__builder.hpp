// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from arm_driver:msg/JointCommand.idl
// generated code does not contain a copyright notice

#ifndef ARM_DRIVER__MSG__DETAIL__JOINT_COMMAND__BUILDER_HPP_
#define ARM_DRIVER__MSG__DETAIL__JOINT_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "arm_driver/msg/detail/joint_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace arm_driver
{

namespace msg
{

namespace builder
{

class Init_JointCommand_velocities
{
public:
  explicit Init_JointCommand_velocities(::arm_driver::msg::JointCommand & msg)
  : msg_(msg)
  {}
  ::arm_driver::msg::JointCommand velocities(::arm_driver::msg::JointCommand::_velocities_type arg)
  {
    msg_.velocities = std::move(arg);
    return std::move(msg_);
  }

private:
  ::arm_driver::msg::JointCommand msg_;
};

class Init_JointCommand_positions
{
public:
  explicit Init_JointCommand_positions(::arm_driver::msg::JointCommand & msg)
  : msg_(msg)
  {}
  Init_JointCommand_velocities positions(::arm_driver::msg::JointCommand::_positions_type arg)
  {
    msg_.positions = std::move(arg);
    return Init_JointCommand_velocities(msg_);
  }

private:
  ::arm_driver::msg::JointCommand msg_;
};

class Init_JointCommand_joint_names
{
public:
  Init_JointCommand_joint_names()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_JointCommand_positions joint_names(::arm_driver::msg::JointCommand::_joint_names_type arg)
  {
    msg_.joint_names = std::move(arg);
    return Init_JointCommand_positions(msg_);
  }

private:
  ::arm_driver::msg::JointCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::arm_driver::msg::JointCommand>()
{
  return arm_driver::msg::builder::Init_JointCommand_joint_names();
}

}  // namespace arm_driver

#endif  // ARM_DRIVER__MSG__DETAIL__JOINT_COMMAND__BUILDER_HPP_
