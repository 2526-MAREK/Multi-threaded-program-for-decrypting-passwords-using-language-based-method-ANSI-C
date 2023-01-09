#pragma once

#include <ctype.h>
#include <openssl/evp.h>
#include <openssl/md5.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

#include "dynamic_arrays.h"

#define NUM_THREADS 7
#define MAX_NUMBER_LIMITING_ADDITIONAL_WORD_TO_DICTIONARY 99

pthread_t threads[NUM_THREADS];

char **new_dictionary_for_producent_1;
char **new_dictionary_for_producent_2;
char **new_dictionary_for_producent_3;
char **new_word_for_producent_4;
char **new_dictionary_for_producent_4; 
char **new_word_for_producent_5;
char **new_dictionary_for_producent_5;

pthread_attr_t attr;
pthread_mutex_t pswd_mutex;
pthread_cond_t display_pswd_threshold_cv;

void delete_all_busy_memory();
void init_global_memory_for_producents();

