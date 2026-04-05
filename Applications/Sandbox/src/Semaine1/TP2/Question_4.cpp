#include <cstdint> 
#include <cstring> 
#include <cstdio> 
#include <cmath> 
#include <limits> 
#include <iostream>
#include <numeric>
 
// Lire les bits d'un float — C++17 légal (pas de type punning UB) 
uint32_t floatBits(float f) { 
    uint32_t bits; 
    std::memcpy(&bits, &f, sizeof(float));
    return bits; 
} 
 
// Afficher les 3 champs d'un float 
void inspectFloat(float f) { 
    uint32_t bits = floatBits(f); 
    uint32_t sign     = (bits >> 31) & 0x1; 
    uint32_t exponent = (bits >> 23) & 0xFF; 
    uint32_t mantissa =  bits        & 0x7FFFFF; 
   
 
    printf("float %.10f\n", f); 
    printf("  Bits    : %08X\n", bits); 
    printf("  Signe   : %u\n", sign); 
    printf("  Exposant: %u (biais=127-> 2^%d)\n", exponent, (int)exponent-127); 
    printf("  Mantisse: %06X (1.%06X en hex)\n", mantissa, mantissa); 

} 
 
// Mesure de l'epsilon machine par boucle (ne PAS utiliser en production) 
float measureEpsilon() { 
    float eps = 1.0f; 
    while(1.0f + eps / 2.0f != 1.0f) { 
        eps /= 2.0f; 
    } 
    return eps;
}

 
int main() {
    float eps = measureEpsilon();
    std::cout<<"Epsilon par boucle donne: "<<eps<<"\n";
    std::cout<<"std::numeric_limits<float>::epsilon(): donne "<<std::numeric_limits<float>::epsilon()<<"\n";



return 0; 
} 