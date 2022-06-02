#include "reactor.hpp"
/*
create new reactor
*/
preactor newReactor()
{
    preactor rec = new reactor();
    return rec;
}
/*
create now request and and call the func that in client to handle the request
*/

void InstallHandler(preactor pr, void *(func)(void *), int fd)
{
    preqests p_reqests = new reqests();
    p_reqests->_fd = fd;
    p_reqests->ptreactor = pr;
    pr->func = func;
    pr->_fd = fd;
    pthread_create(&(pr->_id), NULL, func, p_reqests);
}
/*
delete (deallocate) the reactor 
not is used cause i do in manualy in the code using vector that contain all the preactor that create 
and 'free' also the fd in the 'pollhandler' that inside client
*/
void RemoveHandler(preactor pr, int fd)
{
    pr->_fd = -1;
    delete pr;
}