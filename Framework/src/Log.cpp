#include "Log.h"



Log::Log(){



}


void Log::addGeneration(const std::vector<Node> &newGen){
    this->generations.push_back(newGen);

}