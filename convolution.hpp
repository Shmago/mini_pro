#ifndef __CONVOLUTION_HPP__
#define __CONVOLUTION_HPP__

#include<vector>
#include<iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "image.hpp"
#include "filter.hpp"
#include <mpi.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))


template<typename T>
class Convolution
{
public:
    Convolution(const Image<T> &im)
    : image(im) {}

    void convol(
            const Filter<T> & filtre,
            std::vector<T> & part,
            int rank, int ndeb, int nfin,
            int size_bloc, int reste, bool p3)
    {

        //int cpt = 0; /* ne sert a rien ? */

        /*
        if (rank == 0)
        {
            Image<T> retour;
            std::cout<<image.type<<std::endl;
            retour.width = image.width;
            retour.height = image.height;
            retour.level = image.level;
            retour.type = image.type;
            if(p3){
                retour.data.resize(image.width*image.height*3);
            }
            else{
                retour.data.resize(image.width*image.height);
            }
        }
        */

        //std::vector<T> copie(image.gwidth()*image.gheight());
        for (int i=ndeb; i<nfin;           i++)
        for (int j=0;    j<image.gwidth(); j++)
        {
            T red = 0;
            T green = 0;
            T blue = 0;

            for (int k=0; k<filtre.height; k++)
            for (int l=0; l<filtre.width;  l++)
            {
                int x = j - filtre.width/2 + l;
                x += image.gwidth();
                x %= image.gwidth();
                int y = i - filtre.height/2 + k;
                y += image.gheight();
                y %= image.gheight();
                T val = filtre.filtre_val[k * filtre.width + l];
                if (p3)
                {
                    red   += image.gval(x*3 + 0, y*3) * val;
                    green += image.gval(x*3 + 1, y*3) * val;
                    blue  += image.gval(x*3 + 2, y*3) * val;
                }
                std::cout << val << std::endl;
            }
            if (p3)
            {
                part[i*image.gwidth()*3 + j*3 - ndeb*image.gwidth()]
                = int(/*filtre.factor*/MIN(image.level, MAX(0, red)));
                part[i*image.gwidth()*3 + j*3 + 1 - ndeb*image.gwidth()]
                = int(/*filtre.factor*/MIN(image.level, MAX(0, green)));
                part[i*image.gwidth()*3 + j*3 + 2- ndeb*image.gwidth()]
                = int(/*filtre.factor*/MIN(image.level, MAX(0, blue)));
            }
            else
                part[i*image.gwidth() + j - ndeb*image.gwidth()]
                = int(MIN(image.level, MAX(0, val)));
        }

    }
    //void operator()(const Filter& filter);
private:
    Image<T> image;
};

/*
Convolution(image);
convol(gaussian_blur());
convol(sharpen());
*/

#endif // __CONVOLUTION_HPP__
