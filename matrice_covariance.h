/*
Cette classe crée une partie de la matrice de covariance associée aux données. Cette dernière contient
l'incertitude sur les observations ainsi que celle liée au processus de fit des courbes de lumière SALT2.
*/

//Evite les définition multiples des instances.
#ifndef MATRICE_COVARIANCE_H
#define MATRICE_COVARIANCE_H

#include <vector>
#include <C:\Users\Victor\Desktop\C++\Codes\eigen-3.4.0\Eigen/dense>

//COV_block crée une matrice 3x3 lié à une supernova et contenant l'information sur l'incertitude liée aux observations.
class COV_block{
    public :
        Eigen::Matrix3d block_matrix;
        COV_block(double Alpha ,double  Beta , Eigen::VectorXd& VM, Eigen::VectorXd& VX, Eigen::VectorXd& VC, int i);
};

//COV_matrix est une matrice par block 3Nx3N qui regroupe toute l'incertitude des N supernovae sur la diagonale.
class COV_matrix{
    public:
        Eigen::MatrixXd final_matrix;

        //On passe par les références des vecteurs pour éviter de copier le vecteur entier à chaque initialisation.
        COV_matrix(double Alpha, double Beta, Eigen::VectorXd& VM, Eigen::VectorXd& VX, Eigen::VectorXd& VC, int N);
        //std::vector<double>& VX
};

#endif // MATRICE_COVARIANCE_H