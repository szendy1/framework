#ifndef FRAMEWORK_GENPROGLIB_H
#define FRAMEWORK_GENPROGLIB_H


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
#include "mgl2/mgl.h"

template <typename T>
class Func;

template <typename T>
class Log;

template <typename T>
class Node;

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

    std::vector<Func < T> >
            functions;
    std::vector<Func < T> >
            terminals;

    void setPopulationSize(unsigned size);

    void setGenerationsLimit(unsigned limit);

    void setInitializationMethod(std::string method);

    void setMutationProbability(unsigned probability);

    void setCrossoverProbability(unsigned probability);

    void setNumberOfAttempts(unsigned num);

    void setMaxTreeHeight(unsigned height);

    const Log <T> &getLog() const;

    void addFunction(const Func <T> &func);

    void setFunctions(const std::vector<Func < T>

    > &func);

    void addTerminal(const Func <T> &term);

    void setTerminals(const std::vector<Func < T>

    > &term);

    void setStandardisedFitness(bool isStandard);

    const std::vector<Node < T>> &

    getCurrentGeneration();

    void setCurrentGeneration(const std::vector<Node < T>>

                              &currGen);

    const std::vector<Node < T>> &

    getLastGeneration();


    virtual double fitFunc(const Node <T> &root) { return 0.0; };

    virtual bool terminationCriterion();

    virtual void preEvaluation() {};

    virtual void postCycle();

private:
    std::mutex m;

    std::vector<Node < T> >
            lastGeneration;
    std::vector<Node < T> >
            currentGeneration;
    std::vector<Node < T> >
            temporaryGeneration;

    unsigned generation;

    unsigned populationSize;
    unsigned generationsLimit;

    std::string initMethod = fullInitializationMethod;

    unsigned mutationProbability;
    unsigned crossoverProbability;

    unsigned numberOfAttempts;

    unsigned maxTreeHeight;

    bool standardisedFitness = true;

    Log <T> log;

    //Random generator
    std::random_device rd;
    std::mt19937 mt = std::mt19937(rd()); // seed the generator
    int getRnd(int from, int to);

    Node <T> fullTreeCreate();

    Node <T> growTreeCreate();

    const std::vector<Node < T> >

    growRecursively(const int depth, const Func <T> &func);

    const std::vector<Node < T> >

    fullRecursively(const int depth, const Func <T> &func);

    void performMutation();

    Node <T> mutate(const Node <T> &tree);

    Node <T> findAndReplace(const Node <T> &tree, int num, int depth);

    void performCrossover();

    std::pair<Node < T>, Node <T>> crossover(
            const Node <T> &tree1,
            const Node <T> &tree2
    );

    std::pair<Node < T> &, int>
    getChildByNum(Node<T>
                  &tree,
                  int num
    );

    Node <T> getRandomIndividual();

    void createIndividual();

    void evaluateIndividual(int i);

};

template<typename T>
class Func {
    std::function<T(const std::vector<Node<T> > &, std::vector<T>)> func;
    int minArity;
    int maxArity;
    std::string repr;
public:
    Func(const std::function<T(const std::vector<Node<T> > &, std::vector<T>)> &f, int minArity, int maxArity,
         const std::string &r);

    const std::function<T(const std::vector<Node<T> > &, std::vector<T>)> &getFunc();

    const int getMinArity() const;

    const int getMaxArity() const;

    const std::string &getRepr() const;

};


template<typename T>
class Node {
private:
    std::string data;
    Func<T> func;

    std::string preorder();

    int numNodes;
    int myNum;

    double fitness;
    double normalizedFitness;
    double accumulatedNormalizedFitness;

    std::vector<Node<T>> children;

    bool isTerm;
public:
    Node(const Func<T> &func, bool term);

    Node(const Func<T> &data, const std::vector<Node> &nodes);

    Node(const Node<T> &node) = default;

    Node(Node<T> &&node) = default;

    Node &operator=(const Node<T> &) = default;

    Node &operator=(Node<T> &&node) = default;

    const std::string &getData() const;

    const Func<T> &getFunc() const;

    const std::vector<Node<T>> &getChildren() const;

    std::vector<Node<T>> &getMutableChildren();

    int enumerate(int num);

    const int height() const;

    std::string toString();

    void addChild(const Node &child);

    void setChildren(const std::vector<Node> &child);

    const double getFitness() const;

    const double getNormalizedFitness() const;

    const double getAccumulatedNormalizedFitness() const;

    void setFitness(const double &fit);

    void setNormalizedFitness(const double &fit);

    void setAccumulatedNormalizedFitness(const double &fit);

    const int getLineageSize() const;

    const int getNodeNum() const;

    const bool isTerminal() const;

    bool operator<(const Node &other) const {
        return (this->fitness < other.fitness);
    }

};


template<typename T>
class Log {
    std::vector<std::vector<Node<T> > > generations;

    bool disabled;

    double getAverageFitness(unsigned int gen);

public:
    Log();

    void addGeneration(const std::vector<Node<T>> newGen);

    const std::vector<Node<T>> getGeneration(unsigned int index) const;

    unsigned int getNumberOfGenerations();

    void drawPngGraph(int width = 1680, int height = 1050);

    void setEnabled();

    void setDisabled();

    bool isDisabled();

};



template<typename T>
GenProg<T>::GenProg() {
    lastGeneration = std::vector<Node<T> >{};
    currentGeneration = std::vector<Node<T>>{};

    generation = 0;

    populationSize = 0;
    generationsLimit = 0;

    functions = std::vector<Func<T> > {};
    terminals = std::vector<Func<T> > {};

    mutationProbability = 100;
    crossoverProbability = 0;

    maxTreeHeight = 3;

    log = Log<T>();
    log.setEnabled();
}

template<typename T>
void GenProg<T>::perform() {
    if (!populationSize ||
        !generationsLimit ||
        functions.empty() ||
        terminals.empty()) {
        std::cerr << "Values not initialized !" << std::endl;
        return;
    }
    this->initialize();
    this->evaluate();
    if (!log.isDisabled()) {
        log.addGeneration(currentGeneration);
    }
    lastGeneration = currentGeneration;
    generation = 0;

    while (generation < generationsLimit && !terminationCriterion()) {
        generation++;

        this->vary();

        this->preEvaluation();

        std::cout << "generation : " << generation << std::endl;
        this->evaluate();

        this->selection();

        this->postCycle();
        lastGeneration = currentGeneration;
        if (!log.isDisabled()) {
            log.addGeneration(currentGeneration);
        }

    }
    std::cout << currentGeneration[0].toString() << std::endl;
}

template<typename T>
void GenProg<T>::initialize() {
    std::vector<std::thread> threads;
    for (unsigned i = 0; i < populationSize; i++) {
        std::thread newT(&GenProg<T>::createIndividual, this);
        threads.push_back(std::move(newT));
    }

    for (unsigned i = 0; i < threads.size(); i++) {
        threads[i].join();
    }

}


template<typename T>
void GenProg<T>::createIndividual() {
    if (initMethod == fullInitializationMethod) {
        Node<T> newNode = fullTreeCreate();
        m.lock();
        this->currentGeneration.push_back(newNode);
        m.unlock();
    } else {
        Node<T> newNode = growTreeCreate();
        m.lock();
        this->currentGeneration.push_back(newNode);
        m.unlock();
    }
}


template<typename T>
void GenProg<T>::evaluate() {
    //count fitness based on user-defined fitness function
    std::vector<std::thread> threads;
    for (unsigned i = 0; i < currentGeneration.size(); i++) {
        std::thread newT(&GenProg<T>::evaluateIndividual, this, i);
        threads.push_back(std::move(newT));
    }
    for (unsigned i = 0; i < threads.size(); i++) {
        threads[i].join();
    }
    //count normalized fitness for each Individual
    double fitnessSum = 0.0;
    for (unsigned i = 0; i < currentGeneration.size(); i++) {
        fitnessSum += currentGeneration[i].getFitness();
    }
    if (standardisedFitness) {
        std::vector<double> adjustedFitness;
        double adjustedSum = 0.0;
        for (unsigned i = 0; i < currentGeneration.size(); i++) {
            adjustedFitness.push_back(1 / (1 + currentGeneration[i].getFitness()));
            adjustedSum += (1 / (1 + currentGeneration[i].getFitness()));
        }
        for (unsigned i = 0; i < currentGeneration.size(); i++) {
            double normalizedFitness = adjustedFitness[i] / adjustedSum;
            currentGeneration[i].setNormalizedFitness(normalizedFitness);
        }
    } else {
        for (unsigned i = 0; i < currentGeneration.size(); i++) {
            double fitness = currentGeneration[i].getFitness();
            double normalizedFitness = fitness / fitnessSum;
            currentGeneration[i].setNormalizedFitness(normalizedFitness);
        }
    }
    std::sort(currentGeneration.begin(), currentGeneration.end());
    if (!standardisedFitness) {
        std::reverse(currentGeneration.begin(), currentGeneration.end());
    }
    //count acumulated fitness
    double accumulatedSum = 0.0;
    for (unsigned i = 0; i < currentGeneration.size(); i++) {
        double val = currentGeneration[i].getNormalizedFitness();
        accumulatedSum += val;
        currentGeneration[i].setAccumulatedNormalizedFitness(accumulatedSum);
    }

    std::cout << currentGeneration[0].getFitness() << std::endl;
    std::cout << currentGeneration[currentGeneration.size() - 1].getFitness() << std::endl;
}

template<typename T>
void GenProg<T>::evaluateIndividual(int i) {
    currentGeneration[i].enumerate(1);
    currentGeneration[i].setFitness(fitFunc(currentGeneration[i]));
}


template<typename T>
void GenProg<T>::vary() {
    currentGeneration.clear();

    while (currentGeneration.size() < populationSize * 2) {
        int randomNum = getRnd(0, mutationProbability + crossoverProbability);
        if (currentGeneration.size() == populationSize * 2 - 1) {
            performMutation();
        } else if (mutationProbability < crossoverProbability) {
            if (randomNum <= mutationProbability) {
                performMutation();
            } else {
                performCrossover();
            }
        } else {
            if (randomNum <= crossoverProbability) {
                performCrossover();
            } else {
                performMutation();
            }
        }
    }
    for (unsigned i = 0; i < lastGeneration.size(); i++) {
        currentGeneration.push_back(lastGeneration[i]);
    }
}


template<typename T>
void GenProg<T>::selection() {
    std::sort(currentGeneration.begin(), currentGeneration.end());
    temporaryGeneration = std::vector<Node<T>>{};
    for (unsigned i = 0; i < populationSize; i++) {
        temporaryGeneration.push_back(currentGeneration[i]);
    }
}


template<typename T>
Node<T> GenProg<T>::mutate(const Node<T> &tree) {
    int num = getRnd(1, tree.getLineageSize() + 2);
    Node<T> newTree = this->findAndReplace(tree, num, 0);
    return newTree;
}

template<typename T>
std::pair<Node<T>, Node<T>> GenProg<T>::crossover(const Node<T> &tree1, const Node<T> &tree2) {
    Node<T> firstTreeCopy(tree1);
    int firstRandomNum = getRnd(1, firstTreeCopy.getLineageSize() + 2);

    Node<T> secondTreeCopy(tree2);
    int secondRandomNum = getRnd(1, secondTreeCopy.getLineageSize() + 2);

    if (firstRandomNum == 1 && secondRandomNum == 1) {
        return std::pair<Node<T>, Node<T>> {firstTreeCopy, secondTreeCopy};
    }
    if (firstRandomNum == 1) {
        std::pair<Node<T> &, int> secondTreeRes = getChildByNum(secondTreeCopy, secondRandomNum);
        std::vector<Node<T>> &children2 = secondTreeRes.first.getMutableChildren();

        Node<T> child1 = firstTreeCopy;
        Node<T> child2 = children2[secondTreeRes.second];

        firstTreeCopy = child2;

        children2[secondTreeRes.second] = child1;
        secondTreeRes.first.setChildren(children2);

        return std::pair<Node<T>, Node<T>> {firstTreeCopy, secondTreeCopy};
    }
    if (secondRandomNum == 1) {
        std::pair<Node<T> &, int> firstTreeRes = getChildByNum(firstTreeCopy, firstRandomNum);
        std::vector<Node<T>> &children1 = firstTreeRes.first.getMutableChildren();

        Node<T> child1 = children1[firstTreeRes.second];
        Node<T> child2 = secondTreeCopy;

        secondTreeCopy = child1;

        children1[firstTreeRes.second] = child2;
        firstTreeRes.first.setChildren(children1);

        return std::pair<Node<T>, Node<T>> {firstTreeCopy, secondTreeCopy};
    }
    std::pair<Node<T> &, int> firstTreeRes = getChildByNum(firstTreeCopy, firstRandomNum);
    std::pair<Node<T> &, int> secondTreeRes = getChildByNum(secondTreeCopy, secondRandomNum);

    std::vector<Node<T>> &children1 = firstTreeRes.first.getMutableChildren();
    std::vector<Node<T>> &children2 = secondTreeRes.first.getMutableChildren();

    Node<T> child1 = children1[firstTreeRes.second];
    Node<T> child2 = children2[secondTreeRes.second];

    children1[firstTreeRes.second] = child2;
    children2[secondTreeRes.second] = child1;

    firstTreeRes.first.setChildren(children1);
    secondTreeRes.first.setChildren(children2);

    return std::pair<Node<T>, Node<T>> {firstTreeCopy, secondTreeCopy};
}

template<typename T>
std::pair<Node<T> &, int> GenProg<T>::getChildByNum(Node<T> &tree, int num) {
    std::vector<Node<T>> &children = tree.getMutableChildren();
    for (unsigned i = 0; i < children.size() - 1; i++) {
        if (children[i].getNodeNum() == num) {
            return std::pair<Node<T> &, int>{tree, i};
        } else if (children[i + 1].getNodeNum() > num) {
            return getChildByNum(children[i], num);
        }
    }
    if (children[children.size() - 1].getNodeNum() == num) {
        return std::pair<Node<T> &, int>{tree, children.size() - 1};
    }
    return getChildByNum(children[children.size() - 1], num);
}

template<typename T>
Node<T> GenProg<T>::findAndReplace(const Node<T> &tree, int num, int depth) {
    Node<T> modifiedTree = tree;
    std::vector<Node<T>> children = tree.getChildren();
    for (unsigned i = 0; i < children.size(); i++) {
        if (children[i].getNodeNum() == num) {
            children.erase(children.begin() + i);
            if (initMethod == fullInitializationMethod) {
                children.insert(children.begin() + i, fullRecursively(depth, tree.getFunc())[0]);
            } else {
                children.insert(children.begin() + i, growRecursively(depth, tree.getFunc())[0]);
            }
            break;
        } else if (i == children.size() - 1) {
            children[i] = findAndReplace(children[i], num, depth + 1);
        } else if (children[i + 1].getNodeNum() > num) {
            children[i] = findAndReplace(children[i], num, depth + 1);
            break;
        }
    }
    modifiedTree.setChildren(children);
    return modifiedTree;
}

template<typename T>
int GenProg<T>::getRnd(int from, int to) {
    std::uniform_int_distribution<> distr(from, to - 1); // define the range
    return distr(mt);
}

template<typename T>
Node<T> GenProg<T>::growTreeCreate() {
    if (getRnd(0, 100) > 75) {
        int index = getRnd(0, terminals.size());
        return Node<T>(terminals[index], true);
    }
    int index = getRnd(0, functions.size());
    return Node<T>(functions[index], growRecursively(1, functions[index]));
}

template<typename T>
const std::vector<Node<T> > GenProg<T>::growRecursively(const int depth, const Func<T> &func) {
    int child = getRnd(func.getMinArity(), func.getMaxArity() + 1);
    std::vector<Node<T> > children = std::vector<Node<T> >{};
    if (depth == maxTreeHeight) {
        for (unsigned i = 0; i < child; i++) {
            int index = getRnd(0, terminals.size());
            children.push_back(Node<T>(terminals[index], true));
        }
        return children;
    }
    int termProbability = 50;
    for (unsigned i = 0; i < child; i++) {
        if (getRnd(0, 100) < termProbability) {
            int index = getRnd(0, terminals.size());
            children.push_back(Node<T>(terminals[index], true));
        } else {
            int index = getRnd(0, functions.size());
            Node<T> newNode = Node<T>(functions[index], growRecursively(depth + 1, functions[index]));
            children.push_back(newNode);
        }
    }
    return children;
}


template<typename T>
Node<T> GenProg<T>::fullTreeCreate() {
    int index = getRnd(0, functions.size());
    return Node<T>(functions[index], fullRecursively(2, functions[index]));
}


template<typename T>
const std::vector<Node<T> > GenProg<T>::fullRecursively(const int depth, const Func<T> &func) {
    int child = getRnd(func.getMinArity(), func.getMaxArity() + 1);
    std::vector<Node<T>> children = std::vector<Node<T>>{};
    if (depth >= maxTreeHeight) {
        for (unsigned i = 0; i < child; i++) {
            int index = getRnd(0, terminals.size());
            children.push_back(Node<T>(terminals[index], true));
        }
        return children;
    }
    for (unsigned i = 0; i < child; i++) {
        int index = getRnd(0, functions.size());
        Node<T> newNode = Node<T>(functions[index], fullRecursively(depth + 1, functions[index]));
        children.push_back(newNode);
    }
    return children;
}


template<typename T>
Node<T> GenProg<T>::getRandomIndividual() {
    std::uniform_real_distribution<> distr(0, std::nextafter(1, DBL_MAX));
    double rnd = distr(mt);
    for (unsigned i = 0; i < lastGeneration.size(); i++) {
        if (lastGeneration[i].getAccumulatedNormalizedFitness() > rnd) {
            return lastGeneration[i];
        }
    }
    return lastGeneration[lastGeneration.size() - 1];
}


template<typename T>
void GenProg<T>::performMutation() {
    Node<T> firstIndividual = getRandomIndividual();
    currentGeneration.push_back(mutate(firstIndividual));
}

template<typename T>
void GenProg<T>::performCrossover() {
    Node<T> firstIndividual = getRandomIndividual();
    Node<T> secondIndividual = getRandomIndividual();
    for (unsigned i = 0; i < numberOfAttempts; i++) {
        std::pair<Node<T>, Node<T>> crossoverRes = crossover(firstIndividual, secondIndividual);
        if (crossoverRes.first.height() <= maxTreeHeight && crossoverRes.second.height() <= maxTreeHeight) {
            currentGeneration.push_back(crossoverRes.first);
            currentGeneration.push_back(crossoverRes.second);
            return;
        }
    }
}


template<typename T>
void GenProg<T>::setPopulationSize(unsigned size) {
    this->populationSize = size;
}

template<typename T>
void GenProg<T>::setGenerationsLimit(unsigned limit) {
    this->generationsLimit = limit;
}

template<typename T>
void GenProg<T>::setInitializationMethod(std::string method) {
    this->initMethod = method;
}


template<typename T>
void GenProg<T>::setMutationProbability(unsigned probability) {
    this->mutationProbability = probability;
}

template<typename T>
void GenProg<T>::setCrossoverProbability(unsigned probability) {
    this->crossoverProbability = probability;
}

template<typename T>
void GenProg<T>::setMaxTreeHeight(unsigned height) {
    this->maxTreeHeight = height;
}

template<typename T>
void GenProg<T>::setNumberOfAttempts(unsigned num) {
    this->numberOfAttempts = num;
}

template<typename T>
const Log<T> &GenProg<T>::getLog() const {
    return this->log;
}

template<typename T>
void GenProg<T>::addFunction(const Func<T> &func) {
    this->functions.push_back(func);
};

template<typename T>
void GenProg<T>::setFunctions(const std::vector<Func<T> > &func) {
    this->functions = func;
};

template<typename T>
void GenProg<T>::addTerminal(const Func<T> &term) {
    this->terminals.push_back(term);
};

template<typename T>
void GenProg<T>::setTerminals(const std::vector<Func<T> > &term) {
    this->terminals = term;
}

// if true: the higher fitness, the better
template<typename T>
void GenProg<T>::setStandardisedFitness(bool isStandard) {
    this->standardisedFitness = isStandard;
}

template<typename T>
const std::vector<Node<T>> &GenProg<T>::getCurrentGeneration() {
    return this->currentGeneration;
}

template<typename T>
void GenProg<T>::setCurrentGeneration(const std::vector<Node<T>> &currGen) {
    this->currentGeneration = currGen;
}

template<typename T>
const std::vector<Node<T>> &GenProg<T>::getLastGeneration() {
    return this->lastGeneration;
}

template<typename T>
bool GenProg<T>::terminationCriterion() {
    return false;
}

template<typename T>
void GenProg<T>::postCycle() {
    currentGeneration = temporaryGeneration;
}



template<typename T>
Func<T>::Func(const std::function<T(const std::vector<Node<T> > &, std::vector<T>)> &f, int minArity, int maxArity,
              const std::string &r)
        : func(f), minArity(minArity), maxArity(maxArity), repr(r) {}

template<typename T>
const std::function<T(const std::vector<Node<T> > &, std::vector<T>)> &Func<T>::getFunc() { return this->func; }

template<typename T>
const int Func<T>::getMinArity() const { return this->minArity; }

template<typename T>
const int Func<T>::getMaxArity() const { return this->maxArity; }

template<typename T>
const std::string &Func<T>::getRepr() const { return this->repr; }



template<typename T>
Log<T>::Log() {
}


template<typename T>
void Log<T>::addGeneration(const std::vector<Node<T> > newGen) {
    this->generations.push_back(newGen);
}

template<typename T>
const std::vector<Node<T> > Log<T>::getGeneration(unsigned int index) const {
    if (generations.empty() || generations.size() - 1 < index) {
        std::cerr << "Invalid index" << std::endl;
        return std::vector<Node<T>>{};
    }
    return generations[index];

}

template<typename T>
unsigned int Log<T>::getNumberOfGenerations() {
    if (generations.empty()) {
        return 0;
    }
    return generations.size();
}

template<typename T>
void Log<T>::drawPngGraph(int width, int height) {
    mglGraph gr;
    gr.SetSize(width, height);
    gr.Title("Average Fitness through all generations");
    gr.SetRanges(0, generations.size(), 0, 10);
    gr.Axis();

    std::vector<mglPoint> points;
    for (unsigned int i = 0; i < generations.size(); i++) {
        points.push_back(mglPoint(i, getAverageFitness(i)));
    }
    for (unsigned i = 1; i < points.size(); i++) {
        gr.Line(points[i - 1], points[i], "r", 100);
    }

    gr.Light(true);
    gr.WriteFrame("thread-graph.png");

}

template<typename T>
double Log<T>::getAverageFitness(unsigned int gen) {
    double accumulatedSum = 0.0;
    for (unsigned i = 0; i < generations[gen].size(); i++) {
        accumulatedSum += generations[gen][i].getFitness();
    }
    return accumulatedSum / generations[gen].size();
}

template<typename T>
void Log<T>::setEnabled() { this->disabled = false; }

template<typename T>
void Log<T>::setDisabled() { this->disabled = true; }

template<typename T>
bool Log<T>::isDisabled() {
    return this->disabled;
}

template<typename T>
Node<T>::Node(const Func <T> &func, bool term)
        : func(func), isTerm(term) {
    myNum = 0;
    numNodes = 0;
    fitness = 0.0;
}

template<typename T>
Node<T>::Node(const Func <T> &data, const std::vector <Node<T>> &children)
        : func(data), children(children), isTerm(false) {
    myNum = 0;
    numNodes = 0;
    fitness = 0.0;
}

template<typename T>
void Node<T>::addChild(const Node <T> &child) { this->children.push_back(child); }

template<typename T>
void Node<T>::setChildren(const std::vector <Node<T>> &child) { children = child; }

template<typename T>
const std::vector <Node<T>> &Node<T>::getChildren() const { return this->children; }

template<typename T>
std::vector <Node<T>> &Node<T>::getMutableChildren() { return this->children; }

template<typename T>
const std::string &Node<T>::getData() const { return func.getRepr(); }

template<typename T>
const Func <T> &Node<T>::getFunc() const { return this->func; }

template<typename T>
void Node<T>::setFitness(const double &fit) { this->fitness = fit; }

template<typename T>
void Node<T>::setNormalizedFitness(const double &fit) { this->normalizedFitness = fit; }

template<typename T>
void Node<T>::setAccumulatedNormalizedFitness(const double &fit) { this->accumulatedNormalizedFitness = fit; }

template<typename T>
const double Node<T>::getFitness() const { return this->fitness; }

template<typename T>
const double Node<T>::getNormalizedFitness() const { return this->normalizedFitness; }

template<typename T>
const double Node<T>::getAccumulatedNormalizedFitness() const { return this->accumulatedNormalizedFitness; }

template<typename T>
const int Node<T>::getLineageSize() const { return this->numNodes; }

template<typename T>
const int Node<T>::getNodeNum() const { return this->myNum; }

template<typename T>
const bool Node<T>::isTerminal() const { return this->isTerm; }

template<typename T>
const int Node<T>::height() const {
    if (isTerm) {
        return 1;
    }
    int highest = 0;
    for (int i = 0; i < children.size(); i++) {
        int thisHeight = children[i].height();
        if (highest < thisHeight) {
            highest = thisHeight;
        }
    }
    return highest + 1;
}


template<typename T>
std::string Node<T>::toString() {
    return preorder();
}

template<typename T>
std::string Node<T>::preorder() {
    if (isTerm) {
        return getFunc().getRepr();
    }
    const char *separator = "";
    std::stringstream ss;
    ss << getFunc().getRepr();
    ss << "(";
    for (int i = 0; i < children.size(); i++) {
        ss << separator << children[i].preorder();
        separator = " ";
    }
    ss << ')';
    return ss.str();

}

template<typename T>
int Node<T>::enumerate(int num) {
    this->myNum = num;
    if (this->isTerm) {
        return num;
    }
    for (int i = 0; i < this->children.size(); i++) {
        num = this->children[i].enumerate(num + 1);
    }
    this->numNodes = num - myNum;
    return num;
}

#endif //FRAMEWORK_GENPROGLIB_H
