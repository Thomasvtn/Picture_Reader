#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "reseaun.h"

double init(layer* self, int newsize, int newinput_size)
{
    double newwi[newsize][newinput_size];
    for(int i = 0; i < newsize; i++)
    {
        for(int j = 0; j < newinput_size;i++)
        {
            newwi[i][j] = ran()%10;
        }
    }
    self -> size = newsize;
    self -> input_size = newintput_size;
    self -> weight = newwi;
    self -> bias = rand()%10;
}

double** multmatricbias(double** A, double** B, int lenA,int lenB,double bias)
{
    double C[lenA][lenA];
    for(int row = 0; row< lenA; row++)
    {
        for(int col = 0; col < lenA; col++)
        {
            for(int k = 0; k < lenB; k++)
                C[row][col] += A[row][k]*B[k][col] + bias;
        }
    }
    return C;
}
double aggregation(layer* self, double** data)
{
    return multmatricbias(self -> weight,data, self -> size, self -> input_size, slef -> bias);
}
double activation(*layer self)
{
    C = self -> weight;
    for(int i = 0; i < self -> size; i++)
    {
        for(int j = 0; j< slef -> input_size;++)
            C[i][j] = (1/1+exp(-C[i][j];
    }
    self -> weight = C;
}

double forward(layer* self, double* data)
{
    double agreg = agregation(self, data);
    double activ = activation(self, activ);
    return activ;
}




