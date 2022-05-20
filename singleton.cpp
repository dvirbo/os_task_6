#include "singleton.hpp"
#include <sys/stat.h>

#define END '\0'

LoadBalancer::LoadBalancer()
{
}

LoadBalancer *LoadBalancer::Instance()
{
    if (single == NULL)
    {
        std::lock_guard<std::mutex> lo(mutex_);
        if (single == NULL)
            single = new LoadBalancer();
    }
    return single;
}

void LoadBalancer::Destroy()
{
    if (single != NULL)
    {
        std::lock_guard<std::mutex> lo(mutex_);
        if (single != NULL)
            delete (single);
    }
}
LoadBalancer::~LoadBalancer()
{
    Destroy();
}


int main()
{
    LoadBalancer *lb1 = LoadBalancer::Instance();
    LoadBalancer *lb2 = LoadBalancer::Instance();
    LoadBalancer *lb3 = LoadBalancer::Instance();

    if (lb1 == lb2 && lb2 == lb3)
    {
        std::cout << "Same instance" << endl;
    }

    lb1->fd = open("./text.txt", O_RDWR, S_IRUSR | S_IWUSR);

    if (lb1->fd == -1)
    {
        printf("error: % d\n", errno);
        perror("fali");
    }
    struct stat sb;
    if (fstat(lb1->fd, &sb) == -1)
    {
        perror("couldn't get file size.\n");
    }

    char *file_in_memory = (char *)mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, lb1->fd, 0); // map file to memory
    close(lb1->fd);

    if (lb1->fd == lb2->fd && lb2->fd == lb3->fd)
    {
        std::cout << "pass" << endl;
    }
    else
    {
        std::cout << "fail" << endl;
    }

    // i want to check if i can read from the file with other fd (lb2 or lb3..) --> than i can say that this is singelton

    return 0;
}