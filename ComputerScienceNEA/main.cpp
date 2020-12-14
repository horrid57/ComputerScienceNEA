#include <SFML/Graphics.hpp>
#include "Components.h"
#include <iostream>

void gameMenu(sf::RenderWindow& window) {
    sf::Texture buttonOffTexture;
    buttonOffTexture.loadFromFile("blue.jpg");
    sf::Texture buttonOnTexture;
    buttonOnTexture.loadFromFile("green.png");
    sf::Font arialRounded;
    arialRounded.loadFromFile("ARLRDBD.ttf");

    Button button = Button(window, buttonOffTexture, buttonOnTexture, false, "Cooler Button", arialRounded, 10, 10, 200, 50);
    slider difficultySlider = slider(window, buttonOnTexture, buttonOffTexture, 0.4, 0.3026, 0.591, 0.1577);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        difficultySlider.draw(window);
        button.draw(window);
        if (button.isPressed(window)) {
            return;
            //button.toggleState();
            button.updateTexture();
        }


        window.display();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            return;
        }
    }
}

void settingsMenu(sf::RenderWindow& window) {
    sf::Texture buttonOffTexture;
    buttonOffTexture.loadFromFile("blue.jpg");
    sf::Texture buttonOnTexture;
    buttonOnTexture.loadFromFile("green.png");
    sf::Font arialRounded;
    arialRounded.loadFromFile("ARLRDBD.ttf");

    Button button = Button(window, buttonOffTexture, buttonOnTexture, false, "Super Duper Uncool Button", arialRounded, 10, 10, 200, 50);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        button.draw(window);
        if (button.isPressed(window)) {
            return;
            //button.toggleState();
            button.updateTexture();
        }


        window.display();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            return;
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    window.setFramerateLimit(144);

    sf::Texture buttonOffTexture;
    buttonOffTexture.loadFromFile("blue.jpg");
    sf::Texture buttonOnTexture;
    buttonOnTexture.loadFromFile("green.png");
    sf::Font arialRounded;
    arialRounded.loadFromFile("ARLRDBD.ttf");

    Button startButton = Button(window, buttonOffTexture, buttonOnTexture, false, "START", arialRounded, 0.334, 0.267, 0.313, 0.206);
    Button tutorialButton = Button(window, buttonOffTexture, buttonOnTexture, false, "Tutorial", arialRounded, 0.378, 0.514, 0.227, 0.104);
    Button settingsButton = Button(window, buttonOffTexture, buttonOnTexture, false, "Settings", arialRounded, 0.377, 0.659, 0.227, 0.087);
    Button exitButton = Button(window, buttonOffTexture, buttonOnTexture, false, "Exit", arialRounded, 0.021, 0.877, 0.123, 0.095);



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        startButton.draw(window);
        tutorialButton.draw(window);
        settingsButton.draw(window);
        exitButton.draw(window);
        if (startButton.isPressed(window)) {
            //button.toggleState();
            startButton.updateTexture();
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
