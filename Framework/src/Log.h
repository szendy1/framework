#ifndef FRAMEWORK_LOG_H
#define FRAMEWORK_LOG_H

#include "Node.h"
#include <cairo/cairo.h>
#include <gtk-2.0/gtk/gtk.h>

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

template class Log<double>;

#endif //FRAMEWORK_LOG_H
