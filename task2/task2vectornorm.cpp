#include <thread>
#include <iostream>
#include <mutex>
#include "math.h"
using namespace std;

int* genMatrix(int n) {
    int* M = new int[n*n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // M[i*n+j] = i*n+j;
            if (i==j) {
                M[i*n+j] = 1;
            } else {
                M[i*n+j] = 0;
            }
        }
    }
    return M;
}

void print(int* M, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << M[i*size + j] << " ";
        }
        cout << endl;
    }
}

mutex sMutex;

void euclide(double* S, double* A, int n, int part) {
    double _S = 0;
    for (int i = part*n/4; i < (part+1)*n/4; i++) {
        _S += A[i]*A[i];
    }
    sMutex.lock();
    *S += _S;
    sMutex.unlock();
}

double V[] = {1, 1, 1, 1};

int main() {
    double S = 0;
    euclide(&S, V, 4, 0);
    euclide(&S, V, 4, 1);
    euclide(&S, V, 4, 2);
    euclide(&S, V, 4, 3);
    cout << sqrt(S) << endl;
    return 0;
}