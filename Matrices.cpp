#include <iostream>
#include <vector>
#include <iomanip>
#include "Matrices.h"
using namespace std;

namespace Matrices {
    //CONSTRUCTOR
    Matrix::Matrix(int _rows, int _cols) {
        this->rows = _rows;
        this->cols = _cols;
        //update member vector
        a.resize(rows, vector<double>(cols));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                a.at(i).at(j) = 0.0;
            }
        }
    }

    //OPERATOR OVERLOAD ADD
    Matrix operator+(const Matrix& a, const Matrix& b) {
        if (a.getCols() != b.getCols() || a.getRows() != b.getRows()) {
            throw runtime_error("Error: dimensions must agree");
        }

        Matrix c(a.getRows(), a.getCols()); //error
        for (int i = 0; i < a.getRows(); i++) {
            for (int j = 0; j < a.getCols(); j++) {
                c(i, j) = b(i, j) + a(i, j);
            }
        }
        return c;
    }

    //OPERATOR OVERLOAD MULTIPLY
    Matrix operator*(const Matrix& a, const Matrix& b) {
        if (a.getCols() != b.getRows()) {
            throw runtime_error("Error: dimensions must agree");
        }
        Matrix c(a.getRows(), b.getCols());
        for (int i = 0; i < a.getRows(); i++) {
            for (int k = 0; k < b.getCols(); k++) {
                for (int j = 0; j < b.getRows(); j++) {
                    c(i, k) += (a(i, j) * b(j, k));
                }
            }
        }
        return c;
    }


    //OPERATOR OVERLOAD IF EQUAL
    bool operator==(const Matrix& a, const Matrix& b) {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) {
            return false;
        }
        for (int i = 0; i < a.getRows(); i++) {
            for (int j = 0; j < a.getCols(); j++) {
                if (abs(a(i, j) - b(i, j)) >= 0.001) {
                    return false;
                }
            }
        }
        return true;
    }


    //OPERATOR OVERLOAD IF UNEQUAL
    bool operator!=(const Matrix& a, const Matrix& b) {
        return !(a == b);
    }


    //OPERATOR OVERLOAD OSTREAM
    ostream& operator<<(ostream& os, const Matrix& a) {
        for (int i = 0; i < a.getRows(); i++) {
            for (int j = 0; j < a.getCols(); j++) {
                if (j < a.getCols() - 1) {
                    os << setw(10) << a(i, j) << " ";
                }
                else {
                    os << setw(10) << a(i, j);
                }
            }
            os << endl;
        }
        os << endl;
        return os;
    }

    RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2) {
        a.at(0).at(0) = cos(theta);
        a.at(0).at(1) = -sin(theta);
        a.at(1).at(0) = sin(theta);
        a.at(1).at(1) = cos(theta);
    }

    ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2) {
        a.at(0).at(0) = scale;
        a.at(0).at(1) = 0;
        a.at(1).at(0) = 0;
        a.at(1).at(1) = scale;
    }

    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols) {
        for (int j = 0; j < nCols; j++) {
            a.at(0).at(j) = xShift;
            a.at(1).at(j) = yShift;
        }
    }
}

