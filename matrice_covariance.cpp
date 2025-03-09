#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <gsl/gsl_integration.h>
#include <omp.h>
#include <C:\Users\Victor\Desktop\C++\Codes\matrice_covariance.h>


COV_block::COV_block(double Alpha ,double  Beta , Eigen::VectorXd& VM, Eigen::VectorXd& VX, Eigen::VectorXd& VC, int i){
    block_matrix << (VM[i] + VX[i] * Alpha * Alpha + VC[i] * Beta * Beta), -VX[i] * Alpha, VC[i] * Beta,
              -VX[i] * Alpha, VX[i], 0,
              VC[i] * Beta,  0, VC[i];
}

COV_matrix::COV_matrix(double Alpha, double Beta, Eigen::VectorXd& VM, Eigen::VectorXd& VX, Eigen::VectorXd& VC, int N){

    int blockSize = 3;  //Chaque bloc est une matrice 3x3.

    //Taille totale de la matrice finale : 3N.
    int totalSize = N * blockSize;

    final_matrix = Eigen::MatrixXd::Zero(totalSize, totalSize);

    std::vector<Eigen::Matrix3d> blocks(N); //Stocker les blocs temporairement.

    //Création des blocs en parallèle.
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; i++) {
        blocks[i] = COV_block(Alpha, Beta, VM, VX, VC, i).block_matrix;
    }

    //Assemblage séquentiel (évite les conflits OpenMP).
    for (int i = 0; i < N; i++) {
        final_matrix.block(i * blockSize, i * blockSize, blockSize, blockSize) = blocks[i];
    }
}