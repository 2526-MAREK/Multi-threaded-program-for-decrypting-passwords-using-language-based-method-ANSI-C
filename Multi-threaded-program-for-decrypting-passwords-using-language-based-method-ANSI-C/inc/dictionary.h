#pragma once

#include "global_memory.h"
#include "password.h"

typedef struct
{
  size_t lines_count;
  char **lines;
} DICTIONARY;

DICTIONARY dic1;

int read_dictionary();
void development_dictionary_and_find_password(char *orginal_word_from_producent);
void init_dictionary(DICTIONARY *dic_temp);
