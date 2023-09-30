#ifndef _H_FORMULA_
#define _H_FORMULA_

namespace formula {

// Exclusive upper bound for proficiency levels (see class Formula).
    const int PROFICIENCY_LEVEL_LIMIT = 3;

    class Formula {
    private:
        // Non-negative proficiency level (always starts with 0).
        int proficiencyLevel;
        // Negative-number-terminated array of non-negative integers.
        //  NULL: Not allocated.
        //  first n >= 0 such that [n] < 0: Length is n.
        int *miq, *moq;
        // Null-terminated array of NUL-terminated strings.
        //  NULL: Not allocated.
        //  [0] == NULL: Empty.
        //  [n] == NULL: Length is n.
        char **min, **mon;

        // These arrays will be moved into this object (shared).
        Formula(int *miq, int *moq, char **min, char **mon)
                : proficiencyLevel(0), miq(miq), moq(moq), min(min), mon(mon)
        {}

        // Generate a uniform random number in the *open* interval (0.0, 1.0).
        double mopen01r();

        // Generate the random "output factor" (f > 0.0) variate
        // according to internal randomness and a certain distribution.
        double generateOutputFactor();

    public:
        // Apply the formula onto the shared arrays representing
        // a given inventory.
        void apply(int *q, char **n);

        // Increase this object's proficiency level unless it would
        // equal or exceed `PROFICIENCY_LEVEL_LIMIT`.
        void levelup();
    };

}

#endif /* _H_FORMULA_ */