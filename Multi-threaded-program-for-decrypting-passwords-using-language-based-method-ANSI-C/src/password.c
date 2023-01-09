#include "password.h"

int read_encrypted_password(const char *name_of_password_file)
{
  // Otwieranie pliku do odczytu
  FILE *fptr = fopen(name_of_password_file, "r");
  if (fptr == NULL) // Sprawdzenie, czy plik odczytu został pomyślnie otwarty
  {
    perror("Nie można otworzyć pliku");
    return 1;
  }

  int counter = 0;
  char *temp_line_in = NULL;
  size_t len = 200;
  char *temp;
  while (getline(&temp_line_in, &len, fptr) != -1)
  {
    ++pswd1.quantity_password_in_file;
    temp = strtok(temp_line_in, " ");
    temp = strtok(NULL, " ");
    temp = remove_tabulation_from_str(temp);
    sprintf(pswd1.encrypted_password[counter], "%s", temp);
    temp = strtok(NULL, " ");
    temp = remove_tabulation_from_str(temp);
    sprintf(pswd1.email[counter], "%s", temp);
    counter++;
  }

  fclose(fptr);

  return 0;
}

void bytes2md5(const char *data, int len, char *md5buf)
{
  EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
  const EVP_MD *md = EVP_md5();
  unsigned char md_value[EVP_MAX_MD_SIZE];
  unsigned int md_len, i;
  EVP_DigestInit_ex(mdctx, md, NULL);
  EVP_DigestUpdate(mdctx, data, len);
  EVP_DigestFinal_ex(mdctx, md_value, &md_len);
  EVP_MD_CTX_free(mdctx);
  for (i = 0; i < md_len; i++)
  {
    snprintf(&(md5buf[i * 2]), 16 * 2, "%02x", md_value[i]);
  }
}

bool this_password_is_deciphered(int index)
{
  bool key = false;
  for (size_t i = 0; i < pswd1.index_of_deciphered_pswd.size; ++i)
  {
    if (index == pswd1.index_of_deciphered_pswd.array[i])
    {
      key = true;

      return key;
    }
  }
  return key;
}

void hash_and_find_password(const char *tab1)
{
  char hash[33];
  int index_of_deciphered_pswd_temp = -1;
  bool key = false;
  bytes2md5(tab1, strlen(tab1), hash);

  for (int i = 0; i < pswd1.quantity_password_in_file; ++i)
  {
    pthread_testcancel();
    pthread_mutex_lock(&pswd_mutex);
    
    if (!this_password_is_deciphered(i))
    {
      if (strcmp((const char *)(hash), pswd1.encrypted_password[i]) == 0)
      {
        index_of_deciphered_pswd_temp = i;
        key = true;
      }
      else
      {
        index_of_deciphered_pswd_temp - 1;
        key = false;
      }
      if (index_of_deciphered_pswd_temp != -1 && key)
      {
        sprintf(pswd1.deciphered_password[i], "%s", tab1);
        push_back_dynamic_array_int(&pswd1.index_of_deciphered_pswd, index_of_deciphered_pswd_temp);
        pthread_cond_signal(&display_pswd_threshold_cv);
      }
    }

    pthread_mutex_unlock(&pswd_mutex);
  }
}

void init_passwords(PASSWORD *pswd_temp)
{
  memset(pswd1.email, '\0', QUANTITY_PASSWORD * 50 * sizeof(char));
  memset(pswd1.encrypted_password, '\0', QUANTITY_PASSWORD * 33 * sizeof(char));
  memset(pswd1.deciphered_password, '\0', QUANTITY_PASSWORD * 200 * sizeof(char));

  init_dynamic_array_int(&pswd1.index_of_deciphered_pswd, 1);

  pswd1.quantity_password_in_file = 0;
}
