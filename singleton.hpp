#pragma once

#include <vector>
#include <string>
#include <mutex>
#include <thread>

using std::string;
using std::vector;

class LoadBalancer
{
private:
    static LoadBalancer *single;
    LoadBalancer();
    vector<string> text;
    static std::mutex mutex_;

public:
    static LoadBalancer *Instance(); // return pointer to singlton
    void Destroy();
    string getServer();
    
};

// https://gist.github.com/firatakandere/8a19678bf4a36bc6d3a9#file-loadbalancer-h