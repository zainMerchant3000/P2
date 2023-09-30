#include <cstring>

#include "Formula.h"

using namespace formula;

double Formula::mopen01r()
{
    throw "mopen01r not implemented";
}

double Formula::generateOutputFactor()
{
    // User of mopen01r().
    throw "generateOutputFactor not implemented";
}

// Pre-conditions:
//  q != NULL, n != NULL; q, n refer to valid objects.
void Formula::apply(int *q, char **n)
{
    // Determine output factor.
    double f = this->generateOutputFactor();

    // Apply nested linear search to find matching names in
    // this->min [names of input ingredients] and n [names of inventory ingredients],
    // and then for each one matching subtract the quantity required.

    // Matching indices for the quantity arrays (this->miq, q).
    int i = 0, j = 0;
    for (char *p = *this->min; *p; p++, i++) {
        bool found = false;
        for (char *r = *n; *r; r++, j++) {
            if (strcmp(p, r) == 0) {
                if (q[j] < this->miq[i]) {
                    throw "Not enough (input) ingredient(s)";
                }
                // Consume
                found = true;
                q[j] -= this->miq[i];
                break;
            }
        }
        if (!found) {
            throw "At least one ingredient (input) does not appear.";
        }
    }

    // Do the same using nested linear search on the outputs:
    //  (this->mon, this->moq, n, q).
    i = j = 0;
    for (char *p = *this->mon; *p; p++, i++) {
        bool found = false;
        for (char *r = *n; *r; r++, j++) {
            if (strcmp(p, r) == 0) {
                // Produce
                found = true;
                q[j] += (int)(f * this->moq[i]);
                break;
            }
        }
        if (!found) {
            throw "No spot in inventory for at least one output ingredient in Formula.";
        }
    }
}

void Formula::levelup()
{
    throw "levelup not implemented";
}
