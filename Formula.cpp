#include <cmath>
#include <iostream>

#include "Formula.h"

/*
 Implementation Invariant:
Includes Copy Constructor, assignment operator, and move semantics for efficient deep copying
 Formula is determined by outputFactor (internally controlled by generated number between (0.0 - 1.0)
 proficiencyLevel controls different probabilities of outputFactors
 formula applied with outputfactor to determine outputQuantity (Apply())
 */

using namespace formula;
//calculate random number based on range (0.0, 1.0)
double Formula::GenerateRandomNumber() {
    // Avoid 0.0.
    double d;
    do { d = dist100(rng); } while (d == 0.0);
    return d;
}
// Apply decrements input resources and increments output resources in the inventory
// once as specified in this Formula.
//
// Pre-conditions:
//  1. All ingredient resources and output resources must be allocated in the pair.
//  2. There exists a positive count for each input ingredient in this Formula.
//  3. There exists a non-negative count for each output in this Formula.
// Post-conditions:
//  1. Internal state of this Formula won't change, except for internal RNG and the output Quantity.
//  2. If successful, each Quantity in outputQuantity will be changed based on the formula and
//  4. Either case, there will be no negative counts of outputQuantities.

void Formula::Apply() {
    double f = this->GenerateOutputFactor();
    int i = 0;
    for (const int *p = this->outputQuantities; i < this->countOutputs; p++, i++) {
        // 10x formula for each qty
        this->outputQuantities[i] = static_cast<int>(std::round(
                inputQuantities[i] * 10.0 * f));
    }


}
//determine failure, output factor if successful
double Formula::GenerateOutputFactor() {
    double outputFactor;
    double randomNumber = GenerateRandomNumber();
    if (proficiencyLevel == 0) {
        if (randomNumber < .30) {
            // failure
            outputFactor = 0.0;
        } else if (randomNumber < .50) {
            // 20% chance of 0.75 output
            outputFactor = 0.75;
        } else {
            outputFactor = 1.0;
        }
        //no bonus output
    } else if (proficiencyLevel == 1) {
        // a level 1 Formula may have a 25 % chance of failure,
        // 20 % chance of ¾ output, 50 % chance of normal output, and 5 % chance of bonus output
        if (randomNumber < .25) { // failure
            outputFactor = 0.0;
        } else if (randomNumber < .45) { // 20% chance of 0.75 output
            outputFactor = 0.75;
        } else if (randomNumber < .95) {
            outputFactor = 1.0;
        }
            //bonus output
        else outputFactor = 1.1;
    } else if (proficiencyLevel == 2) {
        // level 2 the chances could change to 20, 15, 55, and 10, respectively.
        if (randomNumber < .20) {
            outputFactor = 0.0;
        } else if (randomNumber < .35) { //20% chance of 0.75 output
            outputFactor = 0.75;
        } else if (randomNumber < .90) {
            outputFactor = 1.0;
        }
            //bonus output
        else outputFactor = 1.1;
    } else if (proficiencyLevel == 3) {
        // level 3 the chances could change to 15, 10, 60, and 15, respectively.
        if (randomNumber < .15) { // failure
            outputFactor = 0.0;
        } else if (randomNumber < .25) { // 20% chance of 0.75 output
            outputFactor = 0.75;
        } else if (randomNumber < .85) {
            outputFactor = 1.0;
        }
            //bonus output
        else outputFactor = 1.1;
    } else {
        throw "Unknown proficiency level {0}";
    }
    return outputFactor;
}

//preconditon:
// postcondition: proficiency level goes above the maximum level defined by class designer (checked within method)
/// <summary>Increase the proficiency level by one, up to but not including the level limit.</summary>
void Formula::LevelUp() {
    if (proficiencyLevel < PROFICIENCY_LEVEL_LIMIT) {
        proficiencyLevel++;
    }
}
//create copy of input arrays for users to query
void Formula::CopyInputInto(int *q, const char **n) const {
    for (int i = 0; i < this->countInputs; i++) {
        q[i] = this->inputQuantities[i];
        n[i] = this->inputNames[i];
    }
}
//create copy of output arrays for users to query
void Formula::CopyOutputInto(int *q, const char **n) const {
    for (int i = 0; i < this->countOutputs; i++) {
        q[i] = this->outputQuantities[i];
        n[i] = this->outputNames[i];
    }
}
//copy constructor
Formula::Formula(const Formula &src) : proficiencyLevel(src.proficiencyLevel),
                                       countInputs(src.countInputs), countOutputs(src.countOutputs), rng_dev(),
                                       rng(rng_dev()),
                                       dist100(0.0, 1.0) {
    this->inputNames = new const char *[this->countInputs];
    this->inputQuantities = new int[this->countInputs];
    for (int i = 0; i < this->countInputs; i++) {
        this->inputNames[i] = src.inputNames[i];
        this->inputQuantities[i] = src.inputQuantities[i];
    }
    this->outputNames = new const char *[this->countOutputs];
    this->outputQuantities = new int[this->countOutputs];
    for (int i = 0; i < this->countOutputs; i++) {
        this->outputNames[i] = src.outputNames[i];
        this->outputQuantities[i] = src.outputQuantities[i];
    }
}
//assignment operator
Formula &Formula::operator=(const Formula &src) {
    if (this == &src) return *this;
    this->proficiencyLevel = src.proficiencyLevel;
    this->countInputs = src.countInputs;
    this->countOutputs = src.countOutputs;
    this->inputNames = new const char *[this->countInputs];
    this->inputQuantities = new int[this->countInputs];
    for (int i = 0; i < this->countInputs; i++) {
        this->inputNames[i] = src.inputNames[i];
        this->inputQuantities[i] = src.inputQuantities[i];
    }
    this->outputNames = new const char *[this->countOutputs];
    this->outputQuantities = new int[this->countOutputs];
    for (int i = 0; i < this->countOutputs; i++) {
        this->outputNames[i] = src.outputNames[i];
        this->outputQuantities[i] = src.outputQuantities[i];
    }
    return *this;
}
//move copy constructor
Formula::Formula(Formula &&src) noexcept: proficiencyLevel(src.proficiencyLevel),
                                          countInputs(src.countInputs), countOutputs(src.countOutputs),
                                          inputNames(src.inputNames), inputQuantities(src.inputQuantities),
                                          outputNames(src.outputNames), outputQuantities(src.outputQuantities),
                                          rng_dev(),
                                          rng(rng_dev()),
                                          dist100(0.0, 1.0) {
    src.countInputs = 0;
    src.inputNames = nullptr;
    src.inputQuantities = nullptr;
    src.countOutputs = 0;
    src.outputNames = nullptr;
    src.outputQuantities = nullptr;
}
//move assignment operator
Formula &Formula::operator=(Formula &&src) noexcept {
    using std::swap;
    swap(this->proficiencyLevel, src.proficiencyLevel);
    swap(this->countInputs, src.countInputs);
    swap(this->inputNames, src.inputNames);
    swap(this->inputQuantities, src.inputQuantities);
    swap(this->countOutputs, src.countOutputs);
    swap(this->outputNames, src.outputNames);
    swap(this->outputQuantities, src.outputQuantities);
    return *this;
}
