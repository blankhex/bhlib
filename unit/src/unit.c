#include <bh/unit.h>
#include <stdlib.h>

typedef struct bh_unit_s
{
    struct bh_unit_s *next;
    const char *name;
    bh_unit_cb_t func;
} bh_unit_t;

static bh_unit_t *root = NULL;

void bh_unit_add(const char *name, bh_unit_cb_t func)
{
    bh_unit_t *unit, *current;

    unit = malloc(sizeof(*unit));
    if (!unit)
        return;

    unit->name = name;
    unit->func = func;
    unit->next = NULL;

    current = root;
    while (current && current->next)
        current = current->next;

    if (current)
        current->next = unit;
    else
        root = unit;
}

int bh_unit_run(void)
{
    bh_unit_t *current;
    printf("Running tests...\n");

    current = root;
    while (current)
    {
        printf("%s\n", current->name);
        if (current->func())
        {
            printf("\tFAIL\n");
            return -1;
        }
        printf("\tPASS\n");
        fflush(stdout);
        current = current->next;
    }

    return 0;
}

