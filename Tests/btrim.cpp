//
// Created by Conor on 4/3/2018.
//

#include "atr2func.h"

int main() {
    std::string test_array[10] = {"Test.", " Test. ", "  Test.  ", " T e s t.", "TE ST.", "            test.",
                                  "\b\b\btest.", "\t\ttest.", "t\test.", "B"};
    std::string expected_results[10] = {"Test.", "Test.", "Test.", "T e s t.", "TE ST.", "test.", "test.", "test.",
                                        "t\test.", "B"};

    for(int i = 0; i < 10; i++) {
        if(atr2func::btrim(test_array[i]) == expected_results[i]) {
            std::cout << "Test #" << i + 1 << " successful!" << std::endl;
        } else {
            std::cout << "Test #" << i + 1 << " not successful." << std::endl;
        }
    }

    return 0;
}