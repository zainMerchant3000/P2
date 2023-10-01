#ifndef _H_FORMULA_
#define _H_FORMULA_

#include <ctime>
#include <cstdlib>

namespace formula {

// Exclusive upper bound for proficiency levels (see class Formula).
    const int PROFICIENCY_LEVEL_LIMIT = 3;

    class Formula {
    private:
        // Non-negative proficiency level (always starts with 0).
        int proficiencyLevel;

        int *inputQuantity, *outputQuantity;
        // Null-terminated array of NUL-terminated strings.
        //  NULL: Not allocated.
        //  [0] == NULL: Empty.
        //  [n] == NULL: Length is n.
        char **inputName, **outputName;


        // Generate a uniform random number in the *open* interval (0.0, 1.0).
        int GenerateRandomNumb();

        // Generate the random "output factor" (f > 0.0) variate
        // according to internal randomness and a certain distribution.
        //double generateOutputFactor();

    public:
        double generateOutputFactor();


        // These arrays will be moved into this object (shared).

        Formula(int *miq, int *moq, char **min, char **mon) : proficiencyLevel(0), inputQuantity(miq),
                                                              outputQuantity(moq), inputName(min), outputName(mon) {
            srand(time(0));
        }


        // Apply the formula onto the shared arrays representing
        // a given inventory.
        void apply(int *inventoryQuantity, char **inventoryName);

        // Increase this object's proficiency level unless it would
        // equal or exceed `PROFICIENCY_LEVEL_LIMIT`.
        void levelup();

        // getter methods for querying
        int *getInputQuantities();

        int *getOutputQuantities();

        char **getInputName();

        char **getOutputName();

        // using for testing functionality (client should not be able to do query this)
        int getProficiencyLevel();


    };

}

#endif /* _H_FORMULA_ */