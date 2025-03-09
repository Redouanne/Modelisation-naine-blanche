#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <gsl/gsl_integration.h>
#include <omp.h>
#include <C:\Users\Victor\Desktop\C++\Codes\FLRW_model.h>

FLRW::FLRW(double om0, double oml, double H0) : om0(om0), oml(oml), c(2.9979e5), dH(c/H0){}

double FLRW::omk() const {
    return 1.0 - om0 - oml;
}

double FLRW::integrand(double z, void* params) {
    FLRW* model = static_cast<FLRW*>(params); //Convertit "params" en un pointeur vers un objet FLRW.
    double z1 = 1.0 + z;
    return 1.0 / std::sqrt(model->om0 * std::pow(z1, 3) + model->omk() * std::pow(z1, 2) + model->oml);
} // "->" signifie accès via un pointeur.

double FLRW::integrate(double z) {
    gsl_integration_workspace* w = gsl_integration_workspace_alloc(1000); //Alloue de la mémoire pour l'intégration (un n plus grand est plus précis mais plus lent).
    double result, error;
    gsl_function F;
    F.function = &integrand;
    F.params = this;

    //gsl_integration_qag(const gsl_function *f, borne inf, borne sup, epsabs : erreur absolue, double : erreur relative, size_t limit, Méthode, gsl_integration_workspace *workspace, double *result, double *abserr).
    gsl_integration_qag(&F, 0, z, 0, 1e-2, 1000, 6, w, &result, &error); //Méthode 6 : GSL_INTEG_GAUSS61 = 61 point Gauss-Kronrod rules. L'ordre va de 15 à 61 (de 1 à 6 respectivement). Plus l'ordre est grand, plus l'intégrale est fiable pour de fonctions lisses.
    //L'erreur absolue est a 0 car on ne se concentre que sur l'erreur relative : plus variable en fonction du résultat.
    //1000 : nombre de subdivisions
    gsl_integration_workspace_free(w); //Libère la mémoire associée au workspace.

    return result;
}

double FLRW::dL(double z) {
    double I = integrate(z);
    double z1 = 1.0 + z; //Facteur d'échelle a(t).
    double Ok = omk();

    if (Ok < 0) { //Courbé négativement.
        double q = std::sqrt(std::abs(Ok));
        return z1 * std::sin(q * I) / q;
    } else if (Ok > 0) { //Courbé positivement.
        if (Ok == 1) return 0.5 * (z1 * z1 - 1);
        double q = std::sqrt(Ok);
        return z1 * std::sinh(q * I) / q;
    } else { //Univers plat.
        return z1 * I;
    }
}

double FLRW::mu(double z) {
    return 5.0 * std::log10(dL(z)) + 25.0;
}