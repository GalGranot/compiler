#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>
#include <iostream>

void errorAndExit(std::string error)
{
    std::cerr << error << std::endl;
    exit(1);
}

#endif //__UTILS_H__