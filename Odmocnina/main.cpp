#include <iostream>
#include <vector>
#include <cmath>
#include <functional>

#include "genprog.h"

std::vector<double> values;

template <typename values_t> class myGenProg : public GenProg<values_t>{
public:
    double fitFunc(const Node &root) override;
};

static double evaluateTree(const Node &child, double val);

static double plus(const std::vector<Node> &children, double val);

static double minus(const std::vector<Node> &children, double val);

static double multiply(const std::vector<Node> &children, double val);

static double divide(const std::vector<Node> &children, double val);

template <typename values_t> double myGenProg<values_t>::fitFunc(const Node &root) {
    double res = 0.0;
    for (int i =0 ; i < values.size();i++){
        values[i];
        double e = evaluateTree(root, values[i]);
        res += fabs(e - sqrt(values[i]));
    }

    return res/values.size();
}


double evaluateTree(const Node &child, double val) {
    auto f = child.getFunc();
    if (child.isTerm){
        return val;
    }
    return (f.getFunc()(child.getChildren(),val));
}

double plus(const std::vector<Node> &children, double val) {
    double res =0.0;
    for (int i = 0;i<children.size();i++){
        res+=evaluateTree(children[i],val);
    }
    return res;
}

double minus(const std::vector<Node> &children,double val) {
    if (children.size()==1){
        return -evaluateTree(children[0],val);
    }
    return evaluateTree(children[0],val)-evaluateTree(children[1],val);
}

 double multiply(const std::vector<Node> &children,double val) {
    return evaluateTree(children[0],val)*evaluateTree(children[1],val);
}


 double divide(const std::vector<Node> &children,double val) {
    if (evaluateTree(children[1], val) == 0) {
        return 1;
    }
    return evaluateTree(children[0],val)/evaluateTree(children[1],val);
}

myGenProg<double> g;

int main() {
    //mainLib();

    g.populationSize = 100;
    g.generations = 50;


    g.chanceFullTree = 100;

    g.mutationChance = 60;
    g.crossoverChance = 40;

    g.maxTreeHeight = 5;

    g.terminals = std::vector<std::string> {"input1"};

    g.functions = std::vector<Func> {};
    g.functions.emplace_back(plus,2,5,"+");
    g.functions.emplace_back(minus,1,2,"-");
    g.functions.emplace_back(multiply,2,2,"*");
    g.functions.emplace_back(divide,2,2,"/");

    std::cout << g.functions.size() << std::endl;

    g.perform();

    return 0;
}
