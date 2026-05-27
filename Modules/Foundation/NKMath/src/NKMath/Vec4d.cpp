#include"Vec4d.h"
using namespace NkMath;

    // Constructeurs
    Vec4d::Vec4d() : x(0.0),y(0.0), z(0.0),w(0.0) {}  
    Vec4d::Vec4d(double x, double y, double z, double w) : x(x), y(y), z(z),w(w) {}
    Vec4d::Vec4d(const Vec3d& v, double w) : x(v.x), y(v.y), z(v.z), w(w) {} 

  

    Vec3d Vec4d::ToVec3() const { 
        assert(!nearlyZero(w) && "Cannot dehomogenize: w is zero (direction)"); 
        return {x/w, y/w, z/w}; 
        
    } 
    double& Vec4d::operator[](int i) { assert(i<4); return (&x)[i]; } 

        // Garantie de layout mémoire pour glVertexAttribPointer 
    static_assert(sizeof(Vec3d) == 24, "Vec2d must be 16 bytes (3 doubles)"); 
  

    
