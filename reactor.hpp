#pragma once
#include <iostream>
#include <pthread.h>
#include <memory>

using namespace std;

typedef struct _reactor
{
    int _fd;
    pthread_t _id;
    void *(*func)(void *);
}reactor, *preactor;

typedef struct _reqests
{
    int _fd;
    preactor p_reactor;
} reqests, *preqests;

preactor newReactor(); //creae new reactor
void InstallHandler(preactor p_reactor, void *(func)(void *), int file_des);
void RemoveHandler(preactor p_reactor, int fd_free);
