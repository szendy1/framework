//
// Created by Alexander on 24.01.2017.
//

#include "Node.h"
#include <sstream>
#include <iostream>


Node::Node(const std::string &data)
        : data(data), isTerm(true)
{
    myNum= 0;
    numNodes=0;
    value= 0.0;
}

Node::Node(const Func &func)
        : func(func), isTerm(false)
{
    myNum= 0;
    numNodes=0;
    value= 0.0;
}

Node::Node(const Func &data, const std::vector<Node> &children)
        : func(data), children(children), isTerm(false)
{
    myNum= 0;
    numNodes=0;
    value= 0.0;
}

//Node::Node(Node &&node)
//        : data(std::move(node.data)),
//          children(std::move(node.children)),
//          isTerm(node.isTerm),
//          numNodes(node.numNodes),
//          myNum(node.myNum)
//{
//    node.isTerm=false;
//    node.numNodes=0;
//    node.myNum=0;
//}

//Node& Node::operator=(Node &&node)
//{
//    data=std::move(node.data);
//    children=std::move(node.children);
//    isTerm=node.isTerm;
//    numNodes=node.numNodes;
//    myNum=node.myNum;
//    node.isTerm=false;
//    node.numNodes=0;
//    node.myNum=0;
//}



void Node::addChild(const Node &child){  this->children.push_back(child); }

void Node::setChildren(const std::vector<Node> &child){  children = child; }

const std::vector<Node> &Node::getChildren() const {  return this->children; }

std::vector<Node> &Node::getMutableChildren() {  return this->children; }

const std::string &Node::getData() const{ return this->data; }

const Func &Node::getFunc() const{ return this->func; }

void Node::setValue(const double &val) { this->value=val; }

const double Node::getValue() const{ return this->value; }

const int Node::getLineageSize() const{ return this->numNodes; }

const int Node::getNodeNum() const{ return this->myNum; }

void Node::resetNodeNum() { this->myNum=0; this->numNodes=0;}


int Node::height(){
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


std::string Node::toString(){
    return infix();
}

std::string Node::infix(){
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

int Node::enumerate(int num) {
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

