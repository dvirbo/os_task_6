#pragma once

#include <vector>
#include <string>
#include <mutex>
#include <thread>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

class LoadBalancer
{
private:
    static LoadBalancer *single;
    LoadBalancer();
    static std::mutex mutex_;

public:
     vector<string> vecOfStrs;
    static LoadBalancer *Instance(); // return pointer to singlton
    void Destroy();
   static bool getFileContent(std::string fileName, vector<string> &vecOfStrs);
};

/* Singleton Pattern Example with POSIX Threads Programming:
    https://gist.github.com/firatakandere/8a19678bf4a36bc6d3a9#file-loadbalancer-h
read a file line by line into a vector:
     https://thispointer.com/c-how-to-read-a-file-line-by-line-into-a-vector/
*/