//
// Created by zain7 on 10/3/2023.
//

#include "Plan.h"
#include "Formula.h"

using namespace plan;
using namespace formula;

// Deep copy constructor
Plan::Plan(const Plan &other) : numFormulas(other.numFormulas), formulas(new Formula *[other.numFormulas]) {
    for (int i = 0; i < other.numFormulas; i++) {
        formulas[i] = new Formula(*other.formulas[i]); // Use Formula's copy constructor
    }
}

Plan &Plan::operator=(const Plan &src) {
    if (this == &src)return *this;
    this->numFormulas = src.numFormulas;
    this->formulas = new Formula *[numFormulas];
    for (int i = 0; i < numFormulas; i++) { formulas[i] = new Formula(*src.formulas[i]); }
    return *this;
}

Plan::Plan(Plan &&src) noexcept: numFormulas(src.numFormulas), formulas(src.formulas) {
    src.numFormulas = 0;
    src.formulas = nullptr;
}

Plan &Plan::operator=(Plan &&src) noexcept {
    using std::swap;
    swap(this->numFormulas, src.numFormulas);
    swap(this->formulas, src.formulas);
    return *this;
}

Plan::~Plan() {
    for (int i = 0; i < numFormulas; i++) { delete formulas[i]; }
    delete[] formulas;
}

void plan::Plan::addFormula(Formula *formula) {
    // Create a new array with increased size
    Formula **newFormulas = new Formula *[numFormulas + 1];
    // Copy pointers to the elements from [0, numFormulas).
    for (int i = 0; i < numFormulas; i++) {
        newFormulas[i] = formulas[i];
    }
    // Copy pointer to new formula.
    newFormulas[numFormulas] = formula;
    // Clean up old array and update
    delete[] formulas;
    formulas = newFormulas;
    numFormulas++;
}

void plan::Plan::removeLastFormula() {
    if (numFormulas > 0) {
        // Create a new array with reduced size
        Formula **newFormulas = new Formula *[numFormulas - 1];
        for (size_t i = 0; i < numFormulas - 1; ++i) {
            newFormulas[i] = formulas[i];
        }
        // Clean up old array and update
        delete[] formulas;
        formulas = newFormulas;
        --numFormulas;
    }
}

void plan::Plan::replaceFormula(int indexRep, Formula *formula) {
    if (indexRep < numFormulas) {
        // Know that, by a precondition, `formula` refers to an object in heap memory,
        // and every object referred to in `this->formulas` is also in heap memory.
        delete formulas[indexRep];
        formulas[indexRep] = formula;
    }
}

int plan::Plan::getNumFormula() {
    return numFormulas;
}
