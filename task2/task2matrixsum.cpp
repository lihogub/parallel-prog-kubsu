#include <thread>
#include <iostream>
using namespace std;

void summ(int* A, int* B, int* C, int n, int part) {
    for (int i = part*n*n/4; i < (part+1)*n*n/4; i++) 
        C[i] = A[i] + B[i];
}

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

int main() {
    int n = 5;
    int* a = genMatrix(n);
    int* b = genMatrix(n);
    int* c = new int[n*n];

    thread A(summ, a, b, c, n, 0);
    thread B(summ, a, b, c, n, 1);
    thread C(summ, a, b, c, n, 2);
    thread D(summ, a, b, c, n, 3);

    A.join();
    B.join();
    C.join();
    D.join();

    print(c, n);
    return 0;
}
