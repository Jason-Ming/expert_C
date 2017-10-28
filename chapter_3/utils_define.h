#ifndef __UTILS_DEFINE_H__
#define __UTILS_DEFINE_H__

#include <stdio.h>
#include <string.h>


#include "type_define.h"
#include "value_define.h"


#define R_FALSE_RET(condition, value)\
    if(!(condition))\
    {\
        return value;\
    }

#define R_ASSERT(condition, value)\
    if(!(condition))\
    {\
        printf("ASSERT! "#condition"\n");\
        return value;\
    }

#define R_ASSERT_DO(condition, value, action)\
    if(!(condition))\
    {\
        printf("ASSERT! "#condition"\n");\
        action;\
        return value;\
    }

#define R_ASSERT_LOG(condition, value, fmt, args...)\
    if(!(condition))\
    {\
        printf("ASSERT! "#condition"\n");\
        printf(fmt,##args);\
        return value;\
    }

#define R_ASSERT_LOG_DO(condition, value, action, fmt, args...)\
    if(!(condition))\
    {\
        printf("ASSERT! "#condition"\n");\
        printf(fmt,##args);\
        action;\
        return value;\
    }

#define DEBUG 0

#ifdef DEBUG
#define LOG(fmt, args...)\
    printf("##LOG[file:%s:%d, function: %s] "fmt"\n",__FILE__,__LINE__,__func__,##args)
#else
#define LOG(fmt, args...)
#endif

/* */
#define LOG1(format, ...) printf(format, ##__VA_ARGS__)

#endif

