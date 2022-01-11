#include <gtk/gtk.h>

int main( int   argc,
          char *argv[] )
{
    GtkWidget *window;
    GtkWidget *combo;
    size_t n;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    
    gtk_container_set_border_width (GTK_CONTAINER(window), 10);
    
    combo = gtk_combo_box_new_text();
    
    for (n=0; n < 20; ++n)
    {
        gtk_combo_box_append_text(GTK_COMBO_BOX(combo), "Some Item");
    }

    gtk_container_add (GTK_CONTAINER (window), combo);

    gtk_widget_show (combo);
    
    gtk_widget_show (window);

    gtk_main ();
    
    return 0;
}