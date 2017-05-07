//
// Created by Alexander on 31.01.2017.
//

#ifndef FRAMEWORK_GENERATION_H
#define FRAMEWORK_GENERATION_H

#include "Node.h"

class Generation {


public:
    std::vector<Node> population;
    Generation(const std::vector<Node> &pop);
    void addTree(Node tree);




};


#endif //FRAMEWORK_GENERATION_H
