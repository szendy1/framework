
#ifndef FRAMEWORK_GENPROG_H
#define FRAMEWORK_GENPROG_H

#include <string>
#include <vector>
#include <random>
#include <functional>

template <typename T> class Node;
template <typename T> class Func;
template <typename T> class Log;

template <typename T > class GenProg {
private:
    std::random_device  rd; // obtain a random number from hardware
    std::mt19937        mt; // seed the generator

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
    std::vector< Node<T> > gen;
    int populationSize;
    int generations;

    std::vector< Func<T> > functions;
    std::vector< Func<T> > terminals;

    double chanceFullTree;

    double mutationChance;
    double crossoverChance;

    int maxTreeHeight;

    Log<T> log;

    GenProg();
    void perform();
    void initialize();
    void evaluate();
    void vary();
    void selection();

    void addfunction(const Func<T> &func);

    virtual double fitFunc(const Node<T> &root) { return 0.0; };

};

template < typename T > class Func {
    std::function<T(const std::vector<Node < T> > &, std::vector<T> ) >
    func;
    int minArity;
    int maxArity;
    std::string repr;
public:
    Func(const std::function< T(const std::vector< Node<T> > &, std::vector<T>) > &f, int minArity, int maxArity, const std::string &r );
    const std::function<T(const std::vector< Node<T> > &, std::vector<T> ) > getFunc();

    const int getMinArity() const;

    const int getMaxArity() const;

    const std::string getRepr() const;
};


template <typename T> class Node {

    std::string data;
    Func<T> func;

    std::string infix();

    int numNodes;
    int myNum;

    double value;

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

    int height();
    std::string toString();
    void addChild(const Node &child);
    void setChildren(const std::vector<Node> &child);

    const double getValue() const;
    void setValue(const double &val);

    const int getLineageSize() const;
    const int getNodeNum() const;
    void resetNodeNum();

    const bool isTerminal() const {return this->isTerm;};

    bool operator < (const Node& str) const;

};

template <typename T> class Log {
    std::vector<std::vector<Node<T> > > generations;
public:
    Log();
    void addGeneration(const std::vector<Node<T>> &newGen);
    std::vector<Node<T>> getGeneration(unsigned int index);
    unsigned int getNumberOfGenerations();
};


#endif //FRAMEWORK_GENPROG_H
