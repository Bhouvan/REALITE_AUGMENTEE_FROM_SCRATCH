#pragma once 
#include <cmath>
#include <numeric>
#include <iterator>


 
namespace nkentseu {
    namespace math {
// Constantes 
constexpr double kEps  = 1e-9;            // epsilon double pour tests 
constexpr float  kFEps = 1e-6f;           // epsilon float pour tests 
 
// Valide : ni NaN, ni Inf 
inline bool isFiniteValid(double x) { return std::isfinite(x); } 
inline bool isFiniteValid(float  x) { return std::isfinite(x); } 
 
// Proche de zéro 
inline bool nearlyZero(double x, double eps = kEps)  { return std::abs(x) < eps; } 
inline bool nearlyZero(float  x, float  eps = kFEps) { return std::abs(x) < eps; } 
 
// Égalité relative 
inline bool approxEq(double a, double b, double eps = kEps) { 
    if(a == b) return true; 
double maxAB = std::max(std::abs(a), std::abs(b)); 
return std::abs(a - b) <= eps * std::max(1.0, maxAB); 
} 
// Sommation de Kahan 
double kahanSum(const double* data, int n); 
    
double sommeNaive(const double* data, int n);

void RemplirTab(double* data,int n, double);

}
}
    
     // namespace NkMath 
