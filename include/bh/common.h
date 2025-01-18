#ifndef BH_COMMON_H
#define BH_COMMON_H

#include <stddef.h>
#include <stdint.h>

#define BH_OK           0x0000
#define BH_ERROR        0x0001
#define BH_NOIMPL       0x0002
#define BH_OOM          0x0003
#define BH_INVALID      0x0004
#define BH_FOUND        0x0005
#define BH_NOTFOUND     0x0006
#define BH_TIMEOUT      0x0007

#define BH_UNUSED(x)    (void)(x)
#define BH_PTR2INT(x)   ((intptr_t)(x))
#define BH_INT2PTR(x)   ((void*)(x))

typedef int (*bh_equal_cb_t)(const void *, const void *);
typedef size_t (*bh_hash_cb_t)(const void *);

#endif /* BH_COMMON_H */

