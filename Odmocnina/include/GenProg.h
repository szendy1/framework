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
    static constexpr char *fullInitializationMethod = (char*)"full";
    static constexpr char *growInitializationMethod = (char*)"grow";

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

template
class GenProg<double>;

#endif //FRAMEWORK_GENPROG_H


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
    if (standardisedFitness){
        std::vector<double> adjustedFitness;
        double adjustedSum = 0.0;
        for (unsigned i = 0; i < currentGeneration.size(); i++){
            adjustedFitness.push_back(1/(1+currentGeneration[i].getFitness()));
            adjustedSum+=(1/(1+currentGeneration[i].getFitness()));
        }
        for (unsigned i=0; i < currentGeneration.size();i++){
            double normalizedFitness = adjustedFitness[i] / adjustedSum;
            currentGeneration[i].setNormalizedFitness(normalizedFitness);
        }
    }
    else{
        for (unsigned i = 0; i < currentGeneration.size(); i++) {
            double fitness = currentGeneration[i].getFitness();
            double normalizedFitness = fitness / fitnessSum;
            currentGeneration[i].setNormalizedFitness(normalizedFitness);
        }
    }
    std::sort(currentGeneration.begin(), currentGeneration.end());
    if (!standardisedFitness){
        std::reverse(currentGeneration.begin(),currentGeneration.end());
    }
    //count acumulated fitness
    double accumulatedSum = 0.0;
    for (unsigned i = 0; i < currentGeneration.size(); i++) {
        double val = currentGeneration[i].getNormalizedFitness();
        accumulatedSum += val;
        currentGeneration[i].setAccumulatedNormalizedFitness(accumulatedSum);
    }

    std::cout << currentGeneration[0].getFitness() << std::endl;
    std::cout << currentGeneration[currentGeneration.size()-1].getFitness() << std::endl;
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
    for (unsigned i=0;i<lastGeneration.size();i++){
        currentGeneration.push_back(lastGeneration[i]);
    }
}


template<typename T>
void GenProg<T>::selection() {
    std::sort(currentGeneration.begin(),currentGeneration.end());
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
            }
            else{
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

template <typename T>
const std::vector<Node<T>> &GenProg<T>::getCurrentGeneration() {
    return this->currentGeneration;
}

template<typename T>
void GenProg<T>::setCurrentGeneration(const std::vector<Node<T>> &currGen) {
    this->currentGeneration = currGen;
}

template <typename T>
const std::vector<Node<T>> &GenProg<T>::getLastGeneration() {
    return this->lastGeneration;
}

template<typename T>
bool GenProg<T>::terminationCriterion() {
    return false;
}

template <typename T>
void GenProg<T>::postCycle(){

    if (!log.isDisabled()){
            log.addGeneration(temporaryGeneration);
        }
    lastGeneration = temporaryGeneration;
}
