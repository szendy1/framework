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

#include "Log.h"
#include "Node.h"
#include "Func.h"

template <typename T > class GenProg {
private:
    std::vector< Node<T> > gen;

    int populationSize;
    int generationsLimit;


    double chanceFullTree;
    double chanceGrowTree;


    double mutationChance;
    double crossoverChance;

    int numberOfAttempts;

    int maxTreeHeight;

    Log<T> log;

    std::random_device  rd;
    std::mt19937        mt;

    const int getRnd(int from, int to);
    Node<T> fullTreeCreate();
    Node<T> growTreeCreate();
    const std::vector< Node<T> > growRecursively(const int depth, const Func<T> &func);
    const std::vector< Node<T> > fullRecursively(const int depth, const Func<T> &func);

    void performMutation(std::vector<Node<T>> &actualGeneration);
    Node<T> mutate(const Node<T> &tree);
    Node<T> findAndReplace(const Node<T> &tree,int num,int depth);

    void performCrossover(std::vector<Node<T>> &actualGeneration);
    std::pair<Node<T>, Node<T>> crossover(const Node<T> &tree1, const Node<T> &tree2);
    std::pair<Node<T> &,int> getChildByNum(Node<T> &tree, int num);
    Node<T> getRandomIndividual();


public:
    GenProg();
    void perform();
    void initialize();
    void evaluate();
    void vary();
    void selection();

    std::vector< Func<T> > functions;
    std::vector< Func<T> > terminals;

    void setPopulationSize(int size);
    void setGenerationsLimit(int limit);

    void setFullMethodChance(int chance);
    void setGrowMethodChance(int chance);

    void setMutationChance(int chance);
    void setCrossoverChance(int chance);

    void setNumberOfAttempts(int num);

    void setMaxTreeHeight(int height);

    const Log<T> &getLog() const;

    /*void addFunction(const Func<T> &func)   { this->functions.push_back(func); };
    void setFunctions(const std::vector< Func<T> > &func)
                                            { this->functions = func; };

    void addTerminal(const Func<T> &term)   {this->terminals.push_back(term); };
    void setTerminals(const std::vector< Func<T> > &term)
                                            { this->terminals = term; };
    */

    virtual double fitFunc(const Node<T> &root) { return 0.0; };

};

template class GenProg<double>;

#endif //FRAMEWORK_GENPROG_H


template<typename T > GenProg<T >::GenProg(){
    mt = std::mt19937 (rd()); // seed the generator

    gen = std::vector< Node<T> >{};
    populationSize = 0;
    generationsLimit = 0;

    functions = std::vector< Func<T> > {};
    terminals = std::vector< Func<T> > {};

    mutationChance = 100;
    crossoverChance = 0;

    maxTreeHeight = 3;

    log = Log<T>();
}

template<typename T > void GenProg<T>::perform(){
    if (!populationSize ||
        !generationsLimit ||
        functions.empty() ||
        terminals.empty() ){
        std::cout << "Values not initialized !" << std::endl;
        return;
    }
    this->initialize();
    this->evaluate();
    log.addGeneration(gen);

    std::cout << "init successful" << std::endl;

    int tmp = 0;
    std::cout<< "Evolution Cycle" << std::endl;
    while (log.getNumberOfGenerations()<generationsLimit){

        //std::cout<< "Vary Cycle" << std::endl;
        this->vary();

        std::cout << "eval started : " << tmp << std::endl;
        this->evaluate();

        //std::cout<< "Selection Cycle" << std::endl;
        this->selection();
        tmp++;
    }

}

template<typename T > void GenProg<T >::initialize(){
    std::cout << "init started" << std::endl;

    for (int i=0;i<populationSize;i++){
        this->gen.push_back(fullTreeCreate());
    }

    std::cout << "init succeed" << std::endl;
}

template<typename T > void GenProg<T >::evaluate() {
    //std::cout << "eval started" << std::endl;
    double sumValue =0.0;
    for (int i=0;i<gen.size();i++){
        gen[i].enumerate(1);
        double val = fitFunc(gen[i]);
        if (val!=val){
            std::cerr << "NaN" << std::endl;
        }
        gen[i].setFitness(val);
        sumValue+=val;
    }
    std::sort(gen.begin(),gen.end());
    double actualSum = 0.0;
    for (int i=0;i<gen.size();i++){
        double val = gen[i].getFitness();
        if (val!=val){
            std::cerr << "NaN next" << std::endl;
        }
        actualSum+= val;
        if (actualSum!=actualSum){
            std::cerr << "NaN Sum" << std::endl;
        }
        gen[i].setFitness(actualSum/sumValue);
        if (gen[i].getFitness()!=gen[i].getFitness()){
            std::cerr << actualSum << std::endl;
            std::cerr << val << std::endl;
            std::cerr << "NaN Value" << std::endl;
        }
    }

    //std::cout << "eval succeed" << std::endl;
}


template<typename T > void GenProg<T >::vary() {
    std::vector<Node<T>> newGeneration = gen;
    while (newGeneration.size()<populationSize*2){
        int randomNum = getRnd(0,mutationChance+crossoverChance);
        if (newGeneration.size()==populationSize*2-1){
            performMutation(newGeneration);
        }
        else if (mutationChance<crossoverChance){
            if (randomNum<=mutationChance){
                performMutation(newGeneration);
            }
            else{
                performCrossover(newGeneration);
            }
        } else {
            if (randomNum<=crossoverChance){
                performCrossover(newGeneration);
            }
            else{
                performMutation(newGeneration);
            }
        }
    }
    gen = newGeneration;
}


template<typename T > void GenProg<T >::selection() {
    std::vector<Node<T>> newGeneration= std::vector<Node<T>>{};
    for (unsigned i= 0; i<populationSize;i++){
        newGeneration.push_back(gen[i]);
    }
    gen = newGeneration;
    log.addGeneration(gen);
}


template<typename T > Node<T> GenProg<T >::mutate(const Node<T> &tree){
    int num = getRnd(1,tree.getLineageSize()+2);
    Node<T> newTree=this->findAndReplace(tree,num,0);
    return newTree;
}

template<typename T > std::pair<Node<T>, Node<T>> GenProg<T >::crossover(const Node<T> &tree1,const Node<T> &tree2) {
    Node<T> firstTreeCopy(tree1);
    int firstRandomNum = getRnd(1,firstTreeCopy.getLineageSize()+2);

    Node<T> secondTreeCopy(tree2);
    int secondRandomNum = getRnd(1,secondTreeCopy.getLineageSize()+2);

    if (firstRandomNum == 1 && secondRandomNum == 1){
        return std::pair<Node<T>,Node<T>> {firstTreeCopy,secondTreeCopy};
    }
    if (firstRandomNum==1){
        std::pair<Node<T> &,int> secondTreeRes = getChildByNum(secondTreeCopy, secondRandomNum);
        std::vector<Node<T>> &children2 = secondTreeRes.first.getMutableChildren();

        Node<T> child1 = firstTreeCopy;
        Node<T> child2 = children2[secondTreeRes.second];

        firstTreeCopy = child2;

        children2[secondTreeRes.second] = child1;
        secondTreeRes.first.setChildren(children2);

        return std::pair<Node<T>,Node<T>> {firstTreeCopy,secondTreeCopy};
    }
    if (secondRandomNum == 1){
        std::pair<Node<T> &,int> firstTreeRes = getChildByNum(firstTreeCopy, firstRandomNum);
        std::vector<Node<T>> &children1 = firstTreeRes.first.getMutableChildren();

        Node<T> child1 = children1[firstTreeRes.second];
        Node<T> child2 = secondTreeCopy;

        secondTreeCopy = child1;

        children1[firstTreeRes.second] = child2;
        firstTreeRes.first.setChildren(children1);

        return std::pair<Node<T>,Node<T>> {firstTreeCopy,secondTreeCopy};
    }
    std::pair<Node<T> &,int> firstTreeRes = getChildByNum(firstTreeCopy, firstRandomNum);
    std::pair<Node<T> &,int> secondTreeRes = getChildByNum(secondTreeCopy, secondRandomNum);

    std::vector<Node<T>> &children1 = firstTreeRes.first.getMutableChildren();
    std::vector<Node<T>> &children2 = secondTreeRes.first.getMutableChildren();

    Node<T> child1 = children1[firstTreeRes.second];
    Node<T> child2 = children2[secondTreeRes.second];

    children1[firstTreeRes.second] = child2;
    children2[secondTreeRes.second] = child1;

    firstTreeRes.first.setChildren(children1);
    secondTreeRes.first.setChildren(children2);

    return std::pair<Node<T>, Node<T>> {firstTreeCopy,secondTreeCopy};
}

template<typename T > std::pair<Node<T> &,int> GenProg<T >::getChildByNum(Node<T> &tree, int num){
    std::vector<Node<T>> &children = tree.getMutableChildren();
    for (int i=0;i<children.size()-1;i++){
        if (children[i].getNodeNum()==num){
            return std::pair<Node<T> &, int>{tree,i};
        }
        else if (children[i+1].getNodeNum()>num){
            return getChildByNum(children[i],num);
        }
    }
    if (children[children.size() - 1].getNodeNum() == num){
        return std::pair<Node<T> &, int>{tree,children.size() - 1};
    }
    return getChildByNum(children[children.size()-1],num);
}

template<typename T > Node<T> GenProg<T >::findAndReplace(const Node<T> &tree,int num,int depth){
    Node<T> modifiedTree = tree;
    std::vector<Node<T>> children = tree.getChildren();
    for (int i=0;i<children.size();i++){
        if (children[i].getNodeNum()==num){
            children.erase(children.begin()+i);
            children.insert(children.begin()+i,fullRecursively(depth,tree.getFunc())[0]);
            break;
        }
        else if (i==children.size()-1){
            children[i]=findAndReplace(children[i],num,depth+1);
        }
        else if (children[i+1].getNodeNum()>num){
            children[i]=findAndReplace(children[i],num,depth+1);
            break;
        }
    }
    modifiedTree.setChildren(children);
    return modifiedTree;
}

template<typename T > const int GenProg<T >::getRnd(int from, int to){
    std::uniform_int_distribution<> distr(from, to-1); // define the range
    return distr(mt);
}

template<typename T > Node<T> GenProg<T >::growTreeCreate(){
    if (getRnd(0,100)>75){
        int index = getRnd(0,terminals.size());
        return Node<T>(terminals[index],true);
    }
    int index = getRnd(0,functions.size());
    return Node<T>(functions[index],growRecursively(1,functions[index]));
}

template<typename T > const std::vector< Node<T> > GenProg<T>::growRecursively(const int depth, const Func<T> &func){
    int child = getRnd( func.getMinArity(), func.getMaxArity()+1);
    std::vector< Node<T> > children = std::vector< Node<T> >{};
    if (depth == maxTreeHeight ){
        for (unsigned i = 0; i<child;i++){
            int index = getRnd(0, terminals.size());
            children.push_back( Node<T>( terminals[index],true ) );
        }
        return children;
    }
    int termChance = 35;
    for (unsigned i = 0; i< child; i++){
        if (getRnd(0,100)<=termChance){
            int index = getRnd(0, terminals.size());
            children.push_back( Node<T>( terminals[index],true ) );
        }
        else{
            int index = getRnd(0,functions.size());
            Node<T> newNode = Node<T>( functions[index], growRecursively( depth+1, functions[index] ) );
            children.push_back(newNode);
        }
    }
    return children;
}


template<typename T > Node<T> GenProg<T>::fullTreeCreate(){
    int index = getRnd(0,functions.size());
    return Node<T>(functions[index],fullRecursively(2,functions[index]));
}


template<typename T > const std::vector< Node<T> > GenProg<T>::fullRecursively(const int depth, const Func<T> &func){
    int child = getRnd( func.getMinArity(), func.getMaxArity()+1);
    std::vector<Node<T>> children = std::vector<Node<T>>{};
    if (depth >= maxTreeHeight ){
        for (unsigned i = 0; i<child;i++){
            int index = getRnd(0, terminals.size());
            children.push_back( Node<T>( terminals[index], true ) );
        }
        return children;
    }
    for (unsigned i = 0; i< child; i++){
        int index = getRnd(0,functions.size());
        Node<T> newNode = Node<T>( functions[index], fullRecursively( depth+1, functions[index]) );
        children.push_back(newNode);
    }
    return children;
}


template<typename T > Node<T> GenProg<T>::getRandomIndividual() {
    std::uniform_real_distribution<> distr(0,std::nextafter(1, DBL_MAX));
    double rnd = distr(mt);
    for (unsigned i =0;i<gen.size();i++){
        if (gen[i].getFitness()>rnd){
            return gen[i];
        }
    }
    return gen[gen.size()-1];
}


template<typename T > void GenProg<T>::performMutation(std::vector<Node<T>> &actualGeneration){
    Node<T> firstIndividual = getRandomIndividual();
    actualGeneration.push_back(mutate(firstIndividual));
}

template<typename T > void GenProg<T>::performCrossover(std::vector<Node<T>> &actualGeneration) {
    Node<T> firstIndividual = getRandomIndividual();
    Node<T> secondIndividual = getRandomIndividual();
    for (unsigned i = 0; i<numberOfAttempts; i++){
        std::pair<Node<T>, Node<T>> crossoverRes = crossover(firstIndividual,secondIndividual);
        if (crossoverRes.first.height() <= maxTreeHeight && crossoverRes.second.height() <= maxTreeHeight) {
            actualGeneration.push_back(crossoverRes.first);
            actualGeneration.push_back(crossoverRes.second);
            return;
        }
    }
}


template <typename T> void GenProg<T>::setPopulationSize(int size){
    this->populationSize=size;
}

template <typename T> void GenProg<T>::setGenerationsLimit(int limit){
    this->generationsLimit = limit;
}

template <typename T> void GenProg<T>::setFullMethodChance(int chance){
    this->chanceFullTree = chance;
}

template <typename T> void GenProg<T>::setGrowMethodChance(int chance){
    this->chanceGrowTree = chance;
}

template <typename T> void GenProg<T>::setMutationChance(int chance){
    this->mutationChance = chance;
}

template <typename T> void GenProg<T>::setCrossoverChance(int chance){
    this->crossoverChance = chance;
}

template <typename T> void GenProg<T>::setMaxTreeHeight(int height){
    this->maxTreeHeight = height;
}

template <typename T> void GenProg<T>::setNumberOfAttempts(int num) {
    this->numberOfAttempts = num;
}

template <typename T> const Log<T> &GenProg<T>::getLog() const {
    return this->log;
}
