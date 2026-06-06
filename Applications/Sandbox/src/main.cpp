#include <iostream>

#include <fstream>
#include <ostream>
#include <cstdint>
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
void drawline(Vec2d P0,Vec2d P1, uint32_t color, std::ofstream& Image, uint32_t* pixels, int width, int height) 
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

    std::vector<Vec2d> points;
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
    
        
        Image.open("NKImage.ppm");
        if (!Image.is_open()) {
            std::cerr << "Error: Could not open file for writing." << std::endl;
            return ;
         }
         Image << "P3\n";
         Image    << width << " " << height << "\n";
         Image << "255\n";
         int k=0;
        for (int i = 0; i < numPixels; i++){
           
            uint32_t pixel = pixels[i];

            uint8_t r = (pixel >> 24) & 255;
            uint8_t g = (pixel >> 16) & 0xFF; 
            uint8_t b = (pixel >> 8) & 0xFF;
            if(i % width == 0 && i != 0){
                Image << static_cast<int>(r) << " " << static_cast<int>(g) << " " << static_cast<int>(b) << " " << std::endl;
                continue;
            }
            Image << static_cast<int>(r) << " " << static_cast<int>(g) << " " << static_cast<int>(b) << " " ;
        }
        Image.close();   
        std::cout << "Image file created successfully." << std::endl;
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
    std::ofstream Image("NKImage.ppm");
    int width = 512;
    int height = 512;
    double angleX = 25.0; 
    double angleY = -41.0;
    
    uint32_t* pixels = new uint32_t[width * height];
    fillpixels(pixels, width, height);
    for(int i=0; i<8; i++)
{
    // Rote si tu veux
   /* cube[i].y = cube[i].y*std::cos(radians(angleX)) - cube[i].z*std::sin(radians(angleX));
   cube[i].z = cube[i].y*std::sin(radians(angleX)) + cube[i].z*std::cos(radians(angleX));
   
   cube[i].x = cube[i].x*std::cos(radians(angleY)) + cube[i].z*std::sin(radians(angleY));  
   cube[i].z = -cube[i].x*std::sin(radians(angleY)) + cube[i].z*std::cos(radians(angleY)); */

   cube[i].z += 2.0;
    double f = 500.0 / cube[i].z; 
    double x2d = cube[i].x * f + 256;
    double y2d = cube[i].y * f + 256;
    Pos2D.push_back(Vec2d(x2d, y2d));
    
}
for(int i=0; i<4; i++){
drawline(Vec2d(Pos2D[i].x, Pos2D[i].y), Vec2d(Pos2D[(i+1)%4].x, Pos2D[(i+1)%4].y), 0xFF0000FF, Image, pixels, width, height); 
if(i==3){
    drawline(Vec2d(Pos2D[i+4].x, Pos2D[i+4].y), Vec2d(Pos2D[(i+5)%8 + 4].x, Pos2D[(i+5)%8 + 4].y), 0xFF0000FF, Image, pixels, width, height); 
}else{
    drawline(Vec2d(Pos2D[i+4].x, Pos2D[i+4].y), Vec2d(Pos2D[(i+5)%8].x, Pos2D[(i+5)%8].y), 0xFF0000FF, Image, pixels, width, height); 
}
drawline(Vec2d(Pos2D[i].x, Pos2D[i].y), Vec2d(Pos2D[i+4].x, Pos2D[i+4].y), 0xFF0000FF, Image, pixels, width, height); 

}
delete[] pixels;
    
    

    return 0;
}