//
// Created by tunay on 4/23/25.
//

#include "../include/mime.h"
#include <string.h>

int get_type(const char* extension) {
    if (extension == NULL) return "application/octet-stream";
    if (strcmp(extension, "html") == 0) return "text/html";
    if (strcmp(extension,"txt") == 0) return "text/plain";
    if (strcmp(extension,"css") == 0) return "text/css";
    if (strcmp(extension,"js") == 0) return "text/javascript";

    return "application/octet-stream";

}