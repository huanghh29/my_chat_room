#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void* thread(int i){
    sleep(i);
    printf("%d thread id = %lu\n", i, pthread_self());
    sleep(5);
    printf("%d thread id = %lu\n", i, pthread_self());
}
int main(){
    pthread_t tid;
    for (int i = 1; i <= 5;i++)
        pthread_create(&tid, NULL, thread, i);
    // sleep(6);
    printf("main thread id = %lu\n", (long int)tid);
    sleep(11);
    return 0;
}