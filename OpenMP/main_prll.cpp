#include<omp.h>
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

int main(int argc, char const *argv[])
{
    long numThreads = 4;

        if(argc < 5)
    {
        std::cout << "INVALID PARAMETERS" << std::endl;
        exit(1);
    }

    std::string resultPath="INVALID.NULL";
    bool enableDebug = false;
    long inverseAmount = 1;

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

        if(!strcmp(argv[i], "-numThreads"))
        {
            numThreads = atoi(argv[i+1]);
        }
    }

    std::string filename= argv[1];

    if(enableDebug)
    {
        std::cout << "Opening file: " << filename << std::endl;
    }

    Image image(filename.c_str());
    Image resultImage(image.HorizSize(), image.VertSize(), image.Channels());
    
    long mosaicHorizAmount = atoi(argv[2]), mosaicVertAmount = atoi(argv[3]);
    long mosaicHorizSize = atoi(argv[4]), mosaicVertSize = atoi(argv[5]);
    
    if(enableDebug)
    {
        std::cout << "horizSize: " << image.HorizSize() << " vertSize: " << image.VertSize() << " Chn: " << image.Channels() << std::endl;
        std::cout << "1: " << (long)image.Raw()[0] << " 2: " << (long)image.Raw()[1] << " 3: " << (long)image.Raw()[2] << std::endl;
        std::cout << "mosaic size: " << mosaicHorizSize << "," << mosaicVertSize << " mosaic amount: " << mosaicHorizAmount << "," << mosaicVertAmount << std::endl;
    }

    if(enableDebug)
    {
        std::cout << "Starting..." << std::flush;
    }

    omp_lock_t **locks = new omp_lock_t*[image.VertSize()];
    //bool **wasModified = new bool*[image.VertSize()];

    for (long l = 0; l < image.VertSize(); l++)
    {
        locks[l] = new omp_lock_t[image.HorizSize()];
        //wasModified[l] = new bool[image.HorizSize()];
        for (size_t w = 0; w < image.HorizSize(); w++)
        {
            omp_init_lock(&locks[l][w]);
            //wasModified[l][w] = false;
        }
        
    }
    

    clock_t begin = clock();
    #pragma omp parallel num_threads(numThreads)
    #pragma omp for
    for (long i = 0; i < image.VertSize(); i = i + (image.VertSize() / mosaicVertAmount))
    {
        //
        {
            unsigned char midR = 0, midG = 0, midB = 0, midA =0;
            
            
            for (long j = 0; j < image.HorizSize(); j = j + (image.HorizSize() / mosaicHorizAmount))
            {
                long myI = i;
                image.GetPixel(j, myI, &midR, &midG, &midB, &midA);

                //#pragma omp for
                for (long h = myI; h < myI + mosaicVertSize; h++)
                {
                    for (long w = j; w < j + mosaicHorizSize; w++)
                    {
                        if(!(h < 0 || h >= image.VertSize() ||
                           w < 0 || w >= image.HorizSize()))
                        {

                            {
                                if(omp_test_lock(&locks[h][w]))
                                {
                                    //std::cout << "lol" << std::endl;
                                    unsigned char r, g, b, a;

                                    image.GetPixel(w, h, &r, &g, &b, &a);
                                    resultImage.SetPixel(w, h, midR, midG, midB, midA);
                                    
                                    for (size_t t = 0; t < inverseAmount; t++)
                                    {
                                        resultImage.GetPixel(w, h, &r, &g, &b, &a);
                                        resultImage.SetPixel(w, h, 255 -r, 255-g, 255-b, 255-a);
                                    }
                                    //wasModified[h][w] = true;
                                    //omp_unset_lock(&locks[h][w]);
                                }
                                else
                                {
                                    //omp_unset_lock(&locks[h][w]);
                                    //continue;
                                }
                            }
                        }
                        
                    }
                    
                }
            }   



        }
    }

    std::cout << "Done." << std::endl;

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

    results << std::fixed  << mosaicHorizAmount * mosaicVertAmount * mosaicHorizSize * mosaicVertSize << " , " << duration << " , " << "PARALLEL , " << numThreads << std::endl;
    TestingAux::WriteToResults(results);

    if(enableDebug)
    {
        std::cout << results.str() << std::endl;
    }
    return 0;

    /*size_t i;
    int x = 2;

    #pragma omp parallel private(i) firstprivate(x) num_threads(numThreads)
    {
        #pragma omp for
        for (int i = 0; i < 16; i++)
        {
            x = i;
            printf("Thread number: %d prints: %d \n", omp_get_thread_num(), x);
        }
    }
    
    return 0;*/
}