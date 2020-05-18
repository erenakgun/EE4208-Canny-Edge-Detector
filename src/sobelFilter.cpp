#include "sobelFilter.h"

sobelFilter::sobelFilter(int filterType):Matrix(3,3)
{
    /*
     *  filter Type 0 is detector in y direction
     *  filter Type 1 is detector in x direction
     */
    if(filterType == 0)
    {
        mat[0][0] = -1;
        mat[0][1] = -2;
        mat[0][2] = -1;
        mat[1][0] = 0;
        mat[1][1] = 0;
        mat[1][2] = 0;
        mat[2][0] = 1;
        mat[2][1] = 2;
        mat[2][2] = 1;
    }
    else if(filterType == 1)
    {
        mat[0][0] = -1;
        mat[0][1] = 0;
        mat[0][2] = 1;
        mat[1][0] = -2;
        mat[1][1] = 0;
        mat[1][2] = 2;
        mat[2][0] = -1;
        mat[2][1] = 0;
        mat[2][2] = 1;
	}

}
