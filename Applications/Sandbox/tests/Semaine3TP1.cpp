#include <Unitest/Unitest.h>
#include <Unitest/TestMacro.h>
#include <iterator>
#include "NKMath/NKMath.h"

using namespace NkMath;
bool bBool = true;
const double M_PI = 3.14159265358979323846;

TEST_CASE(NKMathMat4d , Identité_inverse) {
    Mat4d TabMat[10];
    Mat4d singular;
    singular.data[0] = 1; singular.data[1] = 2; singular.data[2] = 3; singular.data[3] = 4;
    singular.data[4] = 0; singular.data[5] = 0; singular.data[6] = 0; singular.data[7] = 0;
    singular.data[8] = 1; singular.data[9] = 2; singular.data[10] = 3; singular.data[11] = 4;
    singular.data[12] = 0; singular.data[13] = 1; singular.data[14] = 2; singular.data[15] = 3;
    
    for(int i=0; i<10; i++){
        for(int j=0; j<16; j++){
            TabMat[i].data[j] = rand() / static_cast<double>(RAND_MAX) * 10.0; 
        }
    }
    for(int i = 0; i < 10; i++) {
        Mat4d result = TabMat[i] * Mat4d::Identity();

        for(int j = 0; j < 16; j++) {
            // ASSERT_NEAR(result.data[j], TabMat[i].data[j], kEps);
            bBool = bBool && (approxEq(result.data[j], TabMat[i].data[j], kEps))? true:false;;
        }
        ASSERT_TRUE(bBool);

        bBool = true;        
    }

    for(int i = 0; i < 10; i++) 
        {   Mat4d Mat1 ;
            bool invertible = Inverse(TabMat[i],Mat1);
            if(invertible)
            {
                Mat4d result = Mat1 * TabMat[i];
                for(int j = 0; j < 16; j++) {
                    bBool = bBool &&(approxEq(result.data[j], Mat4d::Identity().data[j], kEps))? true:false;;
                }
               
            } 
            ASSERT_TRUE(bBool);   
            bBool = true;
        }   
    
    ASSERT_FALSE(Inverse(singular, singular));
    Vec4d vec (0,0,-1,1);
    Mat4d R = RotateAxis({0,1,0}, M_PI/2);
    Vec4d v = R * Vec4d{1,0,0,1};
    
    bBool = bBool && (approxEq(v.x, vec.x, kEps));
    bBool = bBool && (approxEq(v.y, vec.y, kEps));
    bBool = bBool && (approxEq(v.z, vec.z, kEps));
    bBool = bBool && (approxEq(v.w, vec.w, kEps));
    ASSERT_TRUE(bBool);
    bBool = true;

}
 