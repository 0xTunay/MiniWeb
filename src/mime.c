//
// Created by tunay on 4/23/25.
//

#include "../include/mime.h"
#include <string.h>

const char *get_type(const char* extension) {

    if (extension == NULL) return "application/octet-stream";
    if (strcmp(extension, "html") == 0) return "text/html";
    if (strcmp(extension, "txt") == 0) return "text/plain";
    if (strcmp(extension, "css") == 0) return "text/css";
    return "application/octet-stream";

}