/*
Name : Beyza Ozan
Id : 150180056
Date :20/04/2020
*/

//******METHODS*******

#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include "classes.h"
#include "main.cpp"

using namespace std;

Person::Person(){ // default constructor of base class
    name = "null";
    surname = "null";
}
Owner::Owner():Person(){} // default constructor of derived class

Owner::Owner(string name,string surname){ //constructor with two parameter
    this->name = name;
    this->surname = surname;
}
Courier::Courier():Person(){ // default constructor of derived class
    vehicle = "null";
}
Courier::Courier(string name, string surname, string vehicle_type){ //constructor with three parameter
    this->name = name;
    this->surname = surname;
    vehicle = vehicle_type;
}
Courier::Courier(const Courier &copied){ // copy constructor of derived class
    this->name = copied.name;
    this->surname = copied.surname;
    this->vehicle = copied.vehicle;
    
}
bool Courier::operator==(const Courier &c) // overload operator ==
{
    
    if(!(this->vehicle.compare(c.vehicle)) && !(this->name.compare(c.name))  && !(this->surname.compare(c.surname)))
        return true;
    else
        return false;
}
Business::Business(){ //  default constructor
    Bname ="null";
    address ="null";
}
Business::Business(string Bname,string address,Owner *owner_array,int num){// constructor with parameters
    head_o = owner_array;
    head_c = NULL;
    this->Bname = Bname;
    this->address = address;
    numofOwners = num;
    per = 100.0 /num;
    for(int i=0;i<num;i++){
       owner_array[i].set_ownership(per);
    }
}
Business::~Business(){ // destructor
}
void Business::hire_courier(Courier &hc){
    Courier * traverse = head_c;
    hc.setnext(NULL);
    if(traverse == NULL) // if there is no courier before
        head_c = &hc;
    else {
        while(traverse->getnext() != NULL)
            traverse = traverse->getnext(); // traverse is traversing until reach end of the list
        traverse->setnext(&hc); // adding to the end of the list
    }
}
void Business::fire_courier(Courier &fc){
    Courier * searched = head_c;
    Courier * tail = head_c;

    if(fc.getname()=="invalid"){
        cout<<"not found the courier"<<endl;
        return;
    }
    if(*head_c == fc){ // if the firing courier is head of the nodes.
        head_c = head_c->getnext();
        searched = NULL;
        return;
    }
    while(searched and !(fc == *searched)){ // written == overload operator
        tail = searched;
        searched = searched->getnext();
    }
    if(!searched){
        cout << "ERROR "<<endl;
        return;
    }
    tail->setnext(searched->getnext());
    searched->setnext(NULL);
    searched= NULL;
}
void Business::list_couriers() const{
    Courier * traverse = head_c;
    if(!traverse){
        cout << "list is empty"<<endl;
        return;
    }
    while(traverse){ // print all the traversing couriers
        cout << traverse->getname() <<" "<< traverse->getsurname() <<" "<<traverse->getVehicle()<<endl;
        traverse = traverse->getnext();
    }
}
void Business::list_owners() const{
    for(int i=0;i<numofOwners;i++){
        cout << head_o[i].getname()<<" "<< head_o[i].getsurname()<<" "<<per<<endl;
    }
}
int Business::calculate_shipment_capacity(){
    Courier * traverse = head_c;
    string V = " ";
    int total = 0;
    while(traverse){
        V = traverse->getVehicle()[0];
        if(V == "c") // if vehicle is car
            total += 200;
        else if(V == "m") // if vehicle is motorcycle
            total += 35;
        else if(V== "b") // if vehicle is bcycle
            total += 10;
        traverse = traverse->getnext();
    }
    return total;
}
void Business::operator()() const // list all information about the business
{
    cout << Bname <<" "<< address <<endl;
    list_owners();
    list_couriers();
}
Courier & Business::operator[](int x) const // returns courier with the given index
{
    Courier* traverse = head_c;
    Courier *invalid = new Courier("invalid","",""); // for invalid index , return empty courier object
    if(head_c == NULL){ // invalid index
        return *invalid;
    }
    for(int i =0; i<x; i++){
        traverse = traverse->getnext();
        if(traverse == NULL)
            return *invalid;
    }
    return *traverse;
}
