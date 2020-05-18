#include "matrix.h"
#include <iostream>

Matrix::Matrix()
{
    row = 0;
    col = 0;
    mat = 0;
}

Matrix::Matrix(int r, int c, double** data)
{
     this->row = r;
     this->col = c;
     this->mat = data;
}

Matrix::Matrix(int r, int c)
{
    row = r;
    col = c;
    this->mat = new double*[row];
    for(int i=0;i<row;i++)
    {
        mat[i] = new double[col];
        for(int j =0; j<col; j++)
        {
            mat[i][j] = 0;
        }

    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < row; ++i)
    {
        delete[] mat[i];
    }
    delete[] mat;
}

void Matrix:: print()
{
    for(int i=0;i<row; ++i)
    {
        for(int j=0;j<col; ++j)
        {
            std::cout<<mat[i][j]<<' ';
        }
        std::cout<<'\n';
    }
}

double Matrix:: normalize()
{
    double maxIntensity = 0;

    for(int i=0;i<row; ++i)
    {
        for(int j=0;j<col; ++j)
        {
            if (mat[i][j]>maxIntensity)
                {
                    maxIntensity =mat[i][j];
                }
        }
    }

    for(int i=0;i<row; ++i)

    {
        for(int j=0;j<col; ++j)
        {
            mat[i][j] = mat[i][j]*255/maxIntensity;
        }
    }

    return maxIntensity;
}

void Matrix:: scale(double scaleFactor)
{
    for (int i=0; i<row; i++)
    {
        for (int j=0; j< col; j++)
        {
            mat[i][j] *= scaleFactor;
        }
    }
}

