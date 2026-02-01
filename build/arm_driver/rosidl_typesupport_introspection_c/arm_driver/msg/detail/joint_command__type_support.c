// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from arm_driver:msg/JointCommand.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "arm_driver/msg/detail/joint_command__rosidl_typesupport_introspection_c.h"
#include "arm_driver/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "arm_driver/msg/detail/joint_command__functions.h"
#include "arm_driver/msg/detail/joint_command__struct.h"


// Include directives for member types
// Member `joint_names`
#include "rosidl_runtime_c/string_functions.h"
// Member `positions`
// Member `velocities`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__JointCommand_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  arm_driver__msg__JointCommand__init(message_memory);
}

void arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__JointCommand_fini_function(void * message_memory)
{
  arm_driver__msg__JointCommand__fini(message_memory);
}

size_t arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__size_function__JointCommand__joint_names(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__get_const_function__JointCommand__joint_names(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__get_function__JointCommand__joint_names(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__fetch_function__JointCommand__joint_names(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__get_const_function__JointCommand__joint_names(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__assign_function__JointCommand__joint_names(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__get_function__JointCommand__joint_names(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__resize_function__JointCommand__joint_names(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__size_function__JointCommand__positions(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__get_const_function__JointCommand__positions(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__get_function__JointCommand__positions(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__fetch_function__JointCommand__positions(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__get_const_function__JointCommand__positions(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__assign_function__JointCommand__positions(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__get_function__JointCommand__positions(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__resize_function__JointCommand__positions(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

size_t arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__size_function__JointCommand__velocities(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__get_const_function__JointCommand__velocities(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__get_function__JointCommand__velocities(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__fetch_function__JointCommand__velocities(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__get_const_function__JointCommand__velocities(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__assign_function__JointCommand__velocities(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__get_function__JointCommand__velocities(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__resize_function__JointCommand__velocities(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__JointCommand_message_member_array[3] = {
  {
    "joint_names",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(arm_driver__msg__JointCommand, joint_names),  // bytes offset in struct
    NULL,  // default value
    arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__size_function__JointCommand__joint_names,  // size() function pointer
    arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__get_const_function__JointCommand__joint_names,  // get_const(index) function pointer
    arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__get_function__JointCommand__joint_names,  // get(index) function pointer
    arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__fetch_function__JointCommand__joint_names,  // fetch(index, &value) function pointer
    arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__assign_function__JointCommand__joint_names,  // assign(index, value) function pointer
    arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__resize_function__JointCommand__joint_names  // resize(index) function pointer
  },
  {
    "positions",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(arm_driver__msg__JointCommand, positions),  // bytes offset in struct
    NULL,  // default value
    arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__size_function__JointCommand__positions,  // size() function pointer
    arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__get_const_function__JointCommand__positions,  // get_const(index) function pointer
    arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__get_function__JointCommand__positions,  // get(index) function pointer
    arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__fetch_function__JointCommand__positions,  // fetch(index, &value) function pointer
    arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__assign_function__JointCommand__positions,  // assign(index, value) function pointer
    arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__resize_function__JointCommand__positions  // resize(index) function pointer
  },
  {
    "velocities",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(arm_driver__msg__JointCommand, velocities),  // bytes offset in struct
    NULL,  // default value
    arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__size_function__JointCommand__velocities,  // size() function pointer
    arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__get_const_function__JointCommand__velocities,  // get_const(index) function pointer
    arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__get_function__JointCommand__velocities,  // get(index) function pointer
    arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__fetch_function__JointCommand__velocities,  // fetch(index, &value) function pointer
    arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__assign_function__JointCommand__velocities,  // assign(index, value) function pointer
    arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__resize_function__JointCommand__velocities  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__JointCommand_message_members = {
  "arm_driver__msg",  // message namespace
  "JointCommand",  // message name
  3,  // number of fields
  sizeof(arm_driver__msg__JointCommand),
  arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__JointCommand_message_member_array,  // message members
  arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__JointCommand_init_function,  // function to initialize message memory (memory has to be allocated)
  arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__JointCommand_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__JointCommand_message_type_support_handle = {
  0,
  &arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__JointCommand_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_arm_driver
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, arm_driver, msg, JointCommand)() {
  if (!arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__JointCommand_message_type_support_handle.typesupport_identifier) {
    arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__JointCommand_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &arm_driver__msg__JointCommand__rosidl_typesupport_introspection_c__JointCommand_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
