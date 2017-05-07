//
// Created by Alexander on 5. 4. 2017.
//

#include "Func.h"


Func::Func(const std::function<double(const std::vector<Node> &,double)> &f, int minCh, int maxCh, const std::string &r)
        : func(f), minChild(minCh), maxChild(maxCh), repr(r)
{}

Func::Func()
{}


const std::function<double(const std::vector<Node> &,double)> Func::getFunc() {return this->func;}

const int Func::getMin() {return this->minChild;}

const int Func::getMax() {return this->maxChild;}

const std::string Func::getRepr() {return this->repr;}