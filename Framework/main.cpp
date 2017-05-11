#include <iostream>


#include "src/Node.h"

#include "src/GenProg.h"

int mainLib() {
    std::cout << "Hello, World!" << std::endl;

    GenProg<double> c;
    c.perform();


    return 0;
}




//GnuPLOt - vykreslovanie grafov
//
/*
 * GenProg genprog;

genprog.perform();

genprog.log.generations[1].population[3].draw();
genprog.log.generations[1].population[3].save("tree.svg");
*/
// Knizica pre kreslenie: cairo
