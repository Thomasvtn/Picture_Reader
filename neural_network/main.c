#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <SDL.h>
#include "layer.h"
#include "Network.h"
//#include "sdl_func.h"
//#include "surface_binlist.h"

#define nbimage 3
int main(int argc,char **argv)
{
    if(argc != 2)
    {
        printf("Invalide argument: nothing for run 1 for load on txt and run \n");
        return 0;
    }
    
    double **inputliste = malloc(nbimage*sizeof(double));
  //  SDL_Surface *image1 = load_image("./imagename1");
  //  SDL_Surface *image2 = load_image("./imagename2");
    double  inputliste1[16] = {1,0,1,1,0,0,1,0,1,0,0,1,1,1,1,1};
    double  inputliste2[16] = {1,0,0,1,0,0,1,0,1,1,1,1,0,0,1,1};
    double  inputliste3[16] = {1,1,1,1,0,0,1,1,0,1,0,0,0,1,0,0};
    inputliste[0] = inputliste1;
    inputliste[2] = inputliste2;
    inputliste[1] = inputliste3;
    int res[nbimage]={(int)'a',(int)'z',(int)'T'}; 
    Network net;
    //loadstruct(&net,"layer.txt");
    initnet(&net,16);
    add_layer(&net,5);
    add_layer(&net,5);
    add_layer(&net,127);
    //loadstruct(&net,"layer.txt");

   // for(int i=0; i<(net.layers_dim);i++)
    //{
      //  printlayer(&net.layers[i]);
        //printf("\n\n");
//    }
    train(&net,inputliste,res,30000,nbimage);
    for(int p=0;p<3;p++)
    {
        double *out1 = calloc(net.input_dim,sizeof(double)); 
        printf("a = %d, %c \n",(int)'a','a');
        printf("predict(%c)= %c \n",(char)res[p],(char)predict(&net,inputliste[p],out1));
    
        double *out2 = calloc(net.input_dim,sizeof(double));
        printf("predict(%c)= %c \n",(char)res[p],(char)predict(&net,inputliste[p],out2)); 
    
        double *out3 = calloc(net.input_dim,sizeof(double));
        printf("predict(%c)= %c \n",(char)res[p],(char)predict(&net,inputliste[p],out3)); 
    }
    if(argv[1][0]=='1')
    {
        savestruct(&net,"layer.txt");
        loadstruct(&net,"layer.txt");
    }
    double *out3 = calloc(net.input_dim,sizeof(double));
    printf("predict(%c)= %c \n",(char)res[1],(char)predict(&net,inputliste[1],out3)); 
    // train(&net,inputliste,res,1000,2);
   // printf("predict(a)= %c",(char)predict(&net,inputliste[0],out1));
   // printf("predict(a)= %c",(char)predict(&net,inputliste[1],out1));
    freeall(&net);
    //free(out1);
    free(inputliste);
    /*
	Network net;
	initnet(&net,2);
	  printf(" resulte j %d  ==?   indexmax %d  \n",result[j],indexmax);
add_layer(&net,3);
	add_layer(&net,1);
	
	double input[4][2]={{0,0},{0,1},{1,0},{1,1}};
	double res[4]={0,1,1,0};
	double **resultliste = malloc(4*sizeof(double));
	for(int i =0;i<4;i++)
	{
		resultliste[i]=calloc(2,sizeof(double));
		resultliste[i][1] = input[i][1];
		resultliste[i][0] = input[i][0];
	}
	double result=evaluate(&net,resultliste,res,4);
	printf("performance initial = %f pourcent ",result*100);
	printf("\n");
	for(int i=0; i<(net.layers_dim);i++)
	{
		printlayer(&net.layers[i]);
		printf("\n\n");
	}
	
	train(&net,resultliste,res,1000,4);
	
	double resu2=evaluate(&net,resultliste,res,4);
	printf("performance finale = %f pourcent ",resu2*100);
	printf("\n");
	
	for(int i=0; i<(net.layers_dim);i++)
	{
		printlayer(&net.layers[i]);
		printf("\n\n");
	}
	free(resultliste);
	freeall(&net);
	
	layer layer1;
	init(&layer1,2,2);
	double input[]={1,1};
#include <stdlib.h>
	double *outpout = calloc(2,sizeof(double));
	forward(&layer1,input,outpout);
	for(int i =0; i<2;i++)
		printf("%f  \n", outpout[i]); 
	free(outpout);
	free(layer1.weight);
	free(layer1.bias);
	*/
	/*
	layer layer1;
	init(&layer1,3,2);
        for(int i = 0; i < 10;i++)
		printf("%f  ", layer1.weight[i]);
	printf("\n");
	printlayer(&layer1);
	free(layer1.weight);

	double A[] = {1,2,3,4,5,6};
	double B[] = {1,1,1,1,1,1}; 
	double *C = calloc(6,sizeof(double));
	addition(C,A,B,2,3);
	for(int i = 0; i<6;i++)
	{
		printf("%f   ",C[i]);
	}
	free(C);
	pr	for(int i = 0; i<6;i++)
	{
		printf("%f   ",C[i]);
	}intf("\n");
	double *D = calloc(2,sizeof(double));
	double input[]={1,1,1};
	multmatric(D,A,input,3,2);
	for(int i = 0; i<5;i++)
	{
		printf("%f   ",D[i]);
	}
	free(D);
	printf("\n");
	*/
	return 0;
}
