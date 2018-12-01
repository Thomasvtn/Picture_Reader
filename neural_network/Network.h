#ifndef NETWORK_H
#define NETWORK_H
#include "layer.h"

typedef struct Network
{
	int input_dim;
	int layers_dim;
	layer *layers; 
}Network;

void initnet(Network *self,int input_dim);
void add_layer(Network *self,int size);
void savestruct(Network *self,char *File);
void loadstruct(Network *self,char *File);
void savenet(Network *self,char *File);
void feedforward(Network *self,double *input,double *out);
int predict(Network *self,double *input,double *out);
double evaluate(Network *self,double **inputlist,int *result,int sizeoflist);

void train(Network *self,double **inputlist,int *result,int step,int lenres);

void freeall(Network *self);
#endif
