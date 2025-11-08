#include <BH/IO.h>


BH_IO *BH_FileNew(const char *path,
                  int mode,
                  int *result)
{
    BH_UNUSED(path);
    BH_UNUSED(mode);

    if (result)
        *result = BH_NOIMPL;

    return NULL;
}


int BH_IOIsFile(BH_IO *device)
{
    return 0;
}
