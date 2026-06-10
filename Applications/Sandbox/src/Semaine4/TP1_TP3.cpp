#include <iostream>

#include <fstream>
#include <ostream>
#include <cstdint>
#include <filesystem>
#include <vector>
#include "NKMath/NKMath.h"
using namespace NkMath;
const double M_PI = 3.14159265358979323846;
const double degrees(double radians) {
    return radians * 180.0 / M_PI;
}
const double radians(double degrees) {
    return degrees * M_PI / 180.0;
}

void fillpixels(uint32_t* pixels, int width, int height) {
    int numPixels = width * height;
    for (int i = 0; i < numPixels; i++){
        uint8_t r = 255;
        uint8_t g = 255; 
        uint8_t b = 255;
        pixels[i] = r << 24 | g << 16 | b << 8;
    }
}
void drawline(Vec2d P0,Vec2d P1, uint32_t color, uint32_t* pixels, int width, int height) 
{
    
        
        int numPixels = width * height;
        //  fillpixels(pixels, width, height);

    int dx = abs(static_cast<int>(P1.x) - static_cast<int>(P0.x));
    int dy = abs(static_cast<int>(P1.y) - static_cast<int>(P0.y));
    bool slope = dy > dx;
    if (slope) {
        std::swap(P0.x, P0.y);
        std::swap(P1.x, P1.y);
    }
    if (P0.x > P1.x) {
        std::swap(P0, P1);
    }
    dx = abs(static_cast<int>(P1.x) - static_cast<int>(P0.x));
    dy = abs(static_cast<int>(P1.y) - static_cast<int>(P0.y));

    int error = dx / 2;
    int ystep = (P0.y < P1.y) ? 1 : -1;
    int y = static_cast<int>(P0.y);

    
    for (int x = static_cast<int>(P0.x); x <= static_cast<int>(P1.x); x++) {
        
            // Set pixel at (y, x) to color
            Vec2d coord = (slope) ? Vec2d(y, x) : Vec2d(x, y);
            pixels[ static_cast<int>(coord.y) * width + static_cast<int>(coord.x) ] = color;
            error -= dy;     
            if (error < 0) {
            y += ystep;
            error += dx;
            }  
    }       
}

Vec4d cube[8] =
{
    {-0.5, -0.5, -0.5,1}, // A
    { 0.5, -0.5, -0.5,1}, // B
    { 0.5,  0.5, -0.5,1}, // C
    {-0.5,  0.5, -0.5,1}, // D

    {-0.5, -0.5,  0.5,1}, // E
    { 0.5, -0.5,  0.5,1}, // F
    { 0.5,  0.5,  0.5,1}, // G
    {-0.5,  0.5,  0.5,1}  // H
};

int main(int argc, char** argv){
     std::vector<Vec2d> Pos2D;
        Vec4d cubeCamera[8];
        int width = 512;
        int height = 512;
        uint32_t* pixels = new uint32_t[width * height];
    
        //Declaration des vecteurs Pour LookAt
        Vec3d eye(1,0,3);
        Vec3d target(0,0,0);
        Vec3d up (0,1,0);           
        Mat4d V = LookAt(eye,target, up);
        Vec3d AxRot (0,1,0);
        std::cout << "Chemin actuel : " << std::filesystem::current_path() << std::endl;
        //drawing the cube
        double fov = 60.0 * M_PI/180;
        double f = (width/2)/std::tan(fov/2); 
        double angle1 = radians(0.0);
        double angle2 = radians(70.0);
        Vec3d axis = {0.5, 1, 0}; 
        Vec3d axis1 = {0, -1, 1};
        Quat q1 = { cos(angle1/2), sin(angle1/2)*axis.x, sin(angle1/2)*axis.y, sin(angle1/2)*axis.z };
        Quat q2 = { cos(angle2/2), sin(angle2/2)*axis1.x, sin(angle2/2)*axis1.y, sin(angle2/2)*axis1.z };
        
        q1 = q1.Normalized();
        q2 = q2.Normalized();
        
        double angle = (2*M_PI/23);
        Mat4d R = RotateAxis(AxRot, angle);
        for(int i = 0; i <60 ; i++)
        {
            
            // calcul de angle pour CETTE frame
            double div = double(i)/60.0;
            Quat q3(Slerp(q1,q2,div));
            fillpixels(pixels, width, height);
            for(int k=0; k<8; k++)
            {
                 
                Vec3d temp(cube[k].x,cube[k].y,cube[k].z);
                temp = Rotate(q3,temp); 
                Vec4d tempback (temp.x,temp.y,temp.z,1);
                Vec4d rotated = R*tempback;
                cubeCamera[k] = V*rotated;
                 if(std::abs(rotated.z) < 0.0001)
                {
                    std::cout << "z trop petit\n";
                
                }
                std::cout << "rotated[k].z " << rotated.z << std::endl;
                
                //std::cout << "x2d :" << x2d << " " << "y2d :"<< y2d <<  std::endl;
                double x2d = cubeCamera[k].x * f /(-cubeCamera[k].z) + width/2;
                double y2d = cubeCamera[k].y * f /(-cubeCamera[k].z) + width/2;
                Pos2D.push_back(Vec2d(x2d, y2d));
                
            }
           
            for(int j=0; j<4; j++){ 
                // face avant
                drawline(
                    Pos2D[j],
                    Pos2D[(j+1)%4],
                    0xFF0000FF,pixels,width,height);

                // face arrière
                drawline(
                    Pos2D[j+4],
                    Pos2D[((j+1)%4)+4],
                    0xFF0000FF,pixels,width,height);

                // arêtes reliant les deux faces
                drawline(
                    Pos2D[j],
                    Pos2D[j+4],
                    0xFF0000FF,pixels,width,height); 

            } 
             // Une seule écriture PPM par frame
            std::string filename = "D:/Nkentseu/Applications/Sandbox/src/Semaine4/image/rotatedFrame" + std::to_string(i) + ".ppm";
            std::ofstream Image(filename);
            Image << "P6\n" << width << " " << height << "\n255\n";
            for(int p = 0; p < width * height; p++){
            uint8_t r = (pixels[p] >> 24) & 0xFF;
            uint8_t g = (pixels[p] >> 16) & 0xFF;
            uint8_t b = (pixels[p] >>  8) & 0xFF;
            
            Image.write(reinterpret_cast<char*>(&b), 1);
            Image.write(reinterpret_cast<char*>(&g), 1);
            Image.write(reinterpret_cast<char*>(&r), 1);       
            
            }  
            Pos2D.clear(); 
            
        }
        
        delete[] pixels;
    return 0;
}
