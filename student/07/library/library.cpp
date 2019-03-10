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


Library::Library(std::string libraryName):
    libraryName_(libraryName)
{

}

void Library::addBook(Book book) {
    vector<Book>::iterator bookIterator = find(this->books.begin(), this->books.end(), book);
    bool bookExists = bookIterator != this->books.end();

    if(bookExists)
        bookIterator->reservations = book.reservations;
    else
        this->books.push_back(book);
}

vector<Book> Library::getBooks() {
    sort(this->books.begin(), this->books.end());
    return this->books;
}


void Library::printBooks(string author) {
    vector<Book> books = this->getBooks();
    int count = 0;
    for (auto book : books) {
        if(book.author == author) {
            count += 1;
            if(book.reservations == 0)
                cout << book.title << " --- " << "on the shelf" << endl;
            else
                cout << book.title << " --- " << book.reservations << " reservations" << endl;
        }
    }


    // If no books by author exist, print error message
    if(count == 0)
        cout << "Error: unknown author" << endl;
}

void Library::printMaterial() {
    for (auto book : this->getBooks()) {
        cout << book.author << ": " << book.title << endl;
    }

}
