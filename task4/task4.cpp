#include <iostream>
#include <thread>

void initMatrix(int* matrix, int n) {
    for (int i = 0; i < n; i++) {
        matrix[i*n + (i+1)] = 1;
        matrix[(i+1)*n + i] = 1;
    }
    matrix[n*(n-1)] = 1; // last to first
    matrix[n-1] = 1; // first to last
}

void print(int* matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << matrix[i*n + j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


void swapVertices(int* matrix, int n, int a, int b) {
    for (int i = 0; i < n; i++) {
        std::swap(matrix[a*n + i], matrix[b*n + i]);
    }
    for (int i = 0; i < n; i++) {
        std::swap(matrix[i*n + a], matrix[i*n + b]);
    }
}

void shuffleVertices(int* matrix, int n) {

}

int main() {
    int n = 3;
    int* M = new int[n*n];
    initMatrix(M, n);
    print(M, n);
    // swapVertices(M, n, 1, 2);
    // print(M, n);





    return 0;
}