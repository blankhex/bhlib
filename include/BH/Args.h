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


/**
 * Parses command line \a options (given by \a argc and \a argv) and calls the
 * specified \a callback with \a data.
 *
 * There are few internal rules:
 * - If the "--" argument is specified, option parsing stops, and the rest of
 *   the arguments are processed as is.
 * - If the "-" argument is specified, it is processed as is.
 * - For long options, if a value is required, the string after the equal sign
 *   or the next argument will be used as the value ("--define=Value" or
 *   "--define Value").
 * - For short options, if a value is required, the string after the option
 *   letter or the next argument will be used as the value ("-DValue" or
 *   "-D Value").
 *
 * Options array should have last element filled with zeros.
 *
 * \param argc      Arguments count
 * \param argv      Arguments array
 * \param options   Options array pointer
 * \param callback  Callback function
 * \param data      Callback data
 *
 * \return On success, returns zero value.
 * \return On failure, returns error code.
 */
int BH_ArgsParse(int argc,
                 char **argv,
                 BH_ArgsOption *options,
                 BH_ArgsCallback callback,
                 void *data);


/**
 * Prints documentation for \a options (with specified \a padding).
 *
 * \param options  Options array pointer
 * \param padding  Padding
 */
void BH_ArgsHelp(BH_ArgsOption *options,
                 int padding);


#endif /* BH_ARGS_H */
