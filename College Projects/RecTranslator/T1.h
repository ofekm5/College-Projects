#pragma once


#include  <iostream>
#include <iomanip>//for measure running time
#include <fstream>//for measure running time
#include <chrono>//for measure running time
using namespace std;
#include <vector>

void sumOfPairsIter(vector<int>& vec, int n, int x);
void sumOfPairsRec(vector<int>& vec, int n, int x, int y);
void sumOfPairsRecConv(vector<int>& vec, int n, int x, int y);
void checkInput(vector<int>& vec, int x, int size);

enum LineType { START, AFTER_FIRST, AFTER_SECOND, AFTER_THIRD };


struct Itemtype { // an item that will be stored in Stack which simulates the recursion.
    int n, x, y;
    LineType line;/* Line = supposed next line to go afterwards */
};

class Node {
private:
    Itemtype data;
    Node* nxt;
public:
    Node(Itemtype _data, Node* _nxt);
    Itemtype getData(void) { return this->data; }
    void setData(Itemtype _data) { this->data = _data; }
    Node* getNXT(void) { return this->nxt; }
    void setNXT(Node* _nxt) { this->nxt = _nxt; }
};

class Stack {
private:
    Node* top;
public:
    Stack();
    ~Stack();
    void MakeEmpty();
    int IsEmpty();
    void Push(Itemtype item);
    Itemtype Pop();
    Itemtype Top();
};



