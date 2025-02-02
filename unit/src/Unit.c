#include <BH/Unit.h>
#include <stdlib.h>

typedef struct BH_Unit
{
    struct BH_Unit *next;
    const char *name;
    BH_UnitCallback cb;
} BH_Unit;


static BH_Unit *root = NULL;


void BH_UnitAdd(const char *name, BH_UnitCallback cb)
{
    BH_Unit *unit, *current;

    /* Allocate and fill new unit test entry */
    unit = malloc(sizeof(*unit));
    if (!unit)
        return;

    unit->next = NULL;
    unit->name = name;
    unit->cb = cb;

    /* Append unit test entry */
    current = root;
    while (current && current->next)
        current = current->next;

    if (current)
        current->next = unit;
    else
        root = unit;
}


int BH_UnitRun(void)
{
    BH_Unit *current;
    printf("Running tests...\n");

    current = root;
    while (current)
    {
        printf("%s\n", current->name);
        if (current->cb())
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

