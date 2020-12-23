#pragma once
#include "Components.h"
#include <iostream>

std::string windowName = "Game Window";

sf::RenderWindow window(sf::VideoMode(1280, 720), windowName, sf::Style::Titlebar | sf::Style::Close);

// Default Elements
sf::Font arialRounded;
sf::Texture buttonOnTexture;
sf::Texture buttonOffTexture;
sf::Texture defaultTexture;

// Variables
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

    classImages = { buttonOnTexture, buttonOffTexture, defaultTexture };

    // Defining Main Menu Elements
    mainStartButton = Button(window, buttonOffTexture, buttonOnTexture, false, "START", arialRounded, 0.334, 0.267, 0.313, 0.206);
    tutorialButton = Button(window, buttonOffTexture, buttonOnTexture, false, "Tutorial", arialRounded, 0.378, 0.514, 0.227, 0.104);
    settingsButton = Button(window, buttonOffTexture, buttonOnTexture, false, "Settings", arialRounded, 0.377, 0.659, 0.227, 0.087);
    exitButton = Button(window, buttonOffTexture, buttonOnTexture, false, "Exit", arialRounded, 0.021, 0.877, 0.123, 0.095);

    // Defining Game Customisation Menu Elements
    difficultySlider = Slider(window, buttonOnTexture, buttonOffTexture, 0, 1, gameDifficulty, 0.4, 0.3026, 0.591, 0.1577);
    menu = Button(window, buttonOffTexture, buttonOnTexture, false, "Menu", arialRounded, 0.0129, 0.0211, 0.1026, 0.0795);
    customisationTitle = Label(window, defaultTexture, "Customise", arialRounded, 0.3688, 0.0152, 0.2323, 0.1111);
    difficultyLabel = Label(window, defaultTexture, "Game Difficulty", arialRounded, 0.4935, 0.1988, 0.2016, 0.0807);
    lengthLabel = Label(window, defaultTexture, "Game Length", arialRounded, 0.4935, 0.5216, 0.161, 0.0561);
    timerLabel = Label(window, defaultTexture, "Timer", arialRounded, 0.4935, 0.7462, 0.1063, 0.0667);
    gameStart = Button(window, buttonOffTexture, buttonOnTexture, false, "START", arialRounded, 0.7566, 0.8117, 0.2164, 0.1415);

    timerFive = Button(window, buttonOffTexture, buttonOnTexture, false, "5 mins", arialRounded, 0.4935, 0.5906, 0.0744, 0.0725);
    timerTen = Button(window, buttonOffTexture, buttonOnTexture, false, "10 mins", arialRounded, 0.5906, 0.5906, 0.0744, 0.0725);
    timerFifthteen = Button(window, buttonOffTexture, buttonOnTexture, false, "15 mins", arialRounded, 0.6878, 0.5906, 0.0744, 0.0725);
    timerTwenty = Button(window, buttonOffTexture, buttonOnTexture, false, "20 mins", arialRounded, 0.7849, 0.5906, 0.0744, 0.0725);
    switch (timerLength) {
    case 5:
        timerFive = Button(window, buttonOffTexture, buttonOnTexture, true, "5 mins", arialRounded, 0.4935, 0.5906, 0.0744, 0.0725);
        break;
    case 10:
        timerTen = Button(window, buttonOffTexture, buttonOnTexture, true, "10 mins", arialRounded, 0.5906, 0.5906, 0.0744, 0.0725);
        break;
    case 15:
        timerFifthteen = Button(window, buttonOffTexture, buttonOnTexture, true, "15 mins", arialRounded, 0.6878, 0.5906, 0.0744, 0.0725);
        break;
    case 20:
        timerTwenty = Button(window, buttonOffTexture, buttonOnTexture, true, "20 mins", arialRounded, 0.7849, 0.5906, 0.0744, 0.0725);
    }
    timerOn = Button(window, buttonOffTexture, buttonOnTexture, timerEnabled, "On", arialRounded, 0.4935, 0.8374, 0.0744, 0.0725);
    timerOff = Button(window, buttonOffTexture, buttonOnTexture, !timerEnabled, "Off", arialRounded, 0.5906, 0.8374, 0.0744, 0.0725);

    className = Label(window, defaultTexture, classNames[playerClass], arialRounded, 0.1143, 0.2304, 0.1955, 0.0830);
    left = Button(window, buttonOffTexture, buttonOnTexture, false, "<", arialRounded, 0.0633, 0.4842, 0.0368, 0.0702);
    right = Button(window, buttonOffTexture, buttonOnTexture, false, ">", arialRounded, 0.3288, 0.4842, 0.0368, 0.0702);
    classImage = Image(window, buttonOnTexture, 0.1045, 0.3415, 0.2200, 0.3333);
    classDescription = Label(window, defaultTexture, "adjawd\naedjkjaddw\ndjadwawd", arialRounded, 0.0419, 0.6901, 0.3454, 0.2678);

    // Defining Settings Menu Elements
    settingsTitle = Label(window, defaultTexture, "Settings", arialRounded, 0.3839, 0.0152, 0.2323, 0.1111);
    resolutionLabel = Label(window, defaultTexture, "Resolution", arialRounded, 0.4232, 0.2187, 0.1537, 0.0800);
    resolutionMin = Button(window, buttonOffTexture, buttonOnTexture, true, "1280 x 720", arialRounded, 0.3508, 0.3184, 0.0738, 0.0700);
    resolutionMid = Button(window, buttonOffTexture, buttonOnTexture, false, "1920 x 1080", arialRounded, 0.4270, 0.3184, 0.0738, 0.0700);
    resolutionMax = Button(window, buttonOffTexture, buttonOnTexture, false, "2560 x 1440", arialRounded, 0.5031, 0.3184, 0.0738, 0.0700);
    fullscreen = Button(window, buttonOffTexture, buttonOnTexture, false, "Fullscreen", arialRounded, 0.5792, 0.3184, 0.0738, 0.0700);
    refreshLabel = Label(window, defaultTexture, "Refresh Rate", arialRounded, 0.4232, 0.5130, 0.1537, 0.0800);
    refreshSlider = Slider(window, buttonOnTexture, buttonOffTexture, 10, 144, framerate, 0.2500, 0.5930, 0.5000, 0.1500);

};
