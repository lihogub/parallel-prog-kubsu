#include <iostream>
#include <mutex>
#include <thread>
#include "string.h"
using namespace std;


mutex resultMutex;
int resultIndex;

void findTgt(int* arr, int* result, int toFind, int size, int threads, int part) {
    for (int i = part*size/threads; i < (part+1)*size/threads; i++) {
        if (arr[i] == toFind) {
            resultMutex.lock();
            result[resultIndex] = i;
            resultIndex++;
            resultMutex.unlock();
        }
    }
}


int main() {
    int size = 4;
    int tgt = 5;
    int* A = new int[size];
    int* B = new int[size];
    memset(B, -1, size);
    int threads = 4;

    A[2] = 5;
    A[3] = 5;
    
    resultIndex = 0;

    thread** threadsV = new thread*[size];
    
    for (int i = 0; i < threads; i++) {
        thread* TH = new thread(findTgt, A, B, tgt, size, threads, i);
        threadsV[i] = TH;
    }

    for (int i = 0; i < threads; i++) {
        threadsV[i]->join();
    }
    
    for (int i = 0; i < size; i++) cout << B[i] << " ";
    cout << endl;
    return 0;
}