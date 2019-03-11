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

    // Searches for the book, if it is not in the struct, adds it.
    // Updates reservations if book exists in struct.
    void addBook(Book book);
    //Sorts books in alphabetical order
    vector<Book> sortBooks();

    // Prints books in asked library.
    void printMaterial();

    // Print books by given author
    // Input argument string author from user
    void printBooks(string author);



private:
    std::string libraryName_;

};




#endif // LIBRARY_HH
