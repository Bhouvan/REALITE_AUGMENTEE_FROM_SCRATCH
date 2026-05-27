#include "Vec2d.h"




namespace NkMath{
    
    // Constructeurs
    Vec2d::Vec2d() : x(0.0), y(0.0) {}  
    Vec2d::Vec2d(double x, double y) : x(x), y(y) {}
    Vec2d::Vec2d(double s) : x(s), y(s) {} 

    // Accès par index — & pour permettre l'écriture
     double& Vec2d::operator[](int i) { 
        assert(i >= 0 && i < 2 && "Vec2d index out of bounds"); 
        return (&x)[i];  // garanti contigu en C++17 
    }  
   const double& Vec2d::operator[](int i) const { 
        assert(i >= 0 && i < 2 && "Vec2d index out of bounds"); 
        return (&x)[i]; 
    }  

    // Opérateurs arithmétiques
    Vec2d Vec2d::operator+(const Vec2d& o) const  { return {x+o.x, y+o.y}; }
    Vec2d Vec2d::operator-(const Vec2d& o) const { return {x-o.x, y-o.y}; } 
    Vec2d Vec2d::operator*(double s)        const { return {x*s, y*s}; } 
    Vec2d Vec2d::operator/(double s)        const { assert(!nearlyZero(s)); return {x/s, y/s}; } 
    Vec2d Vec2d::operator-()                const { return {-x, -y}; } 

    // Opérateurs composés 
    Vec2d& Vec2d::operator+=(const Vec2d& o) { x+=o.x; y+=o.y; return *this; } 
    Vec2d& Vec2d::operator-=(const Vec2d& o) { x-=o.x; y-=o.y; return *this; } 
    Vec2d& Vec2d::operator*=(double s)       { x*=s; y*=s; return *this; } 
          // Norme et normalisation 
    double Vec2d::Norm2() const { return x*x + y*y; } 
    double Vec2d::Norm()  const { return std::sqrt(Norm2()); }

     Vec2d Vec2d::Normalized() const { 
        double n = Norm(); 
        if(nearlyZero(n)) return Vec2d(0.0);  // vecteur nul → retourner zéro 
        return {x/n, y/n}; 
    } 

    bool Vec2d::IsNormalized(double eps = kEps) const { 
        return approxEq(Norm2(), 1.0, eps); 
    } 

    void Vec2d::Print() const { printf("Vec2d(%.6f, %.6f)\n", x, y); }

        // Garantie de layout mémoire pour glVertexAttribPointer 
    static_assert(sizeof(Vec2d) == 16, "Vec2d must be 16 bytes (2 doubles)"); 
    static_assert(offsetof(Vec2d, x) == 0, "x must be first"); 
    static_assert(offsetof(Vec2d, y) == 8, "y must be at offset 8"); 

    } 

  
    
   

        

    
