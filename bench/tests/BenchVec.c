#include <BH/Bench.h>

#include <BH/Math/Vec2i.h>
#include <BH/Math/Vec3i.h>
#include <BH/Math/Vec4i.h>
#include <BH/Math/Vec2f.h>
#include <BH/Math/Vec3f.h>
#include <BH/Math/Vec4f.h>
#include <stdlib.h>


BH_BENCH_TEST(Vec2i)
{
    int a[2], b[2];

    a[0] = (rand() % 100);
    a[1] = (rand() % 100);

    b[0] = (rand() % 100);
    b[1] = (rand() % 100);

    while (BH_BenchIter(state))
    {
        BH_Vec2iAdd(a, b, a);
    }
}


BH_BENCH_TEST(Vec3i)
{
    int a[3], b[3];

    a[0] = (rand() % 100);
    a[1] = (rand() % 100);
    a[2] = (rand() % 100);

    b[0] = (rand() % 100);
    b[1] = (rand() % 100);
    b[2] = (rand() % 100);

    while (BH_BenchIter(state))
    {
        BH_Vec3iAdd(a, b, a);
    }
}


BH_BENCH_TEST(Vec4i)
{
    int a[4], b[4];

    a[0] = (rand() % 100);
    a[1] = (rand() % 100);
    a[2] = (rand() % 100);
    a[3] = (rand() % 100);

    b[0] = (rand() % 100);
    b[1] = (rand() % 100);
    b[2] = (rand() % 100);
    b[3] = (rand() % 100);

    while (BH_BenchIter(state))
    {
        BH_Vec4iAdd(a, b, a);
    }
}


BH_BENCH_TEST(Vec2f)
{
    float a[2], b[2];

    a[0] = (rand() % 100) / 200.0;
    a[1] = (rand() % 100) / 200.0;

    b[0] = (rand() % 100) / 200.0;
    b[1] = (rand() % 100) / 200.0;

    while (BH_BenchIter(state))
    {
        BH_Vec2fAdd(a, b, a);
    }
}


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


BH_BENCH_TEST(Vec4f)
{
    float a[4], b[4];

    a[0] = (rand() % 100) / 200.0;
    a[1] = (rand() % 100) / 200.0;
    a[2] = (rand() % 100) / 200.0;
    a[3] = (rand() % 100) / 200.0;

    b[0] = (rand() % 100) / 200.0;
    b[1] = (rand() % 100) / 200.0;
    b[2] = (rand() % 100) / 200.0;
    b[3] = (rand() % 100) / 200.0;

    while (BH_BenchIter(state))
    {
        BH_Vec4fAdd(a, b, a);
    }
}


int main(int argc, char **argv)
{
    BH_UNUSED(argc);
    BH_UNUSED(argv);

    BH_BENCH_ADD(Vec2i);
    BH_BENCH_ADD(Vec3i);
    BH_BENCH_ADD(Vec4i);
    BH_BENCH_ADD(Vec2f);
    BH_BENCH_ADD(Vec3f);
    BH_BENCH_ADD(Vec4f);

    return BH_BenchRun();
}
