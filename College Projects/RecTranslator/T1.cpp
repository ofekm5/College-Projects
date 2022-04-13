#include "T1.h"

void sumOfPairsIter(vector<int>& vec, int n, int x)
{
    bool found = false;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++) {
            if (vec[i] + vec[j] == x) {
                cout << vec[i] << " " << vec[j] << endl;
                found = true;
            }
        }
    }
}


void sumOfPairsRec(vector<int>& vec, int n, int x, int y)
{
    if (n == 1) {
        if (y != 0 && x == vec[0] + y) {
            cout << vec[0] << " " << y << endl;
        }
    }
    else {
        if (y != 0) {
            if (x == vec[n - 1] + y) {
                cout << vec[n - 1] << " " << y << endl;
            }
            sumOfPairsRec(vec, n - 1, x, y);
        }
        else {
            sumOfPairsRec(vec, n - 1, x, vec[n - 1]);
            sumOfPairsRec(vec, n - 1, x, 0);
        }
    }
}


void sumOfPairsRecConv(vector<int>& vec, int n, int x, int y) {

    Stack S; // Stack which simulates the recursion.
    Itemtype Curr = { n,x,y,START }; // Values of current �recursive call�
    bool returnFromRecursion = false;

    do {
        if (returnFromRecursion)
            Curr = S.Pop();

        if (Curr.line == START) {
            if (Curr.n == 1) {
                if (Curr.y != 0 && x == vec[0] + Curr.y)
                    cout << vec[0] << " " << Curr.y << endl;
                returnFromRecursion = true;
            }
            else {//curr.n!=1
                if (Curr.y != 0)
                {
                    if (x == vec[Curr.n - 1] + Curr.y)
                    {
                        cout << vec[Curr.n - 1] << " " << Curr.y << endl;
                    }

                    /* The first recursion to be called is the second placed in the original code(y=0) */
                    Curr.line = AFTER_FIRST;
                    S.Push(Curr);

                    /* Initializing next level of the stack */
                    Curr.n--;
                    Curr.line = START;

                    returnFromRecursion = false;
                }
                else// y is 0
                {
                    Curr.line = AFTER_SECOND;
                    S.Push(Curr);

                    /* Initializing next level of the stack */
                    Curr.n--;
                    Curr.y = vec[Curr.n];/* Avoding decreasing 1 because of the previous line */
                    Curr.line = START;

                    returnFromRecursion = false;
                }
            }
        }
        else if (Curr.line == AFTER_FIRST) { // else of start
            returnFromRecursion = true;
        }
        else if (Curr.line == AFTER_SECOND) {
            Curr.line = AFTER_THIRD;
            S.Push(Curr);
            Curr.n--;
            Curr.y = 0;
            Curr.line = START;
            returnFromRecursion = false;
        }
        else if (Curr.line == AFTER_THIRD) { /* The last recursion to be called is the first placed in the original code */
            returnFromRecursion = true;
        }
    } while (!S.IsEmpty());

}


Node::Node(Itemtype _data, Node* _nxt) {
    this->data.x = _data.x;
    this->data.n = _data.n;
    this->data.y = _data.y;
    this->data.line = _data.line;
    this->nxt = _nxt;
}


Stack::Stack() {
    this->top = NULL;
}


Stack::~Stack() {
    MakeEmpty();
}


void Stack::MakeEmpty() {
    Node* temp;
    while (this->top != nullptr) {
        temp = this->top;
        this->top = this->top->getNXT();
        delete temp;
    }
}


int Stack::IsEmpty() {
    if (this->top == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}


void Stack::Push(Itemtype item) {
    this->top = new Node(item, top);
}


Itemtype Stack::Pop() {
    if (IsEmpty())
        exit(1);
    Node* temp = this->top;
    Itemtype item = this->top->getData();

    this->top = this->top->getNXT();
    delete temp;

    return item;
}


Itemtype Stack::Top() {
    return this->top->getData();
}


void fun() {
    auto start = chrono::high_resolution_clock::now();
    // unsync the I/O of C and C++.
    ios_base::sync_with_stdio(false);
    fun();// Here you put the name of the function you wish to measure
    auto end = chrono::high_resolution_clock::now();
    // Calculating total time taken by the program.
    double time_taken =
        chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;
    ofstream myfile("Measure.txt"); // The name of the file
    myfile << "Time taken by function <name-of-fun> is : " << fixed
        << time_taken << setprecision(9);
    myfile << " sec" << endl;
    myfile.close();
}


void checkInput(vector<int>& vec, int x, int size) {

    if (x <= 0)//number to check is less than 0
    {
        cout << "wrong input" << endl;
        exit(1);
    }

    if (vec.empty())//empty array
    {
        cout << "wrong input" << endl;
        exit(1);
    }

    if (vec.size() != size) {/*  mismatch between vector and supposed size*/
        cout << "wrong input" << endl;
        exit(1);
    }

    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] <= 0)
        {
            cout << "wrong input" << endl;
            exit(1);
        }
    }
}
