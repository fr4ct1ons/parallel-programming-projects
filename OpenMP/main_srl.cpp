#pragma once
#include<cstdio>
#include<iostream>
#include<fstream>
#include<cmath>
#include<ctime>
#include<cstdlib>

#define STBIW_WINDOWS_UTF8
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include"stb_image_write.h"

#include"Image.h"
#include"testingAux.h"

bool GetPixel(unsigned char *image, int horizSize, int vertSize, int x, int y, int channels, unsigned char *r, unsigned char *g, unsigned char *b, unsigned char *a)
{
    if(x < 0 || x >= horizSize || y < 0 || y >= vertSize)
    {
        return false;
    }

    //for (int i = 0; i < y; i++)
    //{
    //    for (int j = 0; j < x; j++)
    //    {
            unsigned char* pixelOffset;
            pixelOffset = image + ((x + (horizSize * y)) * channels);
            r = channels > 0 ? pixelOffset + 0 : NULL;
            g = channels > 1 ? pixelOffset + 1 : NULL;
            b = channels > 2 ? pixelOffset + 2 : NULL;
            a = channels > 3 ? pixelOffset + 3 : NULL;
            return true;
    //    }
    //}

    return true;
}

int main(int argc, char const *argv[])
{
    if(argc < 5)
    {
        std::cout << "INVALID PARAMETERS" << std::endl;
        exit(1);
    }

    std::string resultPath="INVALID.NULL";
    bool enableDebug = false;
    int inverseAmount = 1;

    for (size_t i = 1; i < argc; i++)
    {
        //std::cout << "Param " << argv[i] << std::endl;

        if(!strcmp(argv[i], "-result"))
        {
            resultPath = argv[i+1];
        }
        
        if (!strcmp(argv[i], "-debug"))
        {
            std::cout << "Debug enabled." << std::endl;
            enableDebug = true;
        }
        
        if(!strcmp(argv[i], "-inverseAmount"))
        {
            inverseAmount = atoi(argv[i+1]);
        }
    }

    std::string filename= argv[1];

    if(enableDebug)
    {
        std::cout << "Opening file: " << filename << std::endl;
    }

    Image image(filename.c_str());
    Image resultImage(image.HorizSize(), image.VertSize(), image.Channels());
    
    int mosaicHorizAmount = atoi(argv[2]), mosaicVertAmount = atoi(argv[3]);
    int mosaicHorizSize = atoi(argv[4]), mosaicVertSize = atoi(argv[5]);
    
    if(enableDebug)
    {
        std::cout << "horizSize: " << image.HorizSize() << " vertSize: " << image.VertSize() << " Chn: " << image.Channels() << std::endl;
        std::cout << "1: " << (int)image.Raw()[0] << " 2: " << (int)image.Raw()[1] << " 3: " << (int)image.Raw()[2] << std::endl;
        std::cout << "mosaic size: " << mosaicHorizSize << "," << mosaicVertSize << " mosaic amount: " << mosaicHorizAmount << "," << mosaicVertAmount << std::endl;
    }

    unsigned char midR = 0, midG = 0, midB = 0, midA =0;
    if(enableDebug)
    {
        std::cout << "Starting..." << std::flush;
    }
    clock_t begin = clock();
    for (int i = 0; i < image.VertSize(); i = i + (image.VertSize() / mosaicVertAmount))
    {
        //std::cout << i << std::endl;
        for (int j = 0; j < image.HorizSize(); j = j + (image.HorizSize() / mosaicHorizAmount))
        {

            //std::cout << (int) midR << " " << (int) midG << " " << (int) midB << " " << "/// ";
            //std::cout << i << " " << j <<std::endl;

            if(image.GetPixel(j, i, &midR, &midG, &midB, &midA))
            {
                //std::cout << "Valid value" << std::endl;
            }
            /*std::cout << "New: \n" <<(int) midR << " " << (int) midG << " " << (int) midB << " " << "/// ";
            std::cout << i << " " << j <<std::endl;*/

            for (int h = i; h < i + mosaicVertSize; h++)
            {
                for (int w = j; w < j + mosaicHorizSize; w++)
                {
                    unsigned char r, g, b, a;

                    image.GetPixel(w, h, &r, &g, &b, &a);
                    resultImage.SetPixel(w, h, midR, midG, midB, midA);
                    
                    for (size_t t = 0; t < inverseAmount; t++)
                    {
                        resultImage.GetPixel(w, h, &r, &g, &b, &a);
                        resultImage.SetPixel(w, h, 255 -r, 255-g, 255-b, 255-a);
                    }
                
                    //image.SetPixel(w, h, r, g, b, a);
                    //image.SetPixel(w, h, 255 -r, 255-g, 255-b, 255-a);
                }
                
            }
            
        }
    }

    clock_t end = clock();
    if(enableDebug)
    {
        std::cout << "Done!" << std::endl;
    }
    double duration = (double) (end - begin)/CLOCKS_PER_SEC;

    if(resultPath != "INVALID.NULL")
    {
        int result = stbi_write_png(resultPath.c_str(), resultImage.HorizSize(), resultImage.VertSize(), resultImage.Channels(), resultImage.Raw(), resultImage.HorizSize() * resultImage.Channels());
        std::cout << "Result: " << result << std::endl;
    }

    if(enableDebug)
        std::cout << "duration: " << duration << std::endl;

    std::stringstream results;

    results << std::fixed  << mosaicHorizAmount * mosaicVertAmount * mosaicHorizSize * mosaicVertSize << " , " << duration << " , " << "SERIAL , 1" << std::endl;
    TestingAux::WriteToResults(results);

    if(enableDebug)
    {
        std::cout << results.str() << std::endl;
    }
    return 0;
}
