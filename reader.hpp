#ifndef READER__HPP
#define READER__HPP

#include"reader.hpp"
#include "image.hpp"

template <typename T>
class Reader {
private:

public:
//methode

    Reader(){}

  Image<T> import(std::string name)
  {
    Image<T> lecture;
	std::ifstream input(name, std::ios::in);
    if ( ! input.good() ) std::cerr << "erreur de chargement";
	std::string temp;
	input >> temp;
	lecture.type = (std::string)temp;
	input >> lecture.width >> lecture.height;
	std::cout << lecture.width << "x" << lecture.height << std::endl;
	input >> lecture.level;
	if(lecture.type == "P3"){
		lecture.data.resize(lecture.width*lecture.height*3);
	}
	else{
		lecture.data.resize(lecture.width*lecture.height);
	}
	for (int k=0; k<lecture.data.size(); k++){
		input >> lecture.data[k];
	}
	input.close();
    return lecture;
  }




};






#endif
