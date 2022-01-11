#include "gtk/gtk.h"

GtkWidget * window;

gint delete_event(GtkWidget * widget, GdkEvent * event, gpointer data)
{
    gtk_main_quit ();
    return FALSE;
}

gint test_event(GtkWidget * widget, GdkEvent * event, gpointer data)
{
    GtkWidget * dialog, * label, * hbox, * frame, * vbox, * radio1, * radio2, * check;
    dialog = gtk_dialog_new_with_buttons ("Message", GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT,
                                         GTK_STOCK_OK, GTK_RESPONSE_NONE, GTK_STOCK_CANCEL, GTK_RESPONSE_NONE, NULL);
    gtk_dialog_set_default_response(GTK_DIALOG(dialog), GTK_RESPONSE_NONE);
    g_signal_connect_swapped (dialog, "response", G_CALLBACK (gtk_widget_destroy), dialog);
    hbox = gtk_hbox_new(TRUE, 3);
    frame = gtk_frame_new("Radio Buttons");
    vbox = gtk_vbox_new(TRUE, 3);
    radio1 = gtk_radio_button_new_with_mnemonic_from_widget (NULL, "_Radio Buttton 1a");
    gtk_box_pack_start (GTK_BOX(vbox), radio1, FALSE, FALSE, 0);
    radio2 = gtk_radio_button_new_with_mnemonic_from_widget (GTK_RADIO_BUTTON (radio1), "R_adio Buttton 1b");
    gtk_box_pack_start (GTK_BOX(vbox), radio2, FALSE, FALSE, 0);
    radio2 = gtk_radio_button_new_with_mnemonic_from_widget (GTK_RADIO_BUTTON (radio1), "Ra_dio Buttton 1c");
    gtk_box_pack_start (GTK_BOX(vbox), radio2, FALSE, FALSE, 0);
    radio1 = gtk_radio_button_new_with_mnemonic_from_widget (NULL, "Rad_io Buttton 2a");
    gtk_box_pack_start (GTK_BOX(vbox), radio1, FALSE, FALSE, 0);
    radio2 = gtk_radio_button_new_with_mnemonic_from_widget (GTK_RADIO_BUTTON (radio1), "Radio _Buttton 2b");
    gtk_box_pack_start (GTK_BOX(vbox), radio2, FALSE, FALSE, 0);
    radio2 = gtk_radio_button_new_with_mnemonic_from_widget (GTK_RADIO_BUTTON (radio1), "Radio B_uttton 2c");
    gtk_box_pack_start (GTK_BOX(vbox), radio2, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(frame), vbox);
    gtk_box_pack_start (GTK_BOX(hbox), frame, FALSE, FALSE, 0);
    frame = gtk_frame_new("Check Boxes");
    vbox = gtk_vbox_new(TRUE, 3);
    check = gtk_check_button_new_with_mnemonic ("Check Bo_x 1");
    gtk_box_pack_start (GTK_BOX(vbox), check, FALSE, TRUE, 0);
    check = gtk_check_button_new_with_mnemonic ("Check Box _2");
    gtk_box_pack_start (GTK_BOX(vbox), check, FALSE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(frame), vbox);
    gtk_box_pack_start (GTK_BOX(hbox), frame, FALSE, TRUE, 0);
    gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox), hbox);
    gtk_widget_show_all (dialog);
    return FALSE;
}

int main( int   argc,
          char *argv[])
{
    GtkWidget * button;
    gtk_init (&argc, &argv);
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    g_signal_connect (G_OBJECT (window), "delete_event", G_CALLBACK (delete_event), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    button = gtk_button_new_with_label ("Click Me!");
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (test_event), NULL);
    gtk_container_add (GTK_CONTAINER (window), button);
    gtk_widget_show (button);
    gtk_widget_show (window);
    gtk_main ();
    return 0;
}


 	  	 
