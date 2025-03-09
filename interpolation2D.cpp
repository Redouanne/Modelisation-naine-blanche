#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_spline2d.h>
#include <omp.h>
#include <C:\Users\Victor\Desktop\C++\Codes\interpolation2D.h>


Interpolator2D::Interpolator2D(const std::vector<Eigen::MatrixXd>& interpolation,
    const std::vector<double>& om0, const std::vector<double>& oml) : n(om0.size()), list_om0(om0), list_oml(oml) {

    size_t num_k = interpolation.size(); // Nombre de couches k

    for (size_t k = 0; k < num_k; k++) {
        gsl_spline2d* spline = gsl_spline2d_alloc(gsl_interp2d_bilinear, n, n);
        gsl_interp_accel* xacc = gsl_interp_accel_alloc();
        gsl_interp_accel* yacc = gsl_interp_accel_alloc();

        std::vector<double> interp_flat(n * n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                interp_flat[i * n + j] = interpolation[k](i,j); //Extraire les données pour ce k
            }
        }

        gsl_spline2d_init(spline, list_om0.data(), list_oml.data(), interp_flat.data(), n, n);

        splines.push_back(spline);
        xaccs.push_back(xacc);
        yaccs.push_back(yacc);
    }
}

void Interpolator2D::verif(const std::vector<Eigen::MatrixXd>& interpolation){
    std::cout << "Interpolation size: " 
          << interpolation.size() << " x "
          << interpolation[0].rows() << " x "
          << interpolation[0].cols() << std::endl;
}