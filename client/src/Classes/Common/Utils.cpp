
#include "Utils.h"
#include <stdio.h>

unsigned int Bomber::Common::convertGidToNew(unsigned int gid)
{
    if (gid == 0)
        return 0;

    unsigned int inputGid = gid;

    gid -= 1;

    unsigned int y = gid/16;
    unsigned int x = gid%16;

    while (y >= 42)
    {
        y -= 42;
        x += 16;
    }

    unsigned int result = y*64 + x + 1;

    printf("old = %u -> new = %u\n", inputGid, result);

    return result;
}

unsigned int Bomber::Common::convertGidToOld(unsigned int gid)
{
    if (gid == 0)
        return 0;

    unsigned int inputGid = gid;

    gid -= 1;

    unsigned int y = gid/64;
    unsigned int x = gid%64;

    while (x >= 16)
    {
        x -= 16;
        y += 42;
    }

    unsigned int result = y*16 + x + 1;

    printf("new = %u -> old = %u\n", inputGid, result);

    return result;
}
