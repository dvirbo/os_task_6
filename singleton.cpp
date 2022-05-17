#include <cstdlib>
#include <iostream>
#include "singleton.hpp"

using namespace std;

LoadBalancer *LoadBalancer::GetLoadBalancer()
{

    if (instance == NULL)
    {
        std::lock_guard<std::mutex> lo(mutex_);
        if (instance == NULL)
            instance = new LoadBalancer();
    }
    return instance;
}

string LoadBalancer::getServer()
{
    return servers[rand() % servers.size()];
}

LoadBalancer::LoadBalancer()
{
    servers.push_back("Server I");
    servers.push_back("Server II");
    servers.push_back("Server III");
    servers.push_back("Server IV");
    servers.push_back("Server V");
}

int main() {
	LoadBalancer *lb1 = LoadBalancer::GetLoadBalancer();
	LoadBalancer *lb2 = LoadBalancer::GetLoadBalancer();
	LoadBalancer *lb3 = LoadBalancer::GetLoadBalancer();

	if (lb1 == lb2 && lb2 == lb3) {
		std::cout << "Same instance" << endl;
	}

	cout << "load balancer 1: <" << lb1 << ">" << endl;
	cout << "load balancer 2: <" << lb2 << ">" << endl;
	cout << "load balancer 3: <" << lb3 << ">" << endl;

	cout << endl << "Generating 15 requests....." << endl << endl;

	for (int i = 0; i < 15; i++) {
		cout << lb1->getServer() << endl;
	}

	return 0;
}