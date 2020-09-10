#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Author: Joseph Pietroluongo
// PID: 5901749
// I affirm that I wrote this program myself without any help
// from any other people or sources from the internet
// Summary: Uses 10 threads to increment a shared variable
// Each thread loops 6 times, incrementing the shared variable by its Thread ID (tid) in every
// iteration of the loop. This number for the tid will be in single digits from 0-9.
*/

//Write a program called tenthreads that uses 10 threads
#define NUM_THREADS 10

typedef struct strct_data_Thread
{
  int tid;
  double threadNum;
} data_Thread;

double shared_x;
pthread_mutex_t lock_x;

void *thr_func(void *arg)
{
  int i;
  data_Thread *data = (data_Thread *)arg;

  pthread_mutex_lock(&lock_x);

//Must loop 6 times and only 6.
  for (i = 0; i < 6; i++)
  
  // incrementing the shared variable by its Thread ID
    shared_x += data->tid;

  printf("Thread %d has finished. \n", data->tid);
  //only one thread is incrementing the shared variable at a time
  pthread_mutex_unlock(&lock_x);

  pthread_exit(NULL);
}

int main(int argc, char **argv)
{
  pthread_t thr[NUM_THREADS];
  int i, rc;

  data_Thread thr_data[NUM_THREADS];

  shared_x = 0;

  pthread_mutex_init(&lock_x, NULL);

  for (i = 0; i < NUM_THREADS; ++i)
  {
    thr_data[i].tid = i;
    thr_data[i].threadNum = (i + 1) * NUM_THREADS;
    if ((rc = pthread_create(&thr[i], NULL, thr_func, &thr_data[i])))
    {
      fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
      return EXIT_FAILURE;
    }
  }

  for (i = 0; i < NUM_THREADS; ++i)
  {
    pthread_join(thr[i], NULL);
  }

//Output the value of the shared variable once all threads have finished incrementing it.
  printf("\nShared variable value: %.1f \n", shared_x);

  return EXIT_SUCCESS;
}