#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <time.h>

std::string windowName = "Game Window";
sf::RenderWindow window(sf::VideoMode(1920, 1080), windowName, sf::Style::Titlebar | sf::Style::Close);

#include "globalVariables.h"
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
    std::vector<std::string> doorOut2;

    srand(time(0));
    int i = 0;
    int attempts = 0;
    int timesStuck = 0;
    while (i <= timerLength) {
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

    for (int i = 0; i < timerLength - 1; i++) {
        sf::Vector2i lastPosition = positions[i];
        sf::Vector2i nextPosition;
        int randInt = rand() % 4;
        switch (randInt)
        {
        case 0:
            // LEFT
            nextPosition = sf::Vector2i(lastPosition.x - roomWidth, lastPosition.y);
            if (!contains(positions, nextPosition)) {
                positions.push_back(nextPosition);
                doorIn.push_back("Right");
                doorOut.push_back("");
                doorOut2.push_back("Left");
            }
            else {
                doorOut2.push_back("");
            }
            break;
        case 1:
            nextPosition = sf::Vector2i(lastPosition.x, lastPosition.y - roomHeight);
            if (!contains(positions, nextPosition)) {
                positions.push_back(nextPosition);
                doorIn.push_back("Bottom");
                doorOut.push_back("");
                doorOut2.push_back("Top");
            }
            else {
                doorOut2.push_back("");
            }
            break;
            // RIGHT
        case 2:
            nextPosition = sf::Vector2i(lastPosition.x + roomWidth, lastPosition.y);
            if (!contains(positions, nextPosition)) {
                positions.push_back(nextPosition);
                doorIn.push_back("Left");
                doorOut.push_back("");
                doorOut2.push_back("Right");
            }
            else {
                doorOut2.push_back("");
            }
            break;
            // DOWN
        case 3:
            nextPosition = sf::Vector2i(lastPosition.x, lastPosition.y + roomHeight);
            if (!contains(positions, nextPosition)) {
                positions.push_back(nextPosition);
                doorIn.push_back("Top");
                doorOut.push_back("");
                doorOut2.push_back("Bottom");
            }
            else {
                doorOut2.push_back("");
            }
            break;
        default:
            doorOut2.push_back("");
            break;
        }
    }

    for (int i = doorOut2.size(); i < positions.size(); i++) {
        doorOut2.push_back("");
    }

    int numberOfRooms = positions.size();
    sf::Vector2i nextPosition;
    for (int i = timerLength + 1; i < numberOfRooms; i++) {
        int randInt = rand() % 4;
        sf::Vector2i lastPosition = positions[i];
        switch (randInt) {
            // LEFT
        case 0:
            nextPosition = sf::Vector2i(lastPosition.x - roomWidth, lastPosition.y);
            if (!contains(positions, nextPosition)) {
                positions.push_back(nextPosition);
                doorIn.push_back("Right");
                doorOut[i] = "Left";
            }
            break;
            // UP
        case 1:
            nextPosition = sf::Vector2i(lastPosition.x, lastPosition.y - roomHeight);
            if (!contains(positions, nextPosition)) {
                positions.push_back(nextPosition);
                doorIn.push_back("Bottom");
                doorOut[i] = "Top";
            }
            break;
            // RIGHT
        case 2:
            nextPosition = sf::Vector2i(lastPosition.x + roomWidth, lastPosition.y);
            if (!contains(positions, nextPosition)) {
                positions.push_back(nextPosition);
                doorIn.push_back("Left");
                doorOut[i] = "Right";
            }
            break;
            // DOWN
        case 3:
            nextPosition = sf::Vector2i(lastPosition.x, lastPosition.y + roomHeight);
            if (!contains(positions, nextPosition)) {
                positions.push_back(nextPosition);
                doorIn.push_back("Top");
                doorOut[i] = "Bottom";
            }
            break;
        };
    }

    for (int i = doorOut2.size(); i < positions.size(); i++) {
        doorOut2.push_back("");
    }
    for (int i = doorOut.size(); i < positions.size(); i++) {
        doorOut.push_back("");
    }

    for (int i = 0; i < positions.size(); i++) {
        rooms.push_back(Room(positions[i].x, positions[i].y, roomWidth, roomHeight, wallThickness, doorIn[i], doorOut[i], doorOut2[i]));
        if (i != timerLength && i != 0) {
            int sideBuffer = 75;
            int numberOfObsticles = 3 + rand() % 3;
            sf::FloatRect rb = rooms[i].getBounds();
            for (int j = 0; j < numberOfObsticles; j++) {
                int width = (float)rand() / float(RAND_MAX) * 80 + 40;
                rooms[i].addObstacle(Obstacle(rb.left + sideBuffer + (rb.width - 2 * sideBuffer - width) * ((float)rand() / float(RAND_MAX)),
                    rb.top + sideBuffer + (rb.height - 2 * sideBuffer - width) * ((float)rand() / float(RAND_MAX)), width, width));
            }
        }
    };

    return rooms;
}

bool gameScreen() {
    long initialTime = 0;
    long endTime = 0;
    rooms = generateRooms();
    std::vector<Wall> allWalls;
    std::vector<Obstacle> allObstacles;
    Player player = Player(buttonOffTexture, 300, 500, 50, 50, 600, 100);
    window.setView(sf::View(player.getCentre(), window.getView().getSize()));
    int exitWidth = 100;
    sf::FloatRect roomBounds = rooms[timerLength].getBounds();
    Exit exit = Exit(roomBounds.left + (roomBounds.width - exitWidth) / 2, roomBounds.top + (roomBounds.height - exitWidth) / 2, exitWidth, exitWidth);
    Message messageBar;
    HUDTextElement healthDisplay = HUDTextElement(std::to_string(player.health) + " / " + std::to_string(player.maximumHealth), 0.05, 0.9);
    long timer = timerLength * 60 * 1000 * 1000;
    HUDTextElement timerDisplay("Default Text", 0.8, 0.9);

    for (int i = 1; i < rooms.size(); i++) {
        for (int j = 0; j < rooms[i].walls.size(); j++) {
            allWalls.push_back(rooms[i].walls[j]);
        }
        for (int j = 0; j < rooms[i].obstacles.size(); j++) {
            allObstacles.push_back(rooms[i].obstacles[j]);
        }
        Key key = Key(0, 0, 35, 35, false);
        sf::FloatRect rb = rooms[i].getBounds();
        for (int j = 0; j < rand() % 5 + 2; j++) {
            if (j == 0) {
                while (!rooms[i].addEnemy(Enemy(rb.left + 50 + (rb.width - 50 * 2) * ((float)rand() / float(RAND_MAX)), 
                    rb.top + 50 + (rb.height - 50 * 2) * ((float)rand() / float(RAND_MAX)),
                    50, 50, 200, 5 + (int)(gameDifficulty * 10), 5 + (int)(gameDifficulty * 10), key))) { }
            }
            else {
                while (!rooms[i].addEnemy(Enemy(rb.left + 50 + (rb.width - 50 * 2) * ((float)rand() / float(RAND_MAX)),
                    rb.top + 50 + (rb.height - 50 * 2) * ((float)rand() / float(RAND_MAX)),
                    50, 50, 200, 5 + (int)(gameDifficulty * 10), 5 + (int)(gameDifficulty * 10)))) { }
            }
        }
        for (int j = 0; j < rand() % 3 + 1; j++) {
            while (!rooms[i].addEnemy(Enemy(rb.left + 50 + (rb.width - 50 * 2) * ((float)rand() / float(RAND_MAX)),
                rb.top + 50 + (rb.height - 50 * 2) * ((float)rand() / float(RAND_MAX)),
                60, 60, 200, 5 + (int)(gameDifficulty * 10), 5 + (int)(gameDifficulty * 10), true))) {
            }
        }
    };

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
        }
        initialTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        window.clear(sf::Color::White);


        float speedScale = (float)timeForLastFrame / 1000000;
        player.move(rooms, speedScale);
        window.setView(sf::View(player.getCentre(), window.getView().getSize()));
        player.attack(rooms);
        if (player.pickUpKeys(rooms)) {
            messageBar.addMessage("Picked Up a Key");
        }
        
        for (int i = 0; i < rooms.size(); i++) {
            rooms[i].draw();
            if (rooms[i].door.isOpened()) {
                for (int j = 0; j < rooms[i].enemies.size(); j++) {
                    rooms[i].enemies[j].searchForPlayer(player.getGlobalBounds(), allWalls, allObstacles);
                    rooms[i].enemies[j].move(speedScale, player.sprite.getPosition(), allWalls, allObstacles);
                    int damage = rooms[i].enemies[j].attackPlayer(player.sprite.getPosition(), player.getGlobalBounds(), allWalls, allObstacles);
                    if (damage > 0) {
                        player.takeDamage(damage);
                        healthDisplay.updateText(std::to_string(player.health) + " / " + std::to_string(player.maximumHealth));
                    }
                }
            }
        };

        if (exit.checkCollision(player.getGlobalBounds()) && sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            return true;
        }
        exit.draw();

        player.draw();
        messageBar.draw();
        healthDisplay.draw();

        if (timerEnabled) {
            timer -= timeForLastFrame;
            if (timer <= 0) {
                return false;
            }
            timerDisplay.updateText(std::to_string(timer / (1000 * 1000)));
            timerDisplay.draw();
        }

        if (player.isDead()) {
            return false;
        }

        window.display();
        endTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        timeForLastFrame = endTime - initialTime;
    }
}

void tutorialScreen() {
    long initialTime = 0;
    long endTime = 0;
    rooms = {
        Room(0, 0, roomWidth, roomHeight, wallThickness, "", "Right", ""),
        Room(0 + roomWidth, 0, roomWidth, roomHeight, wallThickness, "", "Right", "Left"),
        Room(0 + 2 * roomWidth, 0, roomWidth, roomHeight, wallThickness, "Left", "Right", ""),
        Room(0 + 3 * roomWidth, 0, roomWidth, roomHeight, wallThickness, "Left", "Right", ""),
        Room(0 + 4 * roomWidth, 0, roomWidth, roomHeight, wallThickness, "", "", "Left"),
    };
    
    std::vector<Label> labels = {
        Label((roomWidth / 2) - 300, 0, 600, 100, "Welcome to the Tutorial"),
        Label((roomWidth / 2) - 300, roomHeight - 100, 600, 100, "Use W, A, S and D to Move"),
        Label(roomWidth + (roomWidth / 2) - 300, 0, 600, 100, "If you have a Key, you can walk into Doors to open them"),
        Label(roomWidth + (roomWidth / 2) - 300, roomHeight - 100, 600, 100, "You always start the game with 1 Key"),
        Label(2 * roomWidth + (roomWidth / 2) - 300, 0, 600, 100, "Use Left Click to perform a Melee Attack\nRight Click performs a Ranged Attack"),
        Label(2 * roomWidth + (roomWidth / 2) - 300, roomHeight - 100, 600, 100, "Kill the Enemy and pick up their Key"),
        Label(3 * roomWidth + (roomWidth / 2) - 300, 0, 600, 100, "Not all enemies have Keys on them"),
        Label(3 * roomWidth + (roomWidth / 2) - 300, roomHeight - 100, 600, 100, "Enemies will look for, and chase, you in-game\nWhen you are playing you can hide behind boxes to escape"),
        Label(4 * roomWidth + (roomWidth / 2) - 300, 0, 600, 100, "Press E on the Exit to win"),
    };

    Player player = Player(buttonOffTexture, 300, 500, 50, 50, 600, 100);
    window.setView(sf::View(player.getCentre(), window.getView().getSize()));

    int exitWidth = 100;
    sf::FloatRect roomBounds = rooms[4].getBounds();
    Exit exit = Exit(roomBounds.left + (roomBounds.width - exitWidth) / 2, roomBounds.top + (roomBounds.height - exitWidth) / 2, exitWidth, exitWidth);

    Message messageBar;
    HUDTextElement healthDisplay = HUDTextElement(std::to_string(player.health) + " / " + std::to_string(player.maximumHealth), 0.05, 0.9);

    sf::FloatRect rb = rooms[2].getBounds();
    rooms[2].addEnemy(Enemy(rb.left + rb.width / 2 - 25, rb.top + rb.height / 2 - 25, 50, 50, 200, 10, 0, Key(0, 0, 35, 35, false)));
    rb = rooms[3].getBounds();
    rooms[3].addEnemy(Enemy(rb.left + rb.width / 2 - 125, rb.top + rb.height / 2 - 125, 50, 50, 200, 10, 0));
    rooms[3].addEnemy(Enemy(rb.left + rb.width / 2 - 125, rb.top + rb.height / 2 + 75, 50, 50, 200, 10, 0));
    rooms[3].addEnemy(Enemy(rb.left + rb.width / 2 + 75, rb.top + rb.height / 2 - 125, 50, 50, 200, 10, 0, Key(0, 0, 35, 35, false)));
    rooms[3].addEnemy(Enemy(rb.left + rb.width / 2 + 75, rb.top + rb.height / 2 + 75, 50, 50, 200, 10, 0));
    
    
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
        }
        initialTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        window.clear(sf::Color::White);


        float speedScale = (float)timeForLastFrame / 1000000;
        player.move(rooms, speedScale);
        window.setView(sf::View(player.getCentre(), window.getView().getSize()));
        player.attack(rooms);
        if (player.pickUpKeys(rooms)) {
            messageBar.addMessage("Picked Up a Key");
        }

        for (int i = 0; i < rooms.size(); i++) {
            rooms[i].draw();
            if (rooms[i].door.isOpened()) {
                for (int j = 0; j < rooms[i].enemies.size(); j++) {
                    rooms[i].enemies[j].move(speedScale, player.sprite.getPosition(), rooms[i].walls, rooms[i].obstacles, false);
                    rooms[i].enemies[j].attackPlayer(player.sprite.getPosition(), player.getGlobalBounds(), rooms[i].walls, rooms[i].obstacles);
                }
            }
        };

        if (exit.checkCollision(player.getGlobalBounds()) && sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            return;
        }
        exit.draw();

        player.draw();

        for (int i = 0; i < labels.size(); i++) {
            labels[i].draw();
        }

        messageBar.draw();
        healthDisplay.draw();

        if (player.isDead()) {
            return;
        }

        window.display();
        endTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        timeForLastFrame = endTime - initialTime;
    }
}

void resetView() {
    if (resolutionMin.enabled) {
        window.setView(sf::View(sf::FloatRect(0, 0, 1280, 720)));
    }
    else if (resolutionMid.enabled) {
        window.setView(sf::View(sf::FloatRect(0, 0, 1920, 1080)));
    }
    else if (resolutionMax.enabled) {
        window.setView(sf::View(sf::FloatRect(0, 0, 2560, 1440)));
    }
    else if (fullscreen.enabled) {
        window.setView(sf::View(sf::FloatRect(0, 0, sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height)));
    }
}

void endScreen(bool victory) {

    Label mainText = Label(victory ? "VICTORY" : "DEFEAT", 0.3, 0.3, 0.4, 0.1);

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
        }
        window.clear();
        
        if (menu.isPressed()) {
            return;
        }

        menu.draw();
        mainText.draw();

        window.display();
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

        difficultySlider.draw();
        menu.draw();
        className.draw();
        customisationTitle.draw();
        difficultyLabel.draw();
        lengthLabel.draw();
        timerLabel.draw();
        gameStart.draw();
        timerFive.draw();
        timerTen.draw();
        timerFifthteen.draw();
        timerTwenty.draw();
        timerOn.draw();
        timerOff.draw();
        left.draw();
        right.draw();
        classImage.draw();
        classDescription.draw();


        if (menu.isPressed()) {
            return;
        }
        if (gameStart.isPressed()) {
            std::cout << classNames[playerClass] << ", " << gameDifficulty << ", " << timerEnabled << ", " << timerLength << "\n";
            bool outcome = gameScreen();
            resetView();
            endScreen(outcome);
            return;
        }
        difficultySlider.update();
        gameDifficulty = difficultySlider.getValue();
        difficultyLabel.setText(difficultyLabel.getDefaultText() + ": " + std::to_string(difficultySlider.getValue()).substr(0, 4));

        if (left.isPressed()) {
            playerClass--;
            if (playerClass < 0) {
                playerClass = classNames.size() - 1;
            };
            className.setText(classNames[playerClass]);
            classDescription.setText(classDescriptions[playerClass]);
            classImage.changeTexture(classImages[playerClass]);
        }
        else if (right.isPressed()) {
            playerClass++;
            if (playerClass > classNames.size() - 1) {
                playerClass = 0;
            };
            className.setText(classNames[playerClass]); 
            classDescription.setText(classDescriptions[playerClass]);
            classImage.changeTexture(classImages[playerClass]);
        };

        if (timerFive.isPressed()) {
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
        else if (timerTen.isPressed()) {
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
        else if (timerFifthteen.isPressed()) {
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
        else if (timerTwenty.isPressed()) {
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

        if (timerOff.isPressed()) {
            timerOn.setState(false);
            timerOn.updateTexture(buttonOnTexture, buttonOffTexture);
            timerOff.setState(true);
            timerOff.updateTexture(buttonOnTexture, buttonOffTexture);

            timerEnabled = false;
        }
        else if (timerOn.isPressed()) {
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

        menu.draw();
        settingsTitle.draw();
        resolutionLabel.draw();
        resolutionMin.draw();
        resolutionMid.draw();
        resolutionMax.draw();
        fullscreen.draw();
        refreshLabel.draw();
        refreshSlider.draw();

        refreshSlider.update();
        framerate = refreshSlider.getValue();
        window.setFramerateLimit(framerate);
        refreshLabel.setText(refreshLabel.getDefaultText() + ": " + std::to_string((int)refreshSlider.getValue()));

        if (resolutionMin.isPressed()) {
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
        else if (resolutionMid.isPressed()) {
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
        else if (resolutionMax.isPressed()) {
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
        else if (fullscreen.isPressed()) {
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


        if (menu.isPressed()) {
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

        mainStartButton.draw();
        tutorialButton.draw();
        settingsButton.draw();
        exitButton.draw();

        if (mainStartButton.isPressed()) {
            gameMenu();
        }
        else if (tutorialButton.isPressed()) {
            tutorialScreen();
            resetView();
        }
        else if (settingsButton.isPressed()) {
            settingsMenu();
        }
        else if (exitButton.isPressed()) {
            return 1;
        }

        window.display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            return 0;
        }
    }

    return 0;
}
