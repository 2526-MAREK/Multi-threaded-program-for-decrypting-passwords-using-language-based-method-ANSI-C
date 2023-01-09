#include "producers.h"
#include "consumers.h"

#define BUFFER_SIZE 100

void error_pthread(int result, int id_thread, const char *tab)
{
  if (result != 0)
  {
    printf("ERROR; return code from pthread_create() is %d, ID thread is %d, in %s\n", result, id_thread, tab);
    exit(-1);
  }
}

void init_global_memory_for_producents()
{
  int count_of_row = dic1.lines_count;
  int count_of_column;

  count_of_column = 100;
  init_dynamic_array_two_dimension_char(&new_dictionary_for_producent_1, count_of_row, count_of_column);
  count_of_column = 100;
  init_dynamic_array_two_dimension_char(&new_dictionary_for_producent_2, count_of_row, count_of_column);
  count_of_column = 100;
  init_dynamic_array_two_dimension_char(&new_dictionary_for_producent_3, count_of_row, count_of_column);
  count_of_column = 300;
  init_dynamic_array_two_dimension_char(&new_word_for_producent_4, count_of_row, count_of_column);
  count_of_column = 200;
  init_dynamic_array_two_dimension_char(&new_dictionary_for_producent_4, count_of_row, count_of_column);
  count_of_column = 200;
  init_dynamic_array_two_dimension_char(&new_word_for_producent_5, count_of_row, count_of_column);
  count_of_column = 100;
  init_dynamic_array_two_dimension_char(&new_dictionary_for_producent_5, count_of_row, count_of_column);
}

void delete_all_busy_memory()
{
  for (size_t i = 1; i < NUM_THREADS; i++)
  {
    //pthread_mutex_unlock(&pswd_mutex);
    pthread_cancel(threads[i]);
  }

  /*for (size_t i = 1; i < NUM_THREADS; i++)
  {
    pthread_mutex_unlock(&pswd_mutex);
    pthread_join(threads[i], NULL);
  }*/

  int count_of_row = dic1.lines_count;
  delete_dynamic_array_two_dimension_char(&new_dictionary_for_producent_1, count_of_row);
  delete_dynamic_array_two_dimension_char(&new_dictionary_for_producent_3, count_of_row);
  delete_dynamic_array_two_dimension_char(&new_dictionary_for_producent_2, count_of_row);
  delete_dynamic_array_two_dimension_char(&new_word_for_producent_4, count_of_row);
  delete_dynamic_array_two_dimension_char(&new_dictionary_for_producent_4, count_of_row);
  delete_dynamic_array_two_dimension_char(&new_word_for_producent_5, count_of_row);
  delete_dynamic_array_two_dimension_char(&new_dictionary_for_producent_5, count_of_row);
  delete_dynamic_array_two_dimension_char(&dic1.lines, count_of_row);
}

int main()
{
  int temp1;
  int temp2;
  int result_thread;

  bool threads_running = false;

  char buffer[BUFFER_SIZE];

  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  pthread_mutex_init(&pswd_mutex, NULL);
  pthread_cond_init(&display_pswd_threshold_cv, NULL);
  pthread_attr_init(&attr);

  init_dictionary(&dic1);
  temp1 = read_dictionary();

  init_global_memory_for_producents();

  printf("Wczytaj nowa nazwę pliku z hasłami: ");

  while (fgets(buffer, BUFFER_SIZE, stdin) != NULL)
  {
    delete_newline_character(buffer);

    if (threads_running)
    {
      pthread_mutex_unlock(&pswd_mutex);

      for (size_t i = 0; i < NUM_THREADS; i++)
      {
        pthread_mutex_unlock(&pswd_mutex);
        pthread_cancel(threads[i]);
      }

      for (size_t i = 0; i < NUM_THREADS; i++)
      {
        pthread_mutex_unlock(&pswd_mutex);
        pthread_join(threads[i], NULL);
      }

      delete_dynamic_array_int(&pswd1.index_of_deciphered_pswd);
      threads_running = false;
    }

    if (!threads_running)
    {
      init_passwords(&pswd1);

      temp2 = read_encrypted_password(buffer);

      printf("\nRozpoczynam nowy cykl programu... \n");
      pthread_mutex_unlock(&pswd_mutex);
      result_thread = pthread_create(&threads[3], &attr, consumer_display_last_deciphered_password, (void *)0);
      error_pthread(result_thread, 3, "main");
      result_thread = pthread_create(&threads[0], &attr, producer_0_only_low_letters, (void *)3);
      error_pthread(result_thread, 0, "main");
      result_thread = pthread_create(&threads[1], &attr, producer_1_first_upper_letters, (void *)1);
      error_pthread(result_thread, 1, "main");
      result_thread = pthread_create(&threads[2], &attr, producer_2_all_upper_letters, (void *)2);
      error_pthread(result_thread, 2, "main");
      result_thread = pthread_create(&threads[4], &attr, producer_3_only_low_letters_two_words, (void *)4);
      error_pthread(result_thread, 4, "main");
      result_thread = pthread_create(&threads[5], &attr, producer_4_first_upper_letters_two_words, (void *)5);
      error_pthread(result_thread, 5, "main");
      result_thread = pthread_create(&threads[6], &attr, producer_5_all_upper_letters_two_words, (void *)6);
      error_pthread(result_thread, 6, "main");

      threads_running = true;
    }
  }

  pthread_exit(NULL);

  return 0;
}
