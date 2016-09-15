#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;
/*class Car{
	int position;
public:
	Car():position(0){};
	virtual void drive(){
		position += 1;
	}
};

class Taxi: public Car{
};
class Limo: public Car{
};
void startMeter(){std::cout<<"where to go"<<endl;}
class Channel{
public:
	static int connections;
};
int Channel::connections = 0;
class PriorityChannel:public Channel{
};
class NormalChannel:public Channel{
};
Channel ch;
NormalChannel chn1;
PriorityChannel chn2;
PriorityChannel &chef = chn2;
class R{
	public:
		virtual int getV(){return 0;}
		char getT(){return 'R';}
};
class V:public R{
	public:
		virtual int getV(){return 150;}
		char getT(){return 'V';}
};
class S:public R{
	public:
		virtual int getV(){return 50;}
		char getT(){return 'S';}
};
void showInfo(R* repos){
	cout<<repos->getT()<<repos->getV()<<endl;
}
class Person{
	string *namePtr;
public:
	Person(){namePtr = new string;}
	void setName(char *s){*namePtr = s;}
};
class XXX{
public:
	int memberFunc();
};
class YYY:public XXX{
public:
	int memberFunc();
};
class Fruit{
public:
	int weight;
	char season;
};
class Apple:public Fruit{
public:
	enum variety{Gala,Fuji,Granny};
	void setVariety(variety v){type = v;}
private:
	variety type;
};
class Orange:Fruit{
	enum use{Eating,Juice};
public:
	using Fruit::season;
	use type;
};*/
/*class Level1{
public:
	void func1();
};
class Level2:public Level1{
public:
	void func1()=delete;
	int func2(char);
};
class Level3 final:public Level2{
public:
	virtual double func3(int); //overriding non-deleted function ‘virtual double Level3::func3(int)’
};
class Level4:public Level2{
	virtual double func4(int);
	double func5(char a);
};
class Level5:public Level3{   //error: cannot derive from ‘final’ base ‘Level3’ in derived type ‘Level5’
public:
	double func2(char) override;  // ‘double Level5::func2(char)’ marked override, but does not override
	virtual double func3(int) = delete; //deleted function ‘virtual double Level5::func3(int)’
	virtual double func4(char) override; //‘virtual double Level5::func4(char)’ marked override, but does not override
};*/
/*int classCount = 0;
class Course{
	static int	classCount;    //C++ forbids in-class initialization of non-const static member ‘Course::classCount’
	string courseName{"CS101"};
	
	int quizzes[5] {0,0,0,0,0};
	public:
	int room = 100;
	Course(){};
	Course(int a):room(a){};
	Course(string b):courseName(b),room(200){};
	Course(double d):Course(static_cast<int>(d)){};
};*/
class WS{
public:
	virtual ~WS(){cleanup();}
	virtual void cleanup();
};
class PU:public WS{
public:
	void cleanup(){cout<<"PU clean"<<endl;}
};

int main(int argc,char* argv[]){
	/*Car c1;
	Taxi c2;
	Limo c3;
	Car *Cars[3] = {&c1,&c2,&c3};
	Car *cp;
	for(int i = 0;i < 3;i++){
		cp = Cars[i];
		if(typeid(*cp)== typeid(Taxi)){startMeter();}
		cp->drive();
	}*/
	//XXX *bptr = new YYY;
	//YYY *dptr;
	//int* arr = new int[10];
	//delete arr;
	//dptr = dynamic_cast<YYY*>(bptr);
	//dptr = up_cast<XXX*>(bptr);
	//dptr = dynamic_cast<XXX*>(bptr);
	//dptr = bptr;
	//dptr = static_cast<YYY*>(bptr);
	//Orange f1;
	//Apple f2;
	//f1.weight = 12;
	//f2.weight = 14;
	//f1.type = Orange::Juice;
	//f2.setVariety(Apple::Fuji);
	//Course course1{};
	//cout<<course1.room<<endl;
	//PU* pump = new PU;
	//delete pump;
	//char input[] = "sdfdsafa";
	//increment(input[3]);
	//Course course2{300};
	//Course course3{"English101"};
	//Course course4{3.14};
	return 0;
}

