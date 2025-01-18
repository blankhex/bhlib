#include <bh/io.h>

int main()
{
    bh_io_t *io = bh_file_new("hello.txt");
    bh_io_open(io, BH_IO_WRITE);
    bh_io_write(io, "Hello, world!", 13, NULL);
    bh_io_free(io);
    return 0;
}