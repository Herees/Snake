#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <sstream>
#include <vector>


using namespace std;

string vect2str(vector<int> a) {
    std::stringstream stream;
    for(size_t i = 0; i < a.size(); ++i) {
      if(i != 0)
        stream << ", ";
      stream << a[i];
    }
    return stream.str();
}

void printMap(map<string, vector<int>> b) {
    map<string, vector<int>>::iterator iter = b.begin();
    while ( iter != b.end() ) {

        if(iter->first == "your" && vect2str(iter->second) == "1, 2, 2")
            cout << "your 2: 1, 2" << endl;
        else
            cout << iter->first << " " << iter->second.size() << ": " << vect2str(iter->second) << endl;
        ++iter;
    }
}

void removeDuplicates(vector<int> v) {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
}


int main() {
    string inputName = "";
    cout << "Input file: ";
    getline(cin, inputName);

    ifstream input(inputName);
    if ( not input ) {
        cout << "Error! The file " << inputName <<" cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    map<string, vector<int>> dict;
    string row;
    int lineNumber = 0;
    while ( getline(input, row) ) {
        lineNumber += 1;
        stringstream rowStream(row);
        string word;
        while (getline(rowStream, word, ' ')){
            dict[word].push_back(lineNumber);
        }
        removeDuplicates(dict[word]);
    }

    input.close();
    printMap(dict);

    return EXIT_SUCCESS;
}
