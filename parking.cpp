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
    VehicleSize size;
    VehicleSize spot;
    int ind;
    int lvl;
public:
    VehicleSize get_size(){return size;}
    VehicleSize spot_size(){return spot;}
    int get_spot(){return ind;}
    int get_level(){return lvl;}
    void park_vehicle(int level,int pos,VehicleSize s){
        ind = pos;
        lvl = level;
        spot = s;
    }
};

class Bus: public Vehicle {
    // Write your code here
public:
    Bus(){
        size = VehicleSize::Large;
        lvl = -1;
        ind = -1;
    }
};

class Car: public Vehicle {
    // Write your code here
public:
    Car(){
        size = VehicleSize::Compact;
        lvl = -1;
        ind = -1;
    }
};

class Motorcycle: public Vehicle {
    // Write your code here
public:
    Motorcycle(){
        size = VehicleSize::Motorcycle;
        ind = -1;
        lvl = -1;
    }
};

class Level {
    // Write your code here
private:
    int rows,spots_row;
public:
    vector<vector<int> > motorspots;
    vector<vector<int> > carspots;
    vector<vector<int> > busspots;
    Level(int numrows,int spots_per_row){
		rows = numrows;
		spots_row = spots_per_row;
        motorspots.resize(numrows);
        carspots.resize(numrows);
        busspots.resize(numrows);
        int motor_size = spots_per_row/4;
        int car_size = 2*motor_size;
        int bus_size = spots_per_row - 3*motor_size;
        for(auto& m:motorspots)m = vector<int>(motor_size,0);
        for(auto& c:carspots)c = vector<int>(car_size,0);
        for(auto& b:busspots)b = vector<int>(bus_size,0);
    }
    
    int canpark(Vehicle &v,VehicleSize spot,int num){
        if(spot==VehicleSize::Motorcycle){
            for(int i = 0;i < rows;i++){
                for(int j = 0;j < motorspots[i].size();j++){
                    if(motorspots[i][j]==0)return i*motorspots[i].size()+j; 
                }
            }
            return -1;
        }else if(spot==VehicleSize::Compact){
            for(int i = 0;i < rows;i++){
                for(int j = 0;j < carspots[i].size();j++){
                    if(carspots[i][j]==0)return i*carspots[i].size()+j; 
                }
            }
            return -1;
        }else{
            for(int i = 0;i < rows;i++){
                for(int j = 0;j <= (int)busspots[i].size()-num;j++){
                    if(busspots[i][j]==0){
                        bool flag = true;
                        for(int k = j+1;k < j+num;k++){
                            if(busspots[i][k]!=0){
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
    
    void parkVehicle(Vehicle &v,VehicleSize spot,int num,int index,int lvl){
        if(spot==VehicleSize::Motorcycle){
            motorspots[index/motorspots[0].size()][index%motorspots[0].size()] = 1;
        }else if(spot==VehicleSize::Compact){
            carspots[index/carspots[0].size()][index%carspots[0].size()] = 1;
        }else{
            for(int i = 0;i <num;i++)busspots[index/busspots[0].size()][index%busspots[0].size()+i] = 1;
        }
        v.park_vehicle(lvl,index,spot);
    }
    
     void unparkVehicle(Vehicle &v){
        VehicleSize spot = v.spot_size();
        int num = 1;
        if(v.get_size()==VehicleSize::Large)num = 5;
        int index = v.get_spot();
        if(spot==VehicleSize::Motorcycle){
            motorspots[index/motorspots[0].size()][index%motorspots[0].size()] = 0;
        }else if(spot==VehicleSize::Compact){
            carspots[index/carspots[0].size()][index%carspots[0].size()] = 0;
        }else{
            for(int i = 0;i <num;i++){
                busspots[index/busspots[0].size()][index%busspots[0].size()+i] = 0;
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
        VehicleSize size = vehicle.get_size();
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
            index = lvls[i]->canpark(v,VehicleSize::Motorcycle,1);
            if(index != -1){
                lvls[i]->parkVehicle(v,VehicleSize::Motorcycle,1,index,i);
                return true;
            }
        }
        return false;
        
    }
    bool parkInCompact(Vehicle &v){
        int index = -1;
        for(int i = 0;i <lvls.size();i++){
            index = lvls[i]->canpark(v,VehicleSize::Compact,1);
            if(index != -1){
                lvls[i]->parkVehicle(v,VehicleSize::Compact,1,index,i);
                return true;
            }
        }
        return false;
        
    }
    bool parkInBus(Vehicle &v,int num){
        int index = -1;
        int i;
        for(i = 0;i <lvls.size();i++){
            index = lvls[i]->canpark(v,VehicleSize::Large,num);
            if(index != -1){
                lvls[i]->parkVehicle(v,VehicleSize::Large,num,index,i);
                return true;
            }
        }
        return false;
        
    }
    // unPark the vehicle
    void unParkVehicle(Vehicle &vehicle) {
        int i = vehicle.get_level();
        if(lvls[i])lvls[i]->unparkVehicle(vehicle);
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
