#ifndef FRAMEWORK_GENPROG_H
#define FRAMEWORK_GENPROG_H


#include <string>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <random>
#include <cfloat>
#include <thread>
#include <mutex>

#include "Log.h"
#include "Node.h"
#include "Func.h"


template<typename T>
class GenProg {
public:
    static constexpr char *fullInitializationMethod = (char *) "full";
    static constexpr char *growInitializationMethod = (char *) "grow";

    GenProg();

    virtual void perform();

    virtual void initialize();

    virtual void evaluate();

    virtual void vary();

    virtual void selection();

    std::vector<Func<T> > functions;
    std::vector<Func<T> > terminals;

    void setPopulationSize(unsigned size);

    void setGenerationsLimit(unsigned limit);

    void setInitializationMethod(std::string method);

    void setMutationProbability(unsigned probability);

    void setCrossoverProbability(unsigned probability);

    void setNumberOfAttempts(unsigned num);

    void setMaxTreeHeight(unsigned height);

    const Log<T> &getLog() const;

    void addFunction(const Func<T> &func);

    void setFunctions(const std::vector<Func<T> > &func);

    void addTerminal(const Func<T> &term);

    void setTerminals(const std::vector<Func<T> > &term);

    void setStandardisedFitness(bool isStandard);

    const std::vector<Node<T>> &getCurrentGeneration();

    void setCurrentGeneration(const std::vector<Node<T>> &currGen);

    const std::vector<Node<T>> &getLastGeneration();


    virtual double fitFunc(const Node<T> &root) { return 0.0; };

    virtual bool terminationCriterion();

    virtual void preEvaluation() {};

    virtual void postCycle();

private:
    std::mutex m;

    std::vector<Node<T> > lastGeneration;
    std::vector<Node<T> > currentGeneration;
    std::vector<Node<T> > temporaryGeneration;

    unsigned generation;

    unsigned populationSize;
    unsigned generationsLimit;

    std::string initMethod = fullInitializationMethod;

    unsigned mutationProbability;
    unsigned crossoverProbability;

    unsigned numberOfAttempts;

    unsigned maxTreeHeight;

    bool standardisedFitness = true;

    Log<T> log;

    //Random generator
    std::random_device rd;
    std::mt19937 mt = std::mt19937(rd()); // seed the generator
    int getRnd(int from, int to);

    Node<T> fullTreeCreate();

    Node<T> growTreeCreate();

    const std::vector<Node<T> > growRecursively(const int depth, const Func<T> &func);

    const std::vector<Node<T> > fullRecursively(const int depth, const Func<T> &func);

    void performMutation();

    Node<T> mutate(const Node<T> &tree);

    Node<T> findAndReplace(const Node<T> &tree, int num, int depth);

    void performCrossover();

    std::pair<Node<T>, Node<T>> crossover(const Node<T> &tree1, const Node<T> &tree2);

    std::pair<Node<T> &, int> getChildByNum(Node<T> &tree, int num);

    Node<T> getRandomIndividual();

    void createIndividual();

    void evaluateIndividual(int i);

};


#include "GenProg.inl"

#endif //FRAMEWORK_GENPROG_H
