#include "player.hh"
#include <string>
#include <iostream>
Player::Player(std::string Player){
    name_ = Player;
}
std::string Player::get_name(){
return name_;
}

int Player::get_points(){
return points_;
}

void Player::add_points(int a){
    points_ += a;
            if(points_ > 50){
            points_ = 25;
std::cout << name_ <<" gets penalty points!"  << std::endl;
}
}
bool Player::has_won(){
    if(Player::points_==50){
        return true;
    }
        return false;
    }

