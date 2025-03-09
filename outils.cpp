#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_interp2d.h>
#include <gsl/gsl_spline2d.h>
#include <C:\Users\Victor\Desktop\C++\Codes\outils.h>
#include <C:\Users\Victor\Desktop\C++\Codes\eigen-3.4.0\Eigen/dense>
#include <omp.h>

//Générer des linespace comme sur python.
std::vector<double> linspace(double start, double end, int num) {
    std::vector<double> result(num);
    double step = (end - start) / (num - 1);
    
    for (int i = 0; i < num; i++) {
        result[i] = start + i * step;
    }
    return result;
}

//Générer un vecteur qui lit les docs csv 1D.
std::vector<double> read_csv_1D(const std::string& filename) {
    std::vector<double> values;
    std::ifstream file(filename);

    double value;
    while (file >> value) {
        values.push_back(value);
    }

    file.close();
    return values;
}

//Générer un vecteur qui lit les docs csv 2D.
std::vector<std::vector<double>> read_csv_2D(const std::string& filename){
    std::vector<std::vector<double>> data;
    std::ifstream file(filename);

    std::string line;
    char delimiter = ',';

    while (std::getline(file,line,delimiter)){
        std::vector<double> row;
        std::stringstream ss(line);
        double values;

        row.push_back(values);
        while (ss >> values){
            row.push_back(values);
        }
        data.push_back(row);
    }

    file.close();

    return data;
}

//Générer une matrice qui lit les docs csv 2D (plus optimisé et plus facile à manipuler).
Eigen::MatrixXd loadCSVtoEigen(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier CSV.");
    }

    std::vector<std::vector<double>> data;  
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<double> row;
        std::string cell;
        
        while (std::getline(ss, cell, ',')) {
            row.push_back(std::stod(cell));
        }
        
        data.push_back(row);
    }

    file.close();

    // **Conversion en Eigen::MatrixXd**
    int rows = data.size();
    int cols = data[0].size();
    Eigen::MatrixXd matrix(rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix(i, j) = data[i][j];
        }
    }

    return matrix;
}


std::vector<Eigen::MatrixXd> loadCSVtoEigen_3D(const std::string& filename, int n, int N) {
    std::vector<Eigen::MatrixXd> interpolation;  // Un vecteur de matrices 2D
    std::ifstream file(filename);
    
    if (file.is_open()) {
        std::string line;
        int k = 0;
        
        // Pour chaque "k" (chaque couche dans la troisième dimension)
        while (std::getline(file, line) && k < N) {
            Eigen::MatrixXd matrix(n, n);  // Matrice 2D pour cette couche
            int i = 0;
            std::stringstream ss(line);
            
            while (i < n) {
                int j = 0;
                std::string value;
                while (std::getline(ss, value, ',') && j < n) {
                    matrix(i, j) = std::stod(value);
                    j++;
                }
                i++;
            }
            interpolation.push_back(matrix);  // Ajout de la matrice à notre vecteur
            k++;
        }
        file.close();
    } else {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier pour la lecture !" << std::endl;
    }
    
    return interpolation;  // Retourner un vecteur de matrices
}



void saveMatrixToCSV_2D(const std::string& filename, const Eigen::MatrixXd& matrix) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < matrix.rows(); i++) {
            for (int j = 0; j < matrix.cols(); j++) {
                file << matrix(i, j);
                if (j < matrix.cols() - 1) file << ",";  // Séparateur CSV
            }
            file << "\n";
        }
        file.close();
    } else {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier pour l'écriture !" << std::endl;
    }
}

void saveMatrixToCSV_3D(const std::string& filename, const Eigen::MatrixXd& matrix, int n, int N) {
    std::ofstream file(filename);
    if (file.is_open()) {
        // Chaque ligne contiendra i, j, k, et la valeur correspondante
        for (int k = 0; k < N; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    file << i << "," << j << "," << k << "," << matrix(i * n + j, k) << "\n"; // Utilisation de l'indice i*n+j pour l'accès linéaire
                }
            }
        }
        file.close();
    } else {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier pour l'écriture !" << std::endl;
    }
}
