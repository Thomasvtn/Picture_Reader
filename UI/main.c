#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "../segmentation/sdl_func.h"
#include "../segmentation/surface_operations.h"

GtkWidget *g_lbl_res;
GtkWidget *viewimage;
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

void on_OCRBUTTON_clicked()
{
	char *path = "../segmentation/main ";
	int pathlen = strlen(path);
	int filelen = strlen(filename);

	char *finalpath = malloc((pathlen + filelen)*sizeof(char));

	strcpy(finalpath, path);
	strcat(finalpath, filename);

	system(finalpath);

	//gtk_label_set_text(GTK_LABEL(g_lbl_res),"button is working");
	//g_print("%s",filename);
}
