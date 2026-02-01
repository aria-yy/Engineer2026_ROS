// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from arm_driver:msg/JointCommand.idl
// generated code does not contain a copyright notice

#ifndef ARM_DRIVER__MSG__DETAIL__JOINT_COMMAND__TRAITS_HPP_
#define ARM_DRIVER__MSG__DETAIL__JOINT_COMMAND__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "arm_driver/msg/detail/joint_command__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace arm_driver
{

namespace msg
{

inline void to_flow_style_yaml(
  const JointCommand & msg,
  std::ostream & out)
{
  out << "{";
  // member: joint_names
  {
    if (msg.joint_names.size() == 0) {
      out << "joint_names: []";
    } else {
      out << "joint_names: [";
      size_t pending_items = msg.joint_names.size();
      for (auto item : msg.joint_names) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: positions
  {
    if (msg.positions.size() == 0) {
      out << "positions: []";
    } else {
      out << "positions: [";
      size_t pending_items = msg.positions.size();
      for (auto item : msg.positions) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: velocities
  {
    if (msg.velocities.size() == 0) {
      out << "velocities: []";
    } else {
      out << "velocities: [";
      size_t pending_items = msg.velocities.size();
      for (auto item : msg.velocities) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const JointCommand & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: joint_names
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.joint_names.size() == 0) {
      out << "joint_names: []\n";
    } else {
      out << "joint_names:\n";
      for (auto item : msg.joint_names) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: positions
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.positions.size() == 0) {
      out << "positions: []\n";
    } else {
      out << "positions:\n";
      for (auto item : msg.positions) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: velocities
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.velocities.size() == 0) {
      out << "velocities: []\n";
    } else {
      out << "velocities:\n";
      for (auto item : msg.velocities) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const JointCommand & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace arm_driver

namespace rosidl_generator_traits
{

[[deprecated("use arm_driver::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const arm_driver::msg::JointCommand & msg,
  std::ostream & out, size_t indentation = 0)
{
  arm_driver::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use arm_driver::msg::to_yaml() instead")]]
inline std::string to_yaml(const arm_driver::msg::JointCommand & msg)
{
  return arm_driver::msg::to_yaml(msg);
}

template<>
inline const char * data_type<arm_driver::msg::JointCommand>()
{
  return "arm_driver::msg::JointCommand";
}

template<>
inline const char * name<arm_driver::msg::JointCommand>()
{
  return "arm_driver/msg/JointCommand";
}

template<>
struct has_fixed_size<arm_driver::msg::JointCommand>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<arm_driver::msg::JointCommand>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<arm_driver::msg::JointCommand>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ARM_DRIVER__MSG__DETAIL__JOINT_COMMAND__TRAITS_HPP_
