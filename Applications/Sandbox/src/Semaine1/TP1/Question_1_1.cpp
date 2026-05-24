#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <limits>
#include <iostream>
#include <numeric>

uint32_t floatBits(float f)
{
    uint32_t Bits;
    std::memcpy(&Bits,&f,sizeof(f));
    return Bits;
}

void inspectfloat (float f){
    uint32_t Bits = floatBits(f);
    uint32_t Signe = (Bits>>31)&0x1;
    uint32_t Exposant = (Bits >>23)&0xFF;
    uint32_t Mantisse = Bits & 0x7FFFFF;

    printf("float : %.10f \n",f);
    printf("bits : %08X \n",Bits);
    printf("signe : %u \n",Signe);
    printf("Exposant : %u (biais=127 -> 2^%d)\n",Exposant,(int)Exposant - 127);
    printf("Mantisse : %07X (1.%06X en hex)\n", Mantisse,Mantisse );  

}
void Epsilon(float eps)
{
    while(eps/2 + 1.0f != 1.0f){
        eps /=2;
    }
    printf("la valeur de eps est %.10f\n",eps);
    std::cout<<eps<<"\n";
    std::cout<<std::numeric_limits<float>::epsilon()<<"\n";
   
}
void ulp (float x)
{
    uint32_t bits ;// = *(uint32_t*)&x;
    std::memcpy(&bits,&x,sizeof(float));
    bits++;
    float next ;
    std::memcpy(&next,&bits,sizeof(float));
    printf("l'ulp au voisinage de %f est %.10f\n",x,next-x);
    std::cout<<"l'ulp au voisinage de " <<x<< "\test\t"<<next-x<<"\n";
}
bool nearlyEqualULP(float a, float b, int maxULP = 4){
    if(a==b) return true;
    int32_t ia, ib;
    std::memcpy(&ia,&a,sizeof(float));
    std::memcpy(&ib,&b,sizeof(float));
    
    if (ia < 0) ia = 0x80000000 - ia;
    if (ib < 0) ib = 0x80000000 - ib;

    return std::abs(ia-ib)<=maxULP;

}

int main() {
  printf("%u",std::sqrt(-1));
    //std::cout << flags << "\n" << big << "\n";
    return 0;
}

