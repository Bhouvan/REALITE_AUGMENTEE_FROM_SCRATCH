#include <Unitest/Unitest.h>
#include <Unitest/TestMacro.h>
#include <iterator>
#include <cstdlib> 
#include "NKMath/NKMath.h"
using namespace NkMath;
TEST_CASE(NkMathVec3d, Cross)
{
    Vec3d v1(1,0,0);
    Vec3d v2(0,1,0);
    Vec3d v3 (0,0,1);
    Vec3d v4 (0,0,-1); 
    ASSERT_TRUE(Compare(Cross(v1,v2),v3));
    ASSERT_FALSE(Compare(Cross(v1,v2),v4));
}

TEST_CASE(NkMathVec3d, OrthoNomalite)
{
    Vec3d v1(1,0,0);
    Vec3d v2(0,1,0);
    Vec3d v3 (0,0,1);
    Vec3d v4 (0,0,-1); 
    ASSERT_TRUE(Compare(Cross(v1,v2),v3));
    ASSERT_FALSE(Compare(Cross(v1,v2),v4));
    srand(42);
    for (int i = 0; i < 10; i++) {
        Vec3d v1 ((rand()),(rand()+5),(rand()+10));
        Vec3d v2  ((rand()/18),(rand()/2),(rand()/2));
        Vec3d v3  ((rand()+50),(rand()),(rand()*3));
        
        OrthoBasis B;
        B = GramSchmidt(v1,v2,v3);
       
    
       //Norme |u| == 1
        ASSERT_NEAR(1.0,B.u.Norm(),kEps);
        ASSERT_NEAR(1.0,B.v.Norm(),kEps);
        ASSERT_NEAR(1.0,B.w.Norm(),kEps);

        ASSERT_NEAR(0.0,Dot(B.u,B.v),kEps);
        ASSERT_NEAR(0.0,Dot(B.u,B.w),kEps);
        ASSERT_NEAR(0.0,Dot(B.w,B.v),kEps);
    } 
    Vec3d v20 (15,-45,154.14);
    Vec3d v140 (-2,85,12.04);
    ASSERT_TRUE(Compare((Project(v20,v140)+Reject(v20,v140)),v20));
}