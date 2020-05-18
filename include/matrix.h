#ifndef MATRIX_H
#define MATRIX_H


class Matrix
{
    public:
        Matrix();
        Matrix(int r, int c, double** data);
        Matrix(int r, int c);
        ~Matrix();
        void print();
        double normalize();
        void scale (double scaleFactor);

        int row;
        int col;
        double **mat;
};

#endif // MATRIX_H
