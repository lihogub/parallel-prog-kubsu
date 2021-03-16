#include <thread>
#include <iostream>
#include <mutex>
#include "math.h"
using namespace std;

void summ(int* A, int* B, int* C, int n, int part) {
    for (int i = part*n*n/4; i < (part+1)*n*n/4; i++) 
        C[i] = A[i] + B[i];
}

void mult(int* A, int* B, int* C, int n, int hOffset, int vOffset) {
    for (int i = vOffset*n/2; i < (vOffset + 1)*n/2; i++) {
        for (int j = hOffset*n/2; j < (hOffset + 1)*n/2; j++) {
            C[i*n + j] = 0;
            for (int k = 0; k < n; k++) {
                C[i*n + j] += A[i*n + k]*B[k*n + j];
            }
        }
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

int _a[] = {
    1, 1, 1, 
    2, 20, 2, 
    37, 3, 3};
int _b[] = {
    1, 1, 17, 
    2, 2, 2, 
    4, 4, 4};

double _d[] = {1, 1};


int main() {

    // int n = 3;
    // //int* a = genMatrix(n);
    // int* b = genMatrix(n);
    // int * a = _a;
    // //int * b = _b;

    // int* c = new int[n*n];

    // thread A(mult, a,b,c,n,0,0);
    // thread B(mult, a,b,c,n,0,1);
    // thread C(mult, a,b,c,n,1,0);
    // thread D(mult, a,b,c,n,1,1);

    
    // A.join();
    // B.join();
    // C.join();
    // D.join();

    // print(c, n);
    double S = 0;
    int n = 2;
    double* d = _d;
    thread A(euclide, d ,&S, n, 0);
    thread B(euclide, d, &S, n, 1);
    thread C(euclide, d, &S, n, 2);
    thread D(euclide, d, &S, n, 3);


    A.join();
    B.join();
    C.join();
    D.join();

    cout << sqrt(S) << endl;

    return 0;
}

