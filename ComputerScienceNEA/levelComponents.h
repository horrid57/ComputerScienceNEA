#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <chrono>

class Item {
public:
	sf::Sprite sprite;

	Item() { };

	Item(sf::Texture& texture, int xPosition, int yPosition, int width, int height) {
		sprite.setPosition(xPosition, yPosition);
		sprite.setTexture(texture);
		sf::FloatRect bounds = sprite.getGlobalBounds();
		sprite.setScale(width / bounds.width, height / bounds.height);
	}

	bool checkCollision(sf::FloatRect entity) {
		return sprite.getGlobalBounds().intersects(entity);
	}

	sf::FloatRect getBounds() {
		return sprite.getGlobalBounds();
	};

	void draw(sf::RenderWindow& window) {
		window.draw(sprite);
	};
};

class Key {
public:
	sf::Sprite sprite;
	bool visible = false;

	Key() { };

	Key(sf::Texture& texture, int xPosition, int yPosition, int width, int height, bool keyDropped = false) {
		visible = keyDropped;
		sprite.setPosition(xPosition, yPosition);
		sprite.setTexture(texture);
		sf::FloatRect bounds = sprite.getGlobalBounds();
		sprite.setScale(width / bounds.width, height / bounds.height);
	}

	bool checkCollision(sf::FloatRect entity, bool pickUp = false) {
		if (sprite.getGlobalBounds().intersects(entity) && visible) {
			if (pickUp) {
				visible = false;
			}
			return true;
		}
		return false;
	}

	sf::FloatRect getBounds() {
		return sprite.getGlobalBounds();
	};

	void draw(sf::RenderWindow& window) {
		if (visible) {
			window.draw(sprite);
		}
	};

	void setPosition(sf::FloatRect entity) {
		sprite.setPosition(entity.left, entity.top);
	}
	void setPosition(int x, int y) {
		sprite.setPosition(x, y);
	}

	void setDropped(bool drop = true) {
		visible = drop;
	}
};

/*class ItemHandler {
public:
	std::vector<Key> keys;

	ItemHandler() { };

	ItemHandler(std::vector<Key> keyVector) {
		keys = keyVector;
	};

	bool checkKeyCollisions(sf::FloatRect entity, bool pickUp = false) {
		bool collided = false;
		for (int i = 0; i < keys.size(); i++) {
			if (keys[i].checkCollision(entity, pickUp)) {
				collided = true;
			}
		}
		return collided;
	}

	void draw(sf::RenderWindow& window) {
		for (int i = 0; i < keys.size(); i++) {
			keys[i].draw(window);
		}
	}
};*/

class Wall {
public:
	sf::Sprite sprite;

	Wall() { };

	Wall(sf::Texture& texture, int xPosition, int yPosition, int width, int height) {
		sprite.setPosition(xPosition, yPosition);
		sprite.setTexture(texture);
		sf::FloatRect bounds = sprite.getGlobalBounds();
		sprite.setScale(width / bounds.width, height / bounds.height);
	};

	sf::FloatRect getBounds() {
		return sprite.getGlobalBounds();
	};

	void draw(sf::RenderWindow& window) {
		window.draw(sprite);
	};

	bool checkCollision(sf::FloatRect entity) {
		return sprite.getGlobalBounds().intersects(entity);
	}
};

class Door {
public:
	sf::Sprite sprite;
	bool opened = false;

	Door() { };

	Door(sf::Texture& texture, int xPosition, int yPosition, int width, int height) {
		sprite.setPosition(xPosition, yPosition);
		sprite.setTexture(texture);
		sf::FloatRect bounds = sprite.getGlobalBounds();
		sprite.setScale(width / bounds.width, height / bounds.height);
	};

	sf::FloatRect getBounds() {
		return sprite.getGlobalBounds();
	};

	void draw(sf::RenderWindow& window) {
		window.draw(sprite);
	};

	bool checkCollision(sf::FloatRect entity) {
		return sprite.getGlobalBounds().intersects(entity);
	};

	void setOpen(bool state) {
		opened = state;
	};

	bool isOpened() {
		return opened;
	};
};


class Enemy {
public:
	sf::Sprite sprite;
	int health = 0;
	int speed = 0;
	int strength = 0;
	bool hasKey = false;
	double damageCooldown = 1000;
	double lastDamaged = 0;

	Enemy() { };

	Enemy(sf::Texture texture, int xPosition, int yPosition, int width, int height, int enemySpeed, int maxHealth, int hitStrength, bool key = false) {
		hasKey = key;
		sprite.setPosition(xPosition, yPosition);
		sprite.setTexture(texture);
		sf::FloatRect bounds = sprite.getGlobalBounds();
		sprite.setScale(width / bounds.width, height / bounds.height);
		health = maxHealth;
		speed = enemySpeed;
		strength = hitStrength;
	};

	void draw(sf::RenderWindow& window) {
		if (health > 0) {
			window.draw(sprite);
		}
	};

	bool checkCollision(sf::FloatRect entity) {
		if (health > 0) {
			return sprite.getGlobalBounds().intersects(entity);
		}
		return false;
	};

	void damage(int damage) {
		double timeNow = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		if (lastDamaged + damageCooldown < timeNow) {
			lastDamaged = timeNow;
			health = health - damage;
		}
	};

	bool isDead() {
		return health <= 0;
	};

	bool dropsKey() {
		return hasKey;
	};

	sf::FloatRect getGlobalBounds() {
		return sprite.getGlobalBounds();
	}
};


class Room {
public:
	std::vector<Wall> walls;
	Door door;
	Key key;
	sf::FloatRect bounds = sf::FloatRect(0, 0, 0, 0);
	std::vector<Enemy> enemies = {};

	Room() { };

	Room(sf::Texture& wallTexture, sf::Texture& doorTexture, int xPosition, int yPosition, int width, int height, int wallThickness, Key& keyObject, std::string firstHole, std::string secondHole = "") {
		bounds = sf::FloatRect(xPosition, yPosition, width, height);
		if (firstHole == "Top" || secondHole == "Top") {
			walls.push_back(Wall(wallTexture, xPosition, yPosition, width * 0.3, wallThickness));
			walls.push_back(Wall(wallTexture, xPosition + width * 0.7, yPosition, width * 0.3, wallThickness));
		}
		else {
			walls.push_back(Wall(wallTexture, xPosition, yPosition, width, wallThickness));
		}
		if (firstHole == "Bottom" || secondHole == "Bottom") {
			walls.push_back(Wall(wallTexture, xPosition, yPosition + height - wallThickness, width * 0.3, wallThickness));
			walls.push_back(Wall(wallTexture, xPosition + width * 0.7, yPosition + height - wallThickness, width * 0.3, wallThickness));
		}
		else {
			walls.push_back(Wall(wallTexture, xPosition, yPosition + height - wallThickness, width, wallThickness));
		}


		if (firstHole == "Left" || secondHole == "Left") {
			walls.push_back(Wall(wallTexture, xPosition, yPosition + wallThickness, wallThickness, (height - (2 * wallThickness)) * 0.3));
			walls.push_back(Wall(wallTexture, xPosition, yPosition + wallThickness + (height - (2 * wallThickness)) * 0.7, wallThickness, (height - (2 * wallThickness)) * 0.3));
		}
		else {
			walls.push_back(Wall(wallTexture, xPosition, yPosition + wallThickness, wallThickness, height - (2 * wallThickness)));
		}
		if (firstHole == "Right" || secondHole == "Right") {
			walls.push_back(Wall(wallTexture, xPosition + width - wallThickness, yPosition + wallThickness, wallThickness, (height - (2 * wallThickness)) * 0.3));
			walls.push_back(Wall(wallTexture, xPosition + width - wallThickness, yPosition + wallThickness + (height - (2 * wallThickness)) * 0.7, wallThickness, (height - (2 * wallThickness)) * 0.3));
		}
		else {
			walls.push_back(Wall(wallTexture, xPosition + width - wallThickness, yPosition + wallThickness, wallThickness, height - (2 * wallThickness)));
		}

		if (firstHole == "Top") {
			door = Door(doorTexture, xPosition + width * 0.3, yPosition - wallThickness, width * 0.4, wallThickness * 2);
		}
		else if (firstHole == "Bottom") {
			door = Door(doorTexture, xPosition + width * 0.3, yPosition - wallThickness + height, width * 0.4, wallThickness * 2);
		}
		else if (firstHole == "Left") {
			door = Door(doorTexture, xPosition - wallThickness, yPosition + wallThickness + (height - (2 * wallThickness)) * 0.3, wallThickness * 2, (height - 2 * wallThickness) * 0.4);
		}
		else if (firstHole == "Right") {
			door = Door(doorTexture, xPosition + width - wallThickness, yPosition + wallThickness + (height - (2 * wallThickness)) * 0.3, wallThickness * 2, height * 0.4);
		}
		key = keyObject;
	};

	void draw(sf::RenderWindow& window) {
		for (int i = 0; i < walls.size(); i++) {
			walls[i].draw(window);
		};
		if (!door.isOpened()) {
			door.draw(window);
		}
		else {
			for (int i = 0; i < enemies.size(); i++) {
				enemies[i].draw(window);
			}
		};
		key.draw(window);
	};

	bool checkCollisions(sf::FloatRect entity) {
		for (int i = 0; i < walls.size(); i++) {
			if (walls[i].checkCollision(entity)) {
				return true;
			}
		};
		return false;
	};

	bool checkDoorCollisions(sf::FloatRect entity, bool open = false) {
		if (!door.isOpened() && door.checkCollision(entity)) {
			if (open) {
				door.setOpen(true);
			};
			return true;
		};
		return false;
	}

	bool checkEnemyCollisions(sf::FloatRect entity, int attackDamage = 0) {
		bool collided = false;
		for (int i = 0; i < enemies.size(); i++) {
			if (enemies[i].checkCollision(entity)) {
				if (attackDamage != 0) {
					enemies[i].damage(attackDamage);
					if (enemies[i].dropsKey() && enemies[i].isDead()) {
						key.setPosition(enemies[i].getGlobalBounds());
						key.setDropped();
					}
				}
				collided = true;
			}
		}
		return collided;
	}

	bool checkKeyCollision(sf::FloatRect entity) {
		return key.checkCollision(entity, true);
	}

	sf::FloatRect getBounds() {
		return bounds;
	};

	void setEnemies(std::vector<Enemy>& enemyVector) {
		enemies = enemyVector;
	};
};

class Player {
public:
	sf::Sprite sprite;
	int x = 0;
	int y = 0;
	int speed = 0;
	int width = 0;
	int height = 0;
	int tempY = y;
	int tempX = x;
	int moveX = 0;
	int moveY = 0;
	bool keyPressed = false;
	bool collided = false;
	int keys = 1;

	Player() { };

	Player(sf::Texture& texture, int xPosition, int yPosition, int playerWidth, int playerHeight, int playerSpeed, int maxHealth) {
		x = xPosition;
		y = yPosition;
		width = playerWidth;
		height = playerHeight;
		speed = playerSpeed;
		sprite.setTexture(texture);
		sf::FloatRect bounds = sprite.getGlobalBounds();
		sprite.setScale(width / bounds.width, height / bounds.height);
		sprite.setPosition(x, y);
	};

	void move(std::vector<Room>& rooms, float speedScale) {
		keyPressed = false;
		tempX = x;
		tempY = y;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			moveY--;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			moveY++;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			moveX--;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			moveX++;
		}
		if (moveX != 0) {
			if (moveY != 0) {
				tempX += (sqrt(0.5 * speed * speed) * speedScale * moveX);
			}
			else {
				tempX += (speed * speedScale * moveX);
			};
			collided = false;
			for (int i = 0; i < rooms.size(); i++) {
				if (rooms[i].checkCollisions(sf::FloatRect(tempX, tempY, width, height))) {
					collided = true;
				};
				if (rooms[i].checkDoorCollisions(sf::FloatRect(tempX, tempY, width, height))) {
					collided = true;
					if (keys > 0) {
						rooms[i].checkDoorCollisions(sf::FloatRect(tempX, tempY, width, height), true);
						keys--;
					}
				}
			};
			if (!collided) {
				x = tempX;
				sprite.setPosition(x, y);
			}
			else {
				tempX = x;
			}
		}
		if (moveY != 0) {
			if (moveX != 0) {
				tempY += (sqrt(0.5 * speed * speed) * speedScale * moveY);
			}
			else {
				tempY += (speed * speedScale * moveY);
			};
			collided = false;
			for (int i = 0; i < rooms.size(); i++) {
				if (rooms[i].checkCollisions(sf::FloatRect(tempX, tempY, width, height))) {
					collided = true;
				};
				if (rooms[i].checkDoorCollisions(sf::FloatRect(tempX, tempY, width, height))) {
					collided = true;
					if (keys > 0) {
						rooms[i].checkDoorCollisions(sf::FloatRect(tempX, tempY, width, height), true);
						keys--;
					}
				}
			};
			if (!collided) {
				y = tempY;
				sprite.setPosition(x, y);
			}
		}
		moveX = 0;
		moveY = 0;
	};

	void addKey(int number = 1) {
		keys += number;
	}

	sf::FloatRect getGlobalBounds() {
		return sprite.getGlobalBounds();
	};

	void draw(sf::RenderWindow& window) {
		window.draw(sprite);
	};

	sf::Vector2f getCentre() {
		return(sf::Vector2f(x + width / 2, y + width / 2));
	};

	void attack(std::vector<Room>& rooms) {
		for (int i = 0; i < rooms.size(); i++) {
			rooms[i].checkEnemyCollisions(sprite.getGlobalBounds(), 1);
		}
	}
};

