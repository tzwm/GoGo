#include<gtk/gtk.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

GtkWidget* window;
GtkWidget* drawing_area;

gint area_redraw(GtkWidget* widget, GdkEventExpose* event, gpointer data){
    int i;

    GdkColor color;
    GdkDrawable* canvas;
    GdkGC* gc;

    canvas = widget->window;
    gc = widget->style->fg_gc[GTK_WIDGET_STATE(widget)];

    color.red = 65535;
    color.green = 47545;
    color.blue = 2855;
    gdk_gc_set_rgb_fg_color(gc, &color);
    for(i=0;i<300;i++)
        gdk_draw_line(canvas, gc, 0, i, 300, i);

	color.red = 25723;
	color.green = 26985;
	color.blue = 5140;
	gdk_gc_set_rgb_fg_color (gc, &color);
	for(i=0; i<=300; i+=30)
		gdk_draw_line (canvas, gc, i, 0, i, 300);
	for(i=0; i<=300; i+=30)
		gdk_draw_line (canvas, gc, 0, i, 300, i);
	
    color.red = 0;
	color.green = 0;
	color.blue = 0;
	gdk_gc_set_rgb_fg_color (gc, &color);

    return TRUE;
}

gint area_click(GtkWidget* widget, GdkEvent* event, gpointer data){
    char msg[1024];

    memset(msg, 0, sizeof(msg));
    snprintf(msg, sizeof(msg)-1, "hello");
    GtkWidget* dialog;
    dialog = gtk_message_dialog_new(GTK_WINDOW(window), 0, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, msg);

    gtk_dialog_run(GTK_DIALOG(dialog));
    //gtk_widget_destroy(dialog);

    return TRUE;
}

int main(int argc, char *argv[]){
    gtk_set_locale();
    gtk_init(&argc, &argv);
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_usize(window, 400, 400); 
    gtk_window_set_title(GTK_WINDOW(window), "GoGo");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), G_OBJECT(window));

    drawing_area = gtk_drawing_area_new();
    gtk_widget_set_usize(drawing_area, 380, 380);

    g_signal_connect(G_OBJECT(drawing_area), "expose_event", G_CALLBACK(area_redraw), NULL);
    gtk_widget_add_events(drawing_area, GDK_BUTTON_RELEASE_MASK);
    g_signal_connect(GTK_OBJECT(drawing_area), "button_press_event", GTK_SIGNAL_FUNC(area_click), (gpointer)drawing_area);
    
    GtkWidget* fixed = gtk_fixed_new();
    gtk_widget_set_usize(fixed, 20, 20);
    gtk_fixed_put(GTK_FIXED(fixed), drawing_area, 0, 0);
    gtk_container_add(GTK_CONTAINER(window), fixed);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

