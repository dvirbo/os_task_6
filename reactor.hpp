#pragma once
#include <iostream>
#include <pthread.h>

using namespace std;

typedef struct _reactor
{
    int _fd;
    pthread_t _id;
    void* (*func)(void*);
}reactor, *preactor;

typedef struct _reqests
{
    int _fd;
    preactor ptreactor;
} reqests, *preqests;

preactor newReactor(); //creae new reactor
void InstallHandler(preactor pr, void* (func)(void*), int fd);
void RemoveHandler(preactor pr, int fd);
