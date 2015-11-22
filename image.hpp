#ifndef IMAGE__HPP
#define IMAGE__HPP

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

template <typename T>
class Image {
private:

public:
  std::string name;
  std::vector<T> data;
  std::string mode; 
  int width;
  int height;
  int level;
  std::string type;

//méthode
  Image(){}
  T gval(int x, int y){
	return data[width*y+x];
  }
  T gind(int i){
	return data[i];
  }
  int gwidth(){return width;}
  int gheight(){return height;}
};

#endif
