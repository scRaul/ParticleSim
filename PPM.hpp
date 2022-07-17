/*
 PPM class writes ppm3 files. Each pixel
 is colored in using rgb.
 
 covertImage function calls convert.sh
 to converts the ppm files into png
 using pnmtopng.exe
 */

#ifndef PPM__HPP
#define PPM__HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std; 


struct Color{
    int r;
    int g;
    int b;
    Color(int r,int g, int b):r(r),g(g),b(b){}
};
Color getRandomColor();

class PPM{
    
public:
    PPM(int width, int height,string folderPath);
    void setPixelColor(int x, int y, Color color);
    void drawImage(int frame=-1);
private:
    vector<int> imageData;
    vector<int> blankData;
    int pixelsAcross;
    int pixelsDown;
    int imageCount;
    string folderPath;
};
void convertImage(int frame);


#endif
