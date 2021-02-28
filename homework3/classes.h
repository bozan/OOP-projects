/* @ozan18
Student Name: BEYZA OZAN
Student ID: 150180056
Date: 12.05.2020 */

#ifndef classes_h
#define classes_h

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <stdlib.h>
using namespace std;

void d(int x){
    cout<<"DEBUG :"<< x <<endl;
}

//***  ACTIVATION FUNCTIONS ***

float Sigmoid(float x){
    return 1 / (1 + exp(-x));
}
float Tanh(float x){
    return ( exp(x) - exp(-x) ) / ( exp(x) + exp(-x) );
}
float ReLu(float x){
    return fmaxf(0.0,x);
}
float LReLu(float x){
    return  fmaxf((0.1 * x), x);
}

//****** CLASSES******

class Neuron { // abstract base class
    friend class Network; // to use the methods of Neuron class on the Network class
protected:
    float value; //z
    float actvalue; //a
public:
    Neuron(){ };
    virtual void activate() = 0; // pure virtual method
    Neuron(float z) : value(z), actvalue(z) { }; // constructor
    virtual ~Neuron(){ }; // destructor
};

class SigmoidNeuron : public Neuron { // derived class from Neuron base class
public:
    SigmoidNeuron(float z): Neuron(z) { }; //constructor
    void activate();
    ~SigmoidNeuron(){ }; // destructor
};
void SigmoidNeuron::activate(){
    actvalue = Sigmoid(value); // using sigmoid formula
}

class TanhNeuron : public Neuron { // derived class from Neuron base class
public:
    TanhNeuron(float z): Neuron(z) { }; //constructor
    void activate();
    ~TanhNeuron(){ }; // destructor
};
void TanhNeuron::activate(){
    actvalue = Tanh(value); // using tanh formula
}

class ReluNeuron : public Neuron { // derived class from Neuron base class
public :
    ReluNeuron(float z) : Neuron(z) { }; // constructor
    void activate();
    ~ReluNeuron(){ }; // destructor
};
void ReluNeuron::activate(){
    actvalue = ReLu(value); // using ReLu formula
}

class LReluNeuron : public Neuron { // derived class from Neuron base class
public:
    LReluNeuron(float z) : Neuron(z) { }; // constructor
    void activate();
    ~LReluNeuron(){ }; // destructor
};
void LReluNeuron::activate(){
    actvalue = LReLu(value);
}

class NeuronNode {
    friend class Network; // to use the methods of NeuronNode class on the Network class
private:
    NeuronNode * next; // to link the neurons each other
    Neuron* N;
public:
    NeuronNode(Neuron*); // constructor
    NeuronNode *getnext() { return next;}; // getter method but it is not necessary since using friend class
    void setnext(NeuronNode *x){ next = x;}; // setter method but it is not necessary since using friend class
    ~NeuronNode(); // destructor
};
NeuronNode::NeuronNode(Neuron* neuron){
    next = NULL;
    N = neuron;
}
NeuronNode::~NeuronNode(){
    delete N;
}

class Layer {
    friend class Network;  // to use the methods of Layer class on the Network class
private:
    NeuronNode *neuron_head; // head pointer of neuron linked list
public:
    Layer(){neuron_head = NULL;}; // default constructor
    void add_neurons(NeuronNode* adding); // add neurons to end of the linked list
    ~Layer(); //destructor = deletes neuron nodes
};

void Layer::add_neurons(NeuronNode* adding){ // add neurons to end of the linked list
    if (neuron_head == NULL){ // if any neuron have been added before
        neuron_head = adding;
        adding->setnext(NULL);
    }
    else if(neuron_head){
        NeuronNode* traverse = neuron_head;
        while(traverse->getnext()){ // the traverse is traversing to the end of the list
            traverse = traverse->getnext();
        }
        traverse->setnext(adding); // then the new neuron is added to the linked-list
        adding->setnext(NULL);
    }
}
Layer::~Layer(){ // delete neuron nodes (destructor)
    NeuronNode *deleting;
    deleting = neuron_head; // starting to delete from the head of the neurons
    while(deleting != NULL){
        neuron_head = neuron_head->getnext();
        delete deleting; // neurons are deleting one by one
        deleting = neuron_head;
    }
}
class Layernode {
    friend class Network; // to use the methods of LayerNode class on the Network class
private:
    Layer* L;
    Layernode* next; // to link the layers each other
public:
    Layernode(Layer* L ){next = NULL; this->L = L;}; // constructor
    Layernode* getnext(){return next;};  // getter method but it is not necessary since using friend class
    void setnext(Layernode* x){next = x;};  // setter method but it is not necessary since using friend class
    ~Layernode(){ delete L;}; // destructor
    
};

class Network {
private:
    int layer_num;
    Layernode *layer_head;  // head pointer of layers linked list
public:
    Network(){ layer_head = NULL;}; // default constructor
    void add_layers(Layernode* added);
    void generate(int* arr_layers,int* arr_types, float* arr_x);
    void print_result();
    void read_from_file(char* file);
    ~Network(); //destructor = deletes nodes of the layers
};


void Network::add_layers(Layernode* added){ // add layers to end of the linked list
    if(layer_head == NULL){ // if any layer have been added before
        layer_head = added;
        added->setnext(NULL);
    }
    else if(layer_head){
        Layernode* traverse = layer_head;
        while(traverse->getnext()){
            traverse = traverse->getnext(); // the traverse is traversing to the end of the list
        }
        traverse->setnext(added); // then the new layer is added to the linked-list
        added->setnext(NULL);
    }
}

void Network::generate(int* arr_layers,int* arr_types, float* arr_x){
    Layer* layer_obj = new Layer(); // allocated memory for the first layer
    for(int i=0;i<arr_layers[0];i++){ // for 0. layer (the x is given)
        if(arr_types[0]==0){ // if the type of the neuron is Sigmoid
            SigmoidNeuron* n0 = new SigmoidNeuron(arr_x[i]); // create object(n0) of SigmoidNeuron and allocate memory
            NeuronNode* pointer = new NeuronNode(n0);  // create object of NeuronNode, allocate memory (put neuron object 'n0' inside the neuron node 'pointer')
            layer_obj->add_neurons(pointer); // add the 'pointer' inside the layerobj
        }
        else if(arr_types[0]==1){ // if the type of the neuron is Leakly ReLU
            LReluNeuron* n0 = new LReluNeuron(arr_x[i]);
            NeuronNode* pointer = new NeuronNode(n0);
            layer_obj->add_neurons(pointer);
        }
        else if(arr_types[0]==2){ // if the type of the neuron is ReLU
            ReluNeuron* n0 = new ReluNeuron(arr_x[i]);
            NeuronNode* pointer = new NeuronNode(n0);
            layer_obj->add_neurons(pointer);
        }
    }
    Layernode* Lnode_obj = new Layernode(layer_obj);//create and allocated memory for the layernode (put layer object  'layer_obj' inside the layernode ' Lnode_obj ')
    add_layers(Lnode_obj); // add the 'Lnode_obj' to head of the linked-list of layers
    
    // the second part -> To create the next layers after the head layers
    int z,k = 1;
    float new_value;
    Layernode* traverseL = layer_head;
    
    while(traverseL){  // for other layers
        Layer* layer_obj = new Layer(); // allocated memory for the new layer
        float *matrixB = new float[arr_layers[k]]; // created B matrices with dynamic array
        float matrixW[arr_layers[k-1]][arr_layers[k]]; // created W matrices with static array
        
        for(int i=0;i<arr_layers[k];i++){ //filling B matrices
            matrixB[i] = 0.1;
        }
        for(int i=0;i<arr_layers[k-1];i++){ // filling W matrices
            for(int j=0;j<arr_layers[k];j++){
                matrixW[i][j] = 0.1;
            }
        }
        for(int i=0;i<arr_layers[k];i++){
            
            NeuronNode* traverseN = traverseL -> L -> neuron_head; // pointer of neuron node -> traversing neurons for calculating next value
            new_value = 0.0;
            z = 0;
            while(traverseN){ // calculate new value with given matrix formula
                new_value += matrixW[z++][i] * (traverseN -> N -> actvalue);
                traverseN = traverseN->getnext(); // until end of the neuron nodes
            }
            new_value += matrixB[i];
            
            if(arr_types[k]==0){ // if the type of the neuron is Sigmoid
                SigmoidNeuron* nx = new SigmoidNeuron(new_value); // create object(nx) of SigmoidNeuron and allocate memory
                nx->activate(); // to activate the value(z)
                NeuronNode* pointer2 = new NeuronNode(nx); // create object of NeuronNode, allocate memory (put neuron object 'nx' inside the neuron node 'pointer2')
                layer_obj->add_neurons(pointer2); // add the 'pointer2' inside the layerobj
            }
            else if(arr_types[k]==1){ // if the type of the neuron is Leakly ReLU
                LReluNeuron* nx = new LReluNeuron(new_value);
                nx->activate();
                NeuronNode* pointer2 = new NeuronNode(nx);
                layer_obj->add_neurons(pointer2);
            }
            else if(arr_types[k]==2){  // if the type of the neuron is ReLU
                ReluNeuron* nx = new ReluNeuron(new_value);
                nx->activate();
                NeuronNode* pointer2 = new NeuronNode(nx);
                layer_obj->add_neurons(pointer2);
            }
        }
        
        Layernode* Lnode_obj = new Layernode(layer_obj);//create and allocated memory for the layernode (put layer object  'layer_obj' inside the layernode ' Lnode_obj ')
        add_layers(Lnode_obj); // add the 'Lnode_obj' to the linked-list of layers
        k++;
        if(k >= layer_num)
            return;
        traverseL = traverseL->getnext();
        delete [] matrixB;
    }
    
}
void Network::print_result(){ // prints layers and activated values of neurons in each layer
    float a;
    Layernode* layertraverse = layer_head; // the pointer of the layer's head
    for(int i=0;i<layer_num;i++){
        cout<<"Layer "<<i<<":"<<endl;
        NeuronNode* neurontraverse = layertraverse -> L -> neuron_head;  // the pointer of neuron's head
        while(neurontraverse){
            a = neurontraverse -> N -> actvalue;
            cout << a << endl;
            neurontraverse = neurontraverse->getnext();
            
        }
        layertraverse = layertraverse->getnext();
    }
}
void Network::read_from_file(char* file){
    int layer_num;  // how many layers to have
    int *arr_layers; // how many neurons these layers have
    int *arr_types; // the type of the neurons
    float *arr_x; // gives the input values for the network
    float z;
    int x,y;
    ifstream myfile(file);
    if(myfile.is_open()){ // if the file is open
        myfile >> x; // get the first number = number of the layers (first line of file)
        arr_layers = new int[x]; // allocate memory for array of the number of neurons in each layer
        arr_types = new int[x]; // allocate memory for array of types of neurons
        layer_num = x;
        
        for(int i=0;i<layer_num;i++){ // second line
            myfile >> arr_layers[i];
        }
        arr_x = new float[arr_layers[0]]; // allocate memory for array of given x
        try{
        for(int i=0;i<layer_num;i++){ // third line
            myfile >> y;
            arr_types[i] = y;
            if(y>=3 or y<0) throw "Unidentified activation function!"; // Exception status
        }
        }
        catch(const char * error){
            cout<<error<<endl;
            return exit(EXIT_FAILURE);
        }
        try{
            
            for(int i=0;i<arr_layers[0];i++){ // fourth line
                if((myfile.eof())) throw "Input shape does not match!"; // Exception status
                myfile >> z;
                arr_x[i] = z;
            }
            if(!myfile.eof()) throw "Input shape does not match!"; // Exception status

            }
        catch(const char * error){
            cout<<error<<endl;
            return exit(EXIT_FAILURE);
        }
    }
    else
        cout<<"FILE CAN NOT OPEN !"<<endl;
    myfile.close();
    this->layer_num = layer_num;
    generate(arr_layers, arr_types, arr_x); // send the data which are taken from the file

    delete [] arr_x; // since we allocated memory for these arrays we should delete after finish the job
    delete [] arr_types;
    delete [] arr_layers;

}

Network::~Network(){ // destructor -> delete layer nodes
    Layernode* deleting = layer_head; // starting to delete from the head of the layers
    while(deleting != NULL){
        layer_head = layer_head->getnext();
        delete deleting; // layers are deleting one by one
        deleting = layer_head;
    }
}





#endif /* classes_h */
