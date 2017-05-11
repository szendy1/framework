
#ifndef FRAMEWORK_GENPROG_H
#define FRAMEWORK_GENPROG_H

#include <string>
#include <vector>

//int mainLib();

class Node;
class Func;


class Log {

public:
    std::vector<std::vector<Node>> generations;
    Log();
    void Load();
    void Load(const std::string &path);
    void addGeneration(const std::vector<Node> &newGen);

};

template <typename values_t> class GenProg {
public:
    std::vector<Node> gen;
    int populationSize;
    int generations;

    std::vector<Func> functions;
    std::vector<std::string> terminals;

    double chanceFullTree;

    double mutationChance;
    double crossoverChance;

    int maxTreeHeight;

    Log log;
private:


    const int getRnd(int from, int to);
    Node crtFullTree();
    Node crtGrowTree();
    const std::vector<Node> recGrow(const int depth, const Func &func);
    const std::vector<Node> recFull(const int depth, const Func &func);

    void performMutation(std::vector<Node> &actualGeneration);
    Node mutate(const Node &tree);
    Node findAndReplace(const Node &tree,int num,int depth);

    void performCrossover(std::vector<Node> &actualGeneration);
    std::pair<Node, Node> crossover(const Node &tree1, const Node &tree2);
    std::pair<Node &,int> findChildInTree(Node &tree, int num);
    Node getRandomIndividual();


public:
    GenProg();
    void perform();
    void Initialization();
    void Evaluation();
    void Vary();
    void FeedNewGeneration();

    void addfunction(const Func &func);

    virtual double fitFunc(const Node &root) { return 0.0; };

};

class Func {
    std::function<double(const std::vector<Node> &,double)> func;
    int minChild;
    int maxChild;
    std::string repr;
public:
    Func(const std::function<double(const std::vector<Node> &,double)> &f, int minCh, int maxCh, const std::string &r);
    Func();
    const std::function<double(const std::vector<Node> &,double)> getFunc();
    const int getMin() const;
    const int getMax() const;
    const std::string getRepr();

//    Func(const Func &func) = default;
//    Func(Func &&func) = default;
//    Func& operator=(const Func&) = default;
//    Func &operator=(Func &&func) = default;

};

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
#endif //FRAMEWORK_GENPROG_H
