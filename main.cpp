
#include "Game.h"

//using namespace sf

int main(){
    //init Srand
    std::srand(static_cast<unsigned>(time(NULL)));
     /*  
        #Game engine
        -initializes as default with constructor
        -initializes variable of class game
        -initializes our game window
        -initializes our enemy objects
      
     */
     Game game;

    //game loop
    while(game.running())
    {
        /* 
            #Update
            -Poll events
            -get position of mouse in our  window
            -update enemy
        */

        game.update();
        
        /* 
           #Render
           -render and display 
        */
        game.render();
       
    }


    //end of application
    return 0;

}