#pragma once 
#include "Float.h" 
#include <cmath> 
#include <cassert> 
#include <cstdio> 


 
namespace NkMath { 

struct Vec2d  { 
    double x, y; 
    
 
    // Constructeurs 
    Vec2d() ;
    Vec2d(double x, double y);
    explicit Vec2d(double s) ; // fill constructor 
 
    // Accès par index — & pour permettre l'écriture 
    double& operator[](int i) ;

    const double& operator[](int i) const;
    
    // Opérateurs arithmétiques 
    Vec2d operator+(const Vec2d& o) const;
    Vec2d operator-(const Vec2d& o) const; 
    Vec2d operator*(double s)       const; 
    Vec2d operator/(double s)       const; 
    Vec2d operator-()               const;
 
    // Opérateurs composés 
    Vec2d& operator+=(const Vec2d& o);
    Vec2d& operator-=(const Vec2d& o);
    Vec2d& operator*=(double s);

    // Norme et normalisation 
    double Norm2() const ; 
    double Norm()  const ; 
 
    Vec2d Normalized() const;
 
    bool IsNormalized(double eps) const;
    void Print() const;
};

// Dot product : a·b = |a||b|cos(θ) 
inline double Dot(const Vec2d& a, const Vec2d& b) { 
    return a.x*b.x + a.y*b.y; 
} 
inline bool Compare(const Vec2d& a, const Vec2d& b)
{
    return (a.x==b.x && a.y==b.y)?true:false;
}
 
// Cross 2D (scalaire) : composante z du produit vectoriel 3D 
// Positif si b est à gauche de a, négatif si à droite 
inline double Cross2D(const Vec2d& a, const Vec2d& b) { 
    return a.x*b.y - a.y*b.x; 
} 
 
// Lerp linéaire 
inline Vec2d Lerp(const Vec2d& a, const Vec2d& b, double t) { 
    return {a.x + (b.x-a.x)*t, a.y + (b.y-a.y)*t}; 
} 
 
// Opérateur externe scalaire * Vec2d 
inline Vec2d operator*(double s, const Vec2d& v) { return v * s; } 

} // namespace NkMath 
