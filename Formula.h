#ifndef H_FORMULA_
#define H_FORMULA_

#include <random>

namespace formula {
    /// Exclusive upper bound for proficiency levels (see class Formula).
    const int PROFICIENCY_LEVEL_LIMIT = 3;

    class Formula {
    private:
        /// Non-negative proficiency level (always starts with 0).
        int proficiencyLevel{};

        /// Null-terminated array of NUL-terminated strings.
        //  NULL: Not allocated.
        //  [0] == NULL: Empty.
        //  [n] == NULL: Length is n.
        const char **inputNames{}, **outputNames{};
        /// Count the number of each resource.
        int *inputQuantities{}, *outputQuantities{};
        /// Number of elements in `inputQuantities` and `inputNames`.
        int countInputs{};
        /// Number of elements in `outputQuantities` and `outputNames`.
        int countOutputs{};

        /// Used to gather randomness
        std::random_device rng_dev;
        /// Used to generate and maintain random state
        std::mt19937 rng;
        /// Distribution, uniform, [0.0,1.0).
        ///
        /// In `GenerateRandomNumber`, I exclude 0.0.
        std::uniform_real_distribution<double> dist100;

        /// Generate a uniform random number in the *open* interval (0.0, 1.0).
        // double GenerateRandomNumber();

        /// Generate the random "output factor" (f > 0.0) variate
        /// according to internal randomness and a certain distribution.
        // double GenerateOutputFactor();

    public:
        Formula(int n, int m, const int iq[], const char **in, const char **on) : proficiencyLevel(0),
                                                                                  inputQuantities(new int[n]),
                                                                                  outputQuantities(new int[m]),
                                                                                  inputNames(new const char *[n]),
                                                                                  outputNames(new const char *[m]),
                                                                                  countInputs(n),
                                                                                  countOutputs(m),
                                                                                  rng_dev(),
                                                                                  rng(rng_dev()),
                                                                                  dist100(0.0, 1.0) {
            for (int i = 0; i < n; i++) {
                inputQuantities[i] = iq[i];
                inputNames[i] = in[i];
            }
            for (int i = 0; i < m; i++) {
                outputQuantities[i] = 0; // setting outputQuantities to 0
                outputNames[i] = on[i];
            }
        }

        ~Formula() {
            delete[] this->inputQuantities;
            delete[] this->outputQuantities;
            delete[] this->inputNames;
            delete[] this->outputNames;
        }

        double GenerateRandomNumber();

        double GenerateOutputFactor();

        /// Apply the formula onto the shared arrays representing
        /// a given inventory.
        void Apply();

        /// Increase this object's proficiency level unless it would
        /// equal or exceed `PROFICIENCY_LEVEL_LIMIT`.
        void LevelUp();

        // getter methods for querying

        /// Count the input resources
        [[nodiscard]] int InputLength() const { return this->countInputs; }

        /// Count the output resources
        [[nodiscard]] int OutputLength() const { return this->countOutputs; }

        /// Copy the input quantities and names into designated array
        void CopyInputInto(int *q, const char **n) const;

        /// Copy the input quantities and names into designated array
        void CopyOutputInto(int *q, const char **n) const;

        //copy constructor
        Formula(const Formula &);

        //overloaded assignment operator
        Formula &operator=(const Formula &);

        //move copy constructor
        Formula(Formula &&) noexcept;

        //move overloaded assignment operator
        Formula &operator=(Formula &&) noexcept;
    };
}

#endif /* H_FORMULA_ */