// 57AC5 - A simple stack implementation - Marcin Drzymala

#ifndef __STATUS_H__
#define __STATUS_H__

#include <inttypes.h>

// Return codes
typedef enum {
    STATUS_OK = 0,    // Success
    STATUS_NOMEM,     // Insufficient memory
    STATUS_NULLPTR,   // Null pointer error
    STATUS_CORRUPTED, // Memory corruption error
    STATUS_EMPTY,     // Buffer is full
    STATUS_FULL       // Buffer is empty
} status_t;

// Convert status code into string
void status_print(char* buffer, const uint32_t maxlen, const status_t status);

#endif
