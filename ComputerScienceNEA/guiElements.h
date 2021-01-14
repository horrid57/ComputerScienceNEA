#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

// Variables
long timeForLastFrame = 0;
int roomHeight = 500;
int roomWidth = 1000;
int wallThickness = 5;
float framerate = 60;
float gameDifficulty = 0.2;
int timerLength = 10;
bool timerEnabled = false;
int playerClass = 0;
std::vector<std::string> classNames = { "Ranged", "Melee", "Balanced" };
std::vector<std::string> classDescriptions = {
    "The ranged class has a powerful bow\nbut has a sword that doesn't live\nup to expectations",
    "The melee class has a huge sweeping sword\nand a slow, damaged bow that\ndoes little damage",
    "The best of both worlds. This class has a\ndecent bow and a decent sword\nthat make it a good choice"
};
std::vector<sf::Texture> classImages;

// Main Menu Elements
Button mainStartButton;
Button tutorialButton;
Button settingsButton;
Button exitButton;

// Game Customisation Menu Elements
Slider difficultySlider;
Button menu;
Label customisationTitle;
Label difficultyLabel;
Label lengthLabel;
Label timerLabel;
Button gameStart;
Button timerFive;
Button timerTen;
Button timerFifthteen;
Button timerTwenty;
Button timerOn;
Button timerOff;
Label className;
Button left;
Button right;
Label classDescription;
Image classImage;

// Settings Menu Elements
Label settingsTitle;
Label resolutionLabel;
Button resolutionMin;
Button resolutionMid;
Button resolutionMax;
Button fullscreen;
Label refreshLabel;
Slider refreshSlider;

void initialiseElements() {
    // Defining Default Elements
    buttonOffTexture.loadFromFile("blue.jpg");
    defaultTexture.loadFromFile("blue.jpg");
    buttonOnTexture.loadFromFile("green.png");
    arialRounded.loadFromFile("ARLRDBD.ttf");
    wallTexture.loadFromFile("brown.jpg");
    keyTexture.loadFromFile("brown.jpg");
    enemyTexture.loadFromFile("green.png");

    classImages = { buttonOnTexture, buttonOffTexture, defaultTexture };

    // Defining Main Menu Elements
    mainStartButton = Button(false, "START", 0.334, 0.267, 0.313, 0.206);
    tutorialButton = Button(false, "Tutorial", 0.378, 0.514, 0.227, 0.104);
    settingsButton = Button(false, "Settings", 0.377, 0.659, 0.227, 0.087);
    exitButton = Button(false, "Exit", 0.021, 0.877, 0.123, 0.095);

    // Defining Game Customisation Menu Elements
    difficultySlider = Slider(0, 1, gameDifficulty, 0.4, 0.3026, 0.591, 0.1577);
    menu = Button(false, "Menu", 0.0129, 0.0211, 0.1026, 0.0795);
    customisationTitle = Label("Customise", 0.3688, 0.0152, 0.2323, 0.1111);
    difficultyLabel = Label("Game Difficulty", 0.4935, 0.1988, 0.2016, 0.0807);
    lengthLabel = Label("Game Length", 0.4935, 0.5216, 0.161, 0.0561);
    timerLabel = Label("Timer", 0.4935, 0.7462, 0.1063, 0.0667);
    gameStart = Button(false, "START", 0.7566, 0.8117, 0.2164, 0.1415);

    timerFive = Button(false, "5 mins", 0.4935, 0.5906, 0.0744, 0.0725);
    timerTen = Button(false, "10 mins", 0.5906, 0.5906, 0.0744, 0.0725);
    timerFifthteen = Button(false, "15 mins", 0.6878, 0.5906, 0.0744, 0.0725);
    timerTwenty = Button(false, "20 mins", 0.7849, 0.5906, 0.0744, 0.0725);
    switch (timerLength) {
    case 5:
        timerFive = Button(true, "5 mins", 0.4935, 0.5906, 0.0744, 0.0725);
        break;
    case 10:
        timerTen = Button(true, "10 mins", 0.5906, 0.5906, 0.0744, 0.0725);
        break;
    case 15:
        timerFifthteen = Button(true, "15 mins", 0.6878, 0.5906, 0.0744, 0.0725);
        break;
    case 20:
        timerTwenty = Button(true, "20 mins", 0.7849, 0.5906, 0.0744, 0.0725);
    }
    timerOn = Button(timerEnabled, "On", 0.4935, 0.8374, 0.0744, 0.0725);
    timerOff = Button(!timerEnabled, "Off", 0.5906, 0.8374, 0.0744, 0.0725);

    className = Label(classNames[playerClass], 0.1143, 0.2304, 0.1955, 0.0830);
    left = Button(false, "<", 0.0633, 0.4842, 0.0368, 0.0702);
    right = Button(false, ">", 0.3288, 0.4842, 0.0368, 0.0702);
    classImage = Image(window, buttonOnTexture, 0.1045, 0.3415, 0.2200, 0.3333);
    classDescription = Label(" ", 0.0419, 0.6901, 0.3454, 0.2678);

    // Defining Settings Menu Elements
    settingsTitle = Label("Settings", 0.3839, 0.0152, 0.2323, 0.1111);
    resolutionLabel = Label("Resolution", 0.4232, 0.2187, 0.1537, 0.0800);
    resolutionMin = Button(false, "1280 x 720", 0.3508, 0.3184, 0.0738, 0.0700);
    resolutionMid = Button(true, "1920 x 1080", 0.4270, 0.3184, 0.0738, 0.0700);
    resolutionMax = Button(false, "2560 x 1440", 0.5031, 0.3184, 0.0738, 0.0700);
    fullscreen = Button(false, "Fullscreen", 0.5792, 0.3184, 0.0738, 0.0700);
    refreshLabel = Label("Refresh Rate", 0.4232, 0.5130, 0.1537, 0.0800);
    refreshSlider = Slider(10, 144, framerate, 0.2500, 0.5930, 0.5000, 0.1500);

};
