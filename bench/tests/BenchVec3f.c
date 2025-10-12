#include <BH/Bench.h>
#include <BH/Math/Vec3f.h>
#include <stdlib.h>


BH_BENCH_TEST(Vec3f)
{
    float a[3], b[3];

    a[0] = (rand() % 100) / 200.0;
    a[1] = (rand() % 100) / 200.0;
    a[2] = (rand() % 100) / 200.0;

    b[0] = (rand() % 100) / 200.0;
    b[1] = (rand() % 100) / 200.0;
    b[2] = (rand() % 100) / 200.0;

    while (BH_BenchIter(state))
    {
        BH_Vec3fAdd(a, b, a);
    }
}


int main(int argc, char **argv)
{
    BH_UNUSED(argc);
    BH_UNUSED(argv);

    BH_BENCH_ADD(Vec3f);

    return BH_BenchRun();
}
