#ifndef FRAMEWORK_LOG_H
#define FRAMEWORK_LOG_H

#include <iostream>

#include "Node.h"
#include <cmath>
#include <mgl2/mgl.h>


template<typename T>
class Log {
    std::vector<std::vector<Node<T> > > generations;

    bool disabled;

    double getAverageFitness(unsigned int gen);

public:
    Log();

    void addGeneration(const std::vector<Node<T>> newGen);

    const std::vector<Node<T>> getGeneration(unsigned int index) const;

    unsigned int getNumberOfGenerations();

    void drawPngGraph(int width = 1680, int height = 1050);

    void setEnabled();

    void setDisabled();

    bool isDisabled();

};

#include "Log.inl"

#endif //FRAMEWORK_LOG_H
