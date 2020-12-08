#include<cstdio>
#include<iostream>
#include<fstream>

#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

#define STBIW_WINDOWS_UTF8
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include"stb_image_write.h"

#define MY_ACCESS_R 0
#define MY_ACCESS_G 1
#define MY_ACCESS_B 2
#define MY_ACCESS_A 3


int main(int argc, char const *argv[])
{

    /*const int width = 200;
    const int height = 100;
    #define CHANNEL_NUM 3

    /** NOTICE!! You have to use uint8_t array to pass in stb function  /
    // Because the size of color is normally 255, 8bit.
    // If you don't use this one, you will get a weird imge.
    uint8_t* pixels = new uint8_t[width * height * CHANNEL_NUM];

    int index = 0;
    for (int j = height - 1; j >= 0; --j)
    {
    for (int i = 0; i < width; ++i)
    {
    float r = (float)i / (float)width;
    float g = (float)j / (float)height;
    float b = 0.2f;
    int ir = int(255.99 * r);
    int ig = int(255.99 * g);
    int ib = int(255.99 * b);

    pixels[index++] = ir;
    pixels[index++] = ig;
    pixels[index++] = ib;
    }
    }
    
    // if CHANNEL_NUM is 4, you can use alpha channel in png
    stbi_write_png("stbpng.png", width, height, CHANNEL_NUM, pixels, width * CHANNEL_NUM);

    // You have to use 3 comp for complete jpg file. If not, the image will be grayscale or nothing.
    stbi_write_jpg("stbjpg3.jpg", width, height, 3, pixels, 100);
    delete[] pixels;

    return 0;
    */
    int x = 600, y = 900, channels  = 3;
    int desired_no_channels = 3;
    
    unsigned char *img =  new unsigned char[x * y * channels]; //= stbi_load("gato.png", &x, &y, &channels, desired_no_channels);

    std::cout << "X: " << x << " Y: " << y << " Chn: " << channels << std::endl;

    /*if(img == NULL) 
    {
        printf("Error in loading the image\n");
        exit(1);
    }*/

    for (size_t i = 0; i < x; i++)
    {
        for (size_t j = 0; j < y; j++)
        {
            std::cout << "b";
            unsigned char* pixelOffset = img + ((i + (y * j)) * channels);
            pixelOffset[0] = (int) 255.0f * (i/x);
            pixelOffset[1] = (int) 255.0f * (j/y);
        }
    }
    
    std::ofstream file("gato_new.ppm");

    file << "P3\n" << x << " " << y << "\n255 \n";
    

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            unsigned char* pixelOffset = img + ((i + (y * j)) * channels);
            //file << (int) img[((i * j)) + MY_ACCESS_R] << " " << (int) img[(i * j) + MY_ACCESS_G] << " " << (int) img[(i * j) + MY_ACCESS_B] << " \n";
            file << (int) pixelOffset[0] << " " << (int) pixelOffset[1] << " " << (int) pixelOffset[2] << " ";
        }
        file << "\n";
    }

    file.flush();
    file.close();

    /*int result = stbi_write_png("gato_new.png", x, y, desired_no_channels, img, x * channels);
    std::cout << "Result: " << result << std::endl;

    for (size_t i = 0; i < x; i++)
    {
        for (size_t j = 0; j < y; j++)
        {
            unsigned char* pixelOffset = img + ((i + (y * j)) * channels);
            printf("%d ", pixelOffset[0]);
        }
        printf("\n");
    }/*/
    
    return 0;
}
