// Plain C example for synchronization/mutex usage
//
// Note: uses bankaccount_balance variable for storing the money

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_t tid_threadA, tid_threadB;
pthread_mutex_t mx;
volatile double bankaccount_balance = 0.0;

void do_fundraising(void *number_of_raisings_ptr) {
  int number_of_raisings = *(int *)number_of_raisings_ptr;
  for (int i = 0; i < number_of_raisings; i++) {
    pthread_mutex_lock(&mx);
    bankaccount_balance = bankaccount_balance + 1.0;
    pthread_mutex_unlock(&mx);
  }
}

int main(void) {
  int error;
  int amount = 500000;

  // initialize the mutex (necessary before first usage)
  if (pthread_mutex_init(&mx, NULL) != 0) {
    printf("\nmutex init failed\n");
    return 1;
  }

  // Create Thread A - adds 500 000
  error = pthread_create(&tid_threadA, NULL, &do_fundraising, &amount);
  if (error != 0)
    printf("\nThread cannot be created : [%s]", strerror(error));

  // Create Thread B - adds 500 000
  error = pthread_create(&tid_threadB, NULL, &do_fundraising, &amount);
  if (error != 0)
    printf("\nThread cannot be created : [%s]", strerror(error));

  // Wait for both threads to finish
  pthread_join(tid_threadA, NULL);
  pthread_join(tid_threadB, NULL);

  // destroy mutex if you do not need it anymore
  pthread_mutex_destroy(&mx);

  printf("all threads have finished - balance: %f\n", bankaccount_balance);

  return 0;
}
