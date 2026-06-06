#pragma once
#include "Vec3d.h"
#include "Vec2d.h"

 
namespace NkMath { 

struct Vec4d { 
    double x, y, z, w; 
    
 
    // Constructeurs 
    Vec4d() ;
    Vec4d(double x, double y, double z, double w);
    Vec4d(const Vec3d& v, double w); // fill constructor 
    
    Vec3d ToVec3() const;
    double& operator[](int i) ;
};
 
} // namespace NkMath 



  
    
   

        

    
