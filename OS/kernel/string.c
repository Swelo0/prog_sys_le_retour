//////////////////////////////////////////////////////////////////////////////////////////
/// \file string.c
/// \author Thierry Mourao
/// \author Sylvain Thullen
/// \author Sacha Conti
/// \date 29 november 2015
/// \brief Implementation of string and memory manipulation functions.
//////////////////////////////////////////////////////////////////////////////////////////

#include "string.h"

//////////////////////////////////////////////////////////////////////////////////////////
void *memset(void *dst, int value, uint count)
{
    while (count--)
    {
        ((unsigned char*)dst)[count] = (unsigned char)value;
    }
    return dst;
}

//////////////////////////////////////////////////////////////////////////////////////////
void *memcpy(void *dst, void *src, uint count)
{
    while (count--)
    {
        ((unsigned char*)dst)[count] = ((unsigned char*)src)[count];
    }
    return dst;
}

//////////////////////////////////////////////////////////////////////////////////////////
int strncmp(const char *p, const char *q, uint n)
{
    for (uint i = 0; i < n; i++)
    {
        if (p[i] != q[i])
        {
            return (p[i] < q[i] ? -1 : 1);
        }
        else if (p[i] == '\0')
        {
            return 0;
        }
    }
    return 0;
}

