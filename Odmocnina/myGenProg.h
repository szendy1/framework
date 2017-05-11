
#ifndef ODMOCNINA_MYGENPROG_H
#define ODMOCNINA_MYGENPROG_H

#include <genprog.h>

template <typename T > class Func;

class myGenProg : public GenProg<double>{
public:
    std::vector< std::vector<double> > values;
    double fitFunc(const Node<double> &root) override;
    static double evaluateTree(const Node<double> &child, std::vector<double> val);

};

double myGenProg::fitFunc(const Node<double> &root) {
    double res = 0.0;
    for (int i =0 ; i < values.size();i++){
        values[i];
        double e = evaluateTree(root, values[i]);
        res += fabs(e - sqrt(values[i][0]));
    }

    return res/values.size();
}

double myGenProg::evaluateTree(const Node<double> &child, std::vector<double> val) {
    auto f = child.getFunc();
    return (f.getFunc()(child.getChildren(),val));
}

#endif //ODMOCNINA_MYGENPROG_H
