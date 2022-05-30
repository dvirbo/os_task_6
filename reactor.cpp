#include "reactor.hpp"

preactor newReactor()
{
    preactor rec = (preactor)malloc(sizeof(reactor));
    return rec;
}

void InstallHandler(preactor p_reactor, void *(func)(void *), int file_des)
{
    preqests p_reqests = (preqests)malloc(sizeof(reqests));
    p_reqests->_fd = file_des;
    p_reqests->p_reactor = p_reactor;
    p_reactor->func = func;
    p_reactor->_fd = file_des;
    pthread_create(&(p_reactor->_id), NULL, func, p_reqests);
}

void RemoveHandler(preactor p_reactor, int fd_free)
{
    pthread_join(p_reactor->_id, NULL);
    p_reactor->_fd = -1;
    p_reactor->func = nullptr;
}