#ifndef FRAMEWORK_FUNC_H
#define FRAMEWORK_FUNC_H


#include <functional>
#include <vector>

template<typename T>
class Node;

template<typename T>
class Func {
    std::function<T(const std::vector<Node<T> > &, std::vector<T>)> func;
    int minArity;
    int maxArity;
    std::string repr;
public:
    Func(const std::function<T(const std::vector<Node<T> > &, std::vector<T>)> &f, int minArity, int maxArity,
         const std::string &r);

    const std::function<T(const std::vector<Node<T> > &, std::vector<T>)> &getFunc();

    const int getMinArity() const;

    const int getMaxArity() const;

    const std::string &getRepr() const;

};


#include "Func.inl"


#endif //FRAMEWORK_FUNC_H