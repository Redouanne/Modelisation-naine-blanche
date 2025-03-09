/*
Cette classe permet de déterminer les composantes de la fonction de probabilité avec la statistique choisie (gaussienne pas défaut).
La partie RES (Résidual) représente la différence entre la valeur théorique et la valeur expérimentale pour la distance modulus mu.
*/

#include <C:\Users\Victor\Desktop\C++\Codes\eigen-3.4.0\Eigen/dense>
#include <C:\Users\Victor\Desktop\C++\Codes\interpolation2D.h>
#include <C:\Users\Victor\Desktop\C++\Codes\matrice_covariance.h>

#ifndef STATISTICS_H
#define STATISTICS_H

class statistics{
    public:
    
        double statistics;

        static Eigen::VectorXd RES(double A, double B, double M0, double X0, double C0, 
            const std::vector<double>& cosm_params, 
            const Eigen::MatrixXd& Z, const Interpolator2D& interpolator,int N);
        
        double m2loglike(double Alpha, double Beta, double M0, double X0, double C0, 
            const std::vector<double>& cosm_params,
            const Eigen::MatrixXd& data, const Interpolator2D& interpolator,int N);
};

#endif