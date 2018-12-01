#ifndef LAYER_H
#define LAYER_H


typedef struct layer
{
	int size;
	int input_size;
	double *bias;
	double *weight;
	double *deltas;
	double *weightsum;
	double *out;
}layer;
void copietab(double *tab,double *copie,int size);
void multmatric(double newtab[],double A[],double B[],int input_size,int size);
void addition(double newtab[],double B[],int size);
double sigmoid(double x);
double sigmoid_prime(double x);
//double to_one(int y,int n);
void forward(layer *self,double *input,double *output);
void agreg(layer *self,double *input,int input_size,int size,double *output);
void activation(double *output,int len);
void init(layer *self,int newsize, int newinput_size);

void calculweigth(layer *self,double *input);

void printlayer(layer *self);

#endif
