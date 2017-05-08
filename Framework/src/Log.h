#ifndef FRAMEWORK_LOG_H
#define FRAMEWORK_LOG_H


#include "Node.h"

class Log {

public:
    std::vector<std::vector<Node>> generations;
    Log();
    void Load();
    void Load(const std::string &path);
    void addGeneration(const std::vector<Node> &newGen);

};


#endif //FRAMEWORK_LOG_H
