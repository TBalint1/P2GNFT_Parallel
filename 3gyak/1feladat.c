#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

void *waitEightSeconds(void *_)
{
    pthread_t tid;
    int wait_time;

    tid = pthread_self();
    wait_time = 8;
    printf("[%d] Wait 8 seconds ...\n", tid);
    sleep(wait_time);
    printf("[%d] Ready!\n", tid);
}

void *waitFourSeconds(void *_)
{
    pthread_t tid;
    int wait_time;

    tid = pthread_self();
    wait_time = 4;
    printf("[%d] Wait 4 seconds ...\n", tid);
    sleep(wait_time);
    printf("[%d] Ready!\n", tid);
}

int main()
{
    pthread_t thread;
    int wait_time;
    pthread_create(&thread, NULL, waitFourSeconds, NULL);
    printf("[%d] Wait 8 seconds ...\n", thread);
    wait_time = 8;
    sleep(wait_time);
    printf("[%d] Ready!\n", thread);
    pthread_join(thread, NULL);

    pthread_create(&thread, NULL, waitEightSeconds, NULL);
    printf("[%d] Wait 4 seconds ...\n", thread);
    wait_time = 4;
    sleep(wait_time);
    printf("[%d] Ready!\n", thread);
    pthread_join(thread, NULL);

    return 0;
}