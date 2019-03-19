#include <iostream>
#include "queue.hh"
using namespace std;
Queue::Queue(unsigned int cycle){
cycle_ = cycle;
}

void Queue::enqueue(string reg){
    if (is_green_){
        cout << "GREEN: The vehicle " << reg << " need not stop to wait" << endl;
        return;
    }
    Vehicle* nextVehicle = new Vehicle{reg, nullptr};
    if(first_ != nullptr) {
        Vehicle* now = first_;
        while(now->next != nullptr) {
            now = now->next;
        }
        now ->next = nextVehicle;
    } else {
            first_=nextVehicle;
        }
    last_= nextVehicle;
}

void Queue::print(){
    Vehicle* nextVehicle = first_;
    string light = "";
            if (is_green_) {
            light = "GREEN:";
            } else {
            light = "RED:";
            }
            if(nextVehicle == nullptr) {
            cout << light << " No vehicles waiting in traffic lights" << endl;
            return;
}

            cout << light << " Vehicle(s) ";
    if(is_green_){
        unsigned int i = 0;
        while(nextVehicle != nullptr and i < cycle_) {
            i++;
            cout << nextVehicle->reg_num << " ";
            nextVehicle = nextVehicle->next;
        }
    } else {
        while(nextVehicle != nullptr) {
            cout << nextVehicle->reg_num << " ";
            nextVehicle = nextVehicle->next;
        }
    }

    if (is_green_){
        cout<<"can go on"<<endl;
    } else {
        cout<<"waiting in traffic lights"<<endl;
    }
}

void Queue::switch_light(){

}

void Queue::reset_cycle(unsigned int cycle){

}

Queue::~Queue() {

}

