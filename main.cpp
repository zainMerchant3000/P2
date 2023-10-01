#include <iostream>

#include "Formula.h"

using namespace std;
using namespace formula;

int main() {
    int *inputQuantity = new int[5]{10, 6, 6, 6, 7};
    char *inputNames[] = {"butter", "egg", "sugar", "flour", "baking soda", nullptr};
    int *outputQuantity = new int[1]{36};
    char *outputNames[] = {"cookies", nullptr};

    Formula cookies(inputQuantity, outputQuantity, inputNames, outputNames);

    double outputFactor = cookies.generateOutputFactor();
    cout << "getting outputFactor: " << outputFactor << " ";

    //testing inventory
    int *inventoryQty = new int[6]{11, 7, 7, 7, 8, 100};
    char *inventoryNam[] = {"butter", "egg", "sugar", "flour", "baking soda", "cookies", nullptr};

    cookies.apply(inventoryQty, inventoryNam);
    for (int i = 0; i < 6; i++) {
        cout << inventoryQty[i] << endl;
    }
    return 0;
}
