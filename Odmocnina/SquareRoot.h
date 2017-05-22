
#ifndef ODMOCNINA_SQUAREROOT_H
#define ODMOCNINA_SQUAREROOT_H

#include "include/GenProg.h"
#include <functional>

template <typename T > class Func;
template <typename T > class GenProg;

class SquareRoot : public GenProg<double>{
public:
    std::vector< std::vector<double> > values;
    double fitFunc(const Node<double> &root) override;
    static double evaluateTree(const Node<double> &child, const std::vector<double> &val){
        auto f = child.getFunc();
        return f.getFunc()(child.getChildren(),val);
    };

};

double SquareRoot::fitFunc(const Node<double> &root) {
    double res = 0.0;
    for (int i =0 ; i < values.size();i++){
        values[i];
        double e = evaluateTree(root, values[i]);
        res += fabs(e - sqrt(values[i][0]));
    }
    return res/values.size();
}


#endif //ODMOCNINA_SQUAREROOT_H
