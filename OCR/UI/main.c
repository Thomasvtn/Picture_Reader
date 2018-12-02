#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include "../segmentation/sdl_func.h"
#include "../segmentation/surface_operations.h"
#include "../neural_network/layer.h"
#include "../neural_network/Network.h"

int correspondlist[] = {(int)'?', (int)'a', (int)'A', (int)'b', (int)'B', (int)'c', (int)'C', (int)'d', (int)'D', (int)'e', (int)'E', (int)'f', (int)'F', (int)'g', (int)'G', (int)'h', (int)'H', (int)'i', (int)'I', (int)'j', (int)'J', (int)'k', (int)'K', (int)'l', (int)'L', (int)'m', (int)'M', (int)'n', (int)'N', (int)'o', (int)'O', (int)'p', (int)'P', (int)'.', (int)'q', (int)'Q', (int)'r', (int)'R', (int)'s', (int)'S', (int)'t', (int)'T', (int)'u', (int)'U', (int)'v', (int)'V', (int)',', (int)'w', (int)'W', (int)'x', (int)'X', (int)'y', (int)'Y', (int)'z', (int)'Z'};

GtkWidget *g_lbl_res;
GtkWidget *viewimage;
Network net;
//GtkWidget *butto;
char *filename;
int main(int argc, char **argv)
{
	GtkBuilder *builder;
	GtkWidget  *window;
	GError     *error = NULL;

	/* Init GTK+ */
	gtk_init( &argc, &argv );

	/* Create new GtkBuilder object */
	builder = gtk_builder_new();
	/* Load UI from file. If error occurs, report it and quit application.
	 * Replace "tut.glade" with your saved project. */
	if( ! gtk_builder_add_from_file( builder, "test.glade", &error ) )
	{
		g_warning( "%s", error->message );
		g_free( error );
		return( 1 );
	}

	/* Get main window pointer from UI */
	window = GTK_WIDGET( gtk_builder_get_object( builder, "OCR" ) );
	g_lbl_res = GTK_WIDGET(gtk_builder_get_object(builder, "RES"));
	viewimage = GTK_WIDGET(gtk_builder_get_object(builder,"PICTURE"));
	// butto    = GTK_WIDGET(gtk_builder_get_object(builder,"OCRBUTTON"));
	/* Connect signals */
	gtk_builder_connect_signals( builder, NULL );

	/* Destroy builder, since we don't need it anymore */
	g_object_unref( G_OBJECT( builder ) );

	/* Show window. All other widgets are automatically shown by GtkBuilder */
	gtk_widget_show( window );

	/* Start main loop */
	gtk_main();

	return( 0 );
}

void clica(GtkFileChooser *filechooserbutton ){//this button was inserted through Glade
	//char *filename;
	//GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
	filename = gtk_file_chooser_get_filename (filechooserbutton);
	gtk_label_set_text(GTK_LABEL(g_lbl_res),filename);
	gtk_image_set_from_file (GTK_IMAGE (viewimage), filename);

}

void on_TRAIN_clicked()
{	
	char path[] = "../ressources/database/1/";

	double **list_bin = list_binlist(path);

	train(&net, list_bin, correspondlist, 1000, 58);
}

void on_OCRBUTTON_clicked()
{
	initnet(&net,256);
	add_layer(&net,100);
	add_layer(&net,127);

	SDL_Surface *image_surface = load_image(filename);	
	
	char finalresult[1000];

	select_line_surface(image_surface, finalresult, net);

	for(size_t i = 0; i < 1000; i++)
		printf("%c", finalresult[i]);

	//gtk_label_set_text(GTK_LABEL(g_lbl_res),"button is working");
	//g_print("%s",filename);
}
void on_QUIT_clicked()
{
	gtk_main_quit();
        exit(EXIT_SUCCESS);
}
