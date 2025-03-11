#include <BH/Args.h>
#include <BH/Unit.h>
#include <string.h>


typedef struct DBG_State
{
    int key[128];
    char *args[128];
    size_t size;
} DBG_State;


static int DBG_Process(int key,
                       char *arg,
                       void *data)
{
    DBG_State *state = (DBG_State *)data;

    state->key[state->size] = key;
    state->args[state->size] = arg;
    state->size++;

    return BH_OK;
}


static int DBG_AlwaysPass(int key,
                          char *arg,
                          void *data)
{
    BH_UNUSED(key);
    BH_UNUSED(arg);
    BH_UNUSED(data);

    return BH_OK;
}


static int DBG_AlwaysFail(int key,
                          char *arg,
                          void *data)
{
    BH_UNUSED(key);
    BH_UNUSED(arg);
    BH_UNUSED(data);

    return BH_ERROR;
}


BH_UNIT_TEST(Empty)
{
    int argc = 1;

    char *argv[] = {
        "./app"
    };

    BH_ArgsOption options[] = {
        {0, NULL, 0, NULL}
    };

    DBG_State state;
    memset(&state, 0, sizeof(state));

    BH_VERIFY(BH_ArgsParse(argc, argv, options, DBG_AlwaysFail, NULL) == BH_OK);
    BH_VERIFY(BH_ArgsParse(argc, argv, options, DBG_AlwaysPass, NULL) == BH_OK);
    BH_VERIFY(BH_ArgsParse(argc, argv, options, DBG_Process, &state) == BH_OK);
    BH_VERIFY(state.size == 0);
    BH_VERIFY(strcmp(argv[0], "./app") == 0);

    return 0;
}


BH_UNIT_TEST(Args)
{
    int argc = 4;

    char *argv[] = {
        "./app",
        "a",
        "b",
        "c"
    };

    BH_ArgsOption options[] = {
        {0, NULL, 0, NULL}
    };

    DBG_State state;
    memset(&state, 0, sizeof(state));

    BH_VERIFY(BH_ArgsParse(argc, argv, options, DBG_Process, &state) == BH_OK);
    BH_VERIFY(state.size == 3);
    BH_VERIFY(state.key[0] == 0 && strcmp(state.args[0], "a") == 0);
    BH_VERIFY(state.key[1] == 0 && strcmp(state.args[1], "b") == 0);
    BH_VERIFY(state.key[2] == 0 && strcmp(state.args[2], "c") == 0);

    BH_VERIFY(strcmp(argv[0], "./app") == 0);
    BH_VERIFY(strcmp(argv[1], "a") == 0);
    BH_VERIFY(strcmp(argv[2], "b") == 0);
    BH_VERIFY(strcmp(argv[3], "c") == 0);

    return 0;
}


BH_UNIT_TEST(Dash)
{
    int argc = 5;

    char *argv[] = {
        "./app",
        "a",
        "--",
        "-a",
        "--b"
    };

    BH_ArgsOption options[] = {
        {0, NULL, 0, NULL}
    };

    DBG_State state;
    memset(&state, 0, sizeof(state));

    BH_VERIFY(BH_ArgsParse(argc, argv, options, DBG_Process, &state) == BH_OK);

    BH_VERIFY(state.size == 3);
    BH_VERIFY(state.key[0] == 0 && strcmp(state.args[0], "a") == 0);
    BH_VERIFY(state.key[1] == 0 && strcmp(state.args[1], "-a") == 0);
    BH_VERIFY(state.key[2] == 0 && strcmp(state.args[2], "--b") == 0);

    BH_VERIFY(strcmp(argv[0], "./app") == 0);
    BH_VERIFY(strcmp(argv[1], "--") == 0);
    BH_VERIFY(strcmp(argv[2], "a") == 0);
    BH_VERIFY(strcmp(argv[3], "-a") == 0);
    BH_VERIFY(strcmp(argv[4], "--b") == 0);

    return 0;
}


BH_UNIT_TEST(ShortOption)
{
    int argc = 12;

    char *argv[] = {
        "./app",
        "a",
        "-2",
        "b",
        "c",
        "-2d",
        "e",
        "-2",
        "-",
        "f",
        "-113",
        "-1121",
    };

    BH_ArgsOption options[] = {
        {'1', NULL, 0, NULL},
        {'2', NULL, BH_ARGS_VALUE, NULL},
        {'3', NULL, BH_ARGS_VALUE | BH_ARGS_OPTIONAL, NULL},
        {0, NULL, 0, NULL},
    };

    DBG_State state;
    memset(&state, 0, sizeof(state));

    BH_VERIFY(BH_ArgsParse(argc, argv, options, DBG_Process, &state) == BH_OK);
    BH_VERIFY(state.size == 13);
    BH_VERIFY(state.key[0] == 0 && strcmp(state.args[0], "a") == 0);
    BH_VERIFY(state.key[1] == '2' && strcmp(state.args[1], "b") == 0);
    BH_VERIFY(state.key[2] == 0 && strcmp(state.args[2], "c") == 0);
    BH_VERIFY(state.key[3] == '2' && strcmp(state.args[3], "d") == 0);
    BH_VERIFY(state.key[4] == 0 && strcmp(state.args[4], "e") == 0);
    BH_VERIFY(state.key[5] == '2' && strcmp(state.args[5], "-") == 0);
    BH_VERIFY(state.key[6] == 0 && strcmp(state.args[6], "f") == 0);
    BH_VERIFY(state.key[7] == '1' && state.args[7] == NULL);
    BH_VERIFY(state.key[8] == '1' && state.args[8] == NULL);
    BH_VERIFY(state.key[9] == '3' && state.args[9] == NULL);
    BH_VERIFY(state.key[10] == '1' && state.args[10] == NULL);
    BH_VERIFY(state.key[11] == '1' && state.args[11] == NULL);
    BH_VERIFY(state.key[12] == '2' && strcmp(state.args[12], "1") == 0);

    BH_VERIFY(strcmp(argv[0], "./app") == 0);
    BH_VERIFY(strcmp(argv[1], "-2") == 0);
    BH_VERIFY(strcmp(argv[2], "b") == 0);
    BH_VERIFY(strcmp(argv[3], "-2d") == 0);
    BH_VERIFY(strcmp(argv[4], "-2") == 0);
    BH_VERIFY(strcmp(argv[5], "-") == 0);
    BH_VERIFY(strcmp(argv[6], "-113") == 0);
    BH_VERIFY(strcmp(argv[7], "-1121") == 0);
    BH_VERIFY(strcmp(argv[8], "a") == 0);
    BH_VERIFY(strcmp(argv[9], "c") == 0);
    BH_VERIFY(strcmp(argv[10], "e") == 0);
    BH_VERIFY(strcmp(argv[11], "f") == 0);

    return 0;
}


BH_UNIT_TEST(LongOptions)
{
    int argc = 12;

    char *argv[] = {
        "./app",
        "a",
        "--def",
        "b",
        "c",
        "--def=d",
        "e",
        "--def",
        "-",
        "f",
        "--ghj",
        "--abc",
    };

    BH_ArgsOption options[] = {
        {1000, "abc", 0, NULL},
        {1001, "def", BH_ARGS_VALUE, NULL},
        {1002, "ghj", BH_ARGS_VALUE | BH_ARGS_OPTIONAL, NULL},
        {0, NULL, 0, NULL},
    };

    DBG_State state;
    memset(&state, 0, sizeof(state));

    BH_VERIFY(BH_ArgsParse(argc, argv, options, DBG_Process, &state) == BH_OK);
    BH_VERIFY(state.size == 9);
    BH_VERIFY(state.key[0] == 0 && strcmp(state.args[0], "a") == 0);
    BH_VERIFY(state.key[1] == 1001 && strcmp(state.args[1], "b") == 0);
    BH_VERIFY(state.key[2] == 0 && strcmp(state.args[2], "c") == 0);
    BH_VERIFY(state.key[3] == 1001 && strcmp(state.args[3], "d") == 0);
    BH_VERIFY(state.key[4] == 0 && strcmp(state.args[4], "e") == 0);
    BH_VERIFY(state.key[5] == 1001 && strcmp(state.args[5], "-") == 0);
    BH_VERIFY(state.key[6] == 0 && strcmp(state.args[6], "f") == 0);
    BH_VERIFY(state.key[7] == 1002 && state.args[7] == NULL);
    BH_VERIFY(state.key[8] == 1000 && state.args[8] == NULL);

    BH_VERIFY(strcmp(argv[0], "./app") == 0);
    BH_VERIFY(strcmp(argv[1], "--def") == 0);
    BH_VERIFY(strcmp(argv[2], "b") == 0);
    BH_VERIFY(strcmp(argv[3], "--def=d") == 0);
    BH_VERIFY(strcmp(argv[4], "--def") == 0);
    BH_VERIFY(strcmp(argv[5], "-") == 0);
    BH_VERIFY(strcmp(argv[6], "--ghj") == 0);
    BH_VERIFY(strcmp(argv[7], "--abc") == 0);
    BH_VERIFY(strcmp(argv[8], "a") == 0);
    BH_VERIFY(strcmp(argv[9], "c") == 0);
    BH_VERIFY(strcmp(argv[10], "e") == 0);
    BH_VERIFY(strcmp(argv[11], "f") == 0);

    return 0;
}


BH_UNIT_TEST(Complex)
{
    int argc = 15;

    char *argv[] = {
        "./app",
        "a",
        "-i",
        "--input",
        "b",
        "-i-",
        "-i",
        "--input",
        "-",
        "--input",
        "--",
        "-a",
        "-i",
        "--input",
        "--invalid",
    };

    BH_ArgsOption options[] = {
        {'a', "abc", 0, NULL},
        {'i', "input", BH_ARGS_VALUE | BH_ARGS_OPTIONAL, NULL},
        {0, NULL, 0, NULL},
    };

    DBG_State state;
    memset(&state, 0, sizeof(state));

    BH_VERIFY(BH_ArgsParse(argc, argv, options, DBG_Process, &state) == BH_OK);

    BH_VERIFY(state.size == 11);
    BH_VERIFY(state.key[0] == 0 && strcmp(state.args[0], "a") == 0);
    BH_VERIFY(state.key[1] == 'i' && state.args[1] == NULL);
    BH_VERIFY(state.key[2] == 'i' && strcmp(state.args[2], "b") == 0);
    BH_VERIFY(state.key[3] == 'i' && strcmp(state.args[3], "-") == 0);
    BH_VERIFY(state.key[4] == 'i' && state.args[4] == NULL);
    BH_VERIFY(state.key[5] == 'i' && strcmp(state.args[5], "-") == 0);
    BH_VERIFY(state.key[6] == 'i' && state.args[6] == NULL);
    BH_VERIFY(state.key[7] == 0 && strcmp(state.args[7], "-a") == 0);
    BH_VERIFY(state.key[8] == 0 && strcmp(state.args[8], "-i") == 0);
    BH_VERIFY(state.key[9] == 0 && strcmp(state.args[9], "--input") == 0);
    BH_VERIFY(state.key[10] == 0 && strcmp(state.args[10], "--invalid") == 0);

    BH_VERIFY(strcmp(argv[0], "./app") == 0);
    BH_VERIFY(strcmp(argv[1], "-i") == 0);
    BH_VERIFY(strcmp(argv[2], "--input") == 0);
    BH_VERIFY(strcmp(argv[3], "b") == 0);
    BH_VERIFY(strcmp(argv[4], "-i-") == 0);
    BH_VERIFY(strcmp(argv[5], "-i") == 0);
    BH_VERIFY(strcmp(argv[6], "--input") == 0);
    BH_VERIFY(strcmp(argv[7], "-") == 0);
    BH_VERIFY(strcmp(argv[8], "--input") == 0);
    BH_VERIFY(strcmp(argv[9], "--") == 0);
    BH_VERIFY(strcmp(argv[10], "a") == 0);
    BH_VERIFY(strcmp(argv[11], "-a") == 0);
    BH_VERIFY(strcmp(argv[12], "-i") == 0);
    BH_VERIFY(strcmp(argv[13], "--input") == 0);
    BH_VERIFY(strcmp(argv[14], "--invalid") == 0);

    return 0;
}


BH_UNIT_TEST(InvalidShort)
{
    int argc = 4;

    char *argv[] = {
        "./app",
        "a",
        "-b",
        "-c"
    };

    BH_ArgsOption options[] = {
        {0, NULL, 0, NULL}
    };

    DBG_State state;
    memset(&state, 0, sizeof(state));

    BH_VERIFY(BH_ArgsParse(argc, argv, options, DBG_Process, &state) != BH_OK);

    BH_VERIFY(state.size == 2);
    BH_VERIFY(state.key[0] == 0 && strcmp(state.args[0], "a") == 0);
    BH_VERIFY(state.key[1] == BH_ARGS_UNKNOWN && strcmp(state.args[1], "-b") == 0);

    return 0;
}


BH_UNIT_TEST(InvalidLong)
{
    int argc = 4;

    char *argv[] = {
        "./app",
        "a",
        "--b",
        "--c"
    };

    BH_ArgsOption options[] = {
        {0, NULL, 0, NULL}
    };

    DBG_State state;
    memset(&state, 0, sizeof(state));

    BH_VERIFY(BH_ArgsParse(argc, argv, options, DBG_Process, &state) != BH_OK);

    BH_VERIFY(state.size == 2);
    BH_VERIFY(state.key[0] == 0 && strcmp(state.args[0], "a") == 0);
    BH_VERIFY(state.key[1] == BH_ARGS_UNKNOWN && strcmp(state.args[1], "--b") == 0);

    return 0;
}


BH_UNIT_TEST(Aesthetics)
{
    BH_ArgsOption options[] = {
        {'a', "abc", 0, NULL},
        {'b', "bcd", BH_ARGS_VALUE, "B option"},
        {'i', "input", BH_ARGS_VALUE | BH_ARGS_OPTIONAL, "Input option"},
        {1000, "long-option", 0, "Long options\nWith newline"},
        {'p', NULL, 0, "P option"},
        {0, NULL, 0, NULL},
    };

    BH_ArgsHelp(options, 0);
    return 0;
}


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    BH_UNIT_ADD(Empty);
    BH_UNIT_ADD(Args);
    BH_UNIT_ADD(Dash);
    BH_UNIT_ADD(ShortOption);
    BH_UNIT_ADD(LongOptions);
    BH_UNIT_ADD(Complex);
    BH_UNIT_ADD(InvalidShort);
    BH_UNIT_ADD(InvalidLong);
    BH_UNIT_ADD(Aesthetics);

    return BH_UnitRun();
}
