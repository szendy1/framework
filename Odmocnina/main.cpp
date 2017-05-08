#include <iostream>
#include <vector>
#include <cmath>
#include <functional>

#include "genprog.h"

GenProg<double> g;

struct MyClass {
    static double evaluateTree(const Node &child, double val);

    static double plus(const std::vector<Node> &children, double val);

    static double minus(const std::vector<Node> &children, double val);

    static double multiply(const std::vector<Node> &children, double val);

    static double divide(const std::vector<Node> &children, double val);
};
double MyClass::evaluateTree(const Node &child, double val) {
    auto f = child.getFunc();
    if (child.isTerm){
        return val;
    }
    return (f.getFunc()(child.getChildren(),val));
}

template <class T> T GenProg<T>::fitFunc(const Node &root) {
    double res = 0.0;
    for (int i =0 ; i < g.values.size();i++){
        g.values[i];
        double e = MyClass::evaluateTree(root, g.values[i]);
        res += fabs(e - sqrt(g.values[i]));
    }

    return res/g.values.size();
}

double MyClass::plus(const std::vector<Node> &children, double val) {
    double res =0.0;
    for (int i = 0;i<children.size();i++){
        res+=evaluateTree(children[i],val);
    }
    return res;
}

double MyClass::minus(const std::vector<Node> &children,double val) {
    if (children.size()==1){
        return -evaluateTree(children[0],val);
    }
    return evaluateTree(children[0],val)-evaluateTree(children[1],val);
}

 double MyClass::multiply(const std::vector<Node> &children,double val) {
    return evaluateTree(children[0],val)*evaluateTree(children[1],val);
}


 double MyClass::divide(const std::vector<Node> &children,double val) {
    if (evaluateTree(children[1], val) == 0) {
        return 1;
    }
    return evaluateTree(children[0],val)/evaluateTree(children[1],val);
}
int main() {
    //mainLib();
    g= GenProg<double>();
    g.populationSize = 100;
    g.generations = 50;


    g.chanceFullTree = 100;

    g.mutationChance = 60;
    g.crossoverChance = 40;

    g.maxTreeHeight = 5;
    // TODO: g.terminals/g.values put after g.function -> break on Func p() *(line 77)
    g.terminals = std::vector<std::string> {"input1"};
    g.values = std::vector<double> {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,13.0,15.0,17.0,19.0,20.0,24.0,26.0,28.0,30.0,33.0,35.0,37.0,39.0,40.0,45.0,50.0,54.0,61.0,66.0,67.0,68.0,76.0,86.0};

    Func p(MyClass::plus,2,5,"+");
    Func min(MyClass::minus,1,2,"-");
    Func mul(MyClass::multiply,2,2,"*");
    Func d(MyClass::divide,2,2,"/");


    g.function = std::vector<Func> {p,min,mul,d};
   // g.function = std::vector<Func> {};

    /*g.addFunction(p);
    g.addFunction(min);
    g.addFunction(mul);
    g.addFunction(d);
    */


    // TODO: ??? Functions SET, but not in GenProg ???
    std::cout << g.function.size() << std::endl;

    g.perform();

    return 0;
}
