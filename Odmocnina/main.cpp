#include <iostream>
#include <vector>
#include <cmath>
#include <functional>

#include "include/GenProg.h"
#include "SquareRoot.h"

static double plus(const std::vector< Node<double> > &children, std::vector<double> val);

static double minus(const std::vector< Node<double> > &children, std::vector<double> val);

static double multiply(const std::vector< Node<double> > &children, std::vector<double> val);

static double divide(const std::vector< Node<double> > &children, std::vector<double> val);

static double aterm(const std::vector< Node<double> > &children,std::vector<double> val);

double plus(const std::vector< Node<double> > &children, std::vector<double> val) {
    double res =0.0;
    for (int i = 0;i<children.size();i++){
        res+=SquareRoot::evaluateTree(children[i],val);
    }
    return res;
}

double minus(const std::vector< Node<double> > &children,std::vector<double> val) {
    if (children.size()==1){
        return -SquareRoot::evaluateTree(children[0],val);
    }
    return SquareRoot::evaluateTree(children[0],val)-SquareRoot::evaluateTree(children[1],val);
}

double multiply(const std::vector< Node<double> > &children,std::vector<double> val) {
    return SquareRoot::evaluateTree(children[0],val)*SquareRoot::evaluateTree(children[1],val);
}


double divide(const std::vector< Node<double> > &children,std::vector<double> val) {
    if (SquareRoot::evaluateTree(children[1], val) == 0) {
        return 1;
    }
    return SquareRoot::evaluateTree(children[0],val)/SquareRoot::evaluateTree(children[1],val);
}

double aterm(const std::vector< Node<double> > &children, std::vector<double> val){
    return val[0];
}


int main(int argc, char *argv[]) {

    //mainLib();
    SquareRoot g;
    Log<double> gLog = g.getLog();
    gLog.loadDrawing(argc,argv);

    g.values = {{1.0},{2.0},{3.0},{4.0},{5.0},{6.0},{7.0},{8.0},{9.0},{10.0},{11.0},{13.0},{15.0},{17.0},{19.0},{20.0},{24.0},{26.0},{28.0},{30.0},{33.0},{35.0},{37.0},{39.0},{40.0},{45.0},{50.0},{54.0},{61.0},{66.0},{67.0},{68.0},{76.0},{86.0}};

    g.setPopulationSize(100);
    g.setGenerationsLimit(50);

    g.setFullMethodChance(100);

    g.setMutationChance(60);
    g.setCrossoverChance(40);

    g.setNumberOfAttempts(4);

    g.setMaxTreeHeight(10);

    g.terminals.emplace_back(aterm,0,0,"d");

    g.functions.emplace_back(plus,2,5,"+");
    g.functions.emplace_back(minus,1,2,"-");
    g.functions.emplace_back(multiply,2,2,"*");
    g.functions.emplace_back(divide,2,2,"/");

    g.perform();

    return 0;
}
