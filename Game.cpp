#include "Game.h"

/* private functions */
void Game:: initVariables(){
    this->window = nullptr;
    this->points = 0;
    this->health = 10;
    this->enemySpwanTimerMax = 50.f;
    this->enemySpawnTimer = this-> enemySpwanTimerMax; 
    this->maxEnemies = 100;
    this->mouseHeld = false;
    this->windowControl =0;
    this->dropSpeed =3;
}

void Game:: initWindow(){
    this->videoMode.height = 760;
    this->videoMode.width = 1380;
    this->window = new sf:: RenderWindow(this->videoMode,"Reflextrix", sf:: Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initEnemy(){
    this->enemy.setPosition(200.f,200.f);
    this->enemy.setSize(sf::Vector2f(100.f,100.f));
    this->enemy.setScale(sf::Vector2f(0.5f,0.5f));
    this->enemy.setFillColor(sf::Color::Blue);
    // this->enemy.setOutlineThickness(1.f);
    // this->enemy.setOutlineColor(sf::Color::Magenta);

}

void Game::initFonts(){
    if(!this->fonts.loadFromFile("fonts/ka1.ttf")){
        std::cout<<"ERROR::GAME::INTIFONTS::failed to initialize fonts"<<"\n";
    }
}

void Game::initTexts(){
    this->scoreText.setFont(this->fonts);
    this->scoreText.setCharacterSize(16);
    this->scoreText.setFillColor(sf::Color::Green);       //points
    this->scoreText.setString("NONE");
    this->scoreText.setPosition(10.f,30.f);
    
    this->healthText.setFont(this->fonts);
    this->healthText.setCharacterSize(16);
    this->healthText.setFillColor(sf::Color::Red);        //health
    this->healthText.setString("NONE");
    this->healthText.setPosition(10.f,50.f);

    this->highscoreText.setFont(this->fonts);
    this->highscoreText.setCharacterSize(16);
    this->highscoreText.setFillColor(sf::Color::Cyan);   //highscore
    this->highscoreText.setString("NONE");
    this->highscoreText.setPosition(10.f,10.f);
    
    this->gameTitleText.setFont(this->fonts);
    this->gameTitleText.setCharacterSize(100);
    this->gameTitleText.setFillColor(sf::Color::Blue);  //game title
    this->gameTitleText.setString("REFLEXTRIX");
    this->gameTitleText.setPosition(300.f, 170.f);

    this->gameOverText.setFont(this->fonts);
    this->gameOverText.setCharacterSize(100);
    this->gameOverText.setFillColor(sf::Color::Cyan);   //game over
    this->gameOverText.setString("GAME OVER");
    this->gameOverText.setPosition(300.f,170.f);

    this->startText.setFont(this->fonts);
    this->startText.setCharacterSize(32);
    this->startText.setFillColor(sf::Color::Green);     //start
    this->startText.setString("Start");
    this->startText.setPosition(420.f,400.f);

    this->exitText.setFont(this->fonts);
    this->exitText.setCharacterSize(32);
    this->exitText.setFillColor(sf::Color::Yellow);     //exit
    this->exitText.setString("Exit");
    this->exitText.setPosition(880.f,400.f);

    this->retryText.setFont(this->fonts);
    this->retryText.setCharacterSize(32);
    this->retryText.setFillColor(sf::Color::Green);     //retry
    this->retryText.setString("Retry");
    this->retryText.setPosition(420.f,400.f);

    this->resultScoreText.setFont(this->fonts);
    this->resultScoreText.setCharacterSize(24);
    this->resultScoreText.setFillColor(sf::Color::Black);     //result my score display
    this->resultScoreText.setString("NONE");
    this->resultScoreText.setPosition(500.f,340.f);

    this->resultHighscoreText.setFont(this->fonts);
    this->resultHighscoreText.setCharacterSize(24);
    this->resultHighscoreText.setFillColor(sf::Color::Black);     //result highscore display
    this->resultHighscoreText.setString("NONE");
    this->resultHighscoreText.setPosition(500.f,300.f);
    
}

void Game::initFile(){
    std::ifstream gameFile;
    gameFile.open("highscore.txt",std::ios::out);
    gameFile>>this->highscore;
    gameFile.close();
}

void Game:: getMousePosWindow(){
    /*
       @return void
       gets postion of mouse and stores in vector2i obj
        -mouse postion realtive to window
    */
    this->MousePosWindow = sf::Mouse::getPosition(*this->window);
    this->MousePosView = (this->window->mapPixelToCoords(this->MousePosWindow));
   
}

/* constuctors / distructors */ 
Game:: Game(){
    this->initVariables();
    this->initWindow();
    this->initEnemy();
    this->initFonts();
    this->initTexts();
    this->initFile();

}

Game:: ~Game(){
    delete this->window;

}

/* Accessor */
const bool Game::running() const {
    return this->window->isOpen();
}

int Game:: getHealth(){
    return this->health;
}

/* public functions */
void Game::spawnEnemies(){
    /*
        @return void

        Spwans enimies and sets their positon and color
        -sets a random postion
        -sets a random color
        -adds number of enemies to the vector
    */

   this->enemy.setPosition(
      static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
      0.f
    );

   //this->enemy.setFillColor(sf::Color::Green);
   // Spawn the enemy
   this->enemies.push_back(this->enemy);
}

// #event polling:: recieve event form the window and store in Event obj ev
void Game::pollEvents(){
        
        while(this->window->pollEvent(this->ev))
        {
          switch(this->ev.type)
          {
            case sf::Event::Closed:
            
               this-> window->close();
                break;
    
            case sf::Event::KeyPressed:

                if(this->ev.key.code == sf::Keyboard::Escape)
                this->window->close();
                break;
          }

        }
}

void Game::displayStats(){
    std::cout<<"POINTS: "<<this->points<<"\t"<<"HEALTH: "<<this->health<<std::endl;
}

//control display screen: welcome screen, gamePlay screen and gameOver screen
void Game::updateWindowControl(){
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    { 

        if(this->windowControl == 0){
           if(this->startText.getGlobalBounds().contains(this->MousePosView)){
                this->windowControl =1;
                this->health = 10;
                return;
           }
           else if(this->exitText.getGlobalBounds().contains(this->MousePosView)){
               this->windowControl = 0;
               this->window->close();
               return;
           }

        }
        else if(this->windowControl == 2){
            if(this->retryText.getGlobalBounds().contains(this->MousePosView))
            {
                this->windowControl =1;
                this->health = 10;
                this->points = 00;
                this->initFile();
                this->enemies.clear();
                return;
            }
            else if(this->exitText.getGlobalBounds().contains(this->MousePosView))
            {
                this->windowControl = 0;
                this->window->close();
                return;
            }

        }
        
    }


}

void Game::updateText(){

    std::stringstream  hs,st,ht,rs;

    hs<<"High score: "<<this->highscore<<std::endl;
    this->highscoreText.setString(hs.str());
    this->resultHighscoreText.setString(hs.str());

    if(this->windowControl == 1){

        st << "Points: "<< this->points<<std::endl;
       this->scoreText.setString(st.str());
     
       rs<<"Scored: "<< this->points<<std::endl;
       this->resultScoreText.setString(rs.str());
       
       ht<<"Health: "<<this->health<<std::endl;
       this->healthText.setString(ht.str());
    }
    
}

void Game::updateEnemies(){
     /*  
        @return void

        update timers and spawn enimies when timer reaches max limit and reset the timer
         -update the timer and spwan the enemy adter max timer limit
         -moves the enemy downwards
         -removes the enemy after reaching bottom of the screen

    */
    if(this->enemies.size() < this->maxEnemies){
       if(this->enemySpawnTimer >= this->enemySpwanTimerMax){
          this->spawnEnemies();
          this->enemySpawnTimer = 0.f;
       }
       else{
          this->enemySpawnTimer += 1.f;
       }
    }
   

    for(int i = 0; i< this->enemies.size();i++){

        enemies[i].move(0.f,this->dropSpeed);

        if(this->enemies[i].getPosition().y > this->window->getSize().y){
            this->enemies.erase(this->enemies.begin() + i); 
            this->health -= 1;

            //updates the window to gameOver screen when health finishes
            if(this->health <= 0){

              this->windowControl = 2;  

              if(this->points >= this->highscore)  {
                  std:: ofstream gameFile("highscore.txt",std::ios::trunc);
                  gameFile<<this->points;
                  gameFile.close();
              } 
            }
        }
    }

    //check mouse click
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){


        if(this->mouseHeld == false){

            this->mouseHeld = true;
        
            bool kill = false;

            for(size_t i = 0; i < this->enemies.size() && kill == false; i++){

        
                if(this->enemies[i].getGlobalBounds().contains(this->MousePosView)){
                    
               
                    // Kill the enemy
                    kill = true;
                    this->enemies.erase(this->enemies.begin() + i); 
                    
                    // add points
                    this->points += 10;
                    if(this->points > this->highscore){
                        this->highscore = this->points;
                    }
                }     
            }
        }
    }
    else{
        this->mouseHeld = false;
    } 

    //change speeed after some time

    if( this->points == 200){
       this->dropSpeed = 4;
    } 
    else if(this->points == 400){
        this->dropSpeed = 5;
    }
     else if(this->points == 600){
        this->dropSpeed = 6;
    } 
     else if(this->points == 800){
        this->dropSpeed = 7;
    } 
    else if(this->points == 1000){
        this->dropSpeed = 8;
    }  
     else if(this->points == 1200){
        this->dropSpeed =9;
    }      
    else if(this->points == 1500){
        this->dropSpeed = 10;
    }
    else{
        return;
    }
}

void Game:: update(){

    this->pollEvents();

    this->getMousePosWindow();

    this->updateWindowControl();
    
    if(this->windowControl == 1){

       this->updateEnemies();
    }

    this->updateText();

    //this->displayStats();

}



void Game::renderText(sf::RenderTarget& target){
    if(this->windowControl == 1){
        target.draw(this->scoreText);
        target.draw(this->highscoreText);
        target.draw(this->healthText);
    }
    else if(this->windowControl == 0){
        target.draw(this->gameTitleText);
        target.draw(this->startText);
        target.draw(this->exitText);

    }
    else if(this->windowControl == 2){
        target.draw(this->gameOverText);
        target.draw(this->resultScoreText);
        target.draw(this->resultHighscoreText);
        target.draw(this->retryText);
        target.draw(this->exitText);

    }

}

void Game::renderEnemies(sf::RenderTarget& target){

    //rendering enemies
     for( auto &e: this->enemies){
       target.draw(e);
    }

}

void Game:: render(){
    /* 
       @return void
       - clear old frame
       - Render new objects
       - Display frame in window

       render the game objects
    */
    
    this->window->clear(sf::Color::White);

    if(this->windowControl != 0) {

       this->renderEnemies(*this->window);
    }

    this->renderText(*this->window);

    this->window->display();
}