#include <iostream>
#include <omp.h>
#include <chrono>

using namespace std;


double* genMatrix(int n) {
	double* M = new double[n * n];
	for (int i = 0; i < n * n; i++) {
		M[i] = 1.0 * rand() / rand();
	}
	return M;
}

void print(double* M, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf_s("%10.5f ", M[i * size + j]);
		}
		cout << endl;
	}
	cout << endl;
}

double* sumM(double* A, double* B, int n) {
	double* z = new double[n * n];
	#pragma omp parallel for
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			z[i * n + j] = A[i * n + j] + B[i * n + j];
		}
	}
	return z;
}

double* multM(double* A, double* B, int n, int p) {
	double* C = new double[n * n];
	#pragma omp parallel for if (p>=0)
	for (int i = 0; i < n; i++) {
		int in = i * n;
		for (int j = 0; j < n; j++) {
			int inj = in + j;
			C[inj] = 0.0;
			for (int k = 0; k < n; k++) {
				C[inj] += A[in + k] * B[k * n + j];
			}
		}
		printf_s("%d ", i);
	}
	return C;
}

int main()
{
	srand(time(0));
	int n = 2500;
	double* x = genMatrix(n);
	double* y = genMatrix(n);
	cout << "GO!" << endl;
	auto _start = chrono::steady_clock::now();
	multM(x, y, n, 1);
	auto _stop = chrono::steady_clock::now();
	cout << endl << chrono::duration_cast<chrono::milliseconds>(_stop - _start).count() << endl;

	_start = chrono::steady_clock::now();
	multM(x, y, n, -1);
	_stop = chrono::steady_clock::now();
	cout << chrono::duration_cast<chrono::milliseconds>(_stop - _start).count() << endl;

	//print(z, n);
	return 0;
}