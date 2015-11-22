#ifndef CONVOLUTION__HPP
#define CONVOLUTION__HPP

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
class Convolution {

public:

	Convolution(const Image<T> &im):image(im){}

	void convol(const Filter<T> &filtre, std::vector<T> &part,int rank, int ndeb, int nfin, int size_bloc, int reste, bool p3) {

		int cpt =0;
		/*if(rank==0){
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
		}*/
		T val;
		T red;
		T green;
		T blue;
		
		//std::vector<T> copie(image.gwidth()*image.gheight());
		for (int i=ndeb; i<nfin; i++){
		for (int j=0; j<image.gwidth(); j++) {
			val = 0;
			red = 0;
			green = 0;
			blue = 0;
		
			for (int k=0; k<filtre.height; k++){
			for (int l=0; l<filtre.width; l++) {
				int x = (j - filtre.width/2 + l + image.gwidth() )%image.gwidth();
				int y = (i - filtre.height/2 + k + image.gheight())%image.gheight();
				val += image.gval(x,y)*(filtre.filtre_val[k*filtre.width+l]);
				if(p3){
					red += image.gval(x*3, y*3)*(filtre.filtre_val[k*filtre.width+l]);
					green += image.gval(x*3 + 1, y*3)*(filtre.filtre_val[k*filtre.width+l]);
					blue += image.gval(x*3 + 2, y*3)*(filtre.filtre_val[k*filtre.width+l]);
				}
				//std::cout<<val<<std::endl;
			}
			}
				if(p3){
					part[i*image.gwidth()*3 + j*3 - ndeb*image.gwidth()] = int(/*filtre.factor*/MIN(image.level, MAX(0, red)));
					part[i*image.gwidth()*3 + j*3 + 1 - ndeb*image.gwidth()] = int(/*filtre.factor*/MIN(image.level, MAX(0, green)));
					part[i*image.gwidth()*3 + j*3 + 2- ndeb*image.gwidth()] = int(/*filtre.factor*/MIN(image.level, MAX(0, blue)));
				}
				else{
					part[i*image.gwidth() + j - ndeb*image.gwidth()] = int(MIN(image.level, MAX(0, val)));
				}
		}
		}

	}

	//void operator()(const Filter& filter);

private:
	Image<T> image;
};

/*Convolution(image);
convol(gaussian_blur());
convol(sharpen());*/

#endif
