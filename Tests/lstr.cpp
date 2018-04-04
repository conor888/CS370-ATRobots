//Test written by Nick Spina

#include <iostream>
#include <string>
#include "atr2func.h"

int main(void){

    std::string test_array[10] = {"CS370ATROBOTS", "CS370ATROBOTS", "CS370ATROBOTS", "CS370ATROBOTS", "CS370ATROBOTS", "CS370ATROBOTS",
                                  "CS370ATROBOTS", "CS370ATROBOTS", "CS370ATROBOTS", "CS370ATROBOTS"};

    int test_array2[10] = {0,1,2,3,4,5,6,7,8,9};

    std::string expected_results_lstr[10] = {"", "C", "CS", "CS3", "CS37", "CS370", "CS370A", "CS370AT",
                                        "CS370ATR", "CS370ATRO"};

    std::string expected_results_rstr[10] = {"", "S", "TS", "OTS", "BOTS", "OBOTS", "ROBOTS", "TROBOTS",
                                        "ATROBOTS", "0ATROBOTS"};

    std::string actual_results_lstr[10];
    for (int i = 0; i < 10; i++){
        actual_results_lstr[i] = atr2func::lstr(test_array[i], test_array2[i]);
    }

    std::string actual_results_rstr[10];
    for (int i = 0; i < 10; i++){
        actual_results_rstr[i] = atr2func::rstr(test_array[i], test_array2[i]);
    }

    for(int i = 0; i < 10; i++) {

        std::cout << actual_results_lstr[i] << std::endl;

    }

    for(int i = 0; i < 10; i++) {

        if(actual_results_lstr[i] == expected_results_lstr[i]) {
            std::cout << "Test #" << i + 1 << " for lstr successful!" << std::endl;
        } else {
            std::cout << "Test #" << i + 1 << " for lstr not successful." << std::endl;
        }
    }

    for(int i = 0; i < 10; i++) {

        std::cout << actual_results_rstr[i] << std::endl;

    }

    for(int i = 0; i < 10; i++) {

        if(actual_results_rstr[i] == expected_results_rstr[i]) {
            std::cout << "Test #" << i + 1 << " for rstr successful!" << std::endl;
        } else {
            std::cout << "Test #" << i + 1 << " for rstr not successful." << std::endl;
        }
    }

}

