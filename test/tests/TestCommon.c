#include <BH/Unit.h>
#include <BH/Common.h>


BH_UNIT_TEST(UADD)
{
    BH_VERIFY(!BH_CHECK_UADD_WRAP(100, 100, uint8_t));
    BH_VERIFY(!BH_CHECK_UADD_WRAP(0, 0, uint8_t));
    BH_VERIFY(BH_CHECK_UADD_WRAP(200, 100, uint8_t));
    BH_VERIFY(BH_CHECK_UADD_WRAP(100, 200, uint8_t));
    BH_VERIFY(BH_CHECK_UADD_WRAP(255, 1, uint8_t));
    BH_VERIFY(BH_CHECK_UADD_WRAP(1, 255, uint8_t));

    return 0;
}


BH_UNIT_TEST(USUB)
{
    BH_VERIFY(!BH_CHECK_USUB_WRAP(100, 100, uint8_t));
    BH_VERIFY(!BH_CHECK_USUB_WRAP(0, 0, uint8_t));
    BH_VERIFY(!BH_CHECK_USUB_WRAP(200, 100, uint8_t));
    BH_VERIFY(BH_CHECK_USUB_WRAP(100, 200, uint8_t));
    BH_VERIFY(!BH_CHECK_USUB_WRAP(255, 1, uint8_t));
    BH_VERIFY(BH_CHECK_USUB_WRAP(1, 255, uint8_t));

    return 0;
}


BH_UNIT_TEST(UMUL)
{
    BH_VERIFY(!BH_CHECK_UMUL_WRAP(0, 2, uint8_t));
    BH_VERIFY(!BH_CHECK_UMUL_WRAP(100, 2, uint8_t));
    BH_VERIFY(BH_CHECK_UMUL_WRAP(200, 100, uint8_t));
    BH_VERIFY(BH_CHECK_UMUL_WRAP(100, 200, uint8_t));
    BH_VERIFY(!BH_CHECK_UMUL_WRAP(255, 1, uint8_t));
    BH_VERIFY(!BH_CHECK_UMUL_WRAP(1, 255, uint8_t));

    return 0;
}


int main(int argc, char **argv)
{
    BH_UNUSED(argc);
    BH_UNUSED(argv);

    BH_UNIT_ADD(UADD);
    BH_UNIT_ADD(USUB);
    BH_UNIT_ADD(UMUL);

    return BH_UnitRun();
}
