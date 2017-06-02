#ifndef FRAMEWORK_NODE_H
#define FRAMEWORK_NODE_H


#include <string>
#include <vector>
#include <functional>
#include <sstream>
#include "Func.h"


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


#include "Node.inl"

#endif //FRAMEWORK_NODE_H

