#pragma once 
#include "Float.h" 
#include "Vec2d.h"
#include <cmath> 
#include <cassert> 
#include <cstdio>



 
namespace NkMath { 

struct Vec3d { 
    double x, y, z; 
    
 
    // Constructeurs 
    Vec3d() ;
    Vec3d(double x, double y, double z);
    explicit Vec3d(double s) ; // fill constructor 
    
    // Opérateurs arithmétiques 
    Vec3d operator+(const Vec3d& o) const;
    Vec3d operator-(const Vec3d& o) const; 
    Vec3d operator*(double s)       const; 
    Vec3d operator/(double s)       const; 
    Vec3d operator-()               const;
 
    // Opérateurs composés 
    Vec3d& operator+=(const Vec3d& o);
    Vec3d& operator-=(const Vec3d& o);
    Vec3d& operator*=(double s);

    // Norme et normalisation 
    double Norm2() const ; 
    double Norm()  const ; 
    
 
    Vec3d Normalized() const;
 
    bool IsNormalized(double eps) const;
    void Print() const;
};

 
// Cross product 3D : a × b 
// Résultat : vecteur perpendiculaire à a et b 
// Norme = |a||b|sin(θ) = aire du parallélogramme formé par a et b 
// Direction : règle de la main droite (CCW positif en OpenGL) 
inline Vec3d Cross(const Vec3d& a, const Vec3d& b) { 
    return { 
        a.y*b.z - a.z*b.y,   // composante x 
        a.z*b.x - a.x*b.z,   // composante y 
        a.x*b.y - a.y*b.x    // composante z 
    }; 
} 
inline bool Compare(const Vec3d& a, const Vec3d& b)
{
    return (approxEq(a.x,b.x) && approxEq(a.y,b.y) && approxEq(a.z,b.z))?true:false;
}

// Projection de a sur b : composante de a dans la direction de b 
// proj(a,b) = b × (a·b / |b|²) 
inline double Dot (const Vec3d& a, const Vec3d& b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}
inline Vec3d Project(const Vec3d& a, const Vec3d& b) { 
    double b2 = b.Norm2(); 
    assert(!nearlyZero(b2) && "Cannot project onto zero vector"); 
    return b * (Dot(a, b) / b2); 
} 
 
// Rejection de a par rapport à b : composante de a perpendiculaire à b 
// reject(a,b) = a - proj(a,b) 
inline Vec3d Reject(const Vec3d& a, const Vec3d& b) { 
    return a - Project(a, b); }

// Vérification : 
// Cross({1,0,0}, {0,1,0}) = {0,0,1}  (axe Z = X × Y) 
// Cross({0,1,0}, {1,0,0}) = {0,0,-1} (non-commutatif !) 
// Cross({1,0,0}, {1,0,0}) = {0,0,0}  (vecteurs parallèles → zéro)

 
// Application : décomposer le vecteur vitesse en composantes normale et tangentielle 
// velocity_n = Project(velocity, normal)   ← vitesse vers la surface 
// velocity_t = Reject(velocity, normal)    ← vitesse le long de la surface 
// Utilisé dans la résolution de collision : n'inverser que velocity_n

struct OrthoBasis { 
    Vec3d u, v, w;  // garantis orthogonaux et normalisés 
}; 
 
inline OrthoBasis GramSchmidt(Vec3d a, Vec3d b, Vec3d c) { 
    // Étape 1 : normaliser a → u 
    Vec3d u = a.Normalized(); 
    assert(!nearlyZero(u.Norm()) && "First vector is zero"); 
 
    // Étape 2 : ôter la composante u de b → v 
    Vec3d v = (b - Project(b, u)).Normalized(); 
    assert(!nearlyZero(v.Norm()) && "Vectors are collinear"); 
 
    // Étape 3 : ôter les composantes u et v de c → w 
    Vec3d w = (c - Project(c, u) - Project(c, v)).Normalized(); 
    assert(!nearlyZero(w.Norm()) && "Vectors are coplanar"); 
 
    return {u, v, w}; 
} 

} // namespace NkMath 
