/* @ozan18
Student Name: BEYZA OZAN
Student ID: 150180056
Date: 30.03.2020 */

#ifndef pizza_h
#define pizza_h

#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <string.h>

using namespace std;

//*************** PIZZA *******************
class Pizza{
    friend class Order_List;
private:
    string name;  // name of the pizza
    string size;  // "small" , "medium" or "big"
    string *ingredients; // string pointer which has ingredients
    string crust_type; // "thick" , "normal" , "thin"
    Pizza *next;
public:
    string get_name() const; //This method is required to use the name in private
    string get_size() const; //This method is required to use the size in private
    string get_crust_type() const; //This method is required to use the crust type in private
    string* get_ingredients() const; //This method is required to use the string pointer in private
    Pizza *get_next() const; //This method is required to use the next pointer in private
    void set_next(Pizza *pointer); // This method is required to put next
    Pizza(); // default constructor (no parameter)
    Pizza(string size,string crust_type,int pizza_type); // constructor with 3 parameters
    Pizza(const Pizza& Copied); // copy constructor to copy pizzas and update ingredients
    ~Pizza(); //destructor
    
};

//************** ORDER *********************
class Order{
private:
    string customer; // name of customer
    Pizza *head_pizza;
    Order *next;
    int *drinks;//"Cola","Soda","Ice tea","Fruit juice"
public:
    string get_customer() const{ return customer; } //getter method
    Pizza* get_head_pizza() const{ return head_pizza; } //getter method
    void set_head_pizza(Pizza* newh){ head_pizza = newh; }
    Order* get_next() const{ return next; } //getter method
    void set_next(Order *pointer){ next = pointer; } //setter method
    Order(string customer,Pizza *p_pizza,int* drinks); //constructor with 3 parameter
    Order(string customer,Pizza *p_pizza); //constructor with 2 parameter ->no drinks
    double getPrice() const;
    void printOrder() const;
    ~Order(); //destructor
    
};
//************ ORDER LIST ******************
class OrderList{
private:
    int n; // number of orders
    Order *head_order;
public:
    void set_head_order(Order *head_p){ head_order = head_p; }
    OrderList(); // default constructor
    void takeOrder();
    void listOrders();
    void deliverOrders();
    void my_main();
    ~OrderList(); // destructor
};

Pizza::Pizza() // Default constructor
{
    ingredients = new string[1]; // allocate memory
    size = "medium";
    crust_type = "normal";
    ingredients[0] = "mozarella";
}

Pizza::Pizza(string size,string crust_type,int pizza_type) // Constructor with 3 parameter
{
    this->size = size; // using this pointer to prevent name confuion
    this->crust_type = crust_type;
    ingredients = new string[7]; // allocate memory
    ingredients[6] = "\0";
    ingredients[0] = "mozarella";
    if(pizza_type == 1){
        name = "chicken Pizza";
        ingredients[1] = "chicken";
        ingredients[2] = "mushroom";
        ingredients[3] = "corn";
        ingredients[4] = "onion";
        ingredients[5] = "tomato";
    }
    else if(pizza_type == 2){
        name = "broccoli Pizza";
        ingredients[1] = "broccoli";
        ingredients[2] = "pepperoni";
        ingredients[3] = "olive";
        ingredients[4] = "corn";
        ingredients[5] = "onion";
    }
    else if(pizza_type == 3){
        name = "sausage Pizza";
        ingredients[1] = "sausage";
        ingredients[2] = "tomato";
        ingredients[3] = "olive";
        ingredients[4] = "mushroom";
        ingredients[5] = "corn";
    }
    
}

Pizza::Pizza(const Pizza& Copied) //Copy Constructor : create new pizza as copy the given parameter
{   int removed;
    name = Copied.get_name();
    size = Copied.get_size();
    crust_type = Copied.crust_type;
    this->ingredients = new string[7];
    this->ingredients[6] = "\0";
    for(int i=0;i<6;i++){
        this->ingredients[i] = Copied.get_ingredients()[i];
    }
    cout<<"Please enter the number of the ingredient you want to remove from your pizza."<<endl;
    if(name == "chicken Pizza"){
    cout<<"1. mozarella"<<endl;
    cout<<"2. chicken"<<endl;
    cout<<"3. mushroom"<<endl;
    cout<<"4. corn"<<endl;
    cout<<"5. onion"<<endl;
    cout<<"6. tomato"<<endl;
    }
    else if(name == "broccoli Pizza"){
        cout<<"1. mozarella"<<endl;
        cout<<"2. broccoli"<<endl;
        cout<<"3. pepperoni"<<endl;
        cout<<"4. olive"<<endl;
        cout<<"5. corn"<<endl;
        cout<<"6. onion"<<endl;
    }
    else if(name == "sausage Pizza"){
        cout<<"1. mozarella"<<endl;
        cout<<"2. sausage"<<endl;
        cout<<"3. tomato"<<endl;
        cout<<"4. olive"<<endl;
        cout<<"5. mushroom"<<endl;
        cout<<"6. corn"<<endl;
    }
    cout<<"Press 0 to save it."<<endl;
    
    cin>>removed;
    while(removed != 0){ // deletes the ingredients that the user doesnt want
        if(removed > 6 or removed < 0)
            cout<<"invalid number, try again :"<<endl;
        else
            ingredients[removed-1] = "DELETED";
        cin>>removed;
    }
}
Pizza::~Pizza() // Destructor of Pizza : deletes allocated memories to avoid memory loss
{
    delete[] ingredients;
    next = NULL;
}
string Pizza::get_name() const{ return name; }
string Pizza::get_size() const{ return size; }
string Pizza::get_crust_type() const{ return crust_type; }
string* Pizza::get_ingredients() const{ return ingredients; }
Pizza* Pizza::get_next() const{ return next; }
void Pizza::set_next(Pizza *pointer){ next = pointer; }


Order::Order(string customer, Pizza *p_pizza, int *drinks) //Constructor with 3 parameter
{   this->drinks = new int[5]; // allocate memory
    this->customer = customer;
    head_pizza = p_pizza;
    for(int i=0;i<5;i++)
        this->drinks[i] = drinks[i];
    next = NULL;
}

Order::Order(string customer,Pizza *p_pizza) //Constructor with 2 parameter ->no drinks
{
    head_pizza = p_pizza;
    this->customer = customer;
    drinks = NULL;
    next = NULL;
}

double Order::getPrice() const// calculates how much pizzas cost and returns this double value
{   Pizza *traverse = head_pizza;
    int how_many = 0;
    double drinks_cost = 0;
    if(drinks !=NULL) // if there is a drink(s)
        drinks_cost = drinks[0]*4.0 + drinks[1]*2.0 + drinks[2]*3.0 + drinks[3]*3.5;
    while(traverse != NULL){ // while find the number of the pizza
        traverse = traverse->get_next();
        how_many++;
    }
    if(head_pizza -> get_size() == "small")
        return ((how_many * 15.0) + drinks_cost);
    else if(head_pizza -> get_size() == "medium")
            return ((how_many * 20.0) + drinks_cost);
    else if(head_pizza -> get_size() == "big")
                return ((how_many * 25.0) + drinks_cost);
    return 0.0;
}
void Order::printOrder() const
{
    string drinks_name[6] ={" "," cola"," soda"," ice tea"," fruit juice"};
    Pizza *traverse = head_pizza;
    int i=0;
    cout<<"------------"<<endl;
    cout<<"Name: "<<customer<<endl<<endl;
    while(traverse){
        cout<<traverse->get_name()<<"(";
        i=0;
    while(traverse->get_ingredients()[i] !="\0"){ // prints ingredients of pizza
            if(traverse->get_ingredients()[i]!="DELETED")
                cout<<traverse->get_ingredients()[i]<<", ";
            i++;
        }
        cout<<")"<<endl;
        cout<<"size: "<<traverse->get_size()<<", crust: "<<traverse->get_crust_type()<<endl;
        traverse = traverse -> get_next();
    }
    cout<<endl;
    
    if(drinks) {
        for(int i = 1;i < 5;i++){ // prints drinks name and how many
            if(drinks[i] > 0)
                cout<<drinks[i]<<drinks_name[i]<<", ";
        }
    }
    cout<<endl<<"------------"<<endl;
}
Order::~Order() // Destructor of Order
{
    Pizza *temp = head_pizza;
    while(temp){ // delete all pizzas which taken up space in memory
        head_pizza = head_pizza -> get_next();
        delete temp;
        temp = head_pizza;
    }
    delete[] drinks;
}
//****** ORDER LIST *********
OrderList::OrderList() // Default constructor
{
    n = 0; // number of orders
    head_order = NULL; // first order is null
}
void OrderList::takeOrder() // takes the size ,the type ,the number of pizza and drinks from the user
{
    int pizza_choice;
    int drink_choice =1;
    int num_of_pizza;
    string size;
    string crust_type;
    string name;
    Pizza *traverse;
    Order *otraverse;
    Pizza *ph; // first pizza
    int *drinkss = new int[5];
    for(int i=0;i<5;i++)
        drinkss[i]=0;
    
    
    cout<<"Pizza Menu"<<endl;
    cout<<"1. Chicken Pizza (mozarella, chicken, mushroom, corn, olive, onion, tomato)"<<endl
    <<"2. Broccoli Pizza (mozarella, broccoli, pepperoni, olive, corn, onion)"<<endl
    <<"3. Sausage Pizza (mozarella, sausage, tomato, olive, mushroom, corn)"<<endl
    <<"0. Back to main menu"<<endl;
    cin>>pizza_choice;
    if(pizza_choice > 3 or pizza_choice < 0){
        cout <<"invalid value ,try again! "<<endl;
        takeOrder();
        return;
    }
    else if(pizza_choice == 0){
        my_main();
        return;
    }
    cout<<"Select size: small (15 TL), medium (20 TL), big (25 TL)"<<endl;
    cin>>size;
    while(size !="small" and size !="medium" and size !="big"){
        cout<<"Error! Invalid choice ,try again :"<<endl;
        cin>>size;
    }
    cout<<"Select crust type: thin, normal, thick"<<endl;
    cin>>crust_type;
    while(crust_type !="thin" and crust_type !="normal" and crust_type !="thick"){
        cout<<"Error! Invalid choice ,try again :"<<endl;
        cin>>crust_type;
    }
    ph = new Pizza(size,crust_type,pizza_choice);// PIZZA CREATED
    traverse = ph;

    cout<<"Enter the amount:";
    cin>>num_of_pizza; // COPY PIZZAS
    if(num_of_pizza > 1){
        for(int i=0; i<num_of_pizza-1; i++){
            Pizza *one_more = new Pizza(*ph);// called copy constructor and create copied pizzas
            traverse -> set_next(one_more);
            traverse = traverse -> get_next();
        }
    }

    cout<<"Please choose a drink:"<<endl;
    cout<<"0. no drink"<<endl;
    cout<<"1. cola 4 TL"<<endl;
    cout<<"2. soda 2 TL"<<endl;
    cout<<"3. ice tea 3 TL"<<endl;
    cout<<"4. fruit juice 3.5 TL"<<endl;
    cout<<"Press -1 for save your order"<<endl;
    cin>>drink_choice;
    if(drink_choice == 0)
        drinkss[0] =1;
    else{
        while(drink_choice != -1){
            if(drink_choice > 4 or drink_choice < -1)
                cout<<"invalid number , try again :"<<endl;
            else
                drinkss[drink_choice]++;
            cin>>drink_choice;
        }
    }

    cout<<"Please enter your name:"<<endl;
    cin>>name;
    Order *myOrder;
    if(drinkss[0] == 1)
        myOrder = new Order(name,ph); // ORDER (without drink) CREATED
    else {
        myOrder = new Order(name,ph,drinkss); // ORDER (with drink) CREATED
    }
    myOrder->set_next(NULL);
    otraverse = head_order;
    
    if(head_order == NULL){
        head_order = myOrder;
        n++;
    }
    else{
        while(otraverse -> get_next())
            otraverse = otraverse -> get_next();

        otraverse -> set_next(myOrder);
        n++;
    }
    
    cout<<"Your order is saved, it will be delivered when it is ready..."<<endl;
    my_main();
    
}
void OrderList::listOrders()
{   if(head_order == NULL){ // if there is not even one order
        cout<<"empty"<<endl;
        return ;
    }
    Order *traverse = head_order;
    for(int i=1;i<=n;i++){ // print all order by using printOrder() function
        cout<<i<<endl;
        traverse->printOrder();
        traverse = traverse->get_next();
    }
}
void OrderList::deliverOrders()
{   char yes[2] = "y",no[2] = "n";
    char yesno[2];
    string name;
    string pro_code;
    string real_code ="I am a student";
    Order *traverse = head_order;
    Order *tail = head_order; // behind of traverse
    
    listOrders();
    traverse = head_order;
    if(traverse == NULL) //hiç sipariş yoksa deliver orders fonksiyonundan çıksın.
        return my_main();
    cout<<"Please write the customer name in order to deliver his/her order: ";
    cin>>name;
    
    while(traverse and traverse->get_customer() != name){  // searches order the user wants until find
        tail = traverse;
        traverse = traverse -> get_next();
    }
    if(!traverse){ // if can not find an order matching user's name
        cout<<"Wrong name"<<endl;
        return my_main();
    }
    cout<<"Following order is delivering..."<<endl;
    if(traverse->get_customer() == name){ // if find an order matching user's name
        traverse->printOrder();
        cout<<"Total price: "<<traverse->getPrice()<<endl;
        cout<<"Do you have a promotion code? (y/n)"<<endl;
        cin>>yesno;
        if(strcmp(yesno,yes) == 0){
            
            do {
                cout<<"Enter the promotion code: ";
                getchar();
                getline(cin,pro_code);
                if(pro_code.compare(real_code)==0){ // if the entered value matches with promotion code
                    cout<<"Discounted price: "<< (traverse->getPrice())*0.9<<endl; // %10 discount
                    break;
                }
                else // if promotion code is wrong
                    cout<<"Promotion code is not accepted."<<endl;
                cout<<"Do you have a promotion code? (y/n)"<<endl;
                cin>>yesno;
            }
            while(strcmp(yesno,yes) == 0);

        }
        cout<<"The order is delivered successfully!"<<endl<<endl;
    }

    if(traverse == head_order) {// if the removed one is head order
        if(traverse->get_next()) // unless there is just one order
            head_order = head_order->get_next();
        else
            head_order = NULL;
    }
    else {
        tail->set_next( traverse->get_next() );
        traverse->set_next(NULL); // break the delivered orders from the other orders
    }
    n--;
    Pizza *temp = traverse->get_head_pizza();
    while(temp){ // delete all pizzas which taken up space in memory
        traverse->set_head_pizza(temp -> get_next());
        delete temp;
        temp = traverse->get_head_pizza();
    }
    delete traverse; // deletes the delivered order
    my_main();
}
OrderList::~OrderList() //Destructor of OrderList
{
    Order *temp = head_order;
    while(temp){ // delete all the orders
        head_order = head_order->get_next();
        delete temp;
        temp = head_order;
    }
}
void OrderList::my_main() // we need this function to return main menu whenever we need
{
    int choice;
    cout <<"Welcome "<<endl;
    cout <<"1. Add an order"<<endl;
    cout <<"2. List orders"<<endl;
    cout <<"3. Deliver order"<<endl;
    cout <<"4. Exit"<<endl;
    cout <<"Choose what to do: ";
    cin>>choice;
    if(choice == 1)
        takeOrder();
    
    else if(choice == 2){
        listOrders();
        my_main();
    }
    else if(choice == 3)
        deliverOrders();

    else if(choice == 4)
        cout<<"Goodbye..."<<endl;
    else{
        cout<<"Invalid number! please try again"<<endl;
        my_main();
        return;
    }
}
#endif /* pizza_h */
