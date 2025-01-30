#include <bh/io.h>

int main()
{
    BH_IO *io = BH_FileNew("hello.txt");
    BH_IOOpen(io, BH_IO_WRITE);
    BH_IOWrite(io, "Hello, world!", 13, NULL);
    BH_IOFree(io);

    return 0;
}