#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct date {         //EXEMPLE DE STRUCTURE  
    char day[80];
    int month;
    int year;
};

void save (struct date *p)//met la structure passe en parametre dans output
{
	FILE * file= fopen("output", "wb");
	if (file != NULL) 
	{
   		fwrite(p, sizeof(struct date), 1, file);
            
	}
	fseek(file, 0, SEEK_SET);
        fclose(file);
        free(p);
}
struct date*  load()//charge le contenue de output et renvoie un pointeur vers la structure
{
	struct date *object2=malloc(sizeof(struct date));
	FILE * file= fopen("output", "rb");
    	if (file != NULL) 
	{
        	fread(object2, sizeof(struct date), 1, file);
        	fclose(file);
    	}
        return object2;
}   
int main () {
	struct date *object=malloc(sizeof(struct date));
	strcpy(object->day,"Good day");
	object->month=6;
	object->year=2013;

	save(object);   //object dans output
        struct date *object3=load();  //contenue de output dans *object3
        printf("%d  %d",object3->month,object3->year);
        free(object3);
}
