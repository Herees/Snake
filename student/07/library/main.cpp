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
#include <cctype>
using namespace std;


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


void command_error(std::string command) {
    // Prints the chosen error message
    // Parameters: string command
    std::cout << "Error: error in command " << command << std::endl;
}



bool user_interface(std::map<std::string, Library>& libraries) {
    // UI asks commands until 'quit' is given
    // Checks that given command is available and has the proper amount of parameters
    // returns EXIT_SUCCESS boolean when the user wants to close program
    // Parameters: map<string, Chain> chains

    bool quit = false;
    std::string input;
    std::vector<std::string> inputVector;
    while ( !quit ) {
        // for the input UI
        std::cout << "> ";
        std::getline( std::cin, input );
        inputVector = split(input,' ');

        // If empty line -> continue
        if ( inputVector.size() == 0) {
            continue;

        // Close on quit
        } else if (inputVector.at(0) == "quit"  ) {
            quit = true;

        } else if ( inputVector.at(0) == "libraries") {

            // chains should only have "libraries" in it
            if ( inputVector.size() != 1 ) {
                command_error("libraries");
            } else {
            cout << "Tähän libraries komennon toteutus" << endl;
            }
        } else if ( inputVector.at(0) == "material") {

            // material has two parts, if no such library exists give error
            if ( inputVector.size() != 2 ) {
                command_error("material");

            } else if ( libraries.find( inputVector.at(1) ) != libraries.end() ) {
                cout << "material komennon toteutus tähän" << endl;

            } else {
                std::cout << "Error: unknown library name" << std::endl;
            }

        } else if ( inputVector.at(0) == "books") {

            // books has 3 components,
            // checks if library and book exists, printing error messages if not.
            if ( inputVector.size() != 3 ) {
                command_error("books");

            } else if ( libraries.find( inputVector.at(1) ) == libraries.end() ) {
                std::cout << "Error: unknown library name" << std::endl;

            //} else if ( !libraries.at(inputVector.at(1)).find_author( inputVector.at(2) ) ) {
            //    std::cout << "Error: unknown author" << std::endl;

            } else {
                cout << "books komento tähän"<< endl;
            }

        } else if ( inputVector.at(0) == "reservable" ) {

            // reservable has 2 components
            // checks for the shortest reservation line for requested book
            if ( inputVector.size() != 2 ) {
                command_error("reservable");
                continue;
            }
                cout<< "reservable funktion toteutus tähän" << endl;


        } else if ( inputVector.at(0) == "loanable" ) {

            // loanable has 1 component
            if ( inputVector.size() != 1 ) {
                command_error( "loanable" );

            } else {
                cout << "loanable funktion toteutus/kutsu tähän" << endl;
            }

        } else {
            // If none predetermined commands match print an error
            std::cout << "Error: unknown command" << std::endl;
        }
    }
    return EXIT_SUCCESS;
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
    user_interface(libraries);
    return EXIT_SUCCESS;

}
