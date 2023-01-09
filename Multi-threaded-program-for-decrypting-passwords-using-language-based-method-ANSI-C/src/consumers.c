#include "consumers.h"
void consumer_communicate_and_end(int sig)
{
  printf("\n\nKończyę pracę, udało się rozszyfrować %ld z %d haseł!\n", pswd1.index_of_deciphered_pswd.size, pswd1.quantity_password_in_file);
  delete_all_busy_memory();
  pthread_attr_destroy(&attr);
  pthread_mutex_destroy(&pswd_mutex);
  pthread_cond_destroy(&display_pswd_threshold_cv);
  _exit(0);
}

void *consumer_display_last_deciphered_password(void *idp)
{
  long my_id = (long)idp;

  signal(SIGHUP, consumer_communicate_and_end);

  while (true)
  {
    pthread_testcancel();
    pthread_mutex_lock(&pswd_mutex);
    pthread_cond_wait(&display_pswd_threshold_cv, &pswd_mutex);

    size_t index_temp = pswd1.index_of_deciphered_pswd.array[pswd1.index_of_deciphered_pswd.size - 1];
    printf("Password for %s is %s\n", pswd1.email[index_temp], pswd1.deciphered_password[index_temp]);

    pthread_mutex_unlock(&pswd_mutex);
  }
  delete_dynamic_array_int(&pswd1.index_of_deciphered_pswd);
  pthread_exit(NULL);
}
