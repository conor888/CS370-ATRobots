//
// Created by Conor on 4/3/2018.
//

#include "atr2func.h"

int main() {
    std::string test_array[10] = {"test.", " TEsT. ", "TEST", "!@#$%^&*()", "test test.", "TEST TEST.",
                                  "abcdefghijklmnopqrstuvwxyz", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", ",./<>?:;'[]{}|-=_+",
                                  "hello world"};
    std::string expected_results[10] = {"TEST.", " TEST. ", "TEST", "!@#$%^&*()", "TEST TEST.", "TEST TEST.",
                                        "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", ",./<>?:;'[]{}|-=_+",
                                        "HELLO WORLD"};

    for(int i = 0; i < 10; i++) {
        if(atr2func::ucase(test_array[i]) == expected_results[i]) {
            std::cout << "Test #" << i + 1 << " successful!" << std::endl;
        } else {
            std::cout << "Test #" << i + 1 << " not successful." << std::endl;
        }
    }

    return 0;
}