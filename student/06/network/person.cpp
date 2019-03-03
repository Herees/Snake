#include "person.hh"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

Person::Person(string name)
{
    this->name = name;
}

void Person::addNetwork(string person) {
    this->network.push_back(person);
}
