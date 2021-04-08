#include <iostream>
#include <mutex>
#include <thread>
#include "string.h"
using namespace std;


void toTriangle(double* matrix, int n) {
    for (int fixedRow = 0; fixedRow < n; fixedRow++) {
        for (int row = fixedRow+1; row < n; row++) {
            if (matrix[fixedRow*n+fixedRow] == 0) matrix[fixedRow*n+fixedRow] = 10E-300; 
            double coef = matrix[row*n + fixedRow]/matrix[fixedRow*n + fixedRow];
            for (int col = 0; col < n; col++) {
                matrix[row*n + col] -= coef * matrix[fixedRow*n + col];
            }
        }
    }
}


double detFromTriangle(double* matrix, int n) {
    double S = 1;
    for (int i = 0; i < n; i++) {
        S *= matrix[i*n + i]; 
    }
    return S;
}


double det(double* matrix, int n) {
    toTriangle(matrix, n);
    return detFromTriangle(matrix, n);
}


void print(double* matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i*n + j] << " ";
        }
        cout << endl;
    }
}


double* replaceCol(double* A, double* B, int targetCol, int n) {
    double* newM = new double[n*n];
    memcpy(newM, A, n*n*sizeof(double));
    for (int row = 0; row < n; row++) {
        newM[row*n + targetCol] = B[row];
    }
    return newM;
}


void getSolution(double* A, int n, double D) {
    double d = det(A, n);
    cout << d/D << " ";
}


void calc(double* A, double* B, int n) {
    double* _A = new double[n*n];
    memcpy(_A, A, n*n*sizeof(double));
    double D = det(_A, n);
    thread** threadArray = new thread*[n];
    for (int i = 0; i < n; i++) {
        double* C = replaceCol(A, B, i, n);
        threadArray[i] = new thread(getSolution, C, n, D);
    }
    for (int i = 0; i < n; i++) {
        if (threadArray[i]->joinable()) threadArray[i]->join();
    }
}


int main() {
    cout << "Enter matrix size: " << endl;
    int n;
    cin >> n;

    double* A = new double[n*n];
    double* B = new double[n];

    cout << "Enter matrix: " << endl;
    for (int i = 0; i < n*n; i++) 
        cin >> A[i];

    cout << "Enter solutions: " << endl;
    for (int i = 0; i < n; i++) 
        cin >> B[i];

    calc(A, B, n);

    return 0;
}