#include "matrix.h"
#include "iostream"
#include "Utils.h"
#include <math.h>

void convolution(Matrix &output, Matrix &image,  Matrix &filter, int padding, double scaleFactor)
{
    /*
     * This function implements convolution on an image using specified padding
     *
     * Padding 0 means gaussian filter
     * Padding 1 means sobel filter
     *
     * Output matrix should have same size with the image
     */

    int offset = filter.row/2;

    for (int i=0; i<image.row; i++)
    {
        for (int j=0; j< image.col; j++)
        {
            output.mat[i][j] = convSum ( image, filter, padding, i ,j, offset);
            output.mat[i][j] /=scaleFactor;
        }
    }

}

double convSum (Matrix &image,  Matrix &filter, int padding, int centerRow ,int centerCol, int offset)
{
    double sum = 0;


    for(int i = centerRow - offset; i<centerRow + offset+1; i++)
    {
        for(int j = centerCol - offset; j<centerCol + offset+1; j++)
        {
            //padding area check
            if ( ((i<0) | (i>=image.row)) | ((j<0) | (j>=image.col)))
            {
                // in sobel filter we assume no edges at the edge of the image
                if (padding == 1)
                {
                    return 0;
                }
            }
            else
            {
                sum += image.mat[i][j] * filter.mat[i+offset-centerRow][j+offset-centerCol];
            }

        }
    }
    return sum;
}

void calculateIntensity(Matrix &output, Matrix &edgeX, Matrix &edgeY)
{
    for (int i=0; i<output.row; i++)
    {
        for (int j=0; j<output.col; j++)
        {
            double edgeXVal = edgeX.mat[i][j]*edgeX.mat[i][j];
            double edgeYVal = edgeY.mat[i][j]*edgeY.mat[i][j];
            output.mat[i][j] = sqrt(edgeXVal+edgeYVal);
        }
    }
}
void calculateEdgeDir(Matrix &output, Matrix &edgeX, Matrix &edgeY ,double threshold)
{
    /*
     * As a convention:
     * 1 is edge in x direction
     * 2 is edge in y direction
     * 3 is edge with 45 degree with the x axis
     * 4 is edge with -45 degree with the x axis
     */
    for (int i=0; i<output.row; i++)
    {
        for (int j=0; j<output.col; j++)
        {
            double x = edgeX.mat[i][j];
            double y = edgeY.mat[i][j];

            if (abs(y)-abs(x)>threshold)
            {
                output.mat[i][j] = 1;
            }
            else if(abs(x)-abs(y)>threshold)
            {
                output.mat[i][j] = 2;
            }
            else if (x*y<0)
            {
                output.mat[i][j] = 3;
            }

            else if (x*y>0)
            {
                output.mat[i][j] = 4;
            }
        }
    }
}


void nonMaxSupression(Matrix &output, Matrix &edgeIntensity, Matrix &edgeDir)
{
    // no edges at the limits of the image
    const int offset = 1;

    for (int i=offset; i<output.row-offset; i++)
    {
        for(int j=offset; j<output.col-offset; j++)
        {
            int dir = static_cast<int>(edgeDir.mat[i][j]);
            if (dir == 1)
            {
                //edge in x direction
                int before = static_cast<int>(edgeIntensity.mat[i-1][j]);
                int center = static_cast<int>(edgeIntensity.mat[i][j]);
                int after = static_cast<int>(edgeIntensity.mat[i+1][j]);

                if (maxTrio(before,center,after) != center)
                {
                    output.mat[i][j] = 0;
                }
                else
                {
                    output.mat[i][j] = edgeIntensity.mat[i][j];
                }
            }
            else if (dir == 2)
            {
                //edge in y direction
                int before = static_cast<int>(edgeIntensity.mat[i][j-1]);
                int center = static_cast<int>(edgeIntensity.mat[i][j]);
                int after = static_cast<int>(edgeIntensity.mat[i][j+1]);

                if (maxTrio(before,center,after) != center)
                {
                    output.mat[i][j] = 0;
                }
                else
                {
                    output.mat[i][j] = edgeIntensity.mat[i][j];
                }
            }
            else if (dir == 3)
            {
                //edge in +45 degree
                int before = static_cast<int>(edgeIntensity.mat[i-1][j+1]);
                int center = static_cast<int>(edgeIntensity.mat[i][j]);
                int after = static_cast<int>(edgeIntensity.mat[i+1][j-1]);

                if (maxTrio(before,center,after) != center)
                {
                    output.mat[i][j] = 0;
                }
                else
                {
                    output.mat[i][j] = edgeIntensity.mat[i][j];
                }
            }
            else if (dir == 4)
            {
                //edge in +45 degree
                int before = static_cast<int>(edgeIntensity.mat[i-1][j-1]);
                int center = static_cast<int>(edgeIntensity.mat[i][j]);
                int after = static_cast<int>(edgeIntensity.mat[i+1][j+1]);

                if (maxTrio(before,center,after) != center)
                {
                    output.mat[i][j] = 0;
                }
                else
                {
                    output.mat[i][j] = edgeIntensity.mat[i][j];
                }
            }
            else if (dir == 0)
            {
                //no edge
            }

            else
            {
                std::cerr<< "unknown edge direction: "<<edgeDir.mat[i][j]<<std::endl;
            }
        }
    }
}

int maxTrio(int before, int center, int after)
{
    /*
     * Returns maximum of the given three value
     */

     int maxVal = center;

     maxVal < before ? maxVal = before: maxVal;
     maxVal < after ? maxVal = after: maxVal;

     return maxVal;

}
