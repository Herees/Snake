// Valtteri Kirsilä, 255342, valtteri.kirsila@tuni.fi
// main.cpp
// Main function, split, file reading

#include <iostream>
#include <vector>
#include <cstdlib>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include "library.hh"



std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = true){
    // Split function from a previous assignment
    // Returns the line splitted to a vector
    // Parameters: const string s ( file line ), const char delimiter, bool ignore_empty
    std::vector<std::string> result;
    std::string tmp = s;

    // Splits line from the delimiter character to vector
    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
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


bool read_file_create_libraries_and_books( std::ifstream& fileStream, std::map<std::string, Library>& libraries ) {
    // Tries to open given file. If fails program shuts down.
    // If succeeds creates new Chain objects or adds a shop and its products to a existing one.
    // Returns a true if succeeds else false
    // Parameters: ifstream fileStream ( input file object ), map<string, Chain> chains

    // Variables for file line and its contents
    std::string line;
    std::vector<std::string> lineContents;

    // Loops while there are lines in the file
    while ( getline(fileStream, line ) ) {

        // Splits the line to words to a vector
        lineContents = split( line, ';' );

        // If there are erroneous lines in file close program with a error message
        // (erroneous includes empty cells, lines or not enough cells
        for (auto cell : lineContents) {
            remove_if(cell.begin(), cell.end(), isspace);
            if (cell == " ") {
                    std::cout << "Error: the file has an erroneous line" << std::endl;
                    return false;
            }
        }
        if ( lineContents.size() != 4 ) {
            std::cout << "Error: the file has an erroneous line" << std::endl;
            return false;
        } else {

            // If new library, creates a new Library object and adds it to the data structure
            if ( libraries.find( lineContents.at(0) ) == libraries.end() ) {
                Library new_library( lineContents.at(0) );
                libraries.insert( { lineContents.at(0) ,new_library } );
            }

            // If library doesn't have given book, adds it
            //if ( !libraries.at( lineContents.at(0) ).find_book( lineContents.at(1) )) {
            //    libraries.at( lineContents.at(0) ).add_book( lineContents.at(1) );
            }

        }

    return true;

}


int main()
{
    // Map for Library class objects
    std::map<std::string, Library> libraries;

    // Gets filename
    std::string fileName;
    std::cout << "Input file: ";
    getline(std::cin, fileName);

    // If no such file exists return error message and close program
    std::ifstream fileStream(fileName);
    if (!fileStream) {
        std::cout << "Error: the input file cannot be opened" << std::endl;
        return EXIT_FAILURE;
    }

    // If there is an error during reading the file close the program
    if(!read_file_create_libraries_and_books(fileStream, libraries)) {
            return EXIT_FAILURE;
    }
    //Implement UI
    // user_interface(libraries);
    return EXIT_SUCCESS;

}
