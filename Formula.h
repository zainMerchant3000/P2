#ifndef H_FORMULA_
#define H_FORMULA_

#include <random>

/*
 * //class invariant:
// constructor sets both input and output quantities along with names of each associated quantities as arrays
 size of input quantities and input and outputNames are determined by client
// the client is responsible for providing the number and name of each resource as an array
// the client can query the quantity and name of the input and output resources
// the input quantity and names are immutable after instantiation (are stable throughout the object's lifetime)
// class designer can simulate possible output of resources through Apply()

 copy semantics and deep copying to prevent data curroption (using heap memory)
Formula class is a subObject of Plan class (Formula object is passed as a member variable for composition in Plan class)
array of Formula objects will be injected in constructor for Plan
 */
namespace formula {
    /// Exclusive upper bound for proficiency levels (see class Formula).
    const int PROFICIENCY_LEVEL_LIMIT = 3;

    class Formula {
    private:
        /// Non-negative proficiency level (always starts with 0).
        int proficiencyLevel{};

        /// Store names of input and output resources.
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
        double GenerateOutputFactor();

        ///Generate random number based
        double GenerateRandomNumber();

      ///constructor takes
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





        /// simulate output of number of resources based on outputFactor and proficiency level
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