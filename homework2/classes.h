/*
 Name : Beyza Ozan
 Id : 150180056
 Date :20/04/2020
 */
#ifndef business_h
#define business_h

#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
using namespace std;

//****** PERSON ******
class Person
{
protected:
    string name;
    string surname;
public:
    Person(); // default constructor
    string getname() const{ return name; }
    string getsurname() const{ return surname; }
};
//****** OWNER *******
class Owner : public Person //derived class from person class
{
private:
    int ownership;
public :
    Owner();  // default constructor
    Owner(string name,string surname);  // constructor with parameters
    void set_ownership(int per){ ownership = per; }
};
//****** COURIER ******
class Courier : public Person //derived class from person class
{
private:
    string vehicle; // car ,motorcycle,bicycle
    Courier *next;
public:
    Courier();
    Courier(string name, string surname, string vehicle_type); // constructor with parameters
    Courier(const Courier &copied); //copy constructor
    bool operator==(const Courier& c);
    Courier* getnext() const{ return next; }
    void setnext(Courier* ptr) { next = ptr; }
    string getVehicle() const{ return vehicle; }
};
//****** BUSINESS ******
class Business
{
private:
    string Bname;
    string address;
    int numofOwners;
    double per;
public:
    Courier * head_c;
    Owner * head_o;
    Business(); //default constructor
    Business(string Bname,string address,Owner *owner_array,int num); // constructor with parameters
    ~Business(); //destructor
    void hire_courier(Courier &hiring);
    void fire_courier(Courier &fc);
    void  list_couriers() const;
    void list_owners() const;
    int calculate_shipment_capacity();
    void operator()() const;
    Courier & operator[](int x) const;
    
};

#endif /* business_h */
