#ifndef BH_UNIT_H
#define BH_UNIT_H

#include <stdio.h>
#include <math.h>

typedef int (*BH_UnitCallback)(void);

#define BH_VERIFY(e) \
    do { \
        if (!(e)) { \
            printf("%s:%d\t%s\n", __FILE__, __LINE__, #e); \
            return -1; \
        } \
    } while(0)


#define BH_FAIL(msg) \
    do { \
        printf("%s:%d\t%s\n", __FILE__, __LINE__, msg); \
        return -1; \
    } while(0)


#define BH_VERIFY_DELTA(x, y, e) \
    do { \
        double BH_VERIFY_DELTA = (x)-(y); \
        if (BH_VERIFY_DELTA < 0.0) \
            BH_VERIFY_DELTA = -BH_VERIFY_DELTA; \
        if (BH_VERIFY_DELTA > (e)) { \
            printf("%s:%d\t%s (differs by %f)\n", \
                   __FILE__, __LINE__, #x " == " #y, BH_VERIFY_DELTA); \
            return -1; \
        } \
    } while(0)


#define BH_UNIT_TEST(name) \
    static int unit##name(void)


#define BH_UNIT_ADD(name) \
    BH_UnitAdd(#name, unit##name)


void BH_UnitAdd(const char *name,
                BH_UnitCallback cb);


int BH_UnitRun(void);


#endif /* BH_UNIT_H */
