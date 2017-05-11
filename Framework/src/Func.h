#ifndef FRAMEWORK_FUNC_H
#define FRAMEWORK_FUNC_H


#include <functional>
#include <vector>

class Node;

class Func {
    std::function<double(const std::vector<Node> &,double)> func;
    int minChild;
    int maxChild;
    std::string repr;
public:
    Func(const std::function<double(const std::vector<Node> &,double)> &f, int minCh, int maxCh, const std::string &r);
    Func();
    const std::function<double(const std::vector<Node> &,double)> getFunc();
    const int getMin() const;
    const int getMax() const;
    const std::string getRepr();

//    Func(const Func &func) = default;
//    Func(Func &&func) = default;
//    Func& operator=(const Func&) = default;
//    Func &operator=(Func &&func) = default;

};


#endif //FRAMEWORK_FUNC_H
