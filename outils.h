#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <C:\Users\Victor\Desktop\C++\Codes\eigen-3.4.0\Eigen/dense>

//générer des linespace comme sur python
std::vector<double> linspace(double start, double end, int num);

//générer un vecteur qui lit les docs csv 1D
std::vector<double> read_csv_1D(const std::string& filename);

//générer un vecteur qui lit les docs csv 2D
std::vector<std::vector<double>> read_csv_2D(const std::string& filename);

Eigen::MatrixXd loadCSVtoEigen(const std::string& filename);

std::vector<Eigen::MatrixXd> loadCSVtoEigen_3D(const std::string& filename, int n, int N);

void saveMatrixToCSV_2D(const std::string& filename, const Eigen::MatrixXd& matrix);

void saveMatrixToCSV_3D(const std::string& filename, const Eigen::MatrixXd& matrix, int n, int N);