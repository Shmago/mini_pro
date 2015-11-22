#include "image.hpp"
#include "filter.hpp"
#include "reader.hpp"
#include "convolution.hpp"
#include "writer.hpp"
#include <mpi.h>

int main(int argc, char* argv[])
{
    //initialisation par
    MPI_Init(&argc, &argv);
    int rank;
    int nproc;
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
        printf("nombre de proc : %d\n", nproc);

    Reader<int> reader;
    Image<int> handle = reader.import("star_field.ascii.ppm");
    Convolution<int> c(handle);

    bool p3 = (handle.type == "P3");

    int reste = handle.height % nproc;
    int size_bloc = handle.height / nproc;

    int ndeb, nfin;
    if (rank < reste)
    {
        ndeb = (size_bloc+1)*rank;
        nfin = ndeb + size_bloc + 1;
    }
    else
    {
        ndeb = (size_bloc)*rank;
        nfin = ndeb + size_bloc;
    }
    printf("rang : %d\tdebut : %d\t fin : %d\n",
            rank, ndeb, nfin);

    //initialisation des partitions a calculer
    printf("reste : %d\n", reste);
    std::vector<int> part;
    if (rank < reste)
        if (p3)
            part.resize((size_bloc + 1) * handle.gwidth() * 3);
        else
            part.resize((size_bloc + 1) * handle.gwidth());
    else
        if (p3)
            part.resize(size_bloc * handle.gwidth() * 3);
        else
            part.resize(size_bloc * handle.gwidth());
    printf("taille bloc : %d\n", size_bloc);
    //fin initialisation

    //convolution parallèle
    printf("avant convol\n");
    Filter<int> f = make_sharpen<int>(3, 3);
    c.convol(f, part, rank, ndeb, nfin, size_bloc, reste, p3);
    //communication en cas de memoire distribuee
    //envoi au rang 0 pour l'ecriture
    /*if(rank!=0){
        MPI_Send(&part.front(), part.size(), MPI_FLOAT, 0, 1, MPI_COMM_WORLD);
    }
    else{
        MPI_Status status;
        for(int s = 0; s < nproc; s++){
            if(s<reste){
                MPI_Recv(&part[(size_bloc+1)*s], size_bloc+1, MPI_FLOAT, s, 1, MPI_COMM_WORLD, &status);
            }
            else{
                MPI_Recv(&part[(size_bloc)*s], size_bloc, MPI_FLOAT, s, 1, MPI_COMM_WORLD, &status);
            }
        }
    }*/

    printf("apres convol\n");
    for (int h=0; h<200; h++)
        printf("val part : %d\n", part[0]);

    //ecriture de l'image
    if (rank == 0)
    {
        Writer<int> w;
        Image<int> retour;
        retour.type=handle.type;
        retour.level=handle.level;
        retour.height = handle.height;
        retour.width = handle.width;
        if (p3)
        {
            retour.data.resize(handle.height*handle.width*3);
            for (int j=0; j<handle.width*handle.height*3; j++)
                retour.data[j]=part[j];
        }
        else
        {
            retour.data.resize(handle.height*handle.width);
            for (int j=0; j<handle.width*handle.height; j++)
                retour.data[j]=part[j];
        }
        w.write(retour);
    }

    MPI_Finalize();

    printf("seq\n");
    return 0;
}

