#ifndef FUNCTIONS_HH
#define FUNCTIONS_HH

#endif // FUNCTIONS_HH
#include <vector>
#include <map>
#include <string>
#include "library.hh"

using namespace std;
// Function for recognizing errorous commands, and informing user that their command is not valid.
void command_error(string command);
// Function for reading rows in the input file
bool read_row(string row, map<string, Library>& libraries);
// Function read_file for opening, reading and closing the input file.
bool read_file(map<string, Library>& libraries);
// Function 'printlibraries' prints out all known libraries.
void printLibraries(map<string, Library> libraries);
// Split function given in week 6.
vector<string> split(const string& s, const char delimiter, bool ignore_empty);
// Function 'printReservable' prints shortest reservation line for the book, if under 100 reservations.
void printReservable(map<string, Library> libraries, string title);
// Function 'loanable' prints out all books with zero reservations
// Books are sorted by author, and books by same author are sorted by their title.
void Loanable(vector<Book> books);
//Function 'startUI' launches the user interface of the program.
bool startUI(map<string, Library> libraries);
