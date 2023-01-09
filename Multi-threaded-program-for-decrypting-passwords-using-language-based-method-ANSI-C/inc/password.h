#pragma once

#include "global_memory.h"

#define QUANTITY_PASSWORD 1000

typedef struct
{
  char email[QUANTITY_PASSWORD][50];
  char encrypted_password[QUANTITY_PASSWORD][33];
  char deciphered_password[QUANTITY_PASSWORD][200];
  DynamicArrayINT index_of_deciphered_pswd;
  unsigned int quantity_password_in_file;
} PASSWORD;

PASSWORD pswd1;

int read_encrypted_password(const char *name_of_password_file);
void bytes2md5(const char *data, int len, char *md5buf);
bool this_password_is_deciphered(int index);
void hash_and_find_password(const char *tab1);
void init_passwords(PASSWORD *pswd_temp);