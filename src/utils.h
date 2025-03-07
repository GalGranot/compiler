#ifndef __COMPILER_UTILS_H__
#define __COMPILER_UTILS_H__

#include <unistd.h>
#include <stdio.h>
#include <algorithm>

#define error_exit(msg) \
    do { \
        fprintf(stderr, "%s:%d\n", __FILE__, __LINE__); \
        perror(msg); \
        exit(1); \
    } while(0)

template <typename T, typename U>
bool is_in(const T& container, const U& value)
{
    return std::find(container.begin(), container.end(), value) != container.end();
}

#endif //__COMPILER_UTILS_H__