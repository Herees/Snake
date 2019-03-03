#ifndef PERSON_HH
#define PERSON_HH
#include <string>
#include <vector>

using namespace std;

class Person
{
public:
    string name;
    Person(string name);
    vector <string> network;
    void addNetwork(string person);
};

#endif // PERSON_HH
