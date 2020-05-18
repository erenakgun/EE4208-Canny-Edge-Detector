#include "GaussianFilter.h"
#include <math.h>
#include <iostream>

const double PI = 3.141592653589793238463;

int kernelSizeCalculator(double sigma);
double gaussianDist(int x, int y, double sigma);

GaussianFilter::GaussianFilter(double sigma):Matrix()
{
    int kernelSize = kernelSizeCalculator(sigma);

    row = kernelSize;
    col = kernelSize;

    mat = new  double*[row];
    for(int i=0;i<row;i++)
    {
        mat[i] = new double[col];
    }

    int shift = kernelSize/2;

    double sum =0;
    for(int i=0; i<kernelSize;i++)
    {
        for(int j=0; j<kernelSize; j++)
        {
            mat[i][j] = gaussianDist(i-shift,j-shift,sigma);
            sum+=mat[i][j];
        }
    }
    scaleFactor = sum;
}


int kernelSizeCalculator(double sigma)
{
    int kernelSize = static_cast<int>(ceil(5*sigma));
    kernelSize%2 ==0 ? kernelSize++ : kernelSize;

    return kernelSize;
}

double gaussianDist(int x, int y, double sigma)
{
    double nom = static_cast<double>(x*x+y*y);
    double denom = 2*(sigma*sigma);

    return exp( - nom/denom)/(PI*denom);
}
