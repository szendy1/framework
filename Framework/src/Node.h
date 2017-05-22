#ifndef FRAMEWORK_NODE_H
#define FRAMEWORK_NODE_H


#include <string>
#include <vector>
#include <functional>
#include <sstream>
#include "Func.h"


template <typename T> class Node {
private:
    std::string data;
    Func<T> func;

    std::string infix();

    int numNodes;
    int myNum;

    double fitness;

    std::vector<Node<T>> children;

    bool isTerm;
public:
    Node(const Func<T> &func,bool term);

    Node(const Func<T> &data, const std::vector<Node> &nodes);

    Node(const Node<T> &node) = default;
    Node(Node<T> &&node) = default;

    Node& operator=(const Node<T> &) = default;
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
    void setFitness(const double &fit);

    const int getLineageSize() const;
    const int getNodeNum() const;
    void resetNodeNum();

    const bool isTerminal() const {return this->isTerm;};

    bool operator < (const Node& other) const
    {
        return (this->fitness > other.fitness);
    }

};


template <typename T > Node<T>::Node(const Func<T> &func,bool term)
        : func(func), isTerm(term)
{
    myNum= 0;
    numNodes=0;
    fitness= 0.0;
}

template <typename T > Node<T>::Node(const Func<T> &data, const std::vector<Node<T> > &children)
        : func(data), children(children), isTerm(false)
{
    myNum= 0;
    numNodes=0;
    fitness= 0.0;
}

template <typename T > void Node<T>::addChild(const Node<T> &child){  this->children.push_back(child); }

template <typename T > void Node<T>::setChildren(const std::vector<Node<T> > &child){  children = child; }

template <typename T > const std::vector<Node<T>> &Node<T>::getChildren() const {  return this->children; }

template <typename T > std::vector<Node<T>> &Node<T>::getMutableChildren() {  return this->children; }

template <typename T > const std::string &Node<T>::getData() const{ return func.getRepr(); }

template <typename T > const Func<T> &Node<T>::getFunc() const{ return this->func; }

template <typename T > void Node<T>::setFitness(const double &fit) { this->fitness=fit; }

template <typename T > const double Node<T>::getFitness() const{ return this->fitness; }

template <typename T > const int Node<T>::getLineageSize() const{ return this->numNodes; }

template <typename T > const int Node<T>::getNodeNum() const{ return this->myNum; }

template <typename T > void Node<T>::resetNodeNum() { this->myNum=0; this->numNodes=0;}


template <typename T > const int Node<T>::height() const {
    if (isTerm){
        return 1;
    }
    int highest=0;
    for (int i = 0;i<children.size();i++){
        int thisHeight = children[i].height();
        if (highest<thisHeight){
            highest=thisHeight;
        }
    }
    return highest+1;
}


template <typename T > std::string Node<T>::toString(){
    return infix();
}

template <typename T > std::string Node<T>::infix(){
    if (isTerm) {
        return data;
    }
    std::stringstream ss;
    ss<< data;
    for (int i = 0; i < children.size(); i++) {
        ss << children[i].infix() << " " ;
    }
    return ss.str();

}

template <typename T > int Node<T>::enumerate(int num) {
    this->myNum=num;
    if (this->isTerm){
        return num;
    }
    for (int i=0;i<this->children.size();i++){
        num=this->children[i].enumerate(num+1);
    }
    this->numNodes = num - myNum;
    return num;
}

template class Node<double>;

#endif //FRAMEWORK_NODE_H