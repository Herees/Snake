#include <iostream>
#include <fstream>
#include <string>
#include <map>




void printMap(std::map<std::string, unsigned int> points) {
    std::map<std::string, unsigned int>::iterator iter;
    iter = points.begin();
    std::cout << "Final scores:" << std::endl;
    while ( iter != points.end() ) {
        std::cout << iter->first << ": " << iter->second << std::endl;
        ++iter;
    }
}


int main() {
    std::string inputName, outputName = "";
    std::cout << "Input file: ";
    getline(std::cin, inputName);

    std::ifstream input(inputName);
    if ( not input ) {
        std::cout << "Error! The file " << inputName <<" cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }

    std::map<std::string, unsigned int> points;
    std::string row;

    while ( getline(input, row) ) {
        int colon = row.find(":");
        std::string name = row.substr(0, colon);
        unsigned int point = atoi(row.substr(colon+1).c_str());
        if(points[name]) {
            points[name] += point;
        } else {
            points[name] = point;
        }
    }

    input.close();

    printMap(points);

    return EXIT_SUCCESS;

}
