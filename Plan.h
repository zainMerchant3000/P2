//
// Created by zain7 on 10/3/2023.
//
#ifndef P2_PLAN_H
#define P2_PLAN_H

#include "Formula.h"
/*
 * //class invariant:
// constructor uses dependency injection to insert an intial array of Formulas where size is determined by client
 // Array of Formulas passed as member variable consistent with Composition
// the client is responsible for setting the size of initial array of formulas along with passing the array of objects
 //client responsible for passing heap-allocated Formula object to append
 // client responsible for providing index and Formula object to replace in array of Formula objects
 // client responsible for deallocating any heap memory used for instantiating new objects
 // client can manipulate and change Formula objects through adding to end of array,
//


 copy semantics and deep copying to prevent data curroption (using heap memory)

 */

namespace plan {
    // Import the class Formula from formula into plan
    using formula::Formula;

    /*
     * * 1) visual understanding
        original formula array (from : Formula[0] - Formula[10]

Formula[0], Formula[1], Formula[2]

remove:  Formula[0], Formula[1]

replace: Formula[0], Formula[1], Formula[2] -> different one

     */
    class Plan {
    private:
        /// Every member is a valid (non-null and alive) pointer in the lifetime of this Plan object.
        /// Every member refers to a HEAP-allocated (as opposed to stack- or statically-allocated) object.
        Formula **formulas;
        /// Count the number of `formulas`.
        int numFormulas;
    public:
        /// Count the number of formulas.
        int getNumFormula();

        Plan() : formulas(nullptr), numFormulas(0) {}

        /// Take an existing array of heap-allocated formulas
        ///
        /// ## DEPENDENCY INJECTION
        ///
        /// It's the user's responsibility to create these Formula objects.
        /// \param arrayFormula Array of valid, heap-allocated pointers to Formula objects that outlive this Plan object.
        /// \param sizeOfFormulaArray Count (non-negative) of said array.
        Plan(Formula **arrayFormula,
             int sizeOfFormulaArray) {
            // The array itself is borrowed rather than moved.
            // So, create our own copy of the array.
            formulas = new Formula *[sizeOfFormulaArray];
            numFormulas = sizeOfFormulaArray;
            for (int i = 0; i < sizeOfFormulaArray; i++) {
                formulas[i] = arrayFormula[i];
            }
        }
        ~Plan();

        // Copy
        Plan(const Plan &);

        Plan &operator=(const Plan &);

        // Move
        Plan(Plan &&) noexcept;

        Plan &operator=(Plan &&) noexcept;

        /// Append a new Formula to end of sequence of Formula objects
        void addFormula(Formula *formula);

        /// Remove a Formula from the end of the sequence of Formula objects
        void removeLastFormula();

        /// Given a `formula` allocated in the HEAP memory, replace the old formula at `indexRep` with
        /// this new pointer by sharing (no copy).
        void replaceFormula(int indexRep, Formula *formula);
    };
}

#endif //P2_PLAN_H
