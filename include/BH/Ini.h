#ifndef BH_INI_H
#define BH_INI_H

#include "IO.h"


typedef struct BH_Ini BH_Ini;

BH_Ini *BH_IniNew(void);


void BH_IniFree(BH_Ini *ini);


int BH_IniLoad(BH_Ini *ini,
               BH_IO *io);


int BH_IniSave(BH_Ini *ini,
               BH_IO *io);


int BH_IniSetString(BH_Ini *ini,
                    const char *section,
                    const char *key,
                    const char *value);


const char *BH_IniString(BH_Ini *ini,
                         const char *section,
                         const char *key);


void BH_IniRemoveSection(BH_Ini *ini,
                         const char *section);


void BH_IniRemoveKey(BH_Ini *ini,
                     const char *section,
                     const char *key);


void *BH_IniSectionIterNext(BH_Ini *ini,
                            void *iter);


void *BH_IniSectionIterAt(BH_Ini *ini,
                          const char *section);


const char *BH_IniSectionIterName(void *iter);


void BH_IniSectionIterRemove(BH_Ini *ini,
                             void *iter);


void *BH_IniKVIterNext(void *section,
                       void *iter);


void *BH_IniKVIterAt(void *section,
                     const char *key);


const char *BH_IniKVIterKey(void *iter);


const char *BH_IniKVIterValue(void *iter);


void BH_IniKVIterRemove(void *section,
                        void *iter);


#endif /* BH_INI_H */
