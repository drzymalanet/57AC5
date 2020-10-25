// 57AC5 - A simple stack implementation - Marcin Drzymala

#ifndef __STACK_H__
#define __STACK_H__

#include <inttypes.h>
#include "status.h"

// Check the pointer to the stack object
status_t stack_check(void* pointer);

// Get the version of the stack implementation
status_t stack_ver(void* stack, uint32_t* version);

// Create a new stack collection on the heap with a given length
status_t stack_new(const uint64_t size, void** stack);

// Release the resources associated with the given stack object
status_t stack_free(void** stack);

// Insert a new item into the stack
status_t stack_put(void* stack, void** element);

// Retrieve an item from the stack
status_t stack_pop(void* stack, void** element);

// Get the number of items allocated in the stack
status_t stack_len(void* stack, uint64_t* length);

// Get the total capacity of the stack
status_t stack_cap(void* stack, uint64_t* capacity);

#endif
