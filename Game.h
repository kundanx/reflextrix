#ifndef GAME_H
#define GAME_H

#include<iostream>
#include<fstream>           //c++ standar library for file handeling
#include<vector>
#include<ctime>
#include<sstream>           //c++ standard library to create long strings with mixed data type

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
#include<SFML/Network.hpp>

/*  
    class acts a game engine
*/

class Game{
    private:
    // private variables
    //window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;

    // Resources
    sf::Font fonts; 

    // Texts
    sf::Text gameTitleText;
    sf::Text startText;
    sf::Text exitText;
    sf::Text retryText;
    sf::Text scoreText;
    sf::Text healthText; 
    sf::Text highscoreText;
    sf::Text resultScoreText;
    sf::Text resultHighscoreText;
    sf::Text gameOverText;
    
    
    // Mouse position
    sf::Vector2i MousePosWindow;
    sf::Vector2f MousePosView;

    // Game objects
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;

    // Game logic
    unsigned points;
    int health;
    int highscore;
    float enemySpawnTimer;
    float enemySpwanTimerMax;
    int maxEnemies;
    bool mouseHeld;
    int windowControl;
    float dropSpeed;


    // private functions
    void initVariables();
    void initEnemy();
    void initWindow();
    void getMousePosWindow();
    void displayStats();
    void initFonts();         //get fonts from the library
    void initTexts();         //set fonts, size and color of our texts
    void initFile();
    

    public:
    //  constructors / destructors
    Game();
    virtual ~Game();
    
    // Accessors
    const bool running() const;
    int getHealth();

    //functions
    void spawnEnemies();
    void pollEvents();

    void updateWindowControl();

    void updateText();
    void updateEnemies();
    void update();

    void renderText(sf::RenderTarget& target);
    void renderEnemies(sf::RenderTarget& target);
    void render();


};

#endif