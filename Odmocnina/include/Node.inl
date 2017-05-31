
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
