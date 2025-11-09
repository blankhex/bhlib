#include <BH/Unit.h>
#include <BH/String.h>


BH_UNIT_TEST(EqualStrings)
{
    BH_VERIFY(BH_StringCompare("hello", "hello") == 0);
    BH_VERIFY(BH_StringCompare("", "") == 0);
    BH_VERIFY(BH_StringCompare("a", "a") == 0);
    BH_VERIFY(BH_StringCompare("123", "123") == 0);

    return 0;
}


BH_UNIT_TEST(LessThan)
{
    BH_VERIFY(BH_StringCompare("apple", "banana") < 0);
    BH_VERIFY(BH_StringCompare("aa", "ab") < 0);
    BH_VERIFY(BH_StringCompare("a", "b") < 0);
    BH_VERIFY(BH_StringCompare("", "a") < 0);

    return 0;
}


BH_UNIT_TEST(GreaterThan)
{
    BH_VERIFY(BH_StringCompare("zebra", "apple") > 0);
    BH_VERIFY(BH_StringCompare("ab", "aa") > 0);
    BH_VERIFY(BH_StringCompare("b", "a") > 0);
    BH_VERIFY(BH_StringCompare("a", "") > 0);

    return 0;
}


BH_UNIT_TEST(CaselessEqual)
{
    BH_VERIFY(BH_StringCompareCaseless("hello", "HELLO") == 0);
    BH_VERIFY(BH_StringCompareCaseless("Hello", "hELLO") == 0);
    BH_VERIFY(BH_StringCompareCaseless("TEST", "test") == 0);
    BH_VERIFY(BH_StringCompareCaseless("", "") == 0);
    BH_VERIFY(BH_StringCompareCaseless("MiXeD", "mIxEd") == 0);

    return 0;
}


BH_UNIT_TEST(CaselessLessThan)
{
    BH_VERIFY(BH_StringCompareCaseless("apple", "BANANA") < 0);
    BH_VERIFY(BH_StringCompareCaseless("alpha", "Beta") < 0);
    BH_VERIFY(BH_StringCompareCaseless("a", "Z") < 0);

    return 0;
}


BH_UNIT_TEST(CaselessGreaterThan)
{
    BH_VERIFY(BH_StringCompareCaseless("zebra", "APPLE") > 0);
    BH_VERIFY(BH_StringCompareCaseless("Zulu", "alpha") > 0);
    BH_VERIFY(BH_StringCompareCaseless("Z", "a") > 0);

    return 0;
}


BH_UNIT_TEST(EdgeCases)
{
    BH_VERIFY(BH_StringCompare(
        "this is a very long string for testing purposes",
        "this is a very long string for testing purposes") == 0);

    BH_VERIFY(BH_StringCompare("abc123", "abc124") < 0);

    BH_VERIFY(BH_StringCompare("test", "testing") < 0);
    BH_VERIFY(BH_StringCompare("testing", "test") > 0);

    return 0;
}


BH_UNIT_TEST(CaselessEdgeCases)
{
    BH_VERIFY(BH_StringCompareCaseless("TEST", "TESTING") < 0);
    BH_VERIFY(BH_StringCompareCaseless("TESTING", "test") > 0);

    BH_VERIFY(BH_StringCompareCaseless("file1.txt", "file10.txt") < 0);
    BH_VERIFY(BH_StringCompareCaseless("AaAa", "AAAA") == 0);

    return 0;
}


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    BH_UNIT_ADD(EqualStrings);
    BH_UNIT_ADD(LessThan);
    BH_UNIT_ADD(GreaterThan);
    BH_UNIT_ADD(EdgeCases);
    BH_UNIT_ADD(CaselessEqual);
    BH_UNIT_ADD(CaselessLessThan);
    BH_UNIT_ADD(CaselessGreaterThan);
    BH_UNIT_ADD(CaselessEdgeCases);

    return BH_UnitRun();
}
