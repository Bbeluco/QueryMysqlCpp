#ifndef INPUT_VALIDATIONS_H_NAME
#define INPUT_VALIDATIONS_H_NAME

#include <iostream>
#include <limits>

namespace Inpt_validations {
    static void ignore_buffer_remains() {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    void check_if_cin_is_correct_and_clear() {
        if(std::cin.fail()){
            std::cin.clear();
            ignore_buffer_remains();
        }
    }
}

#endif