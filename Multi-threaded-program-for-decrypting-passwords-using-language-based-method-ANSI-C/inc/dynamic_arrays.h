#pragma once

#include "function_to_string.h"
// Struktura przechowująca tablicę dynamiczną i jej aktualny rozmiar
typedef struct
{
  int *array;
  size_t size;
  size_t capacity;
} DynamicArrayINT;

void init_dynamic_array_int(DynamicArrayINT *da, size_t initial_capacity);
void increase_capacity_dynamic_array_int(DynamicArrayINT *da);
void push_back_dynamic_array_int(DynamicArrayINT *da, int value);
void pop_back_dynamic_array_int(DynamicArrayINT *da);
void delete_dynamic_array_int(DynamicArrayINT *da);

void delete_two_dimensional_char_array(char **array_temp, size_t size_of_array);
void init_dynamic_array_two_dimension_char(char ***array_temp, size_t count_of_row, size_t count_of_column);
void delete_dynamic_array_two_dimension_char(char ***array_temp, size_t count_of_row);
