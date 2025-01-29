#ifndef BH_UNIT_H
#define BH_UNIT_H

#include <stdio.h>
#include <math.h>

typedef int (*bh_unit_cb_t)(void);

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
            printf("%s:%d\t%s (differs by %f)\n", __FILE__, __LINE__, #x " == " #y, BH_VERIFY_DELTA); \
            return -1; \
        } \
    } while(0)


void bh_unit_add(const char *name, bh_unit_cb_t func);
int bh_unit_run(void);

#endif /* BH_UNIT_H */
