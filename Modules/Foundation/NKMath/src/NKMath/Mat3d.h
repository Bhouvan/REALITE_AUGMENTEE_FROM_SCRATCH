#pragma once 
#include "Vec4d.h" 
#include <array> 
 
namespace NkMath { 
 
struct Mat3d { 
    // Stockage column-major : data[col*4 + row] 
    double data[9]; 
 
    Mat3d() { std::fill(data, data+9, 0.0); } 
 
    // Accès row,col/*  */ 
    double& operator()(int row, int col) { 
        assert(row>=0 && row<3 && col>=0 && col<3); 
        return data[col*3 + row];  // column-major ! 
    } 
    const double& operator()(int row, int col) const { 
        return data[col*3 + row]; 
    } 
 
    // Matrice identité 
    static Mat3d Identity() { 
        Mat3d m; 
        m(0,0) = m(1,1) = m(2,2) = 1.0; 
        return m; 
    } 
     // Produit matriciel O(64 multiplications pour 4×4) 
    Mat3d operator*(const Mat3d& o) const { 
        Mat3d result; 
        for(int row = 0; row < 3; row++) 
            for(int col = 0; col < 3; col++) { 
                double sum = 0.0; 
                for(int k = 0; k < 3; k++) 
                    sum += (*this)(row, k) * o(k, col); 
                result(row, col) = sum; 
            } 
        return result; 
    } 
 
    // Multiplication Mat3d × Vec3d 
    Vec3d operator*(const Vec3d& v) const { 
        return { 
            (*this)(0,0)*v.x + (*this)(0,1)*v.y + (*this)(0,2)*v.z,
            (*this)(1,0)*v.x + (*this)(1,1)*v.y + (*this)(1,2)*v.z,
            (*this)(2,0)*v.x + (*this)(2,1)*v.y + (*this)(2,2)*v.z     
        }; ;
    }
 
    // Transposée 
    Mat3d Transposed() const { 
        Mat3d t; 
        for(int r = 0; r < 3; r++) 
            for(int c = 0; c < 3; c++) 
                t(r,c) = (*this)(c,r); 
        return t; 
    } 
 
     // Pointer vers les données pour upload GPU 
    const double* DataPtr() const { return data; } 
    // Pour upload float GPU (convertir en float): 
    void ToFloat(float out[9]) const { 
        for(int i=0; i<9; i++) out[i] = (float)data[i]; 
    }  
}; 

    // Retourne false si la matrice est singulière (non inversible) 
    inline bool Inverse(const Mat3d& m, Mat3d& out) { 
    double aug[3][6]; 
    for(int r = 0; r < 3; r++) 
        for(int c = 0; c < 3; c++) { 
            aug[r][c]   = m(r,c); 
            aug[r][c+3] = (r == c) ? 1.0 : 0.0; 
        }
    
    for(int col = 0; col < 3; col++) { 
        int pivotRow = col; 
        for(int r = col+1; r < 3; r++) 
            if(std::abs(aug[r][col]) > std::abs(aug[pivotRow][col])) 
                pivotRow = r; 
 
        if(pivotRow != col) 
            for(int c = 0; c < 6; c++) 
                std::swap(aug[col][c], aug[pivotRow][c]); 
 
        if(std::abs(aug[col][col]) < 1e-10) return false; 
 
        double inv = 1.0 / aug[col][col]; 
        for(int c = 0; c < 6; c++) aug[col][c] *= inv; 
 
        for(int r = 0; r < 3; r++) { 
            if(r == col) continue; 
            double factor = aug[r][col]; 
            for(int c = 0; c < 6; c++) 
                aug[r][c] -= factor * aug[col][c]; 
        } 
    } 
 
    for(int r = 0; r < 3; r++) 
        for(int c = 0; c < 3; c++) 
            out(r,c) = aug[r][c+3]; 
    return true; 
}


} // namespace NkMath 

 


  