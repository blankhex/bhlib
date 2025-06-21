#ifndef BH_ARGS_H
#define BH_ARGS_H


#include "Common.h"


#define BH_ARGS_ARGUMENT   0
#define BH_ARGS_UNKNOWN   -1

#define BH_ARGS_VALUE      1
#define BH_ARGS_OPTIONAL   2


typedef struct BH_ArgsOption
{
    int key;
    const char *name;
    int flags;
    const char *description;
} BH_ArgsOption;


typedef int (*BH_ArgsCallback)(int key, char *arg, void *data);


int BH_ArgsParse(int argc,
                 char **argv,
                 BH_ArgsOption *options,
                 BH_ArgsCallback callback,
                 void *data);


void BH_ArgsHelp(BH_ArgsOption *options,
                 int padding);


#endif /* BH_ARGS_H */
