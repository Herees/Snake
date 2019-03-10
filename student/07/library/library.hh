/*
####################################################################
# TIE-02207 Programming 2: Basics, S2019                           #
#                                                                  #
# Project2: Library                                                #
# Program description: See library books and reservations          #
#                                                                  #
# File: library.hh                                                 #
# Description: Headers for class Library.                          #
#                                                                  #
# Author: Valtteri Kirsilä, 255342, valtteri.kirsila@tuni.fi       #
####################################################################
*/

#ifndef LIBRARY_HH
#define LIBRARY_HH


#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <cstdlib>

using namespace std;

struct Book {
    std::string title;
    std::string author;
    int reservations;

        // opetator for comparing two books
    bool operator==(const Book& rhs) const {
        return (author == rhs.author) && (title == rhs.title);
    }


    // Operator for sorting books by thei author or title.
    bool operator<(const Book& rhs) const {
        return author == rhs.author ? (title < rhs.title) : author < rhs.author;
    }
};

class Library
{
public:
    Library(string name);
    string name;
    vector<Book> books;

    // Adds new book to the library if it was not found by author and title
    // Otherwise sets reservations by the newest book
    void addBook(Book book);

    // Get sorted books by author and title
    vector<Book> getBooks();

    // Print book materials
    void printMaterial();

    // Print all books by author
    void printBooks(string author);



private:
    std::string libraryName_;

};




#endif // LIBRARY_HH
