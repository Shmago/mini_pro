#ifndef WRITER__HPP
#define WRITER__HPP

#include"image.hpp"


template<typename T>
class Writer{

private:
public:
		Writer(){}

		void write(Image<T> &im){
			std::ofstream output("sortie_image.ascii.pgm", std::ios::out);
			if ( ! output.good() ) {
					std::cerr << "erreur de chargement";
			}
			//std::cout << im.type << std::endl;
			output << im.type << std::endl;
			output << im.gwidth() << " " <<im.gheight() << std::endl;
			output << im.level<<std::endl;
			for (int i = 0; i < im.data.size(); i++){
				output << im.data[i] << " ";
				if (i%17 == 16)
					output << std::endl;
			}
			output.close();
		}
};

#endif
