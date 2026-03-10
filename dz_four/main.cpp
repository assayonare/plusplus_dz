#include "SampleComplex.h"
#include "Matrix.h"

#include <fftw3.h>
#include <chrono>
#include <iostream>

#include <boost/numeric/ublas/matrix.hpp>

using namespace boost::numeric::ublas;

int main()
{
    // ------------------------------
    // 1. СРАВНЕНИЕ УМНОЖЕНИЯ МАТРИЦ
    // ------------------------------

    int size = 300;

    Matrix A(size);
    Matrix B(size);

    A.SetValue(1);
    B.SetValue(2);

    auto start1 = std::chrono::high_resolution_clock::now();

    Matrix C = A * B;

    auto end1 = std::chrono::high_resolution_clock::now();

    std::cout << "Custom Matrix multiplication time: "
              << std::chrono::duration<double>(end1 - start1).count()
              << " sec\n";


    // Boost uBLAS
    matrix<double> A2(size,size);
    matrix<double> B2(size,size);

    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
        {
            A2(i,j) = 1;
            B2(i,j) = 2;
        }

    auto start2 = std::chrono::high_resolution_clock::now();

    matrix<double> C2 = prod(A2,B2);

    auto end2 = std::chrono::high_resolution_clock::now();

    std::cout << "Boost uBLAS multiplication time: "
              << std::chrono::duration<double>(end2 - start2).count()
              << " sec\n";


    // ------------------------------
    // 2. FFT 512x512
    // ------------------------------

    int N = 512;

    SampleComplex data(N);

    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            data(i,j) = std::complex<double>(1,0);


    fftw_plan plan;

    plan = fftw_plan_dft_2d(
        N,
        N,
        (fftw_complex*)data.GetPointer(),
        (fftw_complex*)data.GetPointer(),
        FFTW_FORWARD,
        FFTW_ESTIMATE
    );

    fftw_execute(plan);

    fftw_destroy_plan(plan);

    data.SaveModule("fft.txt");

    std::cout << "FFT result saved to fft.txt\n";

    return 0;
}