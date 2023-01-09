#include "dictionary.h"

void init_dictionary(DICTIONARY *dic_temp)
{
  dic_temp->lines = NULL;
  dic_temp->lines_count = 0;
}

int read_dictionary()
{
  dic1.lines = NULL;
  dic1.lines_count = 0;

  // otwarcie pliku do odczytu
  FILE *fptr = fopen("słownik_test_5.txt", "r");
  if (fptr == NULL)
  {
    perror("Nie można otworzyć pliku");
    return 1;
  }

  // wczytywanie linii z pliku do tablicy
  char *line = NULL;
  size_t len = 0;
  while (getline(&line, &len, fptr) != -1)
  {
    delete_newline_character(line);

    dic1.lines_count++;
    dic1.lines = (char **)realloc(dic1.lines, dic1.lines_count * sizeof(char *)); // zwiększenie rozmiaru tablicy
    dic1.lines[dic1.lines_count - 1] = line;                                      // dodanie nowej linii do tablicy
    line = NULL;                                                                  // zresetowanie wskaźnika na linię
    len = 0;                                                                      // zresetowanie długości linii
  }

  // zwolnienie pamięci i zamknięcie pliku
  free(line);
  fclose(fptr);

  printf("Zakończono wczytywanie słownika !!! Wczytano: %ld slow\n", dic1.lines_count);

  return 0;
}

void development_dictionary_and_find_password(char *orginal_word_from_producent)
{
  unsigned int number = 0;

  char new_dictionary_for_producent_after[300];
  char new_dictionary_for_producent_before[300];
  char new_dictionary_for_producent_after_and_before[300];

  while ((number <= MAX_NUMBER_LIMITING_ADDITIONAL_WORD_TO_DICTIONARY))
  {

    sprintf(new_dictionary_for_producent_after, "%s%d", orginal_word_from_producent, number);

    hash_and_find_password(new_dictionary_for_producent_after);
    pthread_testcancel();

    sprintf(new_dictionary_for_producent_before, "%d%s", number, orginal_word_from_producent);
    hash_and_find_password(new_dictionary_for_producent_before);
    pthread_testcancel();

    int number_to_after_and_before = 0;
    while ((number_to_after_and_before <= MAX_NUMBER_LIMITING_ADDITIONAL_WORD_TO_DICTIONARY))
    {
      sprintf(new_dictionary_for_producent_after_and_before, "%d%s%d", number, orginal_word_from_producent, number_to_after_and_before);
      hash_and_find_password(new_dictionary_for_producent_after_and_before);
      pthread_testcancel();
      number_to_after_and_before += 1;
    }

    number += 1;
  }
}
