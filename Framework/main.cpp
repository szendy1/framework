#include <iostream>


#include "src/Node.h"

#include "src/GenProg.h"

int mainLib() {
    std::cout << "Hello, World!" << std::endl;

    GenProg<double> c;
    c.perform();
/*
    std::cout << c.log.generations[0][0].toString() << std::endl;

    std::cout << c.log.generations[0][0].height() << std::endl;
    std::cout << c.log.generations[0][0].getChildren().size() << std::endl;

    for (int i=0;i<c.log.generations[0][0].getChildren().size();i++){
        std::cout << c.log.generations[0][0].getChildren()[i].getChildren().size() << std::endl;

        std::cout << "Je Term: " <<  c.log.generations[0][0].getChildren()[i].isTerm << std::endl;

        std::cout << "Data "<< c.log.generations[0][0].getChildren()[i].getData() << std::endl;

    }
    if (c.log.generations[0][0].getChildren().size()>0 && c.log.generations[0][0].getChildren()[0].getChildren().size()>0)
        for (int i=0;i<c.log.generations[0][0].getChildren()[0].getChildren().size();i++){
            std::cout << c.log.generations[0][0].getChildren()[0].getChildren()[i].getChildren().size() << std::endl;

            std::cout << "Je Term: " <<  c.log.generations[0][0].getChildren()[0].getChildren()[i].isTerm << std::endl;

            std::cout << "Data "<< c.log.generations[0][0].getChildren()[0].getChildren()[i].getData() << std::endl;

        }

    //std::cout << c.log.generations[0][0].enumerate(0);

*/

    //c.log.addGeneration(std::vector<Node> {tree});

  //  tree.enumerate(1);




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



/*
 *
 * 9
 *
 *
 *
 *
 *
 */

