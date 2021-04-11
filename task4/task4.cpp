#include <iostream>
#include <thread>
#include <numeric>

struct Vertice {
    int index;
    int degree;
};

void initMatrix(int* matrix, int n) {
    for (int i = 0; i < n-1; i++) {
        matrix[i*n + (i+1)] = 1;
        matrix[(i+1)*n + i] = 1;
    }
    matrix[n*(n-1)] = 1; // last to first
    matrix[n-1] = 1; // first to last
}

void print(int* matrix, int n, int m = 1) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << matrix[i*m + j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void print(Vertice* vertices, int n) {
    for (int i = 0; i < n; i++) 
        std::cout << vertices[i].degree << "->" << vertices[i].index << std::endl;
    std::cout << std::endl;
}

void swapVertices(int* matrix, int n, int a, int b) {
    for (int i = 0; i < n; i++) 
        std::swap(matrix[a*n + i], matrix[b*n + i]);
    for (int i = 0; i < n; i++) 
        std::swap(matrix[i*n + a], matrix[i*n + b]);
}

void shuffleVertices(int* matrix, int n) {
    for (int i = 0; i < n; i++) {
        if (rand()%2 == 0) continue;
        for (int j = 0; j < n; j++) {
            if (rand()%2 == 0)
                swapVertices(matrix, n, i, j);
        }
    }
}

int newEdge(int* matrix, int n) {
    int i, j;
    int tries = 0;
    do {
        tries++;
        i = rand() % n;
        j = rand() % n;
    } while (matrix[i*n + j]);
    matrix[i*n + j] = 1;
    matrix[j*n + i] = 1;
    return tries;
}


Vertice* toVerticeArray(int* matrix, int n) {
    Vertice* vertices = new Vertice[n];
    for (int i = 0; i < n; i++) {
        vertices[i].index = i;
        vertices[i].degree = std::accumulate(&matrix[i*n], &matrix[(i+1)*n], 0);
    }
    return vertices;
}

void qsort(Vertice* source, int size);

void run_qsort(Vertice* source, int size) {
    qsort(source, size);
}

void qsort(Vertice* source, int size) {
    if (size <= 1) return;

    int left_s = size / 2;
    int right_s = size - left_s;

    std::thread L(run_qsort, source, left_s);
    std::thread R(run_qsort, source + left_s, right_s);
    if (L.joinable()) L.join();
    if (R.joinable()) R.join();


    Vertice* tmp_array = new Vertice[size];
    int i = 0;
    int iL = 0;
    int iR = left_s;
    while (iL < left_s || iR < size) {
        if (source[iL].degree > source[iR].degree) {
            tmp_array[i++] = source[iL++];
        } else {
            tmp_array[i++] = source[iR++];
        }

        if (iL == left_s) {
            std::copy(source+iR, source+size, tmp_array+i);
            break;
        }
        
        if (iR == size) {
            std::copy(source+iL, source+left_s, tmp_array+i);
            break;
        }
    }
    std::copy(tmp_array, tmp_array+size, source);
    delete[] tmp_array;
}

void testDrive(int vertices, int addEdges) {
    std::cout << "Generating matrix... ";
    auto start = std::chrono::steady_clock::now();
    
    int* M = new int[vertices*vertices];

    auto stop = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count() << " microseconds.\n";

    std::cout << "Initializing matrix... ";
    start = std::chrono::steady_clock::now();

    initMatrix(M, vertices);

    stop = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count() << " microseconds.\n";


    std::cout << "Shuffling vertices... ";
    start = std::chrono::steady_clock::now();

    shuffleVertices(M, vertices);

    stop = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count() << " microseconds.\n";

    std::cout << "Adding edges... ";
    start = std::chrono::steady_clock::now();

    for (int i = 0; i < addEdges; i++) 
        newEdge(M, vertices);

    stop = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count() << " microseconds.\n";

    Vertice* ARR = toVerticeArray(M, vertices);

    std::cout << "Sorting vertices... ";
    start = std::chrono::steady_clock::now();

    qsort(ARR, vertices);

    stop = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count() << " microseconds.\n";
}

int main() {
    srand(time(0));

    int n = 500;
    int edges = 2000;

    testDrive(n, edges);

    return 0;
}