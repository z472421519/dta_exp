#include "sanitizer_common/sanitizer_common.h"
#include "sanitizer_common/sanitizer_internal_defs.h"
#include "sanitizer_common/sanitizer_linux.h"

#include "dfsan.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

using namespace __dfsan;

#define TAINT_INPUT_LABEL 0xFF

extern "C" {

SANITIZER_INTERFACE_ATTRIBUTE 
size_t __dfsw_fread(void *ptr, size_t size, size_t count, FILE *stream,
            dfsan_label ptr_label, dfsan_label size_label,
            dfsan_label count_label, dfsan_label stream_label,
            dfsan_label *ret_label) {
    size_t len = fread(ptr, size, count, stream);
    dfsan_label label;
    if(len > 0) {
        for(int i = 0; i < len; i++) {
            label = dfsan_create_label(i);
            dfsan_set_label(label, (char* )ptr + i, 1);
        }
    }
    *ret_label = 0;
    return len;
}

//dfsan_custom defined
SANITIZER_INTERFACE_ATTRIBUTE
char *__dfsw_fgets(char *s, int size, FILE *stream, dfsan_label s_label,
            dfsan_label size_label, dfsan_label stream_label,
            dfsan_label *ret_label) {
    char *ret = fgets(s, size, stream);
    dfsan_label label; 
    if (ret) {
        for(int i = 0; i < size; i++) {
            label = dfsan_create_label(i);
            if(i == 0)
              dfsan_set_label(label, ret, 1);
            dfsan_set_label(label, (char* )s + i, 1);
        }    
        *ret_label = TAINT_INPUT_LABEL;
    } else {
        *ret_label = 0;
    }
    return ret;
}


SANITIZER_INTERFACE_ATTRIBUTE 
int __dfsw_fgetc(FILE *stream, dfsan_label stream_label, dfsan_label *ret_label) {
    int c = fgetc(stream);
    if(c != EOF) {  
        dfsan_label label = dfsan_create_label(0);
        dfsan_set_label(label, (char* )&c, 4);
        *ret_label = label;
    }
    else
        *ret_label = 0;
    return c;
}

SANITIZER_INTERFACE_ATTRIBUTE 
int __dfsw_fgetc_unlocked(FILE *stream, dfsan_label stream_label, dfsan_label *ret_label) {
    int c = fgetc_unlocked(stream);
    if(c != EOF) {  
        dfsan_label label = dfsan_create_label(0);
        dfsan_set_label(label, (char* )&c, 4);
        *ret_label = label;
    }
    else
        *ret_label = 0;
    return c;
}

SANITIZER_INTERFACE_ATTRIBUTE
int __dfsw_getchar(dfsan_label *ret_label) {
    int c = getchar();
    dfsan_label label;
    if(c != EOF) {
        label = dfsan_create_label(0);
        dfsan_set_label(label, (char* )&c, 4);
        *ret_label = label;
    }
    else
        *ret_label = 0;
    return c;
}

SANITIZER_INTERFACE_ATTRIBUTE
int __dfsw_getc(FILE *stream, dfsan_label stream_label, dfsan_label *ret_label) {
    int c = getc(stream);
    dfsan_label label;
    if(c != EOF) {
        label = dfsan_create_label(0);
        dfsan_set_label(label, (char* )&c, 4);
        *ret_label = label;
    }
    else
        *ret_label = 0;
    return c;
}
}
