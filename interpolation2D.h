#include <iostream>
#include <vector>
#include <gsl/gsl_spline2d.h>
#include <C:\Users\Victor\Desktop\C++\Codes\eigen-3.4.0\Eigen/dense>

//Evite les définition multiples des instances.
#ifndef INTERPOLATION2D_H
#define INTERPOLATION2D_H

class Interpolator2D {
private:
    int n;
    std::vector<gsl_spline2d*> splines;
    std::vector<gsl_interp_accel*> xaccs;
    std::vector<gsl_interp_accel*> yaccs;
    std::vector<double> list_om0, list_oml;

public:
    // Constructeur : Initialise un interpolateur pour chaque valeur de k (pour chaque supernova)
    //const std::vector<std::vector<std::vector<double>>>& interpolation
    Interpolator2D(const std::vector<Eigen::MatrixXd>& interpolation,
                   const std::vector<double>& om0, const std::vector<double>& oml);
    // Méthode d'interpolation pour une valeur (OM, OL)
    std::vector<double> interpolate(double OM, double OL) const {
        std::vector<double> results;
        for (size_t k = 0; k < splines.size(); k++) {
            double value = gsl_spline2d_eval(splines[k], OM, OL, xaccs[k], yaccs[k]);
            results.push_back(value);
        }
        return results;
    }

    void verif(const std::vector<Eigen::MatrixXd>& interpolation);

    // Destructeur : Libère la mémoire
    ~Interpolator2D() {
        for (size_t k = 0; k < splines.size(); k++) {
            gsl_spline2d_free(splines[k]);
            gsl_interp_accel_free(xaccs[k]);
            gsl_interp_accel_free(yaccs[k]);
        }
    }
};

#endif // INTERPOLATION2D 