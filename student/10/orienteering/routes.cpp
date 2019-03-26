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



void Routes::set_map_size(int width, int height){
mapHeight_ = height;
mapWidth_ = width;
}

void Routes::add_point(std::string& name, int x, int y, int height, char marker){
    std::map<std::string, Point*>::iterator iter = points_.find(name);
    if (iter != points_.end()){
        std::cout<<"Error: Points exists"<<std::endl;
        return;
    }
    Point *point = new Point();
    point->name_ = name;
    point->x_ = x;
    point->y_ = y;
    point->height_ = height;
    point->marker_ = marker;
    points_.insert(std::make_pair(name, point));

}

bool Routes::connect_route(std::string& from, std::string& to, std::string& route_name){

}


void Routes::print_map() const {
    bool found = false;
    std::cout<<" ";
    for (unsigned int a= 1; a <= mapWidth_;a++){
        if(a<10){
           std::cout<<"  "<<a;
        } else {
            std::cout<<" "<<a;
        }
        }
    std::cout<<"\n";
    for (unsigned int yPrint = 1; yPrint <= mapHeight_;yPrint++){
        if(yPrint<10){std::cout<<" "<<yPrint;
        } else {
            std::cout<<yPrint;
        }
        for (unsigned int xPrint = 1; xPrint < mapWidth_;xPrint++){
            bool found = false;
            for(auto iter = points_.begin(); iter != points_.end(); ++iter){
                if(iter->second->y_ == yPrint && iter->second->x_ == xPrint){
                    std::cout<<"  "<<iter-> second->marker_;
                    found = true;
                    continue;
                }
            }
            if (!found){
              std::cout<<"  .";
            }
        }
        std::cout<<'\n';
    }
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

