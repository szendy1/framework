
#ifndef ODMOCNINA_MYGENPROG_H
#define ODMOCNINA_MYGENPROG_H

#include "include/genprog.h"
#include <functional>

template <typename T > class Func;
template <typename T > class GenProg;

template <typename T> class myGenProg : public GenProg<T>{
public:
    std::vector< std::vector<T> > values;
    double fitFunc(const Node<T> &root) override;
    static double evaluateTree(const Node<double> &child, std::vector<double> val){
        auto f = child.getFunc();
        return f.getFunc()(child.getChildren(),val);
    };

};

template <typename T> double myGenProg<T>::fitFunc(const Node<T> &root) {
    double res = 0.0;
    for (int i =0 ; i < values.size();i++){
        values[i];
        double e = evaluateTree(root, values[i]);
        res += fabs(e - sqrt(values[i][0]));
    }

    return res/values.size();
}


#endif //ODMOCNINA_MYGENPROG_H
