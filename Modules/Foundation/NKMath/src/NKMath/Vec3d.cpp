#include "Vec3d.h"
#include "Vec2d.h"




namespace NkMath{
    
    // Constructeurs
    Vec3d::Vec3d() : x(0.0),y(0.0), z(0.0) {}  
    Vec3d::Vec3d(double x, double y, double z) : x(x), y(y), z(z) {}
    Vec3d::Vec3d(double s) : x(s),y(s),z(s) {} 

  

    // Opérateurs arithmétiques
    Vec3d Vec3d::operator+(const Vec3d& o) const  { return {x+o.x, y+o.y, z+o.z}; }
    Vec3d Vec3d::operator-(const Vec3d& o) const { return {x-o.x, y-o.y, z-o.z}; } 
    Vec3d Vec3d::operator*(double s)        const { return {x*s, y*s,z*s}; } 
    Vec3d Vec3d::operator/(double s)        const { assert(!nearlyZero(s)); return {x/s, y/s, z/s}; } 
    Vec3d Vec3d::operator-()                const { return {-x, -y, -z}; } 

    // Opérateurs composés 
    Vec3d& Vec3d::operator+=(const Vec3d& o) { x+=o.x; y+=o.y; z+=o.z; return *this; } 
    Vec3d& Vec3d::operator-=(const Vec3d& o) { x-=o.x; y-=o.y; z-=o.z; return *this; } 
    Vec3d& Vec3d::operator*=(double s)       { x*=s; y*=s; z*=s; return *this; } 
          // Norme et normalisation 
    double Vec3d::Norm2() const { return x*x + y*y + z*z;} 
    double Vec3d::Norm()  const { return std::sqrt(Norm2()); }

     Vec3d Vec3d::Normalized() const { 
        
        double n = Norm(); 
        if(nearlyZero(n)) 
        {  
            return Vec3d(0.0);
        }//assert(!nearlyZero(n)&&"n is zero "); //return Vec3d(0.0);  // vecteur nul → retourner zéro 
        return {x/n, y/n, z/n}; 
    } 

    bool Vec3d::IsNormalized(double eps = kEps) const { 
        return approxEq(Norm2(), 1.0); 
    } 

    void Vec3d::Print() const { printf("Vec3d(%.6f, %.6f,%.6f)\n", x, y, z); }

        // Garantie de layout mémoire pour glVertexAttribPointer 
    static_assert(sizeof(Vec3d) == 24, "Vec2d must be 16 bytes (3 doubles)"); 
    static_assert(offsetof(Vec3d, x) == 0, "x must be first"); 
    static_assert(offsetof(Vec3d, y) == 8, "y must be at offset 8"); 
    static_assert(offsetof(Vec3d, z) == 16, "y must be at offset 16"); 

    } 

  
    
   

        

    
