/*
####################################################################
# TIE-02207 Programming 2: Basics, S2019                           #
#                                                                  #
# Project2: Library                                                #
# Program description: See library reservations and read csv file  #
#                                                                  #
# File: main.cpp                                                   #
# Description: The main function, which starts the program.        #
#                                                                  #
# Author: Valtteri Kirsilä, 255342, valtteri.kirsila@tuni.fi       #
####################################################################
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include "library.hh"
using namespace std;


std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = true){
    std::vector<std::string> result;
    std::string tmp = s;
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


map<string, Library> libraries;


// combine vector strings to string
string combine(vector<string> words) {
    string title;
    for (size_t i=0; i<words.size();i++) {
        string word = words[i];
        if (i == 0 and word.front() == '"')
            word.erase(word.begin(), word.begin()+1);
        if (i == words.size()-1 && word.back() == '"')
            word.erase(word.end()-1, word.end());
        if (i == 0)
            title += word;
        else
            title += " " + word;
    }
    return title;
}

// If book is on the shelf, its reservation count is 0. This function turns that string into an integer.
int numReservations(string str) {
    if(str == "on-the-shelf")
        return 0;
    else
        return atoi(str.c_str());
}

int getMinReservations(map<string, Library> libraries, string title) {
    int minReservations = 9999;

    for (auto library : libraries) {
        for (auto book : library.second.books) {
            if(book.reservations < minReservations && book.title == title)
                minReservations = book.reservations;
        }
    }
    return minReservations;
}

// Read row and return possible exception as a boolean
bool read_row(string row, map<string, Library>& libraries) {
    vector<string> result = split(row, ';');
    if(result.size() != 4) {
        cout << "Error: empty field" << endl;
        return false;
    }
    string libraryName = result.at(0);
    string author = result.at(1);
    string title = result.at(2);
    int reservations = numReservations(result.at(3));
    Book book = {title, author, reservations};

    if(libraries.find(libraryName) != libraries.end()) {
        Library& library = libraries.at(libraryName);
        library.addBook(book);
    } else {
        // Library was not found from libraries
        // Create new library and add book
        Library library(libraryName);
        library.addBook(book);
        libraries.insert(make_pair(libraryName, library));
    }
    return true;
}

bool read_file(map<string, Library>& libraries) {
    string inputName, row;
    cout << "Input file: ";
    getline(cin, inputName);
    ifstream input(inputName);

    if (!input) {
        cout << "Error: the input file cannot be opened" << endl;
        return false;
    }

    while ( getline(input, row) ) {
        bool rowSuccess = read_row(row, libraries);
        if(not rowSuccess)
            return false;
    }
    input.close();
    return true;
}

vector<Book> getBooks(map<string, Library> libraries) {
    vector<Book> books;
    for (auto& library : libraries) {
        for (auto& book : library.second.books) {
            books.push_back(book);
        }
    }
    sort(books.begin(), books.end());
    return books;
}




void command_error(std::string command) {
    // Prints the chosen error message
    // Parameters: string command
    std::cout << "Error: error in command " << command << std::endl;
}

void printLibraries(map<string, Library> libraries) {
    // Print name of each library
    for (auto& library : libraries) {
        cout << library.first << endl;
    }
}

void printReservable(map<string, Library> libraries, string title) {
    int minReservations = getMinReservations(libraries, title);

    // no books by title in lib (minReservations has initial value)
    if (minReservations == 9999) {
        cout << "Book is not a library book." << endl;
        return;
    } else if (minReservations >= 100) {
        cout << "The book is not reservable from any library." << endl;
        return;
    }

    if (minReservations == 0)
        cout << "on the shelf" << endl;
    else
        cout << minReservations << " reservations" << endl;

    for (auto& library : libraries) {
        for (auto& book : library.second.books) {
            if(book.reservations == minReservations && book.title == title)
                cout << "--- " << library.first << endl;
        }
    }
}

void Loanable(vector<Book> books) {
    for (auto book : books) {
        if(book.reservations == 0)
            cout << book.author << ": " << book.title << endl;
    }
}

bool startUI(std::map<std::string, Library>& books) {
    // UI asks inputVector until 'quit' is given
    // Checks that given command is available and has the proper amount of parameters
    // returns EXIT_SUCCESS boolean when the user wants to close program
    // Parameters: map<string, Library> books

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

        } else if (inputVector.at(0) == "libraries"  ) {
            if ( inputVector.size() != 1 ) {
                command_error("libraries");
            } else {
                printLibraries(libraries);
            }
        } else if ( inputVector.at(0) == "books") {
            // books should only have "books" in it
            if ( inputVector.size() != 1 ) {
                command_error("books");
            } else {
                string libraryName = inputVector.at(1);
                string author = inputVector.at(2);
                  Library library = libraries.at(libraryName);
                  library.printBooks(author);
            }
        } else if ( inputVector.at(0) == "material") {

            // material has two parts, if no such library exists give error
            string libraryName = inputVector.at(1);
            if ( inputVector.size() != 2 ) {
                command_error("material");

            } else if ( books.find( inputVector.at(1) ) != books.end() ) {
                Library library = libraries.at(libraryName);
                library.printMaterial();

            } else {
                std::cout << "Error: unknown library name" << std::endl;
            }

        } else if ( inputVector.at(0) == "books") {

            // books has 3 components,
            // checks if library and book exists, printing error messages if not.
            if ( inputVector.size() != 3 ) {
                command_error("books");

            } else if ( books.find( inputVector.at(1) ) == books.end() ) {
                std::cout << "Error: unknown library name" << std::endl;
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
                string title = combine(inputVector);
                printReservable(libraries,title);


        } else if ( inputVector.at(0) == "loanable" ) {

            // loanable has 1 component
            if ( inputVector.size() != 1 ) {
                command_error( "loanable" );

            } else {
                vector<Book> books = getBooks(libraries);
                Loanable(books);
            }

        } else {
            // If none predetermined inputVector match print an error
            std::cout << "Error: unknown command" << std::endl;
        }
    }
    return EXIT_SUCCESS;
}

int main()
{
    // Map for Library class objects
    std::map<std::string, Library> books;

    // If there is an error during reading the file close the program
    bool fileSuccess = read_file(libraries);
    if(not fileSuccess) {
        return EXIT_FAILURE;
    }
    startUI(books);
    return EXIT_SUCCESS;

}
