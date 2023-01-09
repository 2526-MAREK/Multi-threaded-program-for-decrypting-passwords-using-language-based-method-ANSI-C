#include "function_to_string.h"

void delete_newline_character(char *line_temp)
{
  char *newline = strchr(line_temp, '\n');
  if (newline != NULL)
  {
    *newline = '\0';
  }
}

char *remove_tabulation_from_str(char *string)
{
  // non_space_count to keep the frequency of non space characters
  int non_space_count = 0;

  //Traverse a string and if it is non space character then, place it at index non_space_count
  for (int i = 0; string[i] != '\0'; i++)
  {
    if (string[i] != '\t')
    {
      string[non_space_count] = string[i];
      non_space_count++; //non_space_count incremented
    }
  }

  //Finally placing final character at the string end
  string[non_space_count] = '\0';
  return string;
}

void change_to_upper(char *string)
{
  int i;

  for (i = 0; string[i] != '\0'; i++)
  {
    if (string[i] >= 'a' && string[i] <= 'z')
    {
      string[i] = string[i] - 'a' + 'A';
    }
  }
}

bool this_string_is_lower(char *array)
{
  bool islower = true;
  for (int j = 0; j < strlen(array); ++j)
  {
    if (isupper(array[j]))
      islower = false;
  }
  return islower;
}