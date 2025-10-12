#include <BH/Util.h>
#include <BH/Unit.h>


BH_UNIT_TEST(Int16)
{
    char buffer[2];

    BH_Write16LEs(buffer, -12345);
    BH_VERIFY(BH_Read16LEs(buffer) == -12345);
    BH_Write16BEs(buffer, BH_Read16BEs(buffer));
    BH_VERIFY(BH_Read16LEs(buffer) == -12345);

    BH_Write16LEu(buffer, 12345);
    BH_VERIFY(BH_Read16LEu(buffer) == 12345);
    BH_Write16BEu(buffer, BH_Read16BEu(buffer));
    BH_VERIFY(BH_Read16LEu(buffer) == 12345);

    return 0;
}


BH_UNIT_TEST(Int32)
{
    char buffer[4];

    BH_Write32LEs(buffer, -12345);
    BH_VERIFY(BH_Read32LEs(buffer) == -12345);
    BH_Write32BEs(buffer, BH_Read32BEs(buffer));
    BH_VERIFY(BH_Read32LEs(buffer) == -12345);

    BH_Write32LEu(buffer, 12345);
    BH_VERIFY(BH_Read32LEu(buffer) == 12345);
    BH_Write32BEu(buffer, BH_Read32BEu(buffer));
    BH_VERIFY(BH_Read32LEu(buffer) == 12345);

    return 0;
}


BH_UNIT_TEST(Int64)
{
    char buffer[8];

    BH_Write64LEs(buffer, -12345);
    BH_VERIFY(BH_Read64LEs(buffer) == -12345);
    BH_Write64BEs(buffer, BH_Read64BEs(buffer));
    BH_VERIFY(BH_Read64LEs(buffer) == -12345);

    BH_Write64LEu(buffer, 12345);
    BH_VERIFY(BH_Read64LEu(buffer) == 12345);
    BH_Write64BEu(buffer, BH_Read64BEu(buffer));
    BH_VERIFY(BH_Read64LEu(buffer) == 12345);

    return 0;
}


int main(int argc, char **argv)
{
    BH_UNUSED(argc);
    BH_UNUSED(argv);

    BH_UNIT_ADD(Int16);
    BH_UNIT_ADD(Int32);
    BH_UNIT_ADD(Int64);

    return BH_UnitRun();
}
