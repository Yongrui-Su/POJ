#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;
// enum type for Vehicle
enum class VehicleSize {
    Motorcycle,
    Compact,
    Large
};

class Vehicle {
    // Write your code here
protected:
    VehicleSize s;
public:
    virtual VehicleSize size(){return s;}
};

class Bus: public Vehicle {
    // Write your code here
public:
    Bus(){s = VehicleSize::Large;}

    
    //int tag(){return t;}
};

class Car: public Vehicle {
    // Write your code here
public:
    Car(){s = VehicleSize::Compact;}
};

class Motorcycle: public Vehicle {
    // Write your code here
public:
    Motorcycle(){s = VehicleSize::Motorcycle;}
};

class Level {
    // Write your code here
private:
    vector<vector<Vehicle*> > motorspots;
    vector<vector<Vehicle*> > carspots;
    vector<vector<Vehicle*> > busspots;
    unordered_map<Vehicle*,pair<VehicleSize,int> > level2spot;
    int rows,spots_row;
public:
    Level(int numrows,int spots_per_row){
        motorspots.resize(numrows);
        carspots.resize(numrows);
        busspots.resize(numrows);
        int motor_size = spots_per_row/4;
        int car_size = 2*motor_size;
        int bus_size = spots_per_row - 3*motor_size;
        for(auto& m:motorspots)m.resize(motor_size);
        for(auto& c:carspots)c.resize(car_size);
        for(auto& b:busspots)b.resize(bus_size);
        this->rows = numrows;
        this->spots_row = spots_per_row;
    }
    
    int canpark(Vehicle *v,VehicleSize spottype,int num){
        if(spottype==VehicleSize::Motorcycle){
            for(int i = 0;i < rows;i++){
                for(int j = 0;j < motorspots[i].size();j++){
                    if(motorspots[i][j]==NULL)return i*motorspots[i].size()+j; 
                }
            }
            return -1;
        }else if(spottype==VehicleSize::Compact){
            for(int i = 0;i < rows;i++){
                for(int j = 0;j < carspots[i].size();j++){
                    if(carspots[i][j]==NULL)return i*carspots[i].size()+j; 
                }
            }
            return -1;
        }else{
            for(int i = 0;i < rows;i++){
                for(int j = 0;j <= (int)busspots[i].size()-num;j++){
                    if(busspots[i][j]==NULL){
                        bool flag = true;
                        for(int k = j+1;k < j+num;k++){
                            if(busspots[i][k]!=NULL){
                                flag = false;
                            }
                        }
                        if(flag)return i*busspots[i].size()+j;
                    }
                }
            }
            return -1;
        }
        return -1;
    }
    
    void parkVehicle(Vehicle *v,VehicleSize spottype,int num,int index){
        if(spottype==VehicleSize::Motorcycle){
            motorspots[index/motorspots[0].size()][index%motorspots[0].size()] = v;
        }else if(spottype==VehicleSize::Compact){
            carspots[index/carspots[0].size()][index%carspots[0].size()] = v;
        }else{
            for(int i = 0;i <num;i++)busspots[index/busspots[0].size()][index%busspots[0].size()+i] = v;
        }
        level2spot[v] = {spottype,index};
    }
    
    void unparkVehicle(Vehicle *v){
        VehicleSize spottype = level2spot[v].first;
        int index = level2spot[v].second;
        if(spottype==VehicleSize::Motorcycle){
            motorspots[index/motorspots[0].size()][index%motorspots[0].size()] = NULL;
        }else if(spottype==VehicleSize::Compact){
            carspots[index/carspots[0].size()][index%carspots[0].size()] = NULL;
        }else{
            for(int i = index%busspots[0].size();i <busspots[0].size();i++){
                if(busspots[index/busspots[0].size()][i] == v){
                    busspots[index/busspots[0].size()][i] = NULL;
                }else break;
            }
        }
    }
};

class ParkingLot {
public:
    // @param n number of leves
    // @param num_rows  each level has num_rows rows of spots
    // @param spots_per_row each row has spots_per_row spots
    vector<Level*> lvls;
    unordered_map<Vehicle*,int> vehicle2lvl;
    ParkingLot(int n, int num_rows, int spots_per_row) {
        // Write your code here
        for(int i = 0;i < n;i++){
            Level* lvl = new Level(num_rows,spots_per_row);
            lvls.push_back(lvl);
        }
    }
    
     ~ParkingLot() {
        // Write your code here
        for(int i = 0;i < lvls.size();i++){
            delete lvls[i];
        }
    }

    // Park the vehicle in a spot (or multiple spots)
    // Return false if failed
    bool parkVehicle(Vehicle &vehicle) {
        // Write your code here
        VehicleSize size = vehicle.size();
        if(size == VehicleSize::Motorcycle){
            if(!parkInMotor(vehicle)){
                if(!parkInCompact(vehicle)){
                    return parkInBus(vehicle,1);
                }
            }
            return true;
        }else if(size == VehicleSize::Compact){
            if(!parkInCompact(vehicle)){
                return parkInBus(vehicle,1);
            }
            return true;
        }else{
            return parkInBus(vehicle,5);
        }
    }
    bool parkInMotor(Vehicle &v){
        int index = -1;
        for(int i = 0;i <lvls.size();i++){
            index = lvls[i]->canpark(&v,VehicleSize::Motorcycle,1);
            if(index != -1){
                lvls[i]->parkVehicle(&v,VehicleSize::Motorcycle,1,index);
                vehicle2lvl[&v] = i;
                return true;
            }
        }
        return false;
        
    }
    bool parkInCompact(Vehicle &v){
        int index = -1;
        for(int i = 0;i <lvls.size();i++){
            index = lvls[i]->canpark(&v,VehicleSize::Compact,1);
            if(index != -1){
                lvls[i]->parkVehicle(&v,VehicleSize::Compact,1,index);
                vehicle2lvl[&v] = i;
                return true;
            }
        }
        return false;
        
    }
    bool parkInBus(Vehicle &v,int num){
        int index = -1;
        int i;
        for(i = 0;i <lvls.size();i++){
            index = lvls[i]->canpark(&v,VehicleSize::Large,num);
            if(index != -1){
                lvls[i]->parkVehicle(&v,VehicleSize::Large,num,index);
                vehicle2lvl[&v] = i;
                return true;
            }
        }
        return false;
        
    }
    // unPark the vehicle
    void unParkVehicle(Vehicle &vehicle) {
        int i = vehicle2lvl[&vehicle];
        if(lvls[i])lvls[i]->unparkVehicle(&vehicle);
    }
};
int main(){
	ParkingLot lot(1,1,14);
	Motorcycle Moto_1;
	Motorcycle Moto_2;
	Motorcycle Moto_3;
	Motorcycle Moto_4;
	Car car_1;
	Car car_2;
	Car car_3;
	Car car_4;
	Car car_5;
	Car car_6;
	Car car_7;
	Bus bus_1;
	if(lot.parkVehicle(Moto_1))cout<<"true"<<endl;
	else cout<<"false"<<endl;
	if(lot.parkVehicle(Moto_2))cout<<"true"<<endl;
	else cout<<"false"<<endl;
	if(lot.parkVehicle(Moto_3))cout<<"true"<<endl;
	else cout<<"false"<<endl;
	if(lot.parkVehicle(car_1))cout<<"true"<<endl;
	else cout<<"false"<<endl;
	if(lot.parkVehicle(car_2))cout<<"true"<<endl;
	else cout<<"false"<<endl;
	if(lot.parkVehicle(car_3))cout<<"true"<<endl;
	else cout<<"false"<<endl;
	if(lot.parkVehicle(Moto_4))cout<<"true"<<endl;
	else cout<<"false"<<endl;
	if(lot.parkVehicle(car_4))cout<<"true"<<endl;
	else cout<<"false"<<endl;
	if(lot.parkVehicle(car_5))cout<<"true"<<endl;
	else cout<<"false"<<endl;
	if(lot.parkVehicle(car_6))cout<<"true"<<endl;
	else cout<<"false"<<endl;
	if(lot.parkVehicle(car_7))cout<<"true"<<endl;
	else cout<<"false"<<endl;
	if(lot.parkVehicle(bus_1))cout<<"true"<<endl;
	else cout<<"false"<<endl;
	lot.unParkVehicle(car_1);
	lot.unParkVehicle(car_3);
	lot.unParkVehicle(car_6);
	lot.unParkVehicle(Moto_4);
	if(lot.parkVehicle(bus_1))cout<<"true"<<endl;
	else cout<<"false"<<endl;
	lot.unParkVehicle(car_7);
	if(lot.parkVehicle(bus_1))cout<<"true"<<endl;
	else cout<<"false"<<endl;
	return 0;
}
