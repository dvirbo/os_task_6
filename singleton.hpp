#pragma once

#include <vector>
#include <string>
#include <mutex>
#include <thread>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


using namespace std;

class LoadBalancer
{
private:
    static LoadBalancer *single;
    LoadBalancer(); // need to implement distractor.. ~
    ~LoadBalancer(); // need to implement distractor.. ~
    static std::mutex mutex_;


public:
     vector<string> vecOfStrs;
     int fd;
    static LoadBalancer *Instance(); // return pointer to singlton
    void Destroy();
   static bool getFileContent(std::string fileName, vector<string> &vecOfStrs);
};

