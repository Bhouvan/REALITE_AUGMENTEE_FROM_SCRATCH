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
 
// Méthode naïve — dangereuse ! 
double varianceNaive(double* data, int n) { 
    double sum  = 0.0, sum2 = 0.0; 
    for(int i = 0; i < n; i++) { 
        sum  += data[i]; 
        sum2 += data[i] * data[i]; 
    } 
    double mean = sum / n; 
    // PROBLÈME : sum2 - sum*sum peut être négatif à cause de l'annulation ! 
    return (sum2 - sum*sum/n) / (n-1); 
}

// Méthode Welford — numériquement stable 
double varianceWelford(double* data, int n) { 
    double mean = 0.0, M2 = 0.0; 
    for(int i = 0; i < n; i++) { 
        double delta  = data[i] - mean; 
        mean += delta / (i + 1); 
        double delta2 = data[i] - mean; 
        M2   += delta * delta2; 
    } 
    return M2 / (n - 1); 
}


 
int main() {
    const int n =4;
    double variancenaive, variancewelford;
    double Tabcopie[]={1.e8,1.e8,1,2}; 
    
    variancenaive = varianceNaive(Tabcopie,n);
    variancewelford = varianceWelford(Tabcopie,n);
    printf("la methode naive nous donne une somme de %.10f \n",variancenaive);
    printf("la variance Welford nous donne %.10f\n",variancewelford);
    //delete[] Tabcopie;


return 0; 
} 