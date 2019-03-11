/*
####################################################################
# TIE-02207 Programming 2: Basics, S2019                           #
#                                                                  #
# Project: Library                                                 #
# Program description: Program for managing library reservations.  #
#                                                                  #
# File: main.cpp                                                   #
# Description: The main function, which starts the program.        #
#                                                                  #
# Author: Valtteri Kirsilä, 255342, valtteri.kirsila@tuni.fi       #
####################################################################
*/

#include <iostream>
#include "functions.hh"
#include "library.hh"
#include <fstream>


int main()
{
    // Map for libraries and books.
    map<string, Library> libraries;

    // If there is an error during reading the file close the program
    if(!read_file(libraries)) {
        return EXIT_FAILURE;
    }
    startUI(libraries);
}
