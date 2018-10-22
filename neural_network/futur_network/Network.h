#ifndef NETWORK_H_INCLUDED
#define NETWORK_H_INCLUDED

typedef struct Network Network;
struct Network
{
    int inpute_dim;
    int layerssize;
    layer[layersize] Layers;
};

void add_layer(Network net, int size);
double feedforward(Network net, int input_data);
int predictwas(Network net, input_data);
double evaluate(Network net, int X, int Y);


#endif // NETWORK_H_INCLUDED
