#ifndef FRAMEWORK_GRAPHICS_H
#define FRAMEWORK_GRAPHICS_H

#include <cairo.h>
#include <math.h>
#include "Node.h"
#include "gtk/gtk.h"
static gboolean on_expose_event (GtkWidget *widget,
                                 GdkEventExpose *event,
                                 gpointer data);

template <typename T> class Graphics{
private:
    const Node<T> node;
    void recursiveDraw(cairo_t *cr, gint w, gint h, const Node<T> &node);
    void drawNode(cairo_t *cr,gint posX, gint posY, const char *data);
    //void plotGraph(int argc, char **argv);


public:
    Graphics(const Node<T> node1): node(node1){};
    void loadDrawing(int argc, char **argv);
    //void setNode(const Node<T> node1) { this->node = node1; };
    const Node<T> & getNode() const { return this->node; };

};

# define SLEEP_LGTH  1
# define NPOINTS     50



template <typename T>
void Graphics<T>::recursiveDraw(cairo_t *cr, gint w, gint h, const Node<T> &node){
    std::vector<Node<T>> children = node.getChildren();
    const char *data = node.getFunc().getRepr().c_str();

    drawNode(cr,w/2,h,data);
    gint newWidth = w/children.size();
    for (unsigned i = 0; i<children.size(); i++){
        recursiveDraw(cr,newWidth,h*2,children[i]);
    }

}

template <typename T> void Graphics<T>::drawNode(cairo_t *cr,gint posX, gint posY, const char *data){
    gint radius = 30;
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_set_line_width(cr, 1);
    cairo_move_to(cr,posX,posY);
    cairo_arc(cr, posX, posY, radius, 0, 2*M_PI);
    cairo_fill_preserve(cr);
    cairo_stroke_preserve(cr);
    cairo_fill(cr);

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_move_to (cr, posX-10, posY+radius-10);
    cairo_show_text (cr, data);
}

static gboolean on_expose_event (GtkWidget *widget,
                         GdkEventExpose *event,
                         gpointer data)
{
    cairo_t *cr;

    GtkWidget *win = gtk_widget_get_toplevel(widget);
    gint w, h;
    gtk_window_get_size(GTK_WINDOW(win), &w, &h);

    cr = gdk_cairo_create (gtk_widget_get_window (widget));

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL,
                           CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 40.0);

    //recursiveDraw(cr,w,h/getNode().height(),);
    //drawNode(cr,w/2,h/10,"*");

    cairo_destroy (cr);

    return FALSE;
}


template <typename T>  void Graphics<T>::loadDrawing(int argc, char *argv[]){
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





template class Graphics<double>;

#endif //FRAMEWORK_GRAPHICS_H
