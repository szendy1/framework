#ifndef FRAMEWORK_LOG_H
#define FRAMEWORK_LOG_H

#include <iostream>

#include "Node.h"
#include <cairo.h>
#include <math.h>
#include "gtk/gtk.h"

//#include "../include/gnuplot_i.hpp"

template <typename T> class Log {
    std::vector<std::vector<Node<T> > > generations;
public:
    Log();
    void addGeneration(const std::vector<Node<T>> &newGen);
    std::vector<Node<T>> getGeneration(unsigned int index);
    unsigned int getNumberOfGenerations();


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




/*
void slow_print ( std::string s );
template <typename T> void Log<T>::plotGraph(int argc, char *argv[]) {
    double d[NPOINTS];
   // dpoint dp[NPOINTS];

    Gnuplot g;

    int i;
    int j;
    double x[NPOINTS];
    double y[NPOINTS];

    g.plot_slope(1.0,0.0,"unity slope");
    sleep(SLEEP_LGTH);


}

void slow_print ( std::string s )

//****************************************************************************80
{
    int i;

    for ( i = 0; i < s.length ( ); i++ )
    {
        std::cout << s[i] << std::flush;
        usleep ( 100000 );
    }
    return;
}*/


template class Log<double>;

#endif //FRAMEWORK_LOG_H
