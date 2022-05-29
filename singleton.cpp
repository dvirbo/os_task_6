#include <sys/stat.h>

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <mutex>
#include <fstream>

template <class T>
class singleton
{
public:
    static singleton *single;
    T _single;
    static std::mutex mutex_;

    int fd;
    singleton(T sin);
    static singleton *Instance(T sin);
    void Destroy();
};

template <class T>
singleton<T> * singleton<T>::single = NULL; //init

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
        single = new Singleton(sin);
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
     FILE *fptr;

    singleton<FILE*>* s = singleton<FILE*>::Instance(fptr); 
    singleton<FILE*>* r = singleton<FILE*>::Instance(fptr);

    // Singleton *lb2 = Singleton::Instance();
    // Singleton *lb3 = Singleton::Instance();

    // if (lb1 == lb2 && lb2 == lb3)
    // {
    //     std::cout << "Same instance" << endl;
    // }

    // lb1->fd = open("./text.txt", O_RDWR, S_IRUSR | S_IWUSR);

    // if (lb1->fd == -1)
    // {
    //     printf("error: % d\n", errno);
    //     perror("fali");
    // }
    // struct stat sb;
    // if (fstat(lb1->fd, &sb) == -1)
    // {
    //     perror("couldn't get file size.\n");
    // }

    // char *file_in_memory = (char *)mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, lb1->fd, 0); // map file to memory
    // close(lb1->fd);

    // if (lb1->fd == lb2->fd && lb2->fd == lb3->fd)
    // {
    //     std::cout << "pass" << endl;
    // }
    // else
    // {
    //     std::cout << "fail" << endl;
    // }

    // i want to check if i can read from the file with other fd (lb2 or lb3..) --> than i can say that this is singleton

    return 0;
}