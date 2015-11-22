#ifndef FILTER__HPP
#define FILTER__HPP

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
#include "image.hpp"




template<typename T>
class Filter
{
	public:
	Filter(int w, int h, std::vector<T> v, float f): width(w), height(h), filtre_val(v), factor(f){}
	std::vector<T> filtre_val;
	int width;
	int height;
	float factor;
};

template<typename T>
Filter<T> make_find_edges(int w, int h){
	std::vector<T> d = {
			 0,  0,  0,  0,  0,
			 0,  0,  0,  0,  0,
			-1, -1,  2,  0,  0,
			 0,  0,  0,  0,  0,
			 0,  0,  0,  0,  0
		};
	float fac =1.0;
	return Filter<T>(w, h, d, fac);
}	

template<typename T>
Filter<T> make_sharpen(int w, int h){
	std::vector<T> d ={
    -1, -1, -1,
    -1,  9, -1,
    -1, -1, -1
	};
	float fac =1.0;
	return Filter<T>(w, h, d, fac);
}

template<typename T>
Filter<T> make_motion_blur(int w, int h, float f){
	std::vector<T> d = {
    1, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 1,
};
	float fac = f;
	return Filter<T>(w, h, d, f);
}	

/*template<typename T>
Filter<T> create_filter(int w, int h, std::vector<T> v, float f){
	return Filter<T> filt(w, h, v, f);
}*/


#endif

