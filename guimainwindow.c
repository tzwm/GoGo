#include "guimainwindow.h"

GtkWidget* mainWindow;
GtkWidget* menubar;
GtkWidget* drawingareaGoban;

int tmpCount;

int coorToPoint(int x){
    int point= x / SIZE;
    if(x- point*SIZE > SIZE/2)
        return point +1;
    else
        return point;
}

gint arearedrawGoban(GtkWidget* widget, GdkEventExpose* event, gpointer data){
    int i, j;
    GdkColor color;
    GdkDrawable* canvas;
    GdkGC* gc;

    canvas = widget->window;
    gc = widget->style->fg_gc[GTK_WIDGET_STATE(widget)];
    
    //to draw background
    color.red = 65535;
    color.green = 47545;
    color.blue = 2855;
    gdk_gc_set_rgb_fg_color(gc, &color);
    for(i = 0; i<GOBAN_WIDTH; i++)
       gdk_draw_line(canvas, gc, 0, i, GOBAN_HEIGHT, i);

    //to draw lines
    color.red =25723;
    color.green = 26985;
    color.blue = 5140;
    gdk_gc_set_rgb_fg_color(gc, &color);
    for(i = 0; i<= GOBAN_WIDTH; i+=SIZE)
        gdk_draw_line(canvas, gc, i, 0, i, GOBAN_HEIGHT);
    for(i = 0; i<= GOBAN_HEIGHT; i+=SIZE)
        gdk_draw_line(canvas, gc, 0, i, GOBAN_WIDTH, i);

    color.red = 0;
    color.green = 0;
    color.blue = 0;
    gdk_gc_set_rgb_fg_color(gc, &color);

    return TRUE;
}

gint clickGoban(GtkWidget* widget, GdkEvent* event, gpointer data){
    tmpCount++;

    int x1, y1, x2, y2;
    
    GdkModifierType state;
    gdk_window_get_pointer(widget->window, &x1, &y1, &state);

    char buf[50];
    sprintf(buf, "%d %d,%d", tmpCount, coorToPoint(x1) +1, coorToPoint(y1) +1);
    gtk_label_set_text(data, buf);

    return TRUE;
}

void init_mainWindow(){
    //init mainWindow
    mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_usize(mainWindow, WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_window_set_title(GTK_WINDOW(mainWindow), "GoGo");
    gtk_window_set_resizable(GTK_WINDOW(mainWindow), FALSE);
    gtk_window_set_position(GTK_WINDOW(mainWindow), GTK_WIN_POS_CENTER);
    g_signal_connect_swapped(G_OBJECT(mainWindow), "destroy", 
                                G_CALLBACK(gtk_main_quit),
                                G_OBJECT(mainWindow));

    //add menu
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

    //add Goban
    GtkWidget* hbox = gtk_hbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(vbox), hbox);
    
    drawingareaGoban = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawingareaGoban, GOBAN_WIDTH, GOBAN_HEIGHT);

    g_signal_connect(G_OBJECT(drawingareaGoban), "expose_event",
                    G_CALLBACK(arearedrawGoban), NULL);

    GtkWidget* fixed = gtk_fixed_new();
    gtk_fixed_put(GTK_FIXED(fixed), drawingareaGoban, 0, 0);
    gtk_container_add(GTK_CONTAINER(hbox), fixed);
    
    //test
    tmpCount = 0;
    GtkWidget* tmpLabel = gtk_label_new("0");
    GtkWidget* tmpFixed = gtk_fixed_new();
    gtk_fixed_put(GTK_FIXED(tmpFixed), tmpLabel, 0, 0);
    gtk_container_add(GTK_CONTAINER(hbox), tmpFixed);
	gtk_widget_add_events(drawingareaGoban, GDK_BUTTON_PRESS_MASK);
    gtk_signal_connect(GTK_OBJECT(drawingareaGoban), "button_press_event",
                        GTK_SIGNAL_FUNC(clickGoban), (gpointer)tmpLabel);
}

int main(int argc, char* argv[]){
    gtk_set_locale();
    gtk_init(&argc, &argv);
   
    init_mainWindow();

    gtk_widget_show_all(mainWindow);
    gtk_main();

    return 0;
}
