
#ifndef FRAMEWORK_GENPROG_H
#define FRAMEWORK_GENPROG_H

#include <string>
#include <vector>

//int mainLib();

class Node;
class Func;


template <class T> class GenProg {
public:
    //Variables
    std::vector<Node> gen;
    int populationSize;
    int generations;

    std::vector<Func> function;
    std::vector<std::string> terminals;

    std::vector<T> values;

    double chanceFullTree;

    double mutationChance;
    double crossoverChance;

    int maxTreeHeight;

    //Functions

    void perform();
    void Initialization();
    void Evaluation();
    void Vary();
    void FeedNewGeneration();

    virtual double fitFunc(const Node &root);

    void addFunction(const Func &func);

};

class Func{
public:
    Func(const std::function<double(const std::vector<Node> &,double)> &f, int minCh, int maxCh, const std::string &r);
    const std::function<double(const std::vector<Node> &,double)> getFunc();
};

class Node{
public:
    const std::vector<Node> &getChildren() const;
    const Func &getFunc() const;
    bool isTerm;

};
#endif //FRAMEWORK_GENPROG_H
