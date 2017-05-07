//
// Created by Alexander on 31.01.2017.
//

#ifndef FRAMEWORK_GENPROG_H
#define FRAMEWORK_GENPROG_H

#include <string>
#include <vector>

#include "Log.h"
#include "Node.h"
#include "Func.h"

class GenProg {
public:
    std::vector<Node> gen;
    int populationSize;
    int generations;

    std::vector<Func> function;
    std::vector<std::string> terminals;

    std::vector<double> values;

    double chanceFullTree;

    double mutationChance;
    double crossoverChance;

    int maxTreeHeight;

    Log log;
private:


    const int getRnd(int from, int to);
    Node crtFullTree();
    Node crtGrowTree();
    const std::vector<Node> recGrow(const int depth, Func func);
    const std::vector<Node> recFull(const int depth, Func func);

    void performMutation(std::vector<Node> &actualGeneration);
    Node mutate(const Node &tree);
    Node findAndReplace(const Node &tree,int num,int depth);

    void performCrossover(std::vector<Node> &actualGeneration);
    std::pair<Node, Node> crossover(const Node &tree1, const Node &tree2);
    std::pair<Node &,int> findChildInTree(Node &tree, int num);
    Node getRandomIndividual();

    virtual double fitFunc(const Node &root) { return 0.0; };
    /*static double evaluateTree(const Node &child, double val);
    static double plus(const std::vector<Node> &children,double val);
    static double minus(const std::vector<Node> &children,double val);
    static double multiply(const std::vector<Node> &children,double val);
    static double divide(const std::vector<Node> &children,double val);
     */
public:
    GenProg();
    void perform();
    void Initialization();
    void Evaluation();
    void Vary();
    void FeedNewGeneration();

    void perform(int generationLimit);

};


#endif //FRAMEWORK_GENPROG_H
