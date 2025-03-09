#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <gsl/gsl_integration.h>
#include <omp.h>
#include <C:\Users\Victor\Desktop\C++\Codes\FLRW_model.h>
#include <C:\Users\Victor\Desktop\C++\Codes\outils.h>
#include <C:\Users\Victor\Desktop\C++\Codes\interpolation2D.h>
#include <C:\Users\Victor\Desktop\C++\Codes\matrice_covariance.h>
#include <C:\Users\Victor\Desktop\C++\Codes\FLRW_statistics.h>

int main() {

    //A exécuter au début pour créer le fichier contenant les données.
    //==============================================================================================
    //system("python lecture.py");
    //==============================================================================================

    //Noms des colonnes : ["zCMB","mB","x1","c","IDSURVEY","zHEL","RA","DEC","VPEC", "cERR", "x1ERR", "mBERR", "COV_x1_c", "COV_x1_x0", "COV_c_x0"]
    //Indices :           [ 0       1    2   3      4        5     6     7     8       9        10       11        12           13         14     ]
    Eigen::MatrixXd data = loadCSVtoEigen("data/data.csv");
    
    

    int n = 101; //Om0 varie de 0 à 1.0. Augmenter n revient à augmenter la précision sur les valeurs de om0 et oml, actuellement à 0.01.
    int N = data.col(0).size(); //Nombre de supernovae étudié.

    std::vector<double> list_om0 = linspace(0,1.0,n);
    std::vector<double> list_oml = linspace(0,1.0,n);



    //Commandes à exécuter lors de la première création des tables d'interpolation.
    //==============================================================================================
    /*
    //allocation de la grille d'interpolation
    Eigen::MatrixXd interpolation(n * n, N);

    #pragma omp parallel for collapse(3) schedule(dynamic, 50) //Parallélisme du calcul des boucles.
    //collapse(3) signifie que le parallélisme s'effectue sur les 3 boucles.
    //Schedule(dynamic) signifie que chaque thread reçoit une quantité variable d'itération en fonction de la tâche a effectuer (meilleur équilibrage mais possibilité de surcharge plus importante).
    for (int i=0; i < n; i++){
        for (int j=0; j < n; j++){
            FLRW universe(list_om0[i], list_oml[j]);
            for (int k=0; k < N; k++){
                interpolation(i * n + j, k) = universe.mu(data.col(0)[k]);;
            }
        }
    }

    saveMatrixToCSV_3D("data/interpolation_table.csv", interpolation,n,N);
    */
    //==============================================================================================


    

    //Création du vecteur d'interpolation pour les distances modulus en fonction de OM et OL.
    Interpolator2D interpolator(loadCSVtoEigen_3D("data/interpolation_table.csv", n,N), list_om0, list_oml);

    //Vérifier la taille de la matrice d'interpolation : Nb de supernovae x 101 x  101.
    //interpolator.verif(loadCSVtoEigen_3D("data/interpolation_table.csv",n,N));

    double OM = 0.341, OL = 0.569;
    std::vector<double> cosm_params = {OM, OL};
    //std::vector<double> mu_values = interpolator.interpolate(OM, OL);
    double Alpha = 0.134, Beta = 3.0, M0 = -19, X0 = 0.038, C0 = -0.016;
    statistics likelihood;
    double result = likelihood.m2loglike(Alpha,Beta,M0,X0,C0, cosm_params,data,interpolator,N);

    std::cout << result << std::endl;
    


    return 0;

}