#pragma once
#include "Components.h"

sf::RenderWindow window(sf::VideoMode(1280, 720), "GameWindow");

sf::Font arialRounded;
sf::Texture buttonOnTexture;
sf::Texture buttonOffTexture;
sf::Texture defaultTexture;

// Main Menu Elements
Button mainStartButton;
Button tutorialButton;
Button settingsButton;
Button exitButton;

// Game Customisation Menu Elements
Slider difficultySlider;
Button menu;
Label className;
Label customisationTitle;
Label difficultyLabel;
Label lengthLabel;
Label timerLabel;
Button gameStart;