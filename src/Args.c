#include <BH/Args.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <memory.h>


static int BH_ArgsExtractArg(int argc,
                             char **argv,
                             BH_ArgsOption *option,
                             BH_ArgsCallback callback,
                             void *data,
                             int *i,
                             int isLong,
                             char *next)
{
    if (isLong && *next == '=')
        return callback(option->key, next + 1, data);

    if (!isLong && *next)
        return callback(option->key, next, data);

    if ((*i) + 1 < argc && !(argv[(*i) + 1][0] == '-' && argv[(*i) + 1][1]))
        return callback(option->key, argv[++(*i)], data);

    if (option->flags & BH_ARGS_OPTIONAL)
        return callback(option->key, NULL, data);

    return BH_ERROR;
}


static int BH_ArgsParseShort(int argc,
                             char **argv,
                             BH_ArgsOption *options,
                             BH_ArgsCallback callback,
                             void *data,
                             int *i)
{
    char *symbol;
    BH_ArgsOption *option;

    for (symbol = argv[*i] + 1; *symbol; symbol++)
    {
        /* Find and process option */
        for (option = options; option->key || option->name; option++)
        {
            if (option->key > 128 || *symbol != option->key)
                continue;

            if (option->flags & BH_ARGS_VALUE)
                return BH_ArgsExtractArg(argc, argv, option, callback, data, i, 0, symbol + 1);

            if (callback(option->key, NULL, data))
                return BH_ERROR;

            break;
        }

        /* Unknown option */
        if (!option->key && !option->name)
        {
            callback(BH_ARGS_UNKNOWN, argv[*i], data);
            return BH_ERROR;
        }
    }

    return BH_OK;
}


static int BH_ArgsParseLong(int argc,
                            char **argv,
                            BH_ArgsOption *options,
                            BH_ArgsCallback callback,
                            void *data,
                            int *i)
{
    char *start, *end;
    BH_ArgsOption *option;

    /* Extract option name from argv */
    start = argv[*i] + 2;
    end = argv[*i] + 2;
    while (isgraph(*end) && *end != '=')
        end++;

    if (end == start)
        return BH_ERROR;

    /* Find and process option */
    for (option = options; option->key || option->name; option++)
    {
        if (!option->name || strlen(option->name) != (size_t)(end - start))
            continue;

        if (memcmp(option->name, start, end - start))
            continue;

        if (option->flags & BH_ARGS_VALUE)
            return BH_ArgsExtractArg(argc, argv, option, callback, data, i, 1, end);

        return callback(option->key, NULL, data);
    }

    /* Unknown long option */
    callback(BH_ARGS_UNKNOWN, argv[*i], data);
    return BH_ERROR;
}


int BH_ArgsParse(int argc,
                 char **argv,
                 BH_ArgsOption *options,
                 BH_ArgsCallback callback,
                 void *data)
{
    int i, j, ignoreRest, size;
    char *arg;

    ignoreRest = 0; i = 1; size = argc;
    while (i < argc)
    {
        arg = argv[i];

        if (arg[0] == '-' && arg[1] && !ignoreRest)
        {
            /* Parse ingore, short or long option */
            if (arg[1] == '-')
            {
                if (arg[2] && BH_ArgsParseLong(argc, argv, options, callback, data, &i))
                    return BH_ERROR;
                else if (!arg[2])
                    ignoreRest = 1;

            }
            else if (arg[1] && BH_ArgsParseShort(argc, argv, options, callback, data, &i))
                return BH_ERROR;

            i++;
        }
        else
        {
            /* Shift arguments */
            for (j = i; j < size - 1; j++)
                argv[j] = argv[j + 1];
            argv[size - 1] = arg;

            if (callback(BH_ARGS_ARGUMENT, arg, data))
                return BH_ERROR;

            argc--;
        }
    }
    return BH_OK;
}


void BH_ArgsHelp(BH_ArgsOption *options,
                 int padding)
{
    int width = 0;
    BH_ArgsOption *option;

    if (padding == 0)
        padding = 30;

    /* Calculate option column width */
    for (option = options; option->key || option->name; option++)
    {
        const char *symbol;
        width = 5;

        /* Print option column with padding */
        if (isgraph(option->key))
        {
            fputs(" -", stdout);
            fputc(option->key, stdout);
        }
        else
            fputs("   ", stdout);

        if (isgraph(option->key) && option->name)
            fputs(", ", stdout);
        else
            fputs("  ", stdout);

        if (option->name)
        {
            width += 3 + strlen(option->name);
            fputs("--", stdout);
            fputs(option->name, stdout);
            fputc(' ', stdout);
        }

        if (option->flags & BH_ARGS_VALUE)
        {
            width += 8;
            if (option->flags & BH_ARGS_OPTIONAL)
            {
                width += 2;
                fputs("[<value>] ", stdout);
            }
            else
                fputs("<value> ", stdout);
        }
        for (; width++ < padding; fputc(' ', stdout));

        /* Print description */
        for (symbol = option->description; symbol && *symbol; symbol++)
        {
            fputc(*symbol, stdout);

            if (*symbol == '\n')
                for (width = 0; width++ < padding; fputc(' ', stdout));
        }
        fputc('\n', stdout);
    }
}
