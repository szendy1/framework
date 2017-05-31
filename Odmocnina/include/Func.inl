
template<typename T>
Func<T>::Func(const std::function<T(const std::vector<Node<T> > &, std::vector<T>)> &f, int minArity, int maxArity,
              const std::string &r)
        : func(f), minArity(minArity), maxArity(maxArity), repr(r) {}

template<typename T>
const std::function<T(const std::vector<Node<T> > &, std::vector<T>)> &Func<T>::getFunc() { return this->func; }

template<typename T>
const int Func<T>::getMinArity() const { return this->minArity; }

template<typename T>
const int Func<T>::getMaxArity() const { return this->maxArity; }

template<typename T>
const std::string &Func<T>::getRepr() const { return this->repr; }