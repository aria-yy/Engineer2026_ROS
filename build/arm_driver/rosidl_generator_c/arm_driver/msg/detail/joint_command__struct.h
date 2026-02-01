// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from arm_driver:msg/JointCommand.idl
// generated code does not contain a copyright notice

#ifndef ARM_DRIVER__MSG__DETAIL__JOINT_COMMAND__STRUCT_H_
#define ARM_DRIVER__MSG__DETAIL__JOINT_COMMAND__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'joint_names'
#include "rosidl_runtime_c/string.h"
// Member 'positions'
// Member 'velocities'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/JointCommand in the package arm_driver.
typedef struct arm_driver__msg__JointCommand
{
  rosidl_runtime_c__String__Sequence joint_names;
  rosidl_runtime_c__double__Sequence positions;
  rosidl_runtime_c__double__Sequence velocities;
} arm_driver__msg__JointCommand;

// Struct for a sequence of arm_driver__msg__JointCommand.
typedef struct arm_driver__msg__JointCommand__Sequence
{
  arm_driver__msg__JointCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} arm_driver__msg__JointCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ARM_DRIVER__MSG__DETAIL__JOINT_COMMAND__STRUCT_H_
