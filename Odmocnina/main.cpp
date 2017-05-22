#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <wx/wx.h>

#include "SquareRoot.h"

static double plus1(const std::vector< Node<double> > &children, std::vector<double> val);

static double minus1(const std::vector< Node<double> > &children, std::vector<double> val);

static double multiply(const std::vector< Node<double> > &children, std::vector<double> val);

static double divide(const std::vector< Node<double> > &children, std::vector<double> val);

static double aterm(const std::vector< Node<double> > &children,std::vector<double> val);

double plus1(const std::vector< Node<double> > &children, std::vector<double> val) {
    double res =0.0;
    for (int i = 0;i<children.size();i++){
        res+=SquareRoot::evaluateTree(children[i],val);
    }
    return res;
}

double minus1(const std::vector< Node<double> > &children,std::vector<double> val) {
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
    SquareRoot g;

    g.values = {{1.0},
                {2.0},
                {3.0},
                {4.0},
                {5.0},
                {6.0},
                {7.0},
                {8.0},
                {9.0},
                {10.0},
                {11.0},
                {13.0},
                {15.0},
                {17.0},
                {19.0},
                {20.0},
                {24.0},
                {26.0},
                {28.0},
                {30.0},
                {33.0},
                {35.0},
                {37.0},
                {39.0},
                {40.0},
                {45.0},
                {50.0},
                {54.0},
                {61.0},
                {66.0},
                {67.0},
                {68.0},
                {76.0},
                {86.0}};

    g.setPopulationSize(100);
    g.setGenerationsLimit(50);

    g.setInitializationMethod(g.fullInitializationMethod);

    g.setMutationProbability(60);
    g.setCrossoverProbability(40);

    g.setNumberOfAttempts(4);

    g.setMaxTreeHeight(5);

    g.addTerminal(Func<double>(aterm, 0, 0, "d"));

    g.addFunction(Func<double>(plus1, 2, 5, "+"));
    g.addFunction(Func<double>(minus1, 1, 2, "-"));
    g.addFunction(Func<double>(multiply, 2, 2, "*"));
    g.addFunction(Func<double>(divide, 2, 2, "/"));

    g.perform();

    Log<double> ggLog = g.getLog();
    ggLog.drawPngGraph();

//WX Widget
   /* int flowers = 21;
    wxString str;
    str.Printf(wxT("There are %d red roses."), flowers);
    wxLogMessage(str);
*/
    return 0;
}
