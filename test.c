// 57AC5 - A simple stack implementation - Marcin Drzymala

#include "stack.h"
#include "status.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int panic(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    fflush(stderr);
    va_end(args);
    exit(-1);
    return -1;
}

int panic_status(char* msg, const status_t status) {
    char text[50];
    status_print(text, sizeof(text), status);
    return panic("%s - Status code %d: %s\n", msg, status, text);
}

int test_stack_overflow() {
    void* stack;
    uint64_t stack_size = 3;
    status_t result;

    // Create a stack
    result = stack_new(stack_size, &stack);
    if ( result != STATUS_OK ) {
        return panic_status("Error when creating stack", result);
    }

    // Fill the stack
    void* p;
    uint32_t i;
    for (i=0; i<stack_size; i++) {
        p = (void*)&i;
        result = stack_put(stack, &p);
        if ( result != STATUS_OK ) {
            return panic_status("Error when putting item into stack", result);
        }
    }

    // Overflow the stack
    p = (void*)&i;
    result = stack_put(stack, &p);
    if ( result != STATUS_FULL ) {
        return panic_status("Wrong error when overflowing stack", result);
    }

    // Release the heap memory
    stack_free(&stack);
}

int test_stack_underflow() {
    void* stack;
    uint64_t stack_size = 3;
    status_t result;

    // Create a stack
    result = stack_new(stack_size, &stack);
    if ( result != STATUS_OK ) {
        return panic_status("Error when creating stack", result);
    }

    // Fill the stack
    void* p;
    uint32_t i;
    for (i=0; i<stack_size; i++) {
        p = (void*)&i;
        result = stack_put(stack, &p);
        if ( result != STATUS_OK ) {
            return panic_status("Error when putting item into stack", result);
        }
    }

    // Empty the stack
    for (i=0; i<stack_size; i++) {
        result = stack_pop(stack, &p);
        if ( result != STATUS_OK ) {
            return panic_status("Error when popping item from the stack", result);
        }
    }

    // Underflow the stack
    result = stack_pop(stack, &p);
    if ( result != STATUS_EMPTY ) {
        return panic_status("Wrong error when underflowing the stack", result);
    }

    // Release the heap memory
    stack_free(&stack);
}

int test_stack_ordering() {
    void* stack;
    uint64_t stack_size = 3;
    status_t result;

    // Create a stack
    result = stack_new(stack_size, &stack);
    if ( result != STATUS_OK ) {
        return panic_status("Error when creating stack", result);
    }

    // Push to the stack
    uint8_t one = 1;
    uint8_t two = 2;
    uint8_t three = 3;
    uint8_t* p_one = &one;
    uint8_t* p_two = &two;
    uint8_t* p_three = &three;

    result = stack_put(stack, (void*)&p_one);
    if ( result != STATUS_OK ) {
        return panic_status("Error when putting item 1 into stack", result);
    }

    result = stack_put(stack, (void*)&p_two);
    if ( result != STATUS_OK ) {
        return panic_status("Error when putting item 2 into stack", result);
    }

    result = stack_put(stack, (void*)&p_three);
    if ( result != STATUS_OK ) {
        return panic_status("Error when putting item 3 into stack", result);
    }

    // Pop from the stack
    uint8_t* val = 0;
    result = stack_pop(stack, (void*)&val);
    if ( result != STATUS_OK ) {
        return panic_status("Error when popping item 3 from the stack", result);
    }
    if ( *val != 3 ) {
        return panic("Wrong item returned from the stack: %d", *val);
    }

    result = stack_pop(stack, (void*)&val);
    if ( result != STATUS_OK ) {
        return panic_status("Error when popping item 2 from the stack", result);
    }
    if ( *val != 2 ) {
        return panic("Wrong item returned from the stack: %d", *val);
    }

    result = stack_pop(stack, (void*)&val);
    if ( result != STATUS_OK ) {
        return panic_status("Error when popping item 1 from the stack", result);
    }
    if ( *val != 1 ) {
        return panic("Wrong item returned from the stack: %d", *val);
    }

    // Release the heap memory
    stack_free(&stack);
}

int main(int argc, char *argv[]) {
    test_stack_overflow();
    test_stack_underflow();
    test_stack_ordering();
    fprintf(stderr, "All tests passed\n");
    fflush(stderr);
    exit(0);
}


