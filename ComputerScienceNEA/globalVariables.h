#pragma once
#include <SFML/Graphics.hpp>

class Message;
class Room;
class Key;
class Wall;
class Door;
class Enemy;
class Player;
class Image;
class Label;
class Button;
class Bar;
class Pointer;
class Slider;


std::vector<Room> rooms;

long timeForLastFrame = 0;
int roomHeight = 500;
int roomWidth = 1000;
int wallThickness = 15;
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

// Default Elements
sf::Font arialRounded;
sf::Texture buttonOnTexture;
sf::Texture buttonOffTexture;
sf::Texture defaultTexture;
sf::Texture wallTexture;
sf::Texture keyTexture;
sf::Texture enemyTexture;
sf::Texture redTexture;
sf::Texture playerAxis;
sf::Texture playerDiagonal;
sf::Texture playerAttackArea;
sf::Texture enemyAxis;
sf::Texture enemyDiagonal;
sf::Texture enemyAttackArea;
sf::Texture exitTexture;
