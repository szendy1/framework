#ifndef FRAMEWORK_LOG_H
#define FRAMEWORK_LOG_H

#include "Node.h"
#include <cairo.h>
#include "gtk/gtk.h"

template <typename T> class Log {
    std::vector<std::vector<Node<T> > > generations;
public:
    Log();
    void addGeneration(const std::vector<Node<T>> &newGen);
    std::vector<Node<T>> getGeneration(unsigned int index);
    unsigned int getNumberOfGenerations();

    void loadDrawing(int argc, char **argv);
};

template <typename T> Log<T>::Log() : generations(std::vector< std::vector< Node<T> > >{})
{
}


template <typename T> void Log<T>::addGeneration(const std::vector<Node<T> > &newGen){
    this->generations.push_back(newGen);
}

template <typename T> std::vector< Node<T> > Log<T>::getGeneration(unsigned int index) {
    if (generations.empty() || generations.size()-1<index){
        std::cerr << "Invalid index" << std::endl;
    }
    return generations[index];

}

template <typename T> unsigned int Log<T>::getNumberOfGenerations() {
    if (generations.empty()){
        return 0;
    }
    return generations.size();
}






static void do_drawing(cairo_t *);

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr,
                              gpointer user_data)
{
    do_drawing(cr);

    return FALSE;
}

static void do_drawing(cairo_t *cr)
{
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL,
                           CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 40.0);

    cairo_move_to(cr, 10.0, 50.0);
    cairo_show_text(cr, "Disziplin ist Macht.");
}


static gboolean
on_expose_event (GtkWidget *widget,
                 GdkEventExpose *event,
                 gpointer data)
{
    cairo_t *cr;

    cr = gdk_cairo_create (gtk_widget_get_window (widget));

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL,
                           CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 40.0);

    cairo_move_to (cr, 30, 30);
    cairo_show_text (cr, "Text");

    cairo_destroy (cr);

    return FALSE;
}


template <typename T> void Log<T>::loadDrawing(int argc, char *argv[]){
    GtkWidget *window;
    GtkWidget *darea;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), darea);

    g_signal_connect(darea, "expose-event",
                     G_CALLBACK(on_expose_event), NULL);
    g_signal_connect(window, "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 1500, 800);
    gtk_window_set_title(GTK_WINDOW(window), "Graphic visualisation of Individual");

    gtk_widget_show_all(window);

    gtk_main();

}


template class Log<double>;

#endif //FRAMEWORK_LOG_H
