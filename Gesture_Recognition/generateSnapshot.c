#include "generateSnapshot.h"


/**
 * @brief calculBinomialCoeff                        n!
 *                             calcul ( n ) = -----------------
 *                                    ( k )    k! * ( n - k )!
 * @param n
 * @param k
 * @return result
 */
uint16_t calculBinomialCoeff (uint16_t n,uint16_t k){
    uint16_t denominator  = 1,numerator = 1,combinaisons;


    for(uint16_t i = k; i > 1; i--) {
        denominator  *= i;
    }

    for(uint16_t j = n; j >= n - k + 1; j--) {
        numerator *= j;
    }

    combinaisons = numerator / denominator  ;
    return combinaisons;
}


