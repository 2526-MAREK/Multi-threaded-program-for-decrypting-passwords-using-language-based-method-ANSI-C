#pragma once

#include "dictionary.h"
#include "password.h" 

void consumer_communicate_and_end(int sig);
void *consumer_display_last_deciphered_password(void *idp);