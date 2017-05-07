//
// Created by Alexander on 31.01.2017.
//

#include "GenProg.h"
#include "Generation.h"
#include "Func.h"

#include <iostream>
#include <ctime>
#include <algorithm>
#include <cmath>

GenProg::GenProg(){
    /*populationSize = 100;
    generations = 50;

    Func p(plus,2,5,"+");
    Func min(minus,1,2,"-");
    Func mul(multiply,2,2,"*");
    Func d(divide,2,2,"/");

    function = std::vector<Func> {p,min,mul,d};

    terminals = std::vector<std::string> {"input1"};


    values = std::vector<double> {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,13.0,15.0,17.0,19.0,20.0,24.0,26.0,28.0,30.0,33.0,35.0,37.0,39.0,40.0,45.0,50.0,54.0,61.0,66.0,67.0,68.0,76.0,86.0};

    chanceFullTree = 100;

    mutationChance = 60;
    crossoverChance = 40;

    maxTreeHeight = 3;
*/
    log = Log();

    srand (time(NULL));

}

/*TODO:
 * volitelne krizenie mutacia
 * (ramped half/half)
 *
 *
 */

void GenProg::perform(){
    if (!populationSize ||
            !generations ||
            function.size() == 0 ||
            terminals.size() == 0 ){
        std::cout << "Values not initialized !" << std::endl;
        return;
    }
    this->Initialization();
    this->Evaluation();
    log.addGeneration(gen);

    std::cout << "init successful" << std::endl;


    std::cout<< "Evolution Cycle" << std::endl;
    while (log.generations.size()<generations){

        std::cout<< "Vary Cycle" << std::endl;
        this->Vary();

        std::cout<< "Evalue Cycle" << std::endl;
        this->Evaluation();

        std::cout<< "Feed Cycle" << std::endl;
        this->FeedNewGeneration();

    }

}

void GenProg::Initialization(){
    std::cout << "init started" << std::endl;

    for (int i=0;i<populationSize;i++){
        this->gen.push_back(crtFullTree());
    }

    std::cout << "init no errors" << std::endl;
}

void GenProg::Evaluation() {
    std::cout << "eval started" << std::endl;
    double sumValue =0.0;
    for (int i=0;i<gen.size();i++){
        gen[i].enumerate(1);
        double val = fitFunc(gen[i]);
        gen[i].setValue(val);
        sumValue+=val;
    }
    std::sort(gen.begin(),gen.end());
    double actualSum = 0.0;
    for (int i=0;i<gen.size();i++){
        double val = gen[i].getValue();
        actualSum+= val;
        gen[i].setValue(actualSum/sumValue);
    }

    std::cout << "eval no errors" << std::endl;
}


void GenProg::Vary() {
    std::vector<Node> newGeneration = gen;
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


void GenProg::FeedNewGeneration() {
    std::vector<Node> newGeneration= std::vector<Node>{};
    for (unsigned i= 0; i<generations;i++){
        newGeneration.push_back(gen[i]);
    }
    gen = newGeneration;
    log.addGeneration(gen);
}


Node GenProg::mutate(const Node &tree){
    int num = getRnd(1,tree.getLineageSize()+2);
    Node newTree=this->findAndReplace(tree,num,0);
    return newTree;
}

std::pair<Node, Node> GenProg::crossover(const Node &tree1,const Node &tree2) {
    Node firstTreeCopy(tree1);
    int firstRandomNum = getRnd(1,firstTreeCopy.getLineageSize()+2);

    Node secondTreeCopy(tree2);
    int secondRandomNum = getRnd(1,secondTreeCopy.getLineageSize()+2);

    if (firstRandomNum == 1 && secondRandomNum == 1){
        return std::pair<Node,Node> {firstTreeCopy,secondTreeCopy};
    }
    if (firstRandomNum==1){
        std::pair<Node &,int> secondTreeRes = findChildInTree(secondTreeCopy, secondRandomNum);
        std::vector<Node> &children2 = secondTreeRes.first.getMutableChildren();

        Node child1 = firstTreeCopy;
        Node child2 = children2[secondTreeRes.second];

        firstTreeCopy = child2;

        children2[secondTreeRes.second] = child1;
        secondTreeRes.first.setChildren(children2);

        return std::pair<Node,Node> {firstTreeCopy,secondTreeCopy};
    }
    if (secondRandomNum == 1){
        std::pair<Node &,int> firstTreeRes = findChildInTree(firstTreeCopy, firstRandomNum);
        std::vector<Node> &children1 = firstTreeRes.first.getMutableChildren();

        Node child1 = children1[firstTreeRes.second];
        Node child2 = secondTreeCopy;

        secondTreeCopy = child1;

        children1[firstTreeRes.second] = child2;
        firstTreeRes.first.setChildren(children1);

        return std::pair<Node,Node> {firstTreeCopy,secondTreeCopy};
    }
    std::pair<Node &,int> firstTreeRes = findChildInTree(firstTreeCopy, firstRandomNum);
    std::pair<Node &,int> secondTreeRes = findChildInTree(secondTreeCopy, secondRandomNum);

    std::vector<Node> &children1 = firstTreeRes.first.getMutableChildren();
    std::vector<Node> &children2 = secondTreeRes.first.getMutableChildren();

    Node child1 = children1[firstTreeRes.second];
    Node child2 = children2[secondTreeRes.second];

    children1[firstTreeRes.second] = child2;
    children2[secondTreeRes.second] = child1;

    firstTreeRes.first.setChildren(children1);
    secondTreeRes.first.setChildren(children2);

    return std::pair<Node, Node> {firstTreeCopy,secondTreeCopy};
}

std::pair<Node &,int> GenProg::findChildInTree(Node &tree, int num){
    std::vector<Node> &children = tree.getMutableChildren();
    for (int i=0;i<children.size()-1;i++){
        if (children[i].getNodeNum()==num){
            return std::pair<Node &, int>{tree,i};
        } 
        else if (children[i+1].getNodeNum()>num){
            return findChildInTree(children[i],num);
        }   
    }
    if (children[children.size() - 1].getNodeNum() == num){
        return std::pair<Node &, int>{tree,children.size() - 1};
    }
    return findChildInTree(children[children.size()-1],num);
}

Node GenProg::findAndReplace(const Node &tree,int num,int depth){
    Node modifiedTree = tree;
    std::vector<Node> children = tree.getChildren();
    for (int i=0;i<children.size();i++){
        if (children[i].getNodeNum()==num){
            children.erase(children.begin()+i);
            children.insert(children.begin()+i,recFull(depth,tree.getFunc())[0]);
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

const int GenProg::getRnd(int from, int to){
    return from + std::rand() % (to - from); // to + from
}

Node GenProg::crtGrowTree(){
    if (getRnd(0,100)>75){
        int index = getRnd(0,terminals.size());
        return Node(terminals[index]);
    }
    int index = getRnd(0,function.size());
    return Node(function[index],recGrow(1,function[index]));
}

const std::vector<Node> GenProg::recGrow(const int depth, Func func){
    int child = getRnd( func.getMin(), func.getMax()+1);
    std::vector<Node> children = std::vector<Node>{};
    if (depth == maxTreeHeight ){
        for (unsigned i = 0; i<child;i++){
            int index = getRnd(0, terminals.size());
            children.push_back( Node( terminals[index] ) );
        }
        return children;
    }
    int termChance = 35;
    for (unsigned i = 0; i< child; i++){
        if (getRnd(0,100)<=termChance){
            int index = getRnd(0, terminals.size());
            children.push_back( Node( terminals[index] ) );
        }
        else{
            int index = getRnd(0,function.size());
            Node newNode = Node( function[index], recGrow( depth+1, function[index] ) );
            children.push_back(newNode);
        }
    }
    return children;
}


Node GenProg::crtFullTree(){
    int index = getRnd(0,function.size());
    return Node(function[index],recFull(2,function[index]));
}


const std::vector<Node> GenProg::recFull(const int depth,Func func){
    int child = getRnd( func.getMin(), func.getMax()+1);
    std::vector<Node> children = std::vector<Node>{};
    if (depth >= maxTreeHeight ){
        for (unsigned i = 0; i<child;i++){
            int index = getRnd(0, terminals.size());
            children.push_back( Node( terminals[index] ) );
        }
        return children;
    }
    for (unsigned i = 0; i< child; i++){
        int index = getRnd(0,function.size());
        Node newNode = Node( function[index], recFull( depth+1, function[index]) );
        children.push_back(newNode);
    }
    return children;
}


Node GenProg::getRandomIndividual() {
    double rnd = (double) (rand()) / (double) (RAND_MAX);
    for (unsigned i =0;i<gen.size();i++){
        if (gen[i].getValue()>rnd){
            return gen[i];
        }
    }
    return gen[gen.size()-1];
}


void GenProg::performMutation(std::vector<Node> &actualGeneration){
    Node firstIndividual = getRandomIndividual();
    actualGeneration.push_back(mutate(firstIndividual));
}

void GenProg::performCrossover(std::vector<Node> &actualGeneration) {
    Node firstIndividual = getRandomIndividual();
    Node secondIndividual = getRandomIndividual();
    std::pair<Node, Node> crossoverRes = crossover(firstIndividual,secondIndividual);
    actualGeneration.push_back(crossoverRes.first);
    actualGeneration.push_back(crossoverRes.second);

}



/*
double GenProg::fitFunc(const Node &root) {
    double res = 0.0;
    for (int i =0 ; i < values.size();i++){
        values[i];
        double e = evaluateTree(root, values[i]);
        res += fabs(e - sqrt(values[i]));
    }

    return res/values.size();
}

double GenProg::evaluateTree(const Node &child, double val) {
    auto f = child.getFunc();
    if (child.isTerm){
        return val;
    }
    return (f.getFunc()(child.getChildren(),val));
}

double GenProg::plus(const std::vector<Node> &children,double val) {
    double res =0.0;
    for (int i = 0;i<children.size();i++){
        res+=evaluateTree(children[i],val);
    }
    return res;
}

double GenProg::minus(const std::vector<Node> &children,double val) {
    if (children.size()==1){
        return -evaluateTree(children[0],val);
    }
    return evaluateTree(children[0],val)-evaluateTree(children[1],val);
}

double GenProg::multiply(const std::vector<Node> &children,double val) {
    return evaluateTree(children[0],val)*evaluateTree(children[1],val);
}


double GenProg::divide(const std::vector<Node> &children,double val) {
    if (evaluateTree(children[1], val) == 0) {
        return 1;
    }
    return evaluateTree(children[0],val)/evaluateTree(children[1],val);
}
*/