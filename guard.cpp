#include <cstdio>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>


int counter = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

class NonCopyable
{
private:
    NonCopyable(NonCopyable const &);            // private copy constructor
    NonCopyable &operator=(NonCopyable const &); // private assignment operator

public:
    NonCopyable(){};
};

// inherite from NonCopyable class
class ScopeMutex : NonCopyable
{

private:
    pthread_mutex_t *mutex_;

public:
    ScopeMutex(pthread_mutex_t *mutex) : mutex_(mutex)
    {
        pthread_mutex_lock(mutex_);
    }

    ~ScopeMutex()
    {
        pthread_mutex_unlock(mutex_);
    }
};

void *routine(void*)
{
    ScopeMutex scopeMutex(&mutex); // lock start here
    counter++;
    printf("%d\n", counter);
    return NULL;
}                                  // lock end here

int main(int argc, char *argv[])
{
    int rc1, rc2;
    pthread_t thread1, thread2;
    if ((rc1 = pthread_create(&thread1, NULL, routine, NULL)))
    {
        printf("Thread creation failed: %d\n", rc1);
    }

    if ((rc2 = pthread_create(&thread2, NULL, routine, NULL)))
    {
        printf("Thread creation failed: %d\n", rc1);
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return 0;
}
/*
 how to run: g++ -std=c++11 guard.cpp -lpthread -o guard
source: https://github.com/secp256/code/blob/5c4e6093ba75b6f8c1438e83b01144d712067efd/cpp/test/a.cpp

part b: https://www.geeksforgeeks.org/strtok-strtok_r-functions-c-examples/
*/