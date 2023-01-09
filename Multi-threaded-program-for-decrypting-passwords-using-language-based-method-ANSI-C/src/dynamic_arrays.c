#include "dynamic_arrays.h"
// Inicjalizuje tablicę dynamiczną
void init_dynamic_array_int(DynamicArrayINT *da, size_t initial_capacity)
{
  da->array = (int *)malloc(initial_capacity * sizeof(int));
  da->size = 0;
  da->capacity = initial_capacity;
}

// Zwiększa pojemność tablicy dynamicznej
void increase_capacity_dynamic_array_int(DynamicArrayINT *da)
{
  da->capacity *= 2;
  da->array = (int *)realloc(da->array, da->capacity * sizeof(int));
}

// Dodaje element na końcu tablicy dynamicznej
void push_back_dynamic_array_int(DynamicArrayINT *da, int value)
{
  if (da->size == da->capacity)
  {
    increase_capacity_dynamic_array_int(da);
  }
  da->array[da->size++] = value;
}

// Usuwa element z końca tablicy dynamicznej
void pop_back_dynamic_array_int(DynamicArrayINT *da)
{
  if (da->size > 0)
  {
    da->size--;
  }
}

// Usuwa tablicę dynamiczną i zwalnia pamięć
void delete_dynamic_array_int(DynamicArrayINT *da)
{
  free(da->array);
}

void init_dynamic_array_two_dimension_char(char ***array_temp, size_t count_of_row, size_t count_of_column)
{
  *array_temp = (char **)malloc(count_of_row * sizeof(char *));
  for (size_t i = 0; i < count_of_row; i++)
  {
    (*array_temp)[i] = (char *)malloc(count_of_column * sizeof(char));
  }
}

void delete_dynamic_array_two_dimension_char(char ***array_temp, size_t count_of_row)
{
  for (size_t i = 0; i < count_of_row; i++)
  {
    free((*array_temp)[i]);
  }
  free(*array_temp);
}
