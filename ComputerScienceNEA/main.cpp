#include <SFML/Graphics.hpp>
#include "Components.h"
#include "guiElements.h"
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>

bool contains(std::vector<sf::Vector2i>& vector, sf::Vector2i value) {
    for (int i = 0; i < vector.size(); i++) {
        if (vector[i] == value) {
            return true;
        }
    }
    return false;
};

std::vector<Room> generateLevel() {
    std::vector<Room> rooms;
    std::vector<sf::Vector2i> positions = { sf::Vector2i(200, 400) };

    int i = 0;
    int attempts = 0;
    int timesStuck = 0;
    while (i < timerLength) {
        int randInt = rand() % 4;
        sf::Vector2i nextPosition;
        sf::Vector2i lastPosition = positions.back();
        //std::cout << i << " " << randInt << " " << lastPosition.x << " " << lastPosition.y << "\n";
        switch (randInt) {
        case 0:
            nextPosition = sf::Vector2i(lastPosition.x - roomWidth, lastPosition.y);
            if (!contains(positions, nextPosition) &&
                !contains(positions, sf::Vector2i(nextPosition.x - roomWidth, nextPosition.y)) &&
                !contains(positions, sf::Vector2i(nextPosition.x, nextPosition.y + roomHeight)) &&
                !contains(positions, sf::Vector2i(nextPosition.x, nextPosition.y - roomHeight))
                ) {
                positions.push_back(nextPosition);
                i++;
                attempts = 0;
            }
            else {
                attempts++;
            }
            break;
        case 1:
            nextPosition = sf::Vector2i(lastPosition.x, lastPosition.y - roomHeight);
            if (!contains(positions, nextPosition) &&
                !contains(positions, sf::Vector2i(nextPosition.x - roomWidth, nextPosition.y)) &&
                !contains(positions, sf::Vector2i(nextPosition.x + roomWidth, nextPosition.y)) &&
                !contains(positions, sf::Vector2i(nextPosition.x, nextPosition.y - roomHeight))
                ) {
                positions.push_back(nextPosition);
                i++;
                attempts = 0;
            }
            else {
                attempts++;
            }
            break;
        case 2:
            nextPosition = sf::Vector2i(lastPosition.x + roomWidth, lastPosition.y);
            if (!contains(positions, nextPosition) &&
                !contains(positions, sf::Vector2i(nextPosition.x + roomWidth, nextPosition.y)) &&
                !contains(positions, sf::Vector2i(nextPosition.x, nextPosition.y + roomHeight)) &&
                !contains(positions, sf::Vector2i(nextPosition.x, nextPosition.y - roomHeight))
                ) {
                positions.push_back(nextPosition);
                i++;
                attempts = 0;
            }
            else {
                attempts++;
            }
            break;
        case 3:
            nextPosition = sf::Vector2i(lastPosition.x, lastPosition.y + roomHeight);
            if (!contains(positions, nextPosition) &&
                !contains(positions, sf::Vector2i(nextPosition.x - roomWidth, nextPosition.y)) &&
                !contains(positions, sf::Vector2i(nextPosition.x + roomWidth, nextPosition.y)) &&
                !contains(positions, sf::Vector2i(nextPosition.x, nextPosition.y + roomHeight))
                ) {
                positions.push_back(nextPosition);
                i++;
                attempts = 0;
            }
            else {
                attempts++;
            }
            break;
        };
        /* If there are too many attempts made with no progress made it can be assumed that the last room is in a 
        * postion where it cannot progress in any of the three directions without the room being a neighbour to two
        * or more rooms.
        * Removing the last room allows the program to try and place a room that won't get it stuck.
        * 
        * There may be an issue in extreme cases where the program digs itself into a hole where the one it goes back
        * to only has one place it can put a room.
        * 
        * Addition of timesStuck should prevent this from happening completely.
        * 
        */
        if (attempts > 50) {
            timesStuck++;
            std::cout << timesStuck;
            if (timesStuck >= positions.size()) {
                timesStuck = positions.size();
            };
            positions.erase(positions.end() - timesStuck, positions.end() - 1);
        }
    }

    for (int i = 0; i < positions.size(); i++) {
        rooms.push_back(Room(wallTexture, positions[i].x, positions[i].y, roomWidth, roomHeight, wallThickness));
    };

    return rooms;
}

void gameScreen(sf::RenderWindow& window) {
    long initialTime = 0;
    long endTime = 0;
    std::vector<Room> rooms = generateLevel();
    Player player = Player(buttonOffTexture, 300, 500, 50, 50, 200, 5);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            };
        }
        initialTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        window.clear();

        for (int i = 0; i < rooms.size(); i++) {
            rooms[i].draw(window);
        };
        player.move(rooms, (float)timeForLastFrame / 1000000);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
            rooms = generateLevel();
        }

        player.draw(window);

        window.display();
        endTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        timeForLastFrame = endTime - initialTime;
    }
}

void gameMenu() {
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
        timerFive.draw(window);
        timerTen.draw(window);
        timerFifthteen.draw(window);
        timerTwenty.draw(window);
        timerOn.draw(window);
        timerOff.draw(window);
        left.draw(window);
        right.draw(window);
        classImage.draw(window);
        classDescription.draw(window);


        if (menu.isPressed(window)) {
            return;
        }
        if (gameStart.isPressed(window)) {
            std::cout << classNames[playerClass] << ", " << gameDifficulty << ", " << timerEnabled << ", " << timerLength << "\n";
            gameScreen(window);
        }
        difficultySlider.update(window);
        gameDifficulty = difficultySlider.getValue();

        if (left.isPressed(window)) {
            playerClass--;
            if (playerClass < 0) {
                playerClass = classNames.size() - 1;
            };
            className.setText(classNames[playerClass]);
            classDescription.setText(classDescriptions[playerClass]);
            classImage.changeTexture(classImages[playerClass]);
        }
        else if (right.isPressed(window)) {
            playerClass++;
            if (playerClass > classNames.size() - 1) {
                playerClass = 0;
            };
            className.setText(classNames[playerClass]); 
            classDescription.setText(classDescriptions[playerClass]);
            classImage.changeTexture(classImages[playerClass]);
        };

        if (timerFive.isPressed(window)) {
            timerTen.setState(false);
            timerFifthteen.setState(false);
            timerTwenty.setState(false);
            timerTen.updateTexture(buttonOnTexture, buttonOffTexture);
            timerFifthteen.updateTexture(buttonOnTexture, buttonOffTexture);
            timerTwenty.updateTexture(buttonOnTexture, buttonOffTexture);

            timerFive.setState(true);
            timerFive.updateTexture(buttonOnTexture, buttonOffTexture);

            timerLength = 5;
        }
        else if (timerTen.isPressed(window)) {
            timerFive.setState(false);
            timerFifthteen.setState(false);
            timerTwenty.setState(false);
            timerFive.updateTexture(buttonOnTexture, buttonOffTexture);
            timerFifthteen.updateTexture(buttonOnTexture, buttonOffTexture);
            timerTwenty.updateTexture(buttonOnTexture, buttonOffTexture);

            timerTen.setState(true);
            timerTen.updateTexture(buttonOnTexture, buttonOffTexture);

            timerLength = 10;
        }
        else if (timerFifthteen.isPressed(window)) {
            timerFive.setState(false);
            timerTen.setState(false);
            timerTwenty.setState(false);
            timerFive.updateTexture(buttonOnTexture, buttonOffTexture);
            timerTen.updateTexture(buttonOnTexture, buttonOffTexture);
            timerTwenty.updateTexture(buttonOnTexture, buttonOffTexture);

            timerFifthteen.setState(true); 
            timerFifthteen.updateTexture(buttonOnTexture, buttonOffTexture);

            timerLength = 15;
        }
        else if (timerTwenty.isPressed(window)) {
            timerFive.setState(false);
            timerTen.setState(false);
            timerFifthteen.setState(false);
            timerFive.updateTexture(buttonOnTexture, buttonOffTexture);
            timerTen.updateTexture(buttonOnTexture, buttonOffTexture);
            timerFifthteen.updateTexture(buttonOnTexture, buttonOffTexture);

            timerTwenty.setState(true);
            timerTwenty.updateTexture(buttonOnTexture, buttonOffTexture);

            timerLength = 20;
        }

        if (timerOff.isPressed(window)) {
            timerOn.setState(false);
            timerOn.updateTexture(buttonOnTexture, buttonOffTexture);
            timerOff.setState(true);
            timerOff.updateTexture(buttonOnTexture, buttonOffTexture);

            timerEnabled = false;
        }
        else if (timerOn.isPressed(window)) {
            timerOff.setState(false);
            timerOff.updateTexture(buttonOnTexture, buttonOffTexture);
            timerOn.setState(true);
            timerOn.updateTexture(buttonOnTexture, buttonOffTexture);

            timerEnabled = true;
        }

        window.display();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            return;
        }
    }
}

void settingsMenu() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        menu.draw(window);
        settingsTitle.draw(window);
        resolutionLabel.draw(window);
        resolutionMin.draw(window);
        resolutionMid.draw(window);
        resolutionMax.draw(window);
        fullscreen.draw(window);
        refreshLabel.draw(window);
        refreshSlider.draw(window);

        refreshSlider.update(window);
        framerate = refreshSlider.getValue();
        window.setFramerateLimit(framerate);

        if (resolutionMin.isPressed(window)) {
            if (!resolutionMin.getState()) {
                window.create(sf::VideoMode(1280, 720), windowName);
                window.setView(sf::View(sf::FloatRect(0, 0, 1280, 720)));
                initialiseElements();
                resolutionMin.setState(true);
                resolutionMid.setState(false);
                resolutionMax.setState(false);
                fullscreen.setState(false);
                resolutionMin.updateTexture(buttonOnTexture, buttonOffTexture);
                resolutionMid.updateTexture(buttonOnTexture, buttonOffTexture);
                resolutionMax.updateTexture(buttonOnTexture, buttonOffTexture);
                fullscreen.updateTexture(buttonOnTexture, buttonOffTexture);
            }
        }
        else if (resolutionMid.isPressed(window)) {
            if (!resolutionMid.getState()) {
                window.create(sf::VideoMode(1920, 1080), windowName);
                window.setView(sf::View(sf::FloatRect(0, 0, 1920, 1080)));
                initialiseElements();
                resolutionMin.setState(false);
                resolutionMid.setState(true);
                resolutionMax.setState(false);
                fullscreen.setState(false);
                resolutionMin.updateTexture(buttonOnTexture, buttonOffTexture);
                resolutionMid.updateTexture(buttonOnTexture, buttonOffTexture);
                resolutionMax.updateTexture(buttonOnTexture, buttonOffTexture);
                fullscreen.updateTexture(buttonOnTexture, buttonOffTexture);
            }
        }
        else if (resolutionMax.isPressed(window)) {
            if (!resolutionMax.getState()) {
                window.create(sf::VideoMode(2560, 1440), windowName);
                window.setView(sf::View(sf::FloatRect(0, 0, 2560, 1440)));
                initialiseElements();
                resolutionMin.setState(false);
                resolutionMid.setState(false);
                resolutionMax.setState(true);
                fullscreen.setState(false);
                resolutionMin.updateTexture(buttonOnTexture, buttonOffTexture);
                resolutionMid.updateTexture(buttonOnTexture, buttonOffTexture);
                resolutionMax.updateTexture(buttonOnTexture, buttonOffTexture);
                fullscreen.updateTexture(buttonOnTexture, buttonOffTexture);
            }
        }
        else if (fullscreen.isPressed(window)) {
            if (!fullscreen.getState()) {
                window.create(sf::VideoMode::getDesktopMode(), windowName, sf::Style::Fullscreen);
                window.setView(sf::View(sf::FloatRect(0, 0, sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height)));
                initialiseElements();
                resolutionMin.setState(false);
                resolutionMid.setState(false);
                resolutionMax.setState(false);
                fullscreen.setState(true);
                resolutionMin.updateTexture(buttonOnTexture, buttonOffTexture);
                resolutionMid.updateTexture(buttonOnTexture, buttonOffTexture);
                resolutionMax.updateTexture(buttonOnTexture, buttonOffTexture);
                fullscreen.updateTexture(buttonOnTexture, buttonOffTexture);
            }
        }


        if (menu.isPressed(window)) {
            return;
        }

        window.display();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            return;
        }
    }
}


int main()
{
    initialiseElements();
    window.setView(sf::View(sf::Vector2f(640, 360), sf::Vector2f(1280, 720)));
    window.setFramerateLimit(framerate);
    window.setVerticalSyncEnabled(false);

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
            gameMenu();
        }
        else if (settingsButton.isPressed(window)) {
            settingsMenu();
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
