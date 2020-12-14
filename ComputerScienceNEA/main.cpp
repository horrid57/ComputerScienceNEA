#include <SFML/Graphics.hpp>
#include "Components.h"
#include "guiElements.h"
#include <iostream>

void gameScreen(sf::RenderWindow& window) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            window.clear();

            window.display();
        }
    }
}

void gameMenu(sf::RenderWindow& window) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        difficultySlider.draw(window);
        menu.draw(window);
        className.draw(window);
        customisationTitle.draw(window);
        difficultyLabel.draw(window);
        lengthLabel.draw(window);
        timerLabel.draw(window);
        gameStart.draw(window);


        if (menu.isPressed(window)) {
            return;
        }
        if (gameStart.isPressed(window)) {
            gameScreen(window);
        }

        window.display();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            return;
        }
    }
}

void settingsMenu(sf::RenderWindow& window) {

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();


        window.display();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            return;
        }
    }
}

int main()
{

    window.setFramerateLimit(144);

    buttonOffTexture.loadFromFile("blue.jpg");
    defaultTexture.loadFromFile("blue.jpg");
    buttonOnTexture.loadFromFile("green.png");
    arialRounded.loadFromFile("ARLRDBD.ttf");

    mainStartButton = Button(window, buttonOffTexture, buttonOnTexture, false, "START", arialRounded, 0.334, 0.267, 0.313, 0.206);
    tutorialButton = Button(window, buttonOffTexture, buttonOnTexture, false, "Tutorial", arialRounded, 0.378, 0.514, 0.227, 0.104);
    settingsButton = Button(window, buttonOffTexture, buttonOnTexture, false, "Settings", arialRounded, 0.377, 0.659, 0.227, 0.087);
    exitButton = Button(window, buttonOffTexture, buttonOnTexture, false, "Exit", arialRounded, 0.021, 0.877, 0.123, 0.095);

    difficultySlider = Slider(window, buttonOnTexture, buttonOffTexture, 0.4, 0.3026, 0.591, 0.1577);
    menu = Button(window, buttonOffTexture, buttonOnTexture, false, "Menu", arialRounded, 0.0129, 0.0211, 0.1026, 0.0795);
    className = Label(window, defaultTexture, "[class name]", arialRounded, 0.1143, 0.2304, 0.1955, 0.0830);
    customisationTitle = Label(window, defaultTexture, "Customise", arialRounded, 0.3688, 0.0152, 0.2323, 0.1111);
    difficultyLabel = Label(window, defaultTexture, "Game Difficulty", arialRounded, 0.4935, 0.1988, 0.2016, 0.0807);
    lengthLabel = Label(window, defaultTexture, "Game Length", arialRounded, 0.4935, 0.5216, 0.161, 0.0561);
    timerLabel = Label(window, defaultTexture, "Timer", arialRounded, 0.4935, 0.7462, 0.1063, 0.0667);
    gameStart = Button(window, buttonOffTexture, buttonOnTexture, false, "START", arialRounded, 0.7566, 0.8117, 0.2164, 0.1415);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        mainStartButton.draw(window);
        tutorialButton.draw(window);
        settingsButton.draw(window);
        exitButton.draw(window);
        if (mainStartButton.isPressed(window)) {
            //button.toggleState();
            mainStartButton.updateTexture();
            gameMenu(window);
        }
        else if (settingsButton.isPressed(window)) {
            settingsMenu(window);
        }
        else if (exitButton.isPressed(window)) {
            return 1;
        }


        window.display();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            return 0;
        }
    }

    return 0;
}
