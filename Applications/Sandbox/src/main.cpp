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
float kahanSum(const float* data, int n){
    float sum = 0.0f;
    float comp = 0.0f;
    
    for(int i = 0;i<n;i++){
        float y = data[i] - comp;
        float t = sum + y;
        comp = (t-sum)-y;
        sum = t;
    }
    return sum;

}

float sommeNaive(const float* data, int n){
    
   return std::accumulate(data, data + n, 0.0f);
}

void RemplirTab(float* data,int n){
    
    
    for(int i= 0;i<n;i++)
    {
    data[i]=0.1f;
     
    }

}
 
int main() {
    const int n = 1000000;
    float sum1, sum2;
    float Tabcopie[n]; 
    RemplirTab(Tabcopie,n);
    sum1 = sommeNaive(Tabcopie,n);
    sum2 = kahanSum(Tabcopie,n);
    printf("la methode naive nous donne une somme de %.10f \n",sum1);
    printf("la somme de kahan nous donne %.10f\n",sum2);


return 0; 
} 