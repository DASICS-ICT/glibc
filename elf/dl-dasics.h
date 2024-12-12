#ifndef __INCLUDE_DASICS_H
#define __INCLUDE_DASICS_H

#define NO_DASICS                   0   // No DASICS config 
#define DASICS_MAPP_TRUSTED         1   // Trusted library in trusted
#define DASICS_MAP_UNTRUSTED_COPY   2   // Trusted library copy in untrusted
#define DASICS_MAP_ALL_UNTRUSTED    3   // All library in untrusted
#define DASICS_MAP_TRUSTED_COPY     4   // Trusted library in untrusted area will be copyed to trusted area

extern unsigned long dasics_flag;
extern unsigned trusted_base;
extern char *trust_lib[];
#include <stdlib.h>
#include <sys/cdefs.h>
static __always_inline char * get_real_name(char * name)
{
    char * local_name = NULL;
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (name[i] == '/')
            local_name = &name[i + 1];       
    }
    if (local_name == NULL)
        local_name = name;    
    return local_name;
}

static __always_inline int is_trust_lib(char * name)
{
  for (int i = 0; trust_lib[i] != NULL; i++)
  {
    if (!strcmp(name, trust_lib[i])) return 1;
  } 
  return 0;
}


#endif