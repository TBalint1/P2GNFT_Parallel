#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

const int N_THREADS = 60;

void *wait(void *_)
{
  pthread_t tid;
  int wait_time;

  tid = pthread_self();
  wait_time = 1;
  printf("[%d] Wait 1 seconds ...\n", tid);
  sleep(wait_time);
  printf("[%d] Ready!\n", tid);
}

int main(int argc, char *argv[])
{
  pthread_t threads[N_THREADS];
  int i;

  printf(":: Start threads ...\n");
  for (i = 0; i < N_THREADS; ++i)
  {
    pthread_create(&threads[i], NULL, wait, NULL);
  }

  printf(":: Join threads ...\n");
  for (i = 0; i < N_THREADS; ++i)
  {
    pthread_join(threads[i], NULL);
  }

  printf(":: Ready.\n");

  return 0;
}
