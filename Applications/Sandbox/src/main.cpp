#include <cstdint> 
#include <cstring> 
#include <cstdio> 
 
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
 
int main() { 
    inspectFloat(0.1f); 
    inspectFloat(1.0f); 
    inspectFloat(0.0f); 
    inspectFloat(-0.0f);   // -0 != +0 en bits, mais == en valeur ! 
    return 0; 
} 