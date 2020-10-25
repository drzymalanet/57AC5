// 57AC5 - A simple stack implementation - Marcin Drzymala

#include <inttypes.h>
#include <stdlib.h>
#include "status.h"

#define MAGIC_STACK_TAG 0x57AC5001 // STACK001

typedef struct stack_t {
    uint32_t tag;
    uint64_t cap;
    uint64_t len;
    void* mem[1];
} stack_t;

status_t stack_check(void* pointer) {
    stack_t* header = (stack_t*) pointer;
    if ( header == 0 ) {
        return STATUS_NULLPTR;
    } else if ( header->tag != MAGIC_STACK_TAG ) {
        return STATUS_CORRUPTED;
    } else if ( header->len > header->cap ) {
        return STATUS_CORRUPTED;
    } else {
        return STATUS_OK;
    }
}

status_t stack_new(const uint64_t size, void** stack) {
    const uint64_t hdr_sz = sizeof(stack_t);
    const uint64_t mem_sz = sizeof(void*) * size;
    *stack = malloc(hdr_sz + mem_sz);
    if ( *stack == 0 ) {
        return STATUS_NOMEM;
    }
    stack_t* header = (stack_t*)(*stack);
    header->tag = MAGIC_STACK_TAG;
    header->cap = size;
    header->len = 0;
    return STATUS_OK;
}

status_t stack_free(void** stack) {
    if ( stack && *stack ) {
        free(*stack);
        *stack = 0;
    }
    return STATUS_OK;
}

status_t stack_put(void* stack, void** element) {
    status_t result = stack_check(stack);
    stack_t* header = (stack_t*) stack;
    if ( result != STATUS_OK ) {
        return result;
    }
    if ( header->cap == header->len ) {
        return STATUS_FULL;
    }
    if ( element == 0 ) {
        return STATUS_NULLPTR;
    }
    header->mem[header->len] = *element;
    header->len++;
    *element = 0;
    return STATUS_OK;
}

status_t stack_pop(void* stack, void** element) {
    stack_t* header = (stack_t*) stack;
    status_t result = stack_check(header);
    if ( result != STATUS_OK ) {
        return result;
    }
    if ( header->len == 0 ) {
        return STATUS_EMPTY;
    }
    if ( element == 0 ) {
        return STATUS_NULLPTR;
    }
    header->len--;
    *element = header->mem[header->len];
    return STATUS_OK;
}

status_t stack_len(void* stack, uint64_t* length) {
    stack_t* header = (stack_t*) stack;
    status_t result = stack_check(header);
    if ( result != STATUS_OK ) {
        return result;
    }
    *length = header->len;
    return STATUS_OK;
}

status_t stack_cap(void* stack, uint64_t* capacity) {
    stack_t* header = (stack_t*) stack;
    status_t result = stack_check(header);
    if ( result != STATUS_OK ) {
        return result;
    }
    *capacity = header->cap;
    return STATUS_OK;
}

status_t stack_ver(void* stack, uint32_t* version) {
    stack_t* header = (stack_t*) stack;
    uint32_t magic_tag = MAGIC_STACK_TAG & 0xFFFFF000;
    uint32_t stack_tag = header->tag & 0xFFFFF000;
    if ( header == 0 ) {
        return STATUS_NULLPTR;
    } else if ( header->len > header->cap ) {
        return STATUS_CORRUPTED;
    } else if ( magic_tag != stack_tag ) {
        return STATUS_CORRUPTED;
    } else {
        *version = header->tag & 0xFFF;
        return STATUS_OK;
    }
}
