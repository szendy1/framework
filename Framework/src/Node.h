//
// Created by Alexander on 24.01.2017.
//

#ifndef FRAMEWORK_NODE_H
#define FRAMEWORK_NODE_H


#include <string>
#include <vector>
#include <functional>
#include "Func.h"


class Node {

    std::string data;
    Func func;

    std::string infix();

    int numNodes;
    int myNum;

    double value;

    std::vector<Node> children;

public:
    bool isTerm = false;
    Node(const std::string &data);
    Node(const Func &func);

    Node(const Func &data, const std::vector<Node> &nodes);

    Node(const Node &node) = default;
    Node(Node &&node) = default;

    Node& operator=(const Node&) = default;
    Node &operator=(Node &&node) = default;

    const std::string &getData() const;
    const Func &getFunc() const;

    const std::vector<Node> &getChildren() const;
    std::vector<Node> &getMutableChildren();

    int enumerate(int num);

    int height();
    std::string toString();
    void addChild(const Node &child);
    void setChildren(const std::vector<Node> &child);

    const double getValue() const;
    void setValue(const double &val);

    const int getLineageSize() const;
    const int getNodeNum() const;
    void resetNodeNum();


    void draw();
    void draw(int level);
    bool operator < (const Node& str) const
    {
        return (value > str.value);
    }

};


#endif //FRAMEWORK_NODE_H