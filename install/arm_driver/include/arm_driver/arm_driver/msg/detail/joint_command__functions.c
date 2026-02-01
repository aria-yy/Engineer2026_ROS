// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from arm_driver:msg/JointCommand.idl
// generated code does not contain a copyright notice
#include "arm_driver/msg/detail/joint_command__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `joint_names`
#include "rosidl_runtime_c/string_functions.h"
// Member `positions`
// Member `velocities`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
arm_driver__msg__JointCommand__init(arm_driver__msg__JointCommand * msg)
{
  if (!msg) {
    return false;
  }
  // joint_names
  if (!rosidl_runtime_c__String__Sequence__init(&msg->joint_names, 0)) {
    arm_driver__msg__JointCommand__fini(msg);
    return false;
  }
  // positions
  if (!rosidl_runtime_c__double__Sequence__init(&msg->positions, 0)) {
    arm_driver__msg__JointCommand__fini(msg);
    return false;
  }
  // velocities
  if (!rosidl_runtime_c__double__Sequence__init(&msg->velocities, 0)) {
    arm_driver__msg__JointCommand__fini(msg);
    return false;
  }
  return true;
}

void
arm_driver__msg__JointCommand__fini(arm_driver__msg__JointCommand * msg)
{
  if (!msg) {
    return;
  }
  // joint_names
  rosidl_runtime_c__String__Sequence__fini(&msg->joint_names);
  // positions
  rosidl_runtime_c__double__Sequence__fini(&msg->positions);
  // velocities
  rosidl_runtime_c__double__Sequence__fini(&msg->velocities);
}

bool
arm_driver__msg__JointCommand__are_equal(const arm_driver__msg__JointCommand * lhs, const arm_driver__msg__JointCommand * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // joint_names
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->joint_names), &(rhs->joint_names)))
  {
    return false;
  }
  // positions
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->positions), &(rhs->positions)))
  {
    return false;
  }
  // velocities
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->velocities), &(rhs->velocities)))
  {
    return false;
  }
  return true;
}

bool
arm_driver__msg__JointCommand__copy(
  const arm_driver__msg__JointCommand * input,
  arm_driver__msg__JointCommand * output)
{
  if (!input || !output) {
    return false;
  }
  // joint_names
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->joint_names), &(output->joint_names)))
  {
    return false;
  }
  // positions
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->positions), &(output->positions)))
  {
    return false;
  }
  // velocities
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->velocities), &(output->velocities)))
  {
    return false;
  }
  return true;
}

arm_driver__msg__JointCommand *
arm_driver__msg__JointCommand__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  arm_driver__msg__JointCommand * msg = (arm_driver__msg__JointCommand *)allocator.allocate(sizeof(arm_driver__msg__JointCommand), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(arm_driver__msg__JointCommand));
  bool success = arm_driver__msg__JointCommand__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
arm_driver__msg__JointCommand__destroy(arm_driver__msg__JointCommand * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    arm_driver__msg__JointCommand__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
arm_driver__msg__JointCommand__Sequence__init(arm_driver__msg__JointCommand__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  arm_driver__msg__JointCommand * data = NULL;

  if (size) {
    data = (arm_driver__msg__JointCommand *)allocator.zero_allocate(size, sizeof(arm_driver__msg__JointCommand), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = arm_driver__msg__JointCommand__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        arm_driver__msg__JointCommand__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
arm_driver__msg__JointCommand__Sequence__fini(arm_driver__msg__JointCommand__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      arm_driver__msg__JointCommand__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

arm_driver__msg__JointCommand__Sequence *
arm_driver__msg__JointCommand__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  arm_driver__msg__JointCommand__Sequence * array = (arm_driver__msg__JointCommand__Sequence *)allocator.allocate(sizeof(arm_driver__msg__JointCommand__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = arm_driver__msg__JointCommand__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
arm_driver__msg__JointCommand__Sequence__destroy(arm_driver__msg__JointCommand__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    arm_driver__msg__JointCommand__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
arm_driver__msg__JointCommand__Sequence__are_equal(const arm_driver__msg__JointCommand__Sequence * lhs, const arm_driver__msg__JointCommand__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!arm_driver__msg__JointCommand__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
arm_driver__msg__JointCommand__Sequence__copy(
  const arm_driver__msg__JointCommand__Sequence * input,
  arm_driver__msg__JointCommand__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(arm_driver__msg__JointCommand);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    arm_driver__msg__JointCommand * data =
      (arm_driver__msg__JointCommand *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!arm_driver__msg__JointCommand__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          arm_driver__msg__JointCommand__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!arm_driver__msg__JointCommand__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
