/*
####################################################################
# TIE-02207 Programming 2: Basics, S2019                           #
#                                                                  #
# Project2: Library                                                #
# Program description: Program for managing library reservations   #
#                                                                  #
# File: library.cpp                                                #
# Description: Methods for class Library.                          #
#                                                                  #
# Author: Valtteri Kirsilä, 255342, valtteri.kirsila@tuni.fi       #
####################################################################
*/
#include "library.hh"


Library::Library(string name): name(name) {
                                   }

void Library::addBook(Book book) {
    vector<Book>::iterator bookIterator = find(books.begin(), books.end(), book);
    if(bool(bookIterator != books.end()))
        bookIterator->reservations = book.reservations;
    else
        books.push_back(book);
}
vector<Book> Library::sortBooks() {
    sort(books.begin(), books.end());
    return books;
}

void Library::printBooks(string author) {
    sort(books.begin(), books.end());
    int books_by_author = 0;
    for (auto book : books) {
        if(book.author == author) {
            books_by_author += 1;
            if(book.reservations == 0)
                cout << book.title << " --- " << "on the shelf" << endl;
            else
                cout << book.title << " --- " << book.reservations << " reservations" << endl;
        }
    }

    // If no books are found, author doesn't exist in libraries. Print error message.
    if(books_by_author == 0)
        cout << "Error: unknown author" << endl;
}

void Library::printMaterial() {
    sort(books.begin(), books.end());
    for (auto book : books) {
        cout << book.author << ": " << book.title << endl;
    }

}
