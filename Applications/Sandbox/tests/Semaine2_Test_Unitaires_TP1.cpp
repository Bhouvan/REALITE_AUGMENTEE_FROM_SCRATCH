 #include <Unitest/Unitest.h>
#include <Unitest/TestMacro.h>

#include "NKMath/NKMath.h"

using namespace NkMath;

TEST_CASE(NkMathVec2d,DotProduct) {
Vec2d v1(1,0);
Vec2d v2(0,1);
Vec2d v3(3,4);
ASSERT_TRUE((Dot(v1,v2)) == 0);
ASSERT_TRUE((Dot(v1,v1)) == 1); 
ASSERT_TRUE((Dot(v3,v3) == 25));

}
TEST_CASE(NkMathVec2d,CrossProduct) {
Vec2d v1(1,0);
Vec2d v2(0,1);
Vec2d v3(3,4);
ASSERT_TRUE((Cross2D(v1,v2)) == 1);
ASSERT_TRUE((Cross2D(v2,v1)) == -1); 
}
TEST_CASE(NkMathVec2d,Normalized) {
Vec2d v3(3,4);
ASSERT_NEAR(1.0,v3.Normalized().Norm(),kEps);

}
TEST_CASE (NkMathVec2d, Access_Modifier)
{
    Vec2d v(2,-15);
    ASSERT_TRUE(v[0]==2);
    ASSERT_TRUE(v[1]==-15);
    v[1] =100;
    v[0] =20;
    ASSERT_TRUE (v[0]==20); 
    ASSERT_TRUE (v[1]==100);
    
   
}

TEST_CASE (NkMathVec2d, sizeofVec2d)
{
    Vec2d v(2,-15);
    ASSERT_TRUE(sizeof(v)==16);
    
   
}