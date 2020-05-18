#ifndef GAUSSIANFILTER_H
#define GAUSSIANFILTER_H

#include <matrix.h>


class GaussianFilter : public Matrix
{
    public:
        GaussianFilter(double sigma);
        double scaleFactor;

};

#endif // GAUSSIANFILTER_H
