// 57AC5 - A simple stack implementation - Marcin Drzymala

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "status.h"

void status_print(char* buffer, const uint32_t maxlen, const status_t status) {
    switch(status) {
        case STATUS_OK:        strncpy(buffer, "STATUS_OK", maxlen); break;
        case STATUS_NOMEM:     strncpy(buffer, "STATUS_NOMEM", maxlen); break;
        case STATUS_NULLPTR:   strncpy(buffer, "STATUS_NULLPTR", maxlen); break;
        case STATUS_CORRUPTED: strncpy(buffer, "STATUS_CORRUPTED", maxlen); break;
        case STATUS_EMPTY:     strncpy(buffer, "STATUS_EMPTY", maxlen); break;
        case STATUS_FULL:      strncpy(buffer, "STATUS_FULL", maxlen); break;
        default: snprintf(buffer, maxlen, "%d", status); break;
    }
}
