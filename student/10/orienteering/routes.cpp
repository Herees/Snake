#include "routes.hh"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>


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
    std::vector<std::string> a;
    bool foundFrom = false;
    bool foundTo = false;
    for(auto iter = points_.begin(); iter != points_.end(); ++iter){
        if(iter->second->name_ == from){
            foundFrom = true;
            continue;
        }
        if(iter->second->name_ == to){
            foundTo = true;
            continue;
        }
    }
        if (foundFrom && foundTo){
            auto iter2 = allRoutes.find(route_name);
            if(iter2 == allRoutes.end()){
               allRoutes.insert(std::make_pair(route_name, a));
               allRoutes.at(route_name).push_back(from);
               allRoutes.at(route_name).push_back(to);
            } else {
               allRoutes.at(route_name).push_back(to);
            }
            /** points_.at(to)->to_.insert(std::make_pair(route_name, points_.at(to)));
            points_.at(from)->from_.insert(std::make_pair(route_name, points_.at(from)));
            if (std::find(allRoutes.begin(), allRoutes.end(), route_name) == allRoutes.end()){
                allRoutes.push_back(route_name);**/

            return true;
        } else {
            return false;
        }
}


void Routes::print_map() const {
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
    for (int yPrint = 1; yPrint <= mapHeight_;yPrint++){
        if(yPrint<10){std::cout<<" "<<yPrint;
        } else {
            std::cout<<yPrint;
        }
        for (int xPrint = 1; xPrint < mapWidth_;xPrint++){
            found = false;
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
std::cout<<"Routes:"<<std::endl;
    for(auto iter = allRoutes.begin(); iter != allRoutes.end(); ++iter){
    std::cout<<" - "<<iter->first<<std::endl;
        }
}

void Routes::print_points() const
{

}

void Routes::print_route(const std::string &name) const {
    for(auto iter = allRoutes.begin(); iter != allRoutes.end(); ++iter){
        if(iter->first == name){
            std::cout<<iter->second[0]<<std::endl;
            for(unsigned int i = 1; i < iter->second.size(); i++){
                std::cout<<" -> "<<iter->second[i]<<std::endl;
            }
            break;
            }
        }
    }

void Routes::route_length(const std::string &name) const
{

}

void Routes::greatest_rise(const std::string &point_name) const
{

}

