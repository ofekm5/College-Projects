#include "T1.h"


int main()
{
    int size, x;
    vector<int>vec;

    cout << "enter data:" << endl;
    cin >> size;

    vec.resize(size);

    for (int i = 0; i < size; i++) {
        cin >> vec[i];
    }

    cin >> x;
    checkInput(vec, x, size);
    cout << "iterative:" << endl;
    sumOfPairsIter(vec, size, x);
    cout << "recursive:" << endl;
    sumOfPairsRec(vec, size, x, 0);
    cout << "Recursion implemented using stack:" << endl;
    sumOfPairsRecConv(vec, (int)vec.size(), x, 0);

    return 0;
}



