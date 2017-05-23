#ifndef FRAMEWORK_LOG_H
#define FRAMEWORK_LOG_H

#include <iostream>

#include "Node.h"
#include <cmath>
#include <cairo.h>
#include <gtk/gtk.h>
#include <mgl2/mgl.h>


template<typename T>
class Log {
    std::vector<std::vector<Node<T> > > generations;

    double getAverageFitness(unsigned int gen);

public:
    Log();

    void addGeneration(const std::vector<Node<T>> newGen);

    const std::vector<Node<T>> getGeneration(unsigned int index) const;

    unsigned int getNumberOfGenerations();

    void drawPngGraph();


};

template<typename T>
Log<T>::Log(){
}


template<typename T>
void Log<T>::addGeneration(const std::vector<Node<T> > newGen) {
    this->generations.push_back(newGen);
}

template<typename T>
const std::vector<Node<T> > Log<T>::getGeneration(unsigned int index) const{
    if (generations.empty() || generations.size() - 1 < index) {
        std::cerr << "Invalid index" << std::endl;
        return std::vector<Node<T>>{};
    }
    return generations[index];

}

template<typename T>
unsigned int Log<T>::getNumberOfGenerations() {
    if (generations.empty()) {
        return 0;
    }
    return generations.size();
}

template<typename T>
void Log<T>::drawPngGraph() {
    mglGraph gr;
    gr.SetSize(1680, 1050);
    gr.Title("Average Fitness through all generations");
    gr.SetRanges(0, generations.size(), 0, 50);
    gr.Axis();

    std::vector<mglPoint> points;
    for (unsigned int i =0; i<generations.size();i++){
        points.push_back(mglPoint(i,getAverageFitness(i)));
    }
    for (unsigned i =1; i<points.size();i++){
        gr.Line(points[i-1],points[i],"r",100);
    }

    gr.Light(true);
    gr.WriteFrame("non-thread-graph.png");

}

template<typename T>
double Log<T>::getAverageFitness(unsigned int gen) {
    double accumulatedSum = 0.0;
    for (unsigned i= 0; i<generations[gen].size();i++){
        accumulatedSum += generations[gen][i].getFitness();
    }
    return accumulatedSum/generations[gen].size();
}


template
class Log<double>;

#endif //FRAMEWORK_LOG_H
