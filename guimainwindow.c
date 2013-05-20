#include "guimainwindow.h"

GtkWidget* mainWindow;
GtkWidget* menubar;

void init_mainWindow(){
    mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_usize(mainWindow, WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_window_set_title(GTK_WINDOW(mainWindow), "GoGo");
    gtk_window_set_resizable(GTK_WINDOW(mainWindow), FALSE);
    gtk_window_set_position(GTK_WINDOW(mainWindow), GTK_WIN_POS_CENTER);
    g_signal_connect_swapped(G_OBJECT(mainWindow), "destroy", 
                                G_CALLBACK(gtk_main_quit),
                                G_OBJECT(mainWindow));


    GtkWidget* vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(mainWindow), vbox);
    
    menubar = gtk_menu_bar_new();
    GtkWidget* filemenu = gtk_menu_new();

    GtkWidget* file = gtk_menu_item_new_with_label("File");
    GtkWidget* quit = gtk_menu_item_new_with_label("Quit");

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 3);

    g_signal_connect(G_OBJECT(quit), "activate", 
                        G_CALLBACK(gtk_main_quit), NULL);
}

int main(int argc, char* argv[]){
    gtk_set_locale();
    gtk_init(&argc, &argv);
   
    init_mainWindow();

    gtk_widget_show_all(mainWindow);
    gtk_main();

    return 0;
}
