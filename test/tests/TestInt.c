#include <BH/String.h>
#include <BH/Unit.h>


BH_UNIT_TEST(Int8)
{
    char str[9];
    size_t size;

    BH_VERIFY(BH_StringFromInt8s(str, 9, -13, 16, NULL) == BH_OK);
    BH_VERIFY(BH_StringToInt8s(str, 16, &size) == -13);
    BH_VERIFY(size == 2);

    BH_VERIFY(BH_StringFromInt8s(str, 9, -13, 10, NULL) == BH_OK);
    BH_VERIFY(BH_StringToInt8s(str, 10, &size) == -13);
    BH_VERIFY(size == 3);

    BH_VERIFY(BH_StringFromInt8s(str, 9, -13, 8, NULL) == BH_OK);
    BH_VERIFY(BH_StringToInt8s(str, 8, &size) == -13);
    BH_VERIFY(size == 3);

    BH_VERIFY(BH_StringFromInt8s(str, 9, -13, 2, NULL) == BH_OK);
    BH_VERIFY(BH_StringToInt8s(str, 2, &size) == -13);
    BH_VERIFY(size == 5);

    BH_VERIFY(BH_StringFromInt8u(str, 9, 200, 16, NULL) == BH_OK);
    BH_VERIFY(BH_StringToInt8u(str, 16, &size) == 200);
    BH_VERIFY(size == 2);

    BH_VERIFY(BH_StringFromInt8u(str, 9, 200, 10, NULL) == BH_OK);
    BH_VERIFY(BH_StringToInt8u(str, 10, &size) == 200);
    BH_VERIFY(size == 3);

    BH_VERIFY(BH_StringFromInt8u(str, 9, 200, 8, NULL) == BH_OK);
    BH_VERIFY(BH_StringToInt8u(str, 8, &size) == 200);
    BH_VERIFY(size == 3);

    BH_VERIFY(BH_StringFromInt8u(str, 9, 200, 2, NULL) == BH_OK);
    BH_VERIFY(BH_StringToInt8u(str, 2, &size) == 200);
    BH_VERIFY(size == 8);

    return 0;
}


BH_UNIT_TEST(Int16)
{
    char str[17];
    size_t size;

    BH_VERIFY(BH_StringFromInt16s(str, 17, -1234, 16, NULL) == BH_OK);
    BH_VERIFY(BH_StringToInt16s(str, 16, &size) == -1234);
    BH_VERIFY(size == 4);

    BH_VERIFY(BH_StringFromInt16s(str, 17, -1234, 10, NULL) == BH_OK);
    BH_VERIFY(BH_StringToInt16s(str, 10, &size) == -1234);
    BH_VERIFY(size == 5);

    BH_VERIFY(BH_StringFromInt16s(str, 17, -1234, 8, NULL) == BH_OK);
    BH_VERIFY(BH_StringToInt16s(str, 8, &size) == -1234);
    BH_VERIFY(size == 5);

    BH_VERIFY(BH_StringFromInt16s(str, 17, -1234, 2, NULL) == BH_OK);
    BH_VERIFY(BH_StringToInt16s(str, 2, &size) == -1234);
    BH_VERIFY(size == 12);

    BH_VERIFY(BH_StringFromInt16u(str, 17, 43210, 16, NULL) == BH_OK);
    BH_VERIFY(BH_StringToInt16u(str, 16, &size) == 43210);
    BH_VERIFY(size == 4);

    BH_VERIFY(BH_StringFromInt16u(str, 17, 43210, 10, NULL) == BH_OK);
    BH_VERIFY(BH_StringToInt16u(str, 10, &size) == 43210);
    BH_VERIFY(size == 5);

    BH_VERIFY(BH_StringFromInt16u(str, 17, 43210, 8, NULL) == BH_OK);
    BH_VERIFY(BH_StringToInt16u(str, 8, &size) == 43210);
    BH_VERIFY(size == 6);

    BH_VERIFY(BH_StringFromInt16u(str, 17, 43210, 2, NULL) == BH_OK);
    BH_VERIFY(BH_StringToInt16u(str, 2, &size) == 43210);
    BH_VERIFY(size == 16);

    return 0;
}


BH_UNIT_TEST(Int32)
{
    char str[33];
    size_t size;

    BH_VERIFY(BH_StringFromInt32s(str, 33, -1234567890l, 16, NULL) == BH_OK);
    BH_VERIFY(BH_StringToInt32s(str, 16, &size) == -1234567890l);
    BH_VERIFY(size == 9);

    BH_VERIFY(BH_StringFromInt32s(str, 33, -1234567890l, 10, NULL) == BH_OK);
    BH_VERIFY(BH_StringToInt32s(str, 10, &size) == -1234567890l);
    BH_VERIFY(size == 11);

    BH_VERIFY(BH_StringFromInt32s(str, 33, -1234567890l, 8, NULL) == BH_OK);
    BH_VERIFY(BH_StringToInt32s(str, 8, &size) == -1234567890l);
    BH_VERIFY(size == 12);

    BH_VERIFY(BH_StringFromInt32s(str, 33, -1234567890l, 2, NULL) == BH_OK);
    BH_VERIFY(BH_StringToInt32s(str, 2, &size) == -1234567890l);
    BH_VERIFY(size == 32);

    BH_VERIFY(BH_StringFromInt32u(str, 33, 3456789012ul, 16, NULL) == BH_OK);
    BH_VERIFY(BH_StringToInt32u(str, 16, &size) == 3456789012ul);
    BH_VERIFY(size == 8);

    BH_VERIFY(BH_StringFromInt32u(str, 33, 3456789012ul, 10, NULL) == BH_OK);
    BH_VERIFY(BH_StringToInt32u(str, 10, &size) == 3456789012ul);
    BH_VERIFY(size == 10);

    BH_VERIFY(BH_StringFromInt32u(str, 33, 3456789012ul, 8, NULL) == BH_OK);
    BH_VERIFY(BH_StringToInt32u(str, 8, &size) == 3456789012ul);
    BH_VERIFY(size == 11);

    BH_VERIFY(BH_StringFromInt32u(str, 33, 3456789012ul, 2, NULL) == BH_OK);
    BH_VERIFY(BH_StringToInt32u(str, 2, &size) == 3456789012ul);
    BH_VERIFY(size == 32);

    return 0;
}


BH_UNIT_TEST(Parsing)
{
    size_t size;

    BH_VERIFY(BH_StringToInt32s("   0x1234", 16, &size) == 0x1234);
    BH_VERIFY(size == 9);

    BH_VERIFY(BH_StringToInt32s("   12345", 10, &size) == 12345);
    BH_VERIFY(size == 8);

    BH_VERIFY(BH_StringToInt32s("   0123", 8, &size) == 0123);
    BH_VERIFY(size == 7);

    BH_VERIFY(BH_StringToInt32s("   0b1111Hello", 2, &size) == 15);
    BH_VERIFY(size == 9);

    BH_VERIFY(BH_StringToInt32s("   0x1234", 0, &size) == 0x1234);
    BH_VERIFY(size == 9);

    BH_VERIFY(BH_StringToInt32s("   0123", 0, &size) == 0123);
    BH_VERIFY(size == 7);

    BH_VERIFY(BH_StringToInt32s("   123", 0, &size) == 123);
    BH_VERIFY(size == 6);

    BH_VERIFY(BH_StringToInt32s("   0b1111", 0, &size) == 15);
    BH_VERIFY(size == 9);

    BH_VERIFY(BH_StringToInt32s("   12345Hello", 10, &size) == 12345);
    BH_VERIFY(size == 8);

    BH_VERIFY(BH_StringToInt32s("   Hello", 10, &size) == 0);
    BH_VERIFY(size == 0);

    return 0;
}


int main(int argc, char **argv)
{
    BH_UNUSED(argc);
    BH_UNUSED(argv);

    BH_UNIT_ADD(Int8);
    BH_UNIT_ADD(Int16);
    BH_UNIT_ADD(Int32);
    BH_UNIT_ADD(Parsing);

    return BH_UnitRun();
}
