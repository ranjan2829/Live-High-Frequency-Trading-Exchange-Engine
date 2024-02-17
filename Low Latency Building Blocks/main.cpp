#include "macros.h"

int main() {
    int value = 9;

    // Example of ASSERT:
    ASSERT(value > 0, "Value should be positive!");

    // Example of LIKELY:
    if (LIKELY(value == 10)) {
        std::cout << "Value is 10, as expected." << std::endl;
    }

    // Example of FATAL:
    if (value < 0) {
        FATAL("Invalid value encountered!");
    }

    return 0;
}
