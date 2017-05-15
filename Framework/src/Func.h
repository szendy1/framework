#ifndef FRAMEWORK_FUNC_H
#define FRAMEWORK_FUNC_H


#include <functional>
#include <vector>

template <typename T > class Node;

template < typename T > class Func {
    std::function< T (const std::vector< Node<T> > &, std::vector< T > ) > func;
    int minArity;
    int maxArity;
    std::string repr;
public:
    Func(const std::function< T (const std::vector< Node<T> > &, std::vector< T > ) > &f, int minArity, int maxArity, const std::string &r);
    const std::function< T (const std::vector< Node<T> > &, std::vector< T > ) > &getFunc(){ return this->func; };
    const int getMinArity() const { return this->minArity; };
    const int getMaxArity() const { return this->maxArity; };
    const std::string &getRepr() const{ return this->repr; };

//    Func(const Func &func) = default;
//    Func(Func &&func) = default;
//    Func& operator=(const Func&) = default;
//    Func &operator=(Func &&func) = default;

};


template <typename T> Func<T>::Func(const std::function< T (const std::vector< Node<T> > &,std::vector<T>)> &f, int minArity, int maxArity, const std::string &r)
        : func(f), minArity(minArity), maxArity(maxArity), repr(r)
{}

template class Func<double>;

#endif //FRAMEWORK_FUNC_H