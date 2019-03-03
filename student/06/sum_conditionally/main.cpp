#include <iostream>
#include <vector>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

unsigned int divisible_by_3_or_7(unsigned int nb, unsigned int sum = 0)
{

    RECURSIVE_FUNC
    // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
    // ------------
                if ( nb == 0 ) {
                    return sum;
                } else {
                if (nb % 3 == 0 || nb % 7 == 0) {
                    sum += nb;
                }
                return divisible_by_3_or_7(nb - 1, sum);


                }
}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    unsigned int upper_bound = 0;
    std::cout << "Enter an upper bound: ";
    std::cin >> upper_bound;
    std::cout << "Sum of non-negative integers between 0 and " << upper_bound << " and divisible by 3 or 7 is " << divisible_by_3_or_7(upper_bound) << std::endl;
    return EXIT_SUCCESS;
}
#endif
