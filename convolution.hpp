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
        if (p3) /* COLOR */
        {
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
                    T filtre_value = filtre.filtre_val[k * filtre.width + l];
                    /* * filtre.factor ? */
                    red   += image.gval(x*3+0, y*3) * filtre_value;
                    green += image.gval(x*3+1, y*3) * filtre_value;
                    blue  += image.gval(x*3+2, y*3) * filtre_value;
                }
                int partpos = ( (i-ndeb)*image.gwidth() + j ) * 3;
                part[partpos + 0] = static_cast<int>(MIN(image.level, MAX(0, red)));
                part[partpos + 1] = static_cast<int>(MIN(image.level, MAX(0, green)));
                part[partpos + 2] = static_cast<int>(MIN(image.level, MAX(0, blue)));
            }
        }
        else
        {
            for (int i=ndeb; i<nfin;           i++)
            for (int j=0;    j<image.gwidth(); j++)
            {
                T grey = 0;
                for (int k=0; k<filtre.height; k++)
                for (int l=0; l<filtre.width;  l++)
                {
                    int x = j - filtre.width/2 + l;
                    x += image.gwidth();
                    x %= image.gwidth();
                    int y = i - filtre.height/2 + k;
                    y += image.gheight();
                    y %= image.gheight();
                    T filtre_value = filtre.filtre_val[k * filtre.width + l];
                    /* * filtre.factor ? */
                    grey += image.gval(x, y) * filtre_value;
                }
                int partpos = (i-ndeb)*image.gwidth() + j;
                part[partpos] = static_cast<int>(MIN(image.level, MAX(0, grey)));
            }
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
