#include <Unitest/Unitest.h>
#include <Unitest/TestMacro.h>
#include <iterator>
#include <cstdlib> 
#include "NKMath/NKMath.h"

double M_PI = 3.14159265358979323846;
using namespace NkMath;
TEST_CASE(NkMathQuaternion, RotateAxis)
{
    Vec3d V1(0,1,0);
    Vec3d V2 (1,0,0);
    Vec3d V3(0,0,-1);
    
    ASSERT_TRUE(NkMath::Compare(Rotate(FromAxisAngle(Vec3d(0,1,0),M_PI/2),Vec3d(1,0,0)),Vec3d (0,0,-1)));
}
TEST_CASE(NkMathQuaternion, QuatMatQuat)
{
    srand(42);
    for(int i=0; i<50 ; i++)
    {   
        double random = rand() / static_cast<double>(RAND_MAX) * 10.0; 
        Quat q1(1,int(random)%3+2.84, random/4 *5.22, random/2*3.9);
        q1 = q1.Quat::Normalized();  
        Mat3d m = ToMat3(q1);
        Quat q2 = FromMat3(m); //return a normalized vector
        ASSERT_TRUE (NkMath::Compare(q1,q2));
    } 
    Quat q1(1,4, 8, 1.2);
    q1 = q1.Quat::Normalized();  
    Quat q2(q1*q1.Inverse());
    Quat q3(1,0,0,0);
    ASSERT_TRUE (NkMath::Compare(q2,q3));
    
    



}
