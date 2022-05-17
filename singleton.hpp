#pragma once

#include <vector>
#include <string>
#include <mutex>
#include <thread>


using std::string;
using std::vector;

class LoadBalancer
{
public:
    static LoadBalancer *GetLoadBalancer();
    string getServer();

private:
   static std::mutex mutex_;
    LoadBalancer();
    LoadBalancer(const LoadBalancer &);
    LoadBalancer &operator=(const LoadBalancer &);

    static LoadBalancer *instance;
    vector<string> servers;
};


// https://gist.github.com/firatakandere/8a19678bf4a36bc6d3a9#file-loadbalancer-h