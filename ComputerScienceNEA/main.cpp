#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <time.h>

std::string windowName = "Game Window";
sf::RenderWindow window(sf::VideoMode(1920, 1080), windowName, sf::Style::Titlebar | sf::Style::Close);

#include "textures.h"
#include "levelComponents.h"
#include "guiComponents.h"
#include "guiElements.h"

bool contains(std::vector<sf::Vector2i>& vector, sf::Vector2i value) {
    for (int i = 0; i < vector.size(); i++) {
        if (vector[i] == value) {
            return true;
        }
    }
    return false;
};

std::vector<Room> generateRooms() {
    std::vector<Room> rooms;
    std::vector<sf::Vector2i> positions = { sf::Vector2i(200, 400) };
    std::vector<std::string> doorIn = { "" };
    std::vector<std::string> doorOut;

    srand(time(0));
    int i = 0;
    int attempts = 0;
    int timesStuck = 0;
    while (i < timerLength) {
        // rand() not truely random... 
        // srand() with a consistantly different starting value changes the start position of the string
        int randInt = rand() % 4;
        sf::Vector2i nextPosition;
        sf::Vector2i lastPosition = positions.back();
        switch (randInt) {
        // LEFT
        case 0:
            nextPosition = sf::Vector2i(lastPosition.x - roomWidth, lastPosition.y);
            if (!contains(positions, nextPosition) &&
                !contains(positions, sf::Vector2i(nextPosition.x - roomWidth, nextPosition.y)) &&
                !contains(positions, sf::Vector2i(nextPosition.x, nextPosition.y + roomHeight)) &&
                !contains(positions, sf::Vector2i(nextPosition.x, nextPosition.y - roomHeight))
                ) {
                positions.push_back(nextPosition);
                doorIn.push_back("Right");
                doorOut.push_back("Left");
                i++;
                attempts = 0;
            }
            else {
                attempts++;
            }
            break;
        // UP
        case 1:
            nextPosition = sf::Vector2i(lastPosition.x, lastPosition.y - roomHeight);
            if (!contains(positions, nextPosition) &&
                !contains(positions, sf::Vector2i(nextPosition.x - roomWidth, nextPosition.y)) &&
                !contains(positions, sf::Vector2i(nextPosition.x + roomWidth, nextPosition.y)) &&
                !contains(positions, sf::Vector2i(nextPosition.x, nextPosition.y - roomHeight))
                ) {
                positions.push_back(nextPosition);
                doorIn.push_back("Bottom");
                doorOut.push_back("Top");
                i++;
                attempts = 0;
            }
            else {
                attempts++;
            }
            break;
        // RIGHT
        case 2:
            nextPosition = sf::Vector2i(lastPosition.x + roomWidth, lastPosition.y);
            if (!contains(positions, nextPosition) &&
                !contains(positions, sf::Vector2i(nextPosition.x + roomWidth, nextPosition.y)) &&
                !contains(positions, sf::Vector2i(nextPosition.x, nextPosition.y + roomHeight)) &&
                !contains(positions, sf::Vector2i(nextPosition.x, nextPosition.y - roomHeight))
                ) {
                positions.push_back(nextPosition);
                doorIn.push_back("Left");
                doorOut.push_back("Right");
                i++;
                attempts = 0;
            }
            else {
                attempts++;
            }
            break;
        // DOWN
        case 3:
            nextPosition = sf::Vector2i(lastPosition.x, lastPosition.y + roomHeight);
            if (!contains(positions, nextPosition) &&
                !contains(positions, sf::Vector2i(nextPosition.x - roomWidth, nextPosition.y)) &&
                !contains(positions, sf::Vector2i(nextPosition.x + roomWidth, nextPosition.y)) &&
                !contains(positions, sf::Vector2i(nextPosition.x, nextPosition.y + roomHeight))
                ) {
                positions.push_back(nextPosition);
                doorIn.push_back("Top");
                doorOut.push_back("Bottom");
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
        *   BUGGY - DISCONNECTED ROOMS HAVE BEEN SEEN - FIGURE IT OUT AT SOME POINT
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
    doorOut.push_back("");
    for (int i = 0; i < positions.size(); i++) {
        rooms.push_back(Room(wallTexture, buttonOnTexture, positions[i].x, positions[i].y, roomWidth, roomHeight, wallThickness, doorIn[i], doorOut[i]));
    };

    return rooms;
}

void transitionIn(sf::RenderWindow& window, float time, int rotation = 45) {
    long initialTime = 0;
    long endTime = 0;
    float speed = window.getSize().x / time;
    int offset;
    sf::RectangleShape line1(sf::Vector2f(window.getSize().x, 100));
    line1.setOrigin(sf::Vector2f(line1.getLocalBounds().width, 0));
    line1.rotate(rotation);
    line1.setPosition(0, window.getSize().y + 100);
    line1.setFillColor(sf::Color::Blue);
    sf::RectangleShape line2(sf::Vector2f(window.getSize().x, 100));
    line2.setOrigin(sf::Vector2f(0, line2.getLocalBounds().height));
    line2.rotate(rotation);
    line2.setPosition(window.getSize().x, -100);
    line2.setFillColor(sf::Color::Blue);
    while (line1.getPosition().x <= window.getSize().x) {
        initialTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            };
        }
        offset = speed * (float)timeForLastFrame / 1000000;
        line1.setPosition(line1.getPosition().x + offset, line1.getPosition().y);
        line2.setPosition(line2.getPosition().x - offset, line2.getPosition().y);
        window.draw(line1);
        window.draw(line2);
        window.display();
        endTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        timeForLastFrame = endTime - initialTime;
    }
}

/*void transitionOut(sf::RenderWindow& window) {
    long initialTime = 0;
    long endTime = 0;
    float speed = window.getSize().x / 1;
    int offset;
    sf::RectangleShape line1(sf::Vector2f(window.getSize().x * 2, window.getSize().x * 2));
    line1.setOrigin(sf::Vector2f(line1.getLocalBounds().width, 0));
    line1.rotate(45);
    line1.setPosition(window.getSize().x, window.getSize().y + 100);
    line1.setFillColor(sf::Color::Blue);
    sf::RectangleShape line2(sf::Vector2f(window.getSize().x * 2, window.getSize().y * 2));
    line2.rotate(45);
    line2.setPosition(0, -2000);
    line2.setFillColor(sf::Color::Blue);
    while (line1.getPosition().x >= window.getView().getCenter().x - window.getView().getSize().x / 2) {
        initialTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            };
        }
        window.clear();
        offset = speed * (float)timeForLastFrame / 1000000;
        line1.setPosition(line1.getPosition().x - offset, line1.getPosition().y);
        line2.setPosition(line2.getPosition().x + offset, line2.getPosition().y);
        window.draw(line1);
        window.draw(line2);
        window.display();
        endTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        timeForLastFrame = endTime - initialTime;
    }
    }
}*/

void gameScreen(sf::RenderWindow& window) {
    // vvvvvvvvv
    //transitionIn(window, 1, 45);
    // ^^^^^^
    long initialTime = 0;
    long endTime = 0;
    std::vector<Room> rooms = generateRooms();
    Player player = Player(buttonOffTexture, 300, 500, 50, 50, 1000, 5);
    window.setView(sf::View(player.getCentre(), window.getView().getSize()));

    std::vector<Enemy> enemies = {};
    for (int i = 1; i < rooms.size() - 1; i++) {
        Key key = Key(0, 0, 20, 20, false);
        enemies = {};
        sf::FloatRect rb = rooms[i].getBounds();
        for (int j = 0; j < rand() % 3 + 2; j++) {
            if (j == 0) {
                enemies.push_back(Enemy(rb.left + rb.width * ((float)rand() / float(RAND_MAX)), rb.top + rb.height * ((float)rand() / float(RAND_MAX)), 50, 50, 5, 5, 5, key));
            }
            else {
                enemies.push_back(Enemy(rb.left + rb.width * ((float)rand() / float(RAND_MAX)), rb.top + rb.height * ((float)rand() / float(RAND_MAX)), 50, 50, 5, 5, 5));
            }
        }
        rooms[i].setEnemies(enemies);
    };
        
    // vvvvv TRANSITION TEST vvvvv
    /*float speed = window.getSize().x / 1;
    int offset;
    sf::RectangleShape line1(sf::Vector2f(window.getSize().x * 2, window.getSize().x * 2));
    line1.setOrigin(sf::Vector2f(line1.getLocalBounds().width, 0));
    line1.rotate(45);
    line1.setPosition(window.getSize().x, window.getSize().y + 100);
    line1.setFillColor(sf::Color::Blue);
    sf::RectangleShape line2(sf::Vector2f(window.getSize().x * 2, window.getSize().y * 2));
    line2.rotate(45);
    line2.setPosition(0, -2000);
    line2.setFillColor(sf::Color::Blue);
    while (line1.getPosition().x >= window.getView().getCenter().x - window.getView().getSize().x / 2) {
        initialTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            };
        }
        window.clear();
        offset = speed * (float)timeForLastFrame / 1000000;
        line1.setPosition(line1.getPosition().x - offset, line1.getPosition().y);
        line2.setPosition(line2.getPosition().x + offset, line2.getPosition().y);
        for (int i = 0; i < rooms.size(); i++) {
            rooms[i].draw(window);
        };
        player.draw(window);
        window.draw(line1);
        window.draw(line2);
        window.display();
        endTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        timeForLastFrame = endTime - initialTime;
    }*/
    // ^^^^^ TRANSITION TEST ^^^^^

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            };
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            };
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
                rooms = generateRooms();
            };
        }
        initialTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        window.clear();

        player.move(rooms, (float)timeForLastFrame / 1000000);
        window.setView(sf::View(player.getCentre(), window.getView().getSize()));
        player.attack(rooms);
        player.pickUpKeys(rooms);

        
        for (int i = 0; i < rooms.size(); i++) {
            rooms[i].draw(window);
        };

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
        difficultyLabel.setText(difficultyLabel.getDefaultText() + ": " + std::to_string(difficultySlider.getValue()).substr(0, 4));

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
        refreshLabel.setText(refreshLabel.getDefaultText() + ": " + std::to_string((int)refreshSlider.getValue()));

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
