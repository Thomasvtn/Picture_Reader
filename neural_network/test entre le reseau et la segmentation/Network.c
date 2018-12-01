#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Network.h"
#include <err.h>
#define clear() printf("\033[H\033[J");

void initnet(Network *self,int input_dim)
{
    self -> input_dim = input_dim; 
    self -> layers_dim = 0; 
    self -> layers = calloc(self->layers_dim,sizeof(layer)); 
}

void add_layer(Network *self,int size)
{
    int input_dim=0;
    if(self->layers_dim > 0)
    {
        input_dim = self->layers[(self->layers_dim)-1].size;
    }
    else
    {
        input_dim = self->input_dim; 
    }
    self ->layers_dim +=1;
    self ->layers = realloc(self->layers,(self->layers_dim)*sizeof(layer));
    layer newlayer;
    init(&newlayer,size,input_dim);
    self ->layers[(self->layers_dim)-1]=newlayer;
}

void savestruct(Network *self,char *File)
{
    /*
    char* ptr=(char*)self->layers[0].weight;
    for(size_t i=0;i<sizeof(Network);i++)
    {
        printf("%d,",*(ptr+i));
    }
    printf("\n");
    return;
    */
    FILE *fichier =NULL;
    fichier = fopen(File, "w");
    if(fichier!=NULL)
    {
        printf("fichier ouvert\n");
        fwrite(self,sizeof(Network),1,fichier);
        fclose(fichier);
    }
    else
    {
        printf("fopen dont work\n");
    }
}
void loadstruct(Network *self,char *File)
{
    FILE *fichier =NULL;
    fichier = fopen(File, "r");
    if(fichier!=NULL)
    {
        printf("fichier ouvert\n");
        size_t res = fread(self,sizeof(Network),1,fichier);
        if(res==0)
            printf("caca");
        fclose(fichier);
    }
    else
    {
        printf("fopen dont work\n");
    }
}
void savenet(Network *self,char *File)
{
    FILE* fichier = NULL;
    
    fichier = fopen(File, "w");
    if (fichier != NULL)
    {
        printf("fichier ouvert %s \n",File);
        layer *listelayer= self->layers;
        int nblayer = self->layers_dim;
        for (int i = 0; i<nblayer;i++)
        {
            double *matrix = listelayer[i].weight;
            int matrixsize = (listelayer[i].size)*(listelayer[i].input_size);
            fwrite(matrix,matrixsize,sizeof(double),fichier);
        }
        fclose(fichier);
    }
    else
    {
        printf("Impossible d'ouvrir le fichieir\n");
    }
}

void feedforward(Network *self, double *input,double *out)
{

    for(int i=0; i<self->input_dim;i++)
    {
        out[i]=input[i];
    }

    for(int i=0; i<self->layers_dim;i++)
    {

        int size = self->layers[i].size;
        double *output=calloc(size,sizeof(double));

        forward(&(self->layers[i]),out,output);
        
        out = realloc(out,size*sizeof(double));
        for(int copie2=0; copie2<size;copie2++)
        {
            //printf("out befor = %f \n",out[copie2]);
            out[copie2]= output[copie2];
           // printf("out after = %f \n",out[copie2]);
            self->layers[i].out[copie2] = output[copie2];
        }
        //printf("size on layer %d \n",size);
        free(output);
    }
    free(out);
}

int predict(Network *self,double *input,double *out)
{
    feedforward(self,input,out);
    
    layer lastelayer = self->layers[self->layers_dim-1]; 
    int size = lastelayer.size;
    
    int index_max=0;
    double max=lastelayer.out[0];

    for(int i=0;i<size;i++)
    {
        if(max<lastelayer.out[i])
        {
            index_max=i;
            max = lastelayer.out[i];
        }
       // printf("out i = %f  %d \n",out[i],i);
    }

    //printf("max = %f\n", max);
    //printf("index_max = %d\n",index_max);
    return index_max; 
}


double evaluate(Network *self,double **inputlist,int *result,int sizeoflist)
{
    //int size = self->layers[self->layers_dim -1].size;
    double sum =0;
    for(int i=0; i<sizeoflist; i++)
    {
        double *out = calloc(self->input_dim,sizeof(double));
        if(predict(self,inputlist[i],out)==result[i])
        {
            sum+=1;
        }
    }
    return sum/(double)sizeoflist;
}


void train(Network *self,double **inputlist,int *result,int step,int lenres)
{
    //double learning_rate = 0.3;
    printf("step %di \n",step);
   // for(int i=0;i<step;i++)
   double condieval;
   do
   {
        double eval = evaluate(self,inputlist,result,lenres);
        printf("eval = %f pourcent \n",eval*100);
        condieval = eval*100;
        //printf("step = %d\n",i);
        for(int j=0; j<lenres;j++)
        {
            int condition = 0;
            int indexmax;
            layer *layerlist = self->layers;
            layer lastlayer = layerlist[self->layers_dim-1];
            double inputdim = self->input_dim;

            do
            {
                double *outi = calloc(inputdim,sizeof(double));
                indexmax= predict(self,inputlist[j],outi);
                //printf(" resulte j %d  ==?   indexmax %d  \n",result[j],indexmax);


                double* outll = lastlayer.out;
                int outsize = layerlist[self->layers_dim-1].size; 
                double *error=calloc(outsize,sizeof(double));
                error[result[j]]=1;

                for(int k = 0; k<outsize; k++)
                {
                    error[k] -= outll[k];
                    //printf("error k = %f\n",error[k]);
                    lastlayer.deltas[k]= error[k];//*outll[k]*(1-outll[k]);
                   // printf("first delta = %f \n",lastlayer->deltas[k]);
                }


                free(error);

                for(int ilayer =self->layers_dim-2; ilayer>=0;ilayer--)
                {
                    layer l = layerlist[ilayer];
                    layer b = layerlist[ilayer+1];
                    int size = layerlist[ilayer].size; 
                    for(int index = 0; index<size; index++)
                    {
                        double wiandt = 0;
                        double pout = l.out[index];
                        for(int all=0;all<size;all++)
                        {
                             double wi= b.weight[all*size+index];
                             double delta = b.deltas[index];
                             wiandt+=wi*delta; 
                        }
                        l.deltas[index] = pout*(1-pout)*wiandt;
                       //printf("delta = %f , %d \n",l->deltas[index],index);
                    }
                }
                
                //double *out2 = calloc(inputdim,sizeof(double));
                //indexmax= predict(self,inputlist[j],out2);

                //printf(" resulte j %d  ==?   indexmax %d  \n",result[j],indexmax);
                condition =!(result[j] == indexmax);

            }while(condition);

        }
    }while(condieval!=100);

}


void freeall(Network *self)
{
    for(int i=0; i<(self->layers_dim);i++)
    {
        free(self->layers[i].bias);
        free(self->layers[i].weight);
        free(self->layers[i].deltas);
        free(self->layers[i].weightsum);
        free(self->layers[i].out);
    }
    free(self->layers);
}

