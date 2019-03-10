// Valtteri Kirsilä, 255342, valtteri.kirsila@tuni.fi
// library.hh
// Contains class Library method and variable declarations and definitions

#ifndef LIBRARY_HH
#define LIBRARY_HH


#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <set>


class Library
{
public:
    Library(std::string libraryName);



private:
    std::string libraryName_;

    // Struct for books
    struct Book {
        std::string title;
        std::string author;
        int reservations;
    };

};

#endif // LIBRARY_HH
