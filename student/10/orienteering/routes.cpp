#include "routes.hh"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>


Routes::Routes()
{

}

Routes::~Routes()
{

}



void set_map_size(int width, int height){

}

void add_point(std::string& name, int x, int y, int height, char marker){
    std::map<std::string, Point*>::iterator iter = points_.find(name);
    if (iter != points_.end()){
        std::cout<<"Error: Points exists"<<std::endl;
        return
    }
    Point point = Point();
    point.name_ = name;
    point.x_ = x;
    point.y_ = y;
    point.height_ = height;
    point.marker_ = marker;
    points_.insert(name,point*);

}

bool connect_route(std::string& from, std::string& to, std::string& route_name){

}


void Routes::print_map() const {

}

void Routes::print_route_names() const
{

}

void Routes::print_points() const
{

}

void Routes::print_route(const std::string &name) const
{

}

void Routes::route_length(const std::string &name) const
{

}

void Routes::greatest_rise(const std::string &point_name) const
{

}

