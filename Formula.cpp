#include <cstring>
#include <cstdlib>
#include "Formula.h"
#include <ctime>

using namespace formula;

#include <iostream>

int Formula::GenerateRandomNumb() {

    int randomNumber = rand() % 101;
    return randomNumber;









    //throw "GenerateRandomNumber not implemented";
}

double Formula::generateOutputFactor() {
    double outputFactor;

    int randomNumber = GenerateRandomNumb();
    //int randomNumber = random.Next(1, 101); // [1,101).

    if (proficiencyLevel == 0) {
        if (randomNumber < 31) {
            // failure
            outputFactor = 0.0;
        } else if (randomNumber < 51) {
            //20% chance of 0.75 output
            outputFactor = 0.75;
        } else if (randomNumber < 101) {
            outputFactor = 1.0;
        } else outputFactor = 0.1234; // TODO: Set this one
        //no bonus output
    } else if (proficiencyLevel == 1) {
        // a level 1 Formula may have a 25 % chance of failure,
        // 20 % chance of ¾ output, 50 % chance of normal output, and 5 % chance of bonus output
        if (randomNumber < 26) { // failure
            // failure = true;
            outputFactor = 0.0;
        } else if (randomNumber < 46) { //20% chance of 0.75 output
            outputFactor = 0.75;
        } else if (randomNumber < 96) {
            outputFactor = 1.0;
        }
            //bonus output
        else outputFactor = 1.1;
    } else if (proficiencyLevel == 2) {
        // level 2 the chances could change to 20, 15, 55, and 10, respectively.
        if (randomNumber < 21) {
            outputFactor = 0.0;
        } else if (randomNumber < 36) { //20% chance of 0.75 output
            outputFactor = 0.75;
        } else if (randomNumber < 91) {
            outputFactor = 1.0;
        }
            //bonus output
        else outputFactor = 1.1;
    } else if (proficiencyLevel == 3) {
        // level 3 the chances could change to 15, 10, 60, and 15, respectively.
        if (randomNumber < 16) { // failure
            outputFactor = 0.0;
        } else if (randomNumber < 26) { //20% chance of 0.75 output
            outputFactor = 0.75;
        } else if (randomNumber < 86) {
            outputFactor = 1.0;
        }
            //bonus output
        else outputFactor = 1.1;
    } else {
        throw "Unknown proficiency level {0}";
    }
    // FIXME: testing
    return 1;

    //return outputFactor;

}

// Pre-conditions:
//  inventoryQuantity != NULL, n != NULL; inventoryQuantity, n refer to valid objects.
void Formula::apply(int *inventoryQuantity, char **inventoryName) {
    // Determine output factor.
    double f = this->generateOutputFactor();

    // Apply nested linear search to find matching names in
    // this->min [names of input ingredients] and n [names of inventory ingredients],
    // and then for each one matching subtract the quantity required.

    // Matching indices for the quantity arrays (this->inputQuantity, inventoryQuantity).
    int i = 0, j = 0;
    for (char **p = this->inputName; *p; p++, i++) {
        bool found = false;
        for (char **r = inventoryName; *r; r++, j++) {
            if (strcmp(*p, *r) == 0) {
                if (inventoryQuantity[j] < this->inputQuantity[i]) {
                    throw "Not enough (input) ingredient(s)";
                }
                // Consume
                found = true;
                inventoryQuantity[j] -= this->inputQuantity[i];
                break;
            }
        }
        j = 0;
        if (!found) {
            throw "At least one ingredient (input) does not appear.";
        }
    }

    // Do the same using nested linear search on the outputs:
    //  (this->outputName, this->outputQuantity, n, inventoryQuantity).
    i = j = 0;
    for (char **p = this->outputName; *p; p++, i++) {
        bool found = false;
        for (char **r = inventoryName; *r; r++, j++) {
            if (strcmp(*p, *r) == 0) {
                // Produce
                found = true;
                inventoryQuantity[j] += (int) (f * this->outputQuantity[i]);
                break;
            }
        }
        j = 0;
        if (!found) {
            throw "No spot in inventory for at least one output ingredient in Formula.";
        }
    }
}

void Formula::levelup() {
    if (proficiencyLevel < PROFICIENCY_LEVEL_LIMIT) {
        proficiencyLevel++;
    }
}

int Formula::getProficiencyLevel() {
    return proficiencyLevel;
}
