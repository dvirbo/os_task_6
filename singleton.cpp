#include <sys/stat.h>

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <mutex>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sys/mman.h>
#include <fcntl.h>

using namespace std;

std::mutex mutex_;

template <class T>
class singleton
{
    static singleton *single;
    T _single;

public:
    int fd;
    singleton(T sin);
    static singleton *Instance(T sin);
    void Destroy();
};


template <class T>
 singleton<T> *singleton<T>::single = NULL; // init


template <class T>
singleton<T>::singleton(T sin)
{
    _single = sin;
}

template <class T>
singleton<T> *singleton<T>::Instance(T sin)
{
    std::lock_guard<std::mutex> lo(mutex_);
    if (single == NULL)
    {
        single = new singleton(sin);
    }

    return single;
}

template <class T>
void singleton<T>::Destroy()
{

    std::lock_guard<std::mutex> lo(mutex_);
    if (single != NULL)
    {
        delete (single);
    }
}

int main()
{
    FILE *fd;

    singleton<FILE *> *f1 = singleton<FILE *>::Instance(fd);
    singleton<FILE *> *f2 = singleton<FILE *>::Instance(fd);


    f1->fd = open("./text.txt", O_RDWR, S_IRUSR | S_IWUSR);


    if (f1->fd == -1)
    {
        printf("error: % d\n", errno);
        perror("fali");
    }
    struct stat sb;
    if (fstat(f1->fd, &sb) == -1)
    {
        perror("couldn't get file size.\n");
    }

    char *file_in_memory = (char *)mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, f1->fd, 0); // map file to memory
    close(f1->fd);

    if (f1->fd == f2->fd)
    {
        std::cout << "pass" << endl;
    }
    else
    {
        std::cout << "fail" << endl;
    }

    return 0;
}