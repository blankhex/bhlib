#ifndef BH_UNIT_H
#define BH_UNIT_H

#include <stdio.h>

typedef int (*bh_unit_cb_t)(void);

#define BH_VERIFY(e) \
    do { if (!(e)) { \
        printf("%s:%d\t%s\n", __FILE__, __LINE__, #e); \
        return -1; \
    } } while(0)


#define BH_FAIL(msg) \
    do { printf("%s:%d\t%s\n", __FILE__, __LINE__, msg); \
    return -1; } while(0)


#define BH_VERIFY_DELTA(x, y, e) \
    do { if ((((x)>(y))?((x)-(y)):((y)-(x)))>(e)) { \
        printf("%s:%d\t%s\n", __FILE__, __LINE__, #x " == " #y); \
        return -1; \
    } while (0)

void bh_unit_add(const char *name, bh_unit_cb_t func);
int bh_unit_run(void);

#endif /* BH_UNIT_H */
