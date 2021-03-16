#include <thread>
#include <iostream>
using namespace std;

int* genMatrix(int n) {
    int* M = new int[n*n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            M[i*n+j] = i*n+j;
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
int main() {
    int n = 3;
    int* a = genMatrix(n);
    int* b = genMatrix(n);

    int* c = new int[n*n];

    thread A(mult, a,b,c,n,0,0);
    thread B(mult, a,b,c,n,0,1);
    thread C(mult, a,b,c,n,1,0);
    thread D(mult, a,b,c,n,1,1);

    
    A.join();
    B.join();
    C.join();
    D.join();
    
    print(c, n);
    return 0;
}