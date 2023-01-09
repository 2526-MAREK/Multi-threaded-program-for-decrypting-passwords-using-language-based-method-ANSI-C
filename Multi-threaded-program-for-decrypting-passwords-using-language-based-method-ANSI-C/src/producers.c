#include "producers.h"

void *producer_0_only_low_letters(void *idp)
{
  long my_id = (long)idp;

  int count = 0;
  bool key = false;

  while (count < dic1.lines_count)
  {
    if (!key)
    {
      hash_and_find_password(dic1.lines[count]);
      pthread_testcancel();
      count++;
    }
    else
    {
      development_dictionary_and_find_password(dic1.lines[count]);
      pthread_testcancel();
      count++;
    }

    if (count - 1 == dic1.lines_count - 1)
    {
      key = true;
      count = 0;
    }
  }

  pthread_exit(NULL);
}

void *producer_1_first_upper_letters(void *idp)
{
  long my_id = (long)idp;

  bool key = false;

  int count = 0;
  
  char temp[100];
  while (count < dic1.lines_count)
  {
    if (!key)
    {
      sprintf(temp, "%s", dic1.lines[count]);
      temp[0] = toupper(temp[0]);
      sprintf(new_dictionary_for_producent_1[count], "%s", temp);
      hash_and_find_password(new_dictionary_for_producent_1[count]);
      pthread_testcancel();
      count++;
    }
    else
    {
      development_dictionary_and_find_password(new_dictionary_for_producent_1[count]);
      pthread_testcancel();
      count++;
    }

    if (count - 1 == dic1.lines_count - 1)
    {
      key = true;
      count = 0;
    }
  }

  pthread_exit(NULL);
}

void *producer_2_all_upper_letters(void *idp)
{
  long my_id = (long)idp;
  
  bool key = false;

  int count = 0;

  char temp[100];

  while (count < dic1.lines_count)
  {
    if (!key)
    {
      sprintf(temp, "%s", dic1.lines[count]);
      change_to_upper(temp);
      sprintf(new_dictionary_for_producent_2[count], "%s", temp);
      hash_and_find_password(new_dictionary_for_producent_2[count]);
      pthread_testcancel();
      count++;
    }
    else
    {
      development_dictionary_and_find_password(new_dictionary_for_producent_2[count]);
      pthread_testcancel();
      count++;
    }

    if (count - 1 == dic1.lines_count - 1)
    {
      key = true;
      count = 0;
    }
  }

  pthread_exit(NULL);
}

void *producer_3_only_low_letters_two_words(void *idp)
{
  long my_id = (long)idp;
  
  bool key = false;

  int count = 0;
  int i = 0;

  while (count < dic1.lines_count)
  {
    if (!key)
    {
      while (i < dic1.lines_count)
      {

        sprintf(new_dictionary_for_producent_3[count], "%s %s", dic1.lines[count], dic1.lines[i]);
        hash_and_find_password(new_dictionary_for_producent_3[count]);
        pthread_testcancel();
        i++;
      }
      i = 0;
    }

    else
    {
      development_dictionary_and_find_password(new_dictionary_for_producent_3[count]);
      pthread_testcancel();
    }

    count++;

    if (count - 1 == dic1.lines_count - 1)
    {
      key = true;
      count = 0;
    }
  }

  pthread_exit(NULL);
}

void *producer_4_first_upper_letters_two_words(void *idp)
{
  long my_id = (long)idp;
  
  bool key = false;

  int count = 0;
  int i = 0;

  char temp[500];
  while (count < dic1.lines_count)
  {
    sprintf(temp, "%s", dic1.lines[count]);
    temp[0] = toupper(temp[0]);
    sprintf(new_dictionary_for_producent_4[count], "%s", temp);

    count++;
  }

  count = 0;
  while (count < dic1.lines_count)
  {
    if (!key)
    {
      while (i < dic1.lines_count)
      {

        sprintf(new_word_for_producent_4[count], "%s %s", new_dictionary_for_producent_4[count], new_dictionary_for_producent_4[i]);
        hash_and_find_password(new_word_for_producent_4[count]);
        pthread_testcancel();
        i++;
      }
      i = 0;
    }

    else
    {
      development_dictionary_and_find_password(new_word_for_producent_4[count]);
      pthread_testcancel();
    }

    count++;
    if (count - 1 == dic1.lines_count - 1)
    {
      key = true;
      count = 0;
    }
  }

  pthread_exit(NULL);
}

void *producer_5_all_upper_letters_two_words(void *idp)
{
  long my_id = (long)idp;
  
  bool key = false;

  int count = 0;
  int i = 0;

  char temp[500];
  while (count < dic1.lines_count)
  {
    sprintf(temp, "%s", dic1.lines[count]);
    change_to_upper(temp);
    sprintf(new_dictionary_for_producent_5[count], "%s", temp);

    count++;
  }

  count = 0;
  while (count < dic1.lines_count)
  {
    if (!key)
    {
      while (i < dic1.lines_count)
      {

        sprintf(new_word_for_producent_5[count], "%s %s", new_dictionary_for_producent_5[count], new_dictionary_for_producent_5[i]);
        hash_and_find_password(new_word_for_producent_5[count]);
        pthread_testcancel();
        i++;
      }
      i = 0;
    }
    else
    {
      development_dictionary_and_find_password(new_word_for_producent_5[count]);
      pthread_testcancel();
    }

    count++;

    if (count - 1 == dic1.lines_count - 1)
    {
      key = true;
      count = 0;
    }
  }

  pthread_exit(NULL);
}
