#include <cstdlib>
#include <iostream>
#include "singleton.hpp"

using namespace std;

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
            delete(single);
    }
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

    // need to map file to vector "text" for checking
    // need to create makefile

    return 0;
}