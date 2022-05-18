#include "singleton.hpp"

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
/*
 * It will iterate through all the lines in file and
 * put them in given vector
 */
bool LoadBalancer::getFileContent(string fileName, vector<string> &vecOfStrs)
{
    // Open the File
    std::ifstream in(fileName.c_str());
    // Check if object is valid
    if (!in)
    {
        std::cerr << "Cannot open the File : " << fileName << endl;
        return false;
    }
    string str;
    // Read the next line from File untill it reaches the end.
    while (getline(in, str))
    {
        // Line contains string of length > 0 then save it in vector
        if (str.size() > 0)
            vecOfStrs.push_back(str);
    }
    // Close The File
    in.close();
    return true;
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
    bool result = LoadBalancer::getFileContent("text.txt", lb1->vecOfStrs);

    if (result)
    {
        // Print the vector contents
        for (std::string &line : lb1->vecOfStrs)
            std::cout << line << std::endl;
    }
    // need to create makefile

    return 0;
}