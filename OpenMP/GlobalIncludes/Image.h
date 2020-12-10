#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"
#include<string>

class Image
{
private:
    //unsigned char *** data;
    unsigned char *img;
    int horizSize;
    int vertSize;
    int channels;
public:
    Image(std::string);
    Image(int horizSize, int vertSize, int channels = 3);
    bool GetPixel(int x, int y, unsigned char *r, unsigned char *g, unsigned char *b, unsigned char *a);
    bool SetPixel(int x, int y, unsigned char r, unsigned char g = 0, unsigned char b = 0, unsigned char a = 0);
    int HorizSize();
    int VertSize();
    int Channels();
    unsigned char* Raw();
};

Image::Image(std::string filename)
{
    img = stbi_load(filename.c_str(), &horizSize, &vertSize, &channels, 0);
}

Image::Image(int newHorizSize, int newVertSize, int newChannels)
{
    img = new unsigned char[horizSize * vertSize * channels];
    channels = newChannels;
    vertSize = newVertSize;
    horizSize = newHorizSize;
}

bool Image::GetPixel(int x, int y, unsigned char *r, unsigned char *g, unsigned char *b, unsigned char *a)
{
    if(x < 0 || x >= horizSize || y < 0 || y >= vertSize)
    {
        return false;
    }

    unsigned char* pixelOffset = img + ((x + (horizSize * y)) * channels);

    if(channels > 0)
        *r = pixelOffset[0];
    if(channels > 1)
        *g = pixelOffset[1];
    if(channels > 2)
        *b = pixelOffset[2];
    if(channels > 3)
        *a = pixelOffset[3];

        //std::cout << (int) *r << " " << (int) *g << " " << (int) *b << " " << "/// ";
        //std::cout << x << " " << y <<std::endl;

    return true;
}

bool Image::SetPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    if(x < 0 || x >= horizSize || y < 0 || y >= vertSize)
    {
        return false;
    }

    unsigned char* pixelOffset = img + ((x + (horizSize * y)) * channels);

    if(channels > 0)
        pixelOffset[0] = r;
    if(channels > 1)
        pixelOffset[1] = g;
    if(channels > 2)
        pixelOffset[2] = b;
    if(channels > 3)
        pixelOffset[3] = a;

    return true;
}

int Image::Channels() {return channels;}
int Image::VertSize() {return vertSize;}
int Image::HorizSize() {return horizSize;}
unsigned char* Image::Raw() {return img;}