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
 


/*  
// Vec3d avec cross product 
// Vec3d avec cross product 
struct Vec3d { 
    double x, y, z; 
 
    // ... (même structure que Vec2d pour les opérateurs de base) 
 
    double Norm2() const { return x*x + y*y + z*z; } 
    double Norm()  const { return std::sqrt(Norm2()); } 
    Vec3d Normalized() const { 
        double n = Norm(); 
        if(nearlyZero(n)) return Vec3d(0.0); 
        return {x/n, y/n, z/n}; 
    } 
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
 
// Vérification : 
// Cross({1,0,0}, {0,1,0}) = {0,0,1}  (axe Z = X × Y) 
// Cross({0,1,0}, {1,0,0}) = {0,0,-1} (non-commutatif !) 
// Cross({1,0,0}, {1,0,0}) = {0,0,0}  (vecteurs parallèles → zéro)
// Projection de a sur b : composante de a dans la direction de b 
// proj(a,b) = b × (a·b / |b|²) 
inline Vec3d Project(const Vec3d& a, const Vec3d& b) { 
    double b2 = b.Norm2(); 
    assert(!nearlyZero(b2) && "Cannot project onto zero vector"); 
    return b * (Dot(a, b) / b2); 
} 
 
// Rejection de a par rapport à b : composante de a perpendiculaire à b 
// reject(a,b) = a - proj(a,b) 
inline Vec3d Reject(const Vec3d& a, const Vec3d& b) { 
    return a - Project(a, b); 
}
// Application : décomposer le vecteur vitesse en composantes normale et tangentielle 
// velocity_n = Project(velocity, normal)   ← vitesse vers la surface 
// velocity_t = Reject(velocity, normal)    ← vitesse le long de la surface 
// Utilisé dans la résolution de collision : n'inverser que velocity_n 


// Orthogonalisation de Gram-Schmidt 
// Entrée : 3 vecteurs (peuvent être non orthogonaux) 
// Sortie : 3 vecteurs orthonormaux (base orthonormale) 
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
  */
// Utilisation : constructeur LookAt (semaine 3), décomposition polaire (M05)

/* 
struct Vec4d { 
    double x, y, z, w; 
 
    Vec4d() : x(0), y(0), z(0), w(0) {} 
    Vec4d(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {} 
    Vec4d(const Vec3d& v, double w) : x(v.x), y(v.y), z(v.z), w(w) {} 
 
    // Conversion vers Vec3d — déhomogénéisation 
    Vec3d ToVec3() const { 
        assert(!nearlyZero(w) && "Cannot dehomogenize: w is zero (direction)"); 
        return {x/w, y/w, z/w}; 
    } 
 
    // Accès 
    double& operator[](int i) { assert(i<4); return (&x)[i]; } 
};

// Convention : 
// w = 1.0 → POINT dans l'espace (la translation de Mat4 s'applique) 
// w = 0.0 → DIRECTION (la translation ne s'applique PAS) 
// Exemple : 
Vec4d point     = {1.0, 2.0, 3.0, 1.0};  // point (1,2,3) 
Vec4d direction = {0.0, 1.0, 0.0, 0.0};  // direction Y+ (vers le haut) 
// Projection (semaine 3) : Mat4d × Vec4d → Vec4d → ToVec3() (÷ par w) 
// Garantie layout mémoire 
static_assert(sizeof(Vec4d) == 32, "Vec4d must be 32 bytes"); 
 */

} // namespace NkMath 
