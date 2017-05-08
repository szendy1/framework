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


/*
template <typename T> Func<T>::Func(const std::function<T(const std::vector<Node> &,T)> &f, int minCh, int maxCh, const std::string &r)
        : func(f), minChild(minCh), maxChild(maxCh), repr(r)
{}

template <typename T> Func<T>::Func()
{}


template <typename T> const std::function<T(const std::vector<Node> &,T)> Func<T>::getFunc() {return this->func;}

template <typename T> const int Func<T>::getMin() {return this->minChild;}

template <typename T> const int Func<T>::getMax() {return this->maxChild;}

template <typename T> const std::string Func<T>::getRepr() {return this->repr;}
 */