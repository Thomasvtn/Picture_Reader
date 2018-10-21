#ifndef RESEAUN_H
#define RESEAUN_H

typedef struct layer layer;
struct layer
{
    int size;
    int input_size;
    double** weight;
    double bias;
};

double init(layer* self, int newsize, int newinput_size);
double** multmatricbias(double** A, double** B, int lenA, int lenB, double bias);
double agregation(layer* self, double** data);
double activation(layer* self);
double forward(layer* self, double* data);

#endif
