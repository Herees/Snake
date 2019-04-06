/*
####################################################################
# TIE-02207 Programming 2: Basics, S2019                           #
#                                                                  #
# Project: Orienteering                                            #
# Program description: Program for orienteering. Seeing points and #
# routes and the map.                                              #
# File: routes.cpp                                                 #
# Description: This class file contains all the functions for class#
# Routes                                                           #
# Author: Valtteri Kirsilä, 255342, valtteri.kirsila@tuni.fi       #
####################################################################
*/


#include "routes.hh"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <cstdlib>


Routes::Routes()
{

}

Routes::~Routes()
{
    for(auto iter = points_.begin(); iter != points_.end(); ++iter){
        delete iter->second;
    }
}



void Routes::set_map_size(int width, int height){
mapHeight_ = height;
mapWidth_ = width;
}

void Routes::add_point(std::string& name, int x, int y, int height, char marker){
    std::map<std::string, Point*>::iterator iter = points_.find(name);
    if (iter != points_.end()){
        return;
    }
    // Makes a new point, save data from input file into the struct form.
    Point *point = new Point();
    point->name_ = name;
    point->x_ = x;
    point->y_ = y;
    point->height_ = height;
    point->marker_ = marker;
    points_.insert(std::make_pair(name, point));
}

bool Routes::connect_route(std::string& from, std::string& to, std::string& route_name){
    // std::vector<std::string> a;
    bool foundFrom = false;
    bool foundTo = false;

    for(auto iter = points_.begin(); iter != points_.end(); ++iter){
        //These if clauses check if there are points to connect asked route between.
        if(iter->first == from){
            foundFrom = true;
            continue;
        }
        if(iter->first == to){
            foundTo = true;
            continue;
        }
    }
    // If points before and after the route were found, adds route as pointers into allRoutes map.
        if (foundFrom && foundTo){
            Point* fromPt = points_.at(from);
            Point* toPt = points_.at(to);
            // Checking that the route doesn't already exist in the map.
            auto iter2 = allRoutes.find(route_name);
            // If route was not already in the map, adds it in.
            if(iter2 == allRoutes.end()){

               allRoutes[route_name]={fromPt,toPt};

            } else {
               allRoutes.at(route_name).push_back(toPt);
            }
            return true;
        } else {
            return false;
        }
}


void Routes::print_map() const {
    // Initializing variable found, which is used in printing points into the map.
    bool found = false;
    std::cout<<" ";
    for (int a= 1; a <= mapWidth_;a++){
        if(a<10){
           std::cout<<"  "<<a;
        } else {
            std::cout<<" "<<a;
        }
        }
    std::cout<<"\n";
    /** These loops go through every x,y coordinate combination. 
     * If that location contains a point, prints point marker. Else prints "." **/
    for (int yPrint = 1; yPrint <= mapHeight_;yPrint++){
        if(yPrint<10){std::cout<<" "<<yPrint;
        } else {
            std::cout<<yPrint;
        }
        for (int xPrint = 1; xPrint < mapWidth_+1;xPrint++){
            found = false;
            for(auto iter = points_.begin(); iter != points_.end(); ++iter){
                 // Checking if the coordinate combination contains a point.
                if(iter->second->y_ == yPrint && iter->second->x_ == xPrint){
                    // Position contained point -> Print point marker.
                    std::cout<<"  "<<iter-> second->marker_;
                    found = true;
                    continue;
                }
            }
            if (!found){
                // Position did not contain marker, prints a dot.
              std::cout<<"  .";
            }
        }
        //New line for next y-coordinate.
        std::cout<<'\n';
    }
}

void Routes::print_route_names() const
{
std::cout<<"Routes:"<<std::endl;
    for(auto iter = allRoutes.begin(); iter != allRoutes.end(); ++iter){
    std::cout<<" - "<<iter->first<<std::endl;
        }
}

void Routes::print_points() const
{
std::cout<<"Points:"<<std::endl;
for(auto iter = points_.begin(); iter != points_.end(); ++iter){
    std::cout<<" - "<<iter->first<<" : "<<iter->second->marker_<<std::endl;
}
}

void Routes::print_route(const std::string &name) const {
    // Boolean routeFound, used for errorous inputs
    bool routeFound = false;
    //This for loop goes through all the routes in the allRoutes map.
    for(auto iter = allRoutes.begin(); iter != allRoutes.end(); ++iter){
        //If the input route is found, this if clause is fullfilled.
        if(iter->first == name){
            routeFound = true;
            std::cout<<iter->second[0]->name_<<std::endl;
            //This for loop prints points on the route.
            for(unsigned int i = 1; i < iter->second.size(); i++){
                std::cout<<" -> "<<iter->second[i]->name_<<std::endl;
            }
            break;
        }
    }
    if(!routeFound){
        std::cout<<"Error: Route named "<<name<<" can't be found"<<std::endl;
    }
}

void Routes::route_length(const std::string &name) const{
    // Boolean routeFound is used for errorous inputs.
    bool routeFound = false;
    // Variable length used to gather length of each path between points from the for loop.
    float length = 0;
    // This for loop goes through all routes in the allRoutes map.
    for(auto iter = allRoutes.begin(); iter != allRoutes.end(); ++iter){
        // If the input route is in the map, this if-clause fullfills.
        if(iter->first == name){
            routeFound = true;
            for(unsigned int i = 0; i < iter->second.size()-1; i++){
               int x1 = iter->second[i]->x_;
               int y1 = iter->second[i]->y_;
               int x2 = iter->second[i+1]->x_;
               int y2 = iter->second[i+1]->y_;
               int xDif = abs(x2-x1);
               int yDif = abs(y2-y1);
               //Length of each path between two points on the route is added to length variable.
               length += sqrt(xDif*xDif + yDif*yDif);
            }
        }
    } if(!routeFound){
        std::cout<<"Error: Route named "<<name<<" can't be found"<<std::endl;
    } else {
        if (length < 10){
            std::cout<<"Route "<<name<<" length was "<<std::fixed<<std::setprecision(1)<<length<<std::endl;
        } else {
            std::cout<<"Route "<<name<<" length was "<<std::fixed<<std::setprecision(0)<<length<<std::endl;
        }
    }
}

void Routes::greatest_rise(const std::string &point_name) const {
    /** Initializing a vector for the route(s) with biggest rise.
     * integers rise1 and 2 are used in comparing rises between routes.
     * boolean pointpassed is used in finding the starting point
     * boolean pointFound is used in determining if the input point exists.
     **/
    std::vector<std::string>risingRoutes;
    int rise1 = 0;
    int rise2 = 0;
    bool pointPassed = false;
    bool pointFound = false;
    int previousPointHeight = 0;
            // Loop through all routes
            for(auto iter = allRoutes.begin(); iter != allRoutes.end(); ++iter){
                pointPassed = false;
                rise1 = 0;
                previousPointHeight = 0;
                // Loop for all points in a route
                for(Point* point: iter->second){
                    // This if clause fullfills after starting point is found in route.
                    if(point->name_ == point_name){
                        // Point was on a route
                        pointFound = true;
                        previousPointHeight = point->height_;
                        // Starting point found
                        pointPassed = true;
                        continue;
                    }
                    // If starting point was found, and route is still rising, this if clause fullfills.
                    if(pointPassed && point->height_>previousPointHeight){
                        rise1 += (point->height_ - previousPointHeight);
                        previousPointHeight = point->height_;
                    } else if(point->height_<previousPointHeight){
                        break;
                    }
                }
                // If the rise on this route was higher than the highest rise before
                if(rise1 > rise2){
                    rise2 = rise1;
                    // Clears vector of all previous routes, as the current rise was higher.
                    risingRoutes.clear();
                    risingRoutes.push_back(iter->first);
                    // If the rise is equal to highest rise
                } else if(rise1 == rise2) {
                    // Also add this route to the vector, along with the equally big rise
                    risingRoutes.push_back(iter->first);
                }
            }
            if(rise2>0){
                std::cout<<"Greatest rise after point "<<point_name<<", "<<rise2<< " meters, is on route(s):"<<std::endl;
                for(unsigned int i = 0; i < risingRoutes.size(); i++){
                    std::cout<<" - "<<risingRoutes[i]<<std::endl;
                }
                // Point was not on any route (Doesn't exist.)
            } else if(!pointFound) {
                std::cout<<"Error: Point named "<<point_name<<" can't be found"<<std::endl;
            } else {
                std::cout<<"No route rises after point "<<point_name<<std::endl;
            }

}


