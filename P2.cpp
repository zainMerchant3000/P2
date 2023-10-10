//Zain-Abbas Merchant
//CPSC 3200 P2
#include <iostream>
#include <random>
#include <algorithm>

#include "Formula.h"
#include "Plan.h"

using namespace std;
using namespace formula;
using namespace plan;

// function that creates array of Formula objects
Formula **
arrayOfFormulas(int nFormulas, int inputLength, int outputLength, const int inputQuantities[], const char *inputNames[],
                const char *outputNames[]) {

    // nFormulas > 0
    Formula **fs = new Formula *[nFormulas];
    // inputLength == outputLength
    // inputLength > 0

    // Randomness
    random_device randomDevice;
    mt19937 rng(randomDevice());
    // Inclusive both sides
    uniform_int_distribution<int> distIL(1, inputLength);
    uniform_int_distribution<int> distOL(1, outputLength);

    for (int i = 0; i < nFormulas; i++) {
        // Each formula may have a different number of input and output resources.
        // Determine the number of inputs.
        int n = distIL(rng);

        // Construct an array of indices to sample without replacement.
        int *indices = new int[n];
        for (int j = 0; j < n; j++) {
            indices[j] = j;
        }
        shuffle(indices, indices + n, rng);

        // Sample.
        int *iqs = new int[n];
        const char **ins = new const char *[n];
        for (int j = 0; j < n; j++) {

            iqs[j] = inputQuantities[indices[j]];
            ins[j] = inputNames[indices[j]];

        }

        // Free aux.
        delete[] indices;

        int m = distOL(rng);

        // Do the same for output resources.
        indices = new int[m];
        for (int i = 0; i < m; i++) {
            indices[i] = i;
        }
        shuffle(indices, indices + m, rng);
        const char **ons = new const char *[m];
        for (int j = 0; j < m; j++) {
            ons[j] = outputNames[indices[j]];
        }

        // Free aux
        delete[] indices;

        // Construct
        fs[i] = new Formula(n, m, iqs, ins, ons);
    }

    return fs;
}

int main() {
    int nFormulas = 20; // Generate length of array of Formulas
    int inputLength = 5; // Each formula has  input variables
    int outputLength = 1; // Each formula has  output variable
    int *inputQuantities = new int[5]{10, 6, 6, 6, 7};
    // make client specify size of array to pass in count input
    const char *inputNames[] = {"butter", "egg", "sugar", "flour", "baking soda"};
    const char *outputNames[] = {"cookies"};
    //create array of Formula objects
    Formula **formulas;
    formulas = arrayOfFormulas(nFormulas, inputLength, outputLength, inputQuantities, inputNames, outputNames);
    //creating myPlan object with initial array of Formula objects

    // Normal constructor Test
    Plan *myPlan = new Plan(formulas, nFormulas);
    Formula *newFormula = new Formula(inputLength, outputLength, inputQuantities, inputNames, outputNames);
    myPlan->addFormula(newFormula);
    int numFormula = myPlan->getNumFormula();
    //std::cout << "numFormulas: " << numFormula << std::endl;
    myPlan->removeLastFormula();
    int numFormula_Two = myPlan->getNumFormula();
   // std::cout << "numFormulas: " << numFormula_Two << std::endl;
    // Replace a Formula at index 1
    Formula *replacementFormula = new Formula(5, 1, inputQuantities, inputNames, outputNames);
    myPlan->replaceFormula(1, replacementFormula);
    int numFormula_Replace = myPlan->getNumFormula();
   // std::cout << "numFormulas: " << numFormula_Replace << std::endl;

    // Copy constructor Test
    Plan *yourPlan = new Plan(*myPlan);
    yourPlan->removeLastFormula();
    int numFormula_Copy = yourPlan->getNumFormula();
    //std::cout << "numFormulas Copy: " << numFormula_Copy << std::endl;
   // std::cout << "numFormulas Original: " << myPlan->getNumFormula() << std::endl;
    myPlan->removeLastFormula();
    //std::cout << "numFormulas Copy: " << yourPlan->getNumFormula() << std::endl;
   // std::cout << "numFormulas Original: " << myPlan->getNumFormula() << std::endl;

    //assignment operator test
    Plan *ourPlan = new Plan(formulas, nFormulas); // normal constructor
    *ourPlan = *myPlan; // assignment operator
    int numFormula_Assignment = myPlan->getNumFormula();
   // std::cout << "numFormulas: " << numFormula_Assignment << std::endl;
    *ourPlan = *ourPlan; // self assignment
    int numFormula_Self = ourPlan->getNumFormula();
    //std::cout << "numFormulas: " << numFormula_Self << std::endl;



    delete yourPlan;
    delete myPlan;
    delete ourPlan;
    return 0;
}
