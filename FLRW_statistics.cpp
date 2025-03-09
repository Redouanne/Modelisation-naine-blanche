#include <C:\Users\Victor\Desktop\C++\Codes\FLRW_statistics.h>
#include <iostream>
#include <math.h>
#include <vector>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Eigen::VectorXd statistics::RES(double A, double B, double M0, double X0, double C0, 
                    const std::vector<double>& cosm_params, 
                    const Eigen::MatrixXd& data, const Interpolator2D& interpolator,int N) {
    
    Eigen::Vector3d Y0A;
    Y0A << M0 - A * X0 + B * C0, X0, C0;

    std::vector<double> mu_values = interpolator.interpolate(cosm_params[0], cosm_params[1]);

    Eigen::VectorXd residual(3 * N);
    for (int i = 0; i < N; ++i) {
        residual.segment<3>(3 * i) = data.row(i).segment(1, 3).transpose() - Eigen::Vector3d(mu_values[i], 0, 0) - Y0A;
    }

    return residual;
}

double statistics::m2loglike(double Alpha, double Beta, double M0, double X0, double C0, 
    const std::vector<double>& cosm_params,
    const Eigen::MatrixXd& data, const Interpolator2D& interpolator,int N) {

        Eigen::VectorXd VM = data.col(11);
        Eigen::VectorXd VX = data.col(10);
        Eigen::VectorXd VC = data.col(9);

        COV_matrix cov(Alpha, Beta, VM, VX, VC, N);

        Eigen::VectorXd delta_mu = statistics::RES(Alpha, Beta, M0, X0, C0, cosm_params, data, interpolator,N);
        Eigen::LLT<Eigen::MatrixXd> llt(cov.final_matrix);
        Eigen::MatrixXd L = llt.matrixL();
        Eigen::VectorXd solution = llt.solve(delta_mu);

        //Partie logarithmique de la fonction de probabilité gaussienne.
        double part_log = 3 * N * std::log(2 * M_PI) + 2 * L.diagonal().array().log().sum();

        //Partie exponentielle de la fonction de probabilité gaussienne.
        double part_exp = delta_mu.dot(solution);

        return part_log + part_exp;
}