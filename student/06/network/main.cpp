#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "person.hh"
using namespace std;
const string HELP_TEXT = "S = store id1 i2\n P = print id\n"
                              "C = count id\n D = depth id";


vector<string> split(const string& s, const char delimiter, bool ignore_empty = false){
    vector<string> result;
    string tmp = s;

    while(tmp.find(delimiter) != string::npos)
    {
        string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

bool isInNetwork(string id, map <string, Person> network) {
    return network.find(id) != network.end();
}


void store(string id1, string id2, map <string, Person>& network) {
    if (isInNetwork(id1, network)) {
        network.at(id1).addNetwork(id2);
    } else {
        Person p1(id1);
        p1.addNetwork(id2);
        network.insert(make_pair(id1 , p1 ));
    }

}
void print(string id, map <string, Person> network, int depth = 1) {
    if (isInNetwork(id, network)) {
        Person person = network.at(id);
        for(size_t i=0;i<person.network.size();i++) {
            string dots;
            dots.insert(0, depth*2, '.');
            string friendId = person.network.at(i);
            cout << dots << friendId << endl;
            print(friendId, network, depth + 1);
        }
    }
}

int count(string id, map <string, Person> network) {
    int c = 0;

    if(! isInNetwork(id, network))
        return c;

    Person person = network.at(id);
    for(size_t i=0;i<person.network.size();i++) {
        string friendId = person.network.at(i);
        c += 1;
        if(isInNetwork(friendId, network))
            c += count(friendId, network);
    }
    return c;
}

int depth(string id, map <string, Person> network, int d = 1) {
    if (isInNetwork(id, network)) {
        Person person = network.at(id);
        for(size_t i=0;i<person.network.size();i++) {
            string friendId = person.network.at(i);
            return depth(friendId, network, d + 1);
        }
    }
    return d;
}

int main()
{
    map <string, Person> network;


    while(true){
        string line;
        cout << "> ";
        getline(cin, line);
        vector<string> parts = split(line, ' ', true);

        string command = parts.at(0);

        if(command == "S" or command == "s"){
            if(parts.size() != 3){
                cout << "Erroneous parameters!" << endl << HELP_TEXT;
            }
            string id1 = parts.at(1);
            string id2 = parts.at(2);

            store(id1, id2, network);

        } else if(command == "P" or command == "p"){
            if(parts.size() != 2){
                cout << "Erroneous parameters!" << endl << HELP_TEXT;
            }
            string id = parts.at(1);
            if(isInNetwork(id, network))
                cout << network.at(id).name << endl;
            print(id, network);

        } else if(command == "C" or command == "c"){
            if(parts.size() != 2){
                cout << "Erroneous parameters!" << endl << HELP_TEXT;
            }
            string id = parts.at(1);

            cout << count(id, network) << endl;

        } else if(command == "D" or command == "d"){
            if(parts.size() != 2){
                cout << "Erroneous parameters!" << endl << HELP_TEXT;
            }
            string id = parts.at(1);

            cout << depth(id, network) << endl;

        } else if(command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        } else {
            cout << "Erroneous command!" << endl << HELP_TEXT;
        }
    }
}
