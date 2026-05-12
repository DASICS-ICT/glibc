#ifndef __INCLUDE_DASICS_H
#define __INCLUDE_DASICS_H
#include <stdlib.h>
#include <string.h>
#include <sys/cdefs.h>
#include <link.h>
#define NO_DASICS                   0   // No DASICS config 
#define DASICS_MAP_TRUSTED          1   // Trusted library in trusted
#define DASICS_MAP_UNTRUSTED_COPY   2   // Trusted library copy in untrusted
#define DASICS_MAP_ALL_UNTRUSTED    3   // All library in untrusted
#define DASICS_MAP_TRUSTED_COPY     4   // Trusted library in untrusted area will be copyed to trusted area

#define DASICS_NOTE_NAME "DASICS"
#define NT_DASICS_UNTRUSTED_LIBRARY 0xDA51C501U
#define DASICS_MAX_UNTRUSTED_LIBS 64
#define DASICS_MAX_LIBRARY_NAME 256

extern unsigned long dasics_flag;
extern unsigned long trust_base;
extern char dasics_untrusted_libs[DASICS_MAX_UNTRUSTED_LIBS][DASICS_MAX_LIBRARY_NAME];
extern unsigned int dasics_untrusted_lib_count;

// main elf
extern struct link_map* dasics_main_elf;

int dasics_register_untrusted_lib(const char *name, size_t len);
void dasics_parse_untrusted_library_notes(struct link_map *main_map);

static __always_inline const char * get_real_name(const char * name)
{
    const char * local_name = NULL;
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (name[i] == '/')
            local_name = &name[i + 1];       
    }
    if (local_name == NULL)
        local_name = name;    
    return local_name;
}

static __always_inline int is_untrusted_lib(const char * name)
{
  for (unsigned int i = 0; i < dasics_untrusted_lib_count; i++)
  {
    if (!strcmp(name, dasics_untrusted_libs[i])) return 1;
  } 
  return 0;
}

static __always_inline int is_trust_lib(const char * name)
{
  return !is_untrusted_lib(name);
}

#endif