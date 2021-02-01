#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <chrono>

class HUDTextElement {
public:
	sf::Text text;
	long transitionInTime = 500000;
	long transitionOutTime = 500000;
	long messageVisibleTime = 1500000;
	long timer = 0;
	sf::Vector2i transitionDistance = sf::Vector2i(0, 100);
	sf::Vector2i defaultPosition;
	int state = 0;
	std::vector<std::string> messages;
	std::string currentMessage = "";

	HUDTextElement(std::string message) {
		text.setString(message);
		text.setPosition(0, 0);
		text.setFont(arialRounded);
		text.setCharacterSize(60);
		text.setFillColor(sf::Color::White);
		updateDefaultPosition();
	}

	void updateDefaultPosition() {
		sf::Vector2f viewCentre = window.getView().getCenter();
		sf::Vector2f viewSize = window.getView().getSize();
		sf::FloatRect textBounds = text.getGlobalBounds();
		defaultPosition = sf::Vector2i(viewCentre.x - viewSize.x / 2 + textBounds.width + 50, viewCentre.y + viewSize.y / 2 - textBounds.height - 50);
	}

	void updateText(std::string message) {
		text.setString(message);
	}

	void draw() {
		updateDefaultPosition();
		text.setPosition(defaultPosition.x, defaultPosition.y);
		window.draw(text);
	}
};


class Exit {
public:
	sf::Sprite sprite;

	Exit() { };

	Exit(int xPosition, int yPosition, int width, int height) {
		sprite.setPosition(xPosition, yPosition);
		sprite.setTexture(exitTexture);
		sf::FloatRect bounds = sprite.getGlobalBounds();
		sprite.setScale(width / bounds.width, height / bounds.height);
	}

	bool checkCollision(sf::FloatRect entity) {
		return (sprite.getGlobalBounds().intersects(entity));
	}
	
	void draw() {
		window.draw(sprite);
	}
};

class Message {
public:
	sf::Text text;
	long transitionInTime = 500000;
	long transitionOutTime = 500000;
	long messageVisibleTime = 1500000;
	long timer = 0;
	sf::Vector2i transitionDistance = sf::Vector2i(0, 100);
	sf::Vector2i defaultPosition;
	int state = 0;
	std::vector<std::string> messages;
	std::string currentMessage = "";

	Message() {
		text.setString("DEFAULT STRING");
		text.setPosition(0, 0);
		text.setFont(arialRounded);
		text.setCharacterSize(30);
		text.setFillColor(sf::Color::White);
		updateDefaultPosition();
	}

	void updateDefaultPosition() {
		sf::Vector2f viewCentre = window.getView().getCenter();
		sf::Vector2f viewSize = window.getView().getSize();
		sf::FloatRect textBounds = text.getGlobalBounds();
		defaultPosition = sf::Vector2i(viewCentre.x - textBounds.width / 2, viewCentre.y - viewSize.y / 2 - textBounds.height - 20);
	}

	void draw() {
		updateDefaultPosition();
		if (messages.size() > 0 && currentMessage == "") {
			currentMessage = messages[0];
			text.setString(currentMessage);
			messages.erase(messages.begin());
			timer = 0;
		}
		if (currentMessage != "") {
			if (state == 0) {
				timer += timeForLastFrame;
				text.setPosition(defaultPosition.x, defaultPosition.y + transitionDistance.y * ((float)timer / (float)transitionInTime));
				if (timer >= transitionInTime) {
					state = 1;
					timer = 0;
				}
			}
			if (state == 1) {
				timer += timeForLastFrame;
				text.setPosition(defaultPosition.x, defaultPosition.y + transitionDistance.y);
				if (timer >= messageVisibleTime) {
					state = 2;
					timer = 0;
				}
			}
			if (state == 2) {
				timer += timeForLastFrame;
				text.setPosition(defaultPosition.x, defaultPosition.y + transitionDistance.y * ((float)(transitionInTime - timer) / (float)transitionInTime));
				if (timer >= transitionOutTime) {
					state = 0;
					timer = 0;
					currentMessage = "";
				}
			}
		}
		if (currentMessage == "") {
			text.setPosition(defaultPosition.x, defaultPosition.y);
		}
		window.draw(text);
	}

	void addMessage(std::string text) {
		messages.push_back(text);
	}
};



class Key {
public:
	sf::Sprite sprite;
	bool visible = false;

	Key() { };

	Key(int xPosition, int yPosition, int width, int height, bool isVisible = false) {
		visible = isVisible;
		sprite.setPosition(xPosition, yPosition);
		sprite.setTexture(keyTexture);
		sf::FloatRect bounds = sprite.getGlobalBounds();
		sprite.setScale(width / bounds.width, height / bounds.height);
	};

	bool checkCollision(sf::FloatRect entity, bool pickUp = false) {
		if (sprite.getGlobalBounds().intersects(entity) && visible) {
			if (pickUp) {
				visible = false;
			}
			return true;
		}
		return false;
	};

	sf::FloatRect getBounds() {
		return sprite.getGlobalBounds();
	};

	void draw() {
		if (visible) {
			window.draw(sprite);
		}
	};

	void setPosition(sf::FloatRect entity) {
		sprite.setPosition(entity.left, entity.top);
	};

	void setPosition(int x, int y) {
		sprite.setPosition(x, y);
	};

	void setDropped(bool drop = true) {
		visible = drop;
	};
};

class Wall {
public:
	sf::Sprite sprite;

	Wall() { };

	Wall(int xPosition, int yPosition, int width, int height) {
		sprite.setPosition(xPosition, yPosition);
		sprite.setTexture(wallTexture);
		sf::FloatRect bounds = sprite.getGlobalBounds();
		sprite.setScale(width / bounds.width, height / bounds.height);
	};

	sf::FloatRect getBounds() {
		return sprite.getGlobalBounds();
	};

	void draw() {
		window.draw(sprite);
	};

	bool checkCollision(sf::FloatRect entity) {
		return sprite.getGlobalBounds().intersects(entity);
	};
};

class Obstacle {
public:
	sf::Sprite sprite;

	Obstacle() { };

	Obstacle(int xPosition, int yPosition, int width, int height) {
		sprite.setPosition(xPosition, yPosition);
		sprite.setTexture(wallTexture);
		sf::FloatRect bounds = sprite.getGlobalBounds();
		sprite.setScale(width / bounds.width, height / bounds.height);
	};

	sf::FloatRect getGlobalBounds() {
		return sprite.getGlobalBounds();
	};

	void draw() {
		window.draw(sprite);
	};

	bool checkCollision(sf::FloatRect entity) {
		return sprite.getGlobalBounds().intersects(entity);
	};
};

class Door {
public:
	sf::Sprite sprite;
	bool opened = false;

	Door() { };

	Door(int xPosition, int yPosition, int width, int height) {
		sprite.setPosition(xPosition, yPosition);
		sprite.setTexture(buttonOnTexture);
		sf::FloatRect bounds = sprite.getGlobalBounds();
		sprite.setScale(width / bounds.width, height / bounds.height);
	};

	sf::FloatRect getBounds() {
		return sprite.getGlobalBounds();
	};

	void draw() {
		window.draw(sprite);
	};

	bool checkCollision(sf::FloatRect entity) {
		if (!opened) {
			return sprite.getGlobalBounds().intersects(entity);
		}
		else {
			return false;
		}
	};

	void setOpen(bool state) {
		opened = state;
	};

	bool isOpened() {
		return opened;
	};
};


class VisionProjectile {
public:
	float xChange = 0;
	float yChange = 0;
	float initialX = 0;
	float initialY = 0;
	float x = 0;
	float y = 0;
	sf::RectangleShape shape;

	VisionProjectile() { };

	VisionProjectile(float xPosition, float yPosition, float speed, float angle) {
		initialX = xPosition;
		initialY = yPosition;
		x = xPosition;
		y = yPosition;
		shape.setSize(sf::Vector2f(20, 20));
		yChange = -speed * cos((angle / 180.0) * 3.1415);
		xChange = speed * sin((angle / 180.0) * 3.1415);
	}

	bool update() {
		x += xChange;
		y += yChange;
		shape.setPosition(x, y);
		window.draw(shape);
		return false;
	}

	bool collidedWithPlayer(sf::FloatRect player) {
		return shape.getGlobalBounds().intersects(player);
	}

	bool travelledFurtherThan(int distance) {
		return (abs(sqrt(pow(initialX - x, 2) + pow(initialY - y, 2)) > distance));
	}
};


class Enemy {
public:
	sf::Sprite sprite;
	Key heldKey;
	bool hasKey = false;
	int health = 0;
	float speed = 0;
	int strength = 0;
	float rotation = 0;
	double damageCooldown = 1000000;
	bool onDamageCooldown = false;
	double damageTimer = 0;
	sf::Vector2f playerCoordinates;

	bool searching = false;
	bool playerInSight = false;
	std::vector<VisionProjectile> visionProjectiles;
	int failedSearchAttempts = 0;
	long searchTimer = 0;
	long searchDelay = 500000;
	bool lastMovementOnAxis = true;
	float stoppingDistanceFromTarget = 100;
	float attackingDistance = 150;

	long attackCooldown = 2000000;
	long attackTimer = 0;
	bool attacking = false;

	Enemy() { };

	Enemy(int xPosition, int yPosition, int width, int height, float enemySpeed, int maxHealth, int hitStrength, Key key) {
		heldKey = key;
		hasKey = true;
		defaultConstructor(xPosition, yPosition, width, height, enemySpeed, maxHealth, hitStrength);
	};

	Enemy(int xPosition, int yPosition, int width, int height, int enemySpeed, int maxHealth, int hitStrength) {
		defaultConstructor(xPosition, yPosition, width, height, enemySpeed, maxHealth, hitStrength);
	};

	void defaultConstructor(int xPosition, int yPosition, int width, int height, int enemySpeed, int maxHealth, int hitStrength) {
		sprite.setPosition(xPosition, yPosition);
		sprite.setTexture(enemyAxis);
		sf::FloatRect bounds = sprite.getGlobalBounds();
		sprite.setOrigin(bounds.width / 2, bounds.height / 2);
		sprite.setScale(width / bounds.width, height / bounds.height);
		health = maxHealth;
		speed = enemySpeed;
		strength = hitStrength;
		rotation = rand() % 360;
		
	};

	void searchForPlayer(sf::FloatRect player, std::vector<Wall>& walls, std::vector<Obstacle>& obstacles) {
		sf::Vector2f windowSize = window.getView().getSize();
		sf::Vector2f windowCentre = window.getView().getCenter();
		if (health > 0 && sprite.getGlobalBounds().intersects(sf::FloatRect(windowCentre.x - windowSize.x / 2, windowCentre.y - windowSize.y / 2, windowSize.x, windowSize.y))) {
			if (searchTimer < searchDelay) {
				searchTimer += timeForLastFrame;
				return;
			}
			if (!searching) {
				for (int i = rotation - 70; i <= rotation + 70; i += 5) {
					visionProjectiles.push_back(VisionProjectile(sprite.getPosition().x, sprite.getPosition().y, 20, i));
				}
				searching = true;
			}
			bool foundPlayer = false;
			std::vector<int> toRemove;
			for (int i = 0; i < visionProjectiles.size(); i++) {
				bool collided = false;
				visionProjectiles[i].update();
				if (visionProjectiles[i].collidedWithPlayer(player)) {
					foundPlayer = true;
				}
				else if (visionProjectiles[i].travelledFurtherThan(1000)) {
					toRemove.push_back(i);
					continue;
				}
				for (int j = 0; j < obstacles.size(); j++) {
					if (obstacles[j].checkCollision(visionProjectiles[i].shape.getGlobalBounds())) {
						toRemove.push_back(i);
						break;
					}
				}
				if (collided) {
					continue;
				}
				for (int j = 0; j < walls.size(); j++) {
					if (walls[j].checkCollision(visionProjectiles[i].shape.getGlobalBounds())) {
						toRemove.push_back(i);
						break;
					}
				}
			}
			if (foundPlayer) {
				visionProjectiles = {};
			}
			else {
				
				for (int i = toRemove.size(); i > 0; i--) {
					visionProjectiles.erase(visionProjectiles.begin() + toRemove[i - 1]);
				}
			}
			toRemove = {};
			if (visionProjectiles.size() == 0) {
				playerInSight = foundPlayer;
				searching = false;
				if (!foundPlayer) {
					failedSearchAttempts++;
				}
				searchTimer = 0;
			}
		}
	}

	float distanceFrom(sf::Vector2f position) {
		return (abs(sqrt(pow(sprite.getPosition().x - position.x, 2) + pow(sprite.getPosition().y - position.y, 2))));
	}

	void move(float speedScale, sf::Vector2f playerPosition, std::vector<Wall>& walls, std::vector<Obstacle>& obstacles) {
		if (health > 0) {
			if (failedSearchAttempts > 2) {
				rotation += rand() % 150 + 30;
				failedSearchAttempts = 0;
			}
			if (playerInSight && distanceFrom(playerPosition) > stoppingDistanceFromTarget) {
				float tanValue = atan2(playerPosition.y - sprite.getPosition().y, playerPosition.x - sprite.getPosition().x) / 3.1415 * 180 + 90;
				rotation = tanValue;

				if (!onDamageCooldown) {
					sf::Vector2f oldPosition = sprite.getPosition();
					sprite.setPosition(oldPosition.x + speed * speedScale * sin((tanValue / 180) * 3.1415), oldPosition.y);
					bool collided = false;
					for (int i = 0; i < walls.size(); i++) {
						if (walls[i].checkCollision(sprite.getGlobalBounds())) {
							collided = true;
							break;
						}
					}
					if (!collided) {
						for (int i = 0; i < obstacles.size(); i++) {
							if (obstacles[i].checkCollision(sprite.getGlobalBounds())) {
								collided = true;
								break;
							}
						}
					}
					if (collided) {
						sprite.setPosition(oldPosition);
					}

					oldPosition = sprite.getPosition();
					sprite.setPosition(oldPosition.x, oldPosition.y - speed * speedScale * cos((tanValue / 180.0) * 3.1415));
					collided = false;
					for (int i = 0; i < walls.size(); i++) {
						if (walls[i].checkCollision(sprite.getGlobalBounds())) {
							collided = true;
							break;
						}
					}
					if (!collided) {
						for (int i = 0; i < obstacles.size(); i++) {
							if (obstacles[i].checkCollision(sprite.getGlobalBounds())) {
								collided = true;
								break;
							}
						}
					}
					if (collided) {
						sprite.setPosition(oldPosition);
					}
				}
			}

			if (onDamageCooldown) {
				if (damageTimer > 0) {
					damageTimer -= timeForLastFrame;
				}
				if (damageTimer < 0) {
					onDamageCooldown = false;
					int a = ((int)rotation / 45) * 45;
					int b = a + 45;
					int roundedRotation = (rotation - a > b - rotation) ? b : a;
					if (roundedRotation % 2 == 0) {
						sprite.setTexture(enemyAxis);
					}
					else {
						sprite.setTexture(enemyDiagonal);
					}
				}
			}
			else {
				int a = ((int)rotation / 45) * 45;
				int b = a + 45;
				int roundedRotation = (rotation - a > b - rotation) ? b : a;
				if (roundedRotation % 2 == 0) {
					if (!lastMovementOnAxis) {
						sprite.setTexture(enemyAxis);
						lastMovementOnAxis = true;
					}
					sprite.setRotation(roundedRotation);
				}
				else {
					if (lastMovementOnAxis) {
						sprite.setTexture(enemyDiagonal);
						lastMovementOnAxis = false;
					}
					sprite.setRotation(roundedRotation - 45);
				}
			}
		}
	}

	bool inRangeOf(sf::Vector2f position) {
		float distance = distanceFrom(position);
		return (distance <= attackingDistance);
	}

	int attackPlayer(sf::Vector2f position) {
		if (attackTimer < attackCooldown && attacking) {
			attackTimer += timeForLastFrame;
		}
		if (inRangeOf(position)) {
			attacking = true;
			if (attackTimer >= attackCooldown && playerInSight && !onDamageCooldown) {
				attackTimer = 0;
				return strength;
			}
		}
		else {
			attacking = false;
		}
		return 0;
	}

	void draw() {
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
		if (!onDamageCooldown) {
			health -= damage;
			onDamageCooldown = true;
			damageTimer = damageCooldown;
			sprite.setTexture(redTexture);
			playerInSight = true;
			failedSearchAttempts = -3;
		}

	};

	bool isDead() {
		return health <= 0;
	};

	bool droppingKey() {
		return (hasKey && isDead());
	};

	Key dropKey() {
		heldKey.setPosition(getGlobalBounds());
		heldKey.setDropped(true);
		return heldKey;
	};

	sf::FloatRect getGlobalBounds() {
		return sprite.getGlobalBounds();
	};
};


class Room {
public:
	std::vector<Wall> walls;
	Door door;
	Key key;
	sf::FloatRect bounds = sf::FloatRect(0, 0, 0, 0);
	std::vector<Enemy> enemies = {};
	std::vector<Obstacle> obstacles = {};

	Room() { };

	Room(int xPosition, int yPosition, int width, int height, int wallThickness, std::string firstHole, std::string secondHole = "", std::string thirdHole = "") {
		bounds = sf::FloatRect(xPosition, yPosition, width, height);
		if (firstHole == "Top" || secondHole == "Top" || thirdHole == "Top") {
			walls.push_back(Wall(xPosition, yPosition, width * 0.3, wallThickness));
			walls.push_back(Wall(xPosition + width * 0.7, yPosition, width * 0.3, wallThickness));
		}
		else {
			walls.push_back(Wall(xPosition, yPosition, width, wallThickness));
		}
		if (firstHole == "Bottom" || secondHole == "Bottom" || thirdHole == "Bottom") {
			walls.push_back(Wall(xPosition, yPosition + height - wallThickness, width * 0.3, wallThickness));
			walls.push_back(Wall(xPosition + width * 0.7, yPosition + height - wallThickness, width * 0.3, wallThickness));
		}
		else {
			walls.push_back(Wall(xPosition, yPosition + height - wallThickness, width, wallThickness));
		}


		if (firstHole == "Left" || secondHole == "Left" || thirdHole == "Left") {
			walls.push_back(Wall(xPosition, yPosition + wallThickness, wallThickness, (height - (2 * wallThickness)) * 0.3));
			walls.push_back(Wall(xPosition, yPosition + wallThickness + (height - (2 * wallThickness)) * 0.7, wallThickness, (height - (2 * wallThickness)) * 0.3));
		}
		else {
			walls.push_back(Wall(xPosition, yPosition + wallThickness, wallThickness, height - (2 * wallThickness)));
		}
		if (firstHole == "Right" || secondHole == "Right" || thirdHole == "Right") {
			walls.push_back(Wall(xPosition + width - wallThickness, yPosition + wallThickness, wallThickness, (height - (2 * wallThickness)) * 0.3));
			walls.push_back(Wall(xPosition + width - wallThickness, yPosition + wallThickness + (height - (2 * wallThickness)) * 0.7, wallThickness, (height - (2 * wallThickness)) * 0.3));
		}
		else {
			walls.push_back(Wall(xPosition + width - wallThickness, yPosition + wallThickness, wallThickness, height - (2 * wallThickness)));
		}

		if (firstHole == "Top") {
			door = Door(xPosition + width * 0.3, yPosition - wallThickness, width * 0.4, wallThickness * 2);
		}
		else if (firstHole == "Bottom") {
			door = Door(xPosition + width * 0.3, yPosition - wallThickness + height, width * 0.4, wallThickness * 2);
		}
		else if (firstHole == "Left") {
			door = Door(xPosition - wallThickness, yPosition + wallThickness + (height - (2 * wallThickness)) * 0.3, wallThickness * 2, (height - 2 * wallThickness) * 0.4);
		}
		else if (firstHole == "Right") {
			door = Door(xPosition + width - wallThickness, yPosition + wallThickness + (height - (2 * wallThickness)) * 0.3, wallThickness * 2, height * 0.4);
		}
	};

	void draw() {
		for (int i = 0; i < walls.size(); i++) {
			walls[i].draw();
		};
		for (int i = 0; i < obstacles.size(); i++) {
			obstacles[i].draw();
		};
		if (!door.isOpened()) {
			door.draw();
		}
		else {
			for (int i = 0; i < enemies.size(); i++) {
				enemies[i].draw();
			}
		};
		key.draw();
	};

	bool checkCollisions(sf::FloatRect entity) {
		for (int i = 0; i < walls.size(); i++) {
			if (walls[i].checkCollision(entity)) {
				return true;
			}
		};
		for (int i = 0; i < obstacles.size(); i++) {
			if (obstacles[i].checkCollision(entity)) {
				return true;
			}
		};
		return false;
	};

	bool checkDoorCollisions(sf::FloatRect entity, bool open = false) {
		if (door.checkCollision(entity)) {
			if (open) {
				door.setOpen(true);
			};
			return true;
		};
		return false;
	};

	void attackEnemies(sf::FloatRect entity, int attackDamage = 0) {
		for (int i = 0; i < enemies.size(); i++) {
			if (enemies[i].checkCollision(entity) && attackDamage != 0) {
				enemies[i].damage(attackDamage);
				if (enemies[i].droppingKey()) {
					key = enemies[i].dropKey();
				}
			}
		}
	};

	bool checkKeyCollision(sf::FloatRect entity) {
		return key.checkCollision(entity, true);
	};

	sf::FloatRect getBounds() {
		return bounds;
	};

	bool addEnemy(Enemy enemy) {
		for (int i = 0; i < obstacles.size(); i++) {
			if (enemy.checkCollision(obstacles[i].getGlobalBounds())) {
				return false;
			}
		}
		enemies.push_back(enemy);
		return true;
	};

	bool addObstacle(Obstacle obstacle) {
		obstacles.push_back(obstacle);
		return true;
	};
};

class Player {
public:
	sf::Sprite sprite;
	sf::Sprite attackArea;
	int health = 0;
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
	bool lastMovementOnAxis = true;
	long attackCooldown = 500000;
	long attackEffectVisible = 80000;
	long attackTimer = attackEffectVisible;

	Player() { };

	Player(sf::Texture& texture, int xPosition, int yPosition, int playerWidth, int playerHeight, int playerSpeed, int maxHealth) {
		health = maxHealth;
		x = xPosition;
		y = yPosition;
		width = playerWidth;
		height = playerHeight;
		speed = playerSpeed;
		sprite.setTexture(playerAxis);
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
		sf::FloatRect bounds = sprite.getGlobalBounds();
		sprite.setScale(width / bounds.width, height / bounds.height);
		sprite.setPosition(x, y);

		attackArea.setTexture(playerAttackArea);
		bounds = attackArea.getGlobalBounds();
		attackArea.setOrigin(bounds.width / 2, bounds.height);
		attackArea.setScale((width + 80) / bounds.width, 100 / bounds.height);
		attackArea.setPosition(x, y);
	};

	void move(std::vector<Room>& rooms, float speedScale) {
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
				if (lastMovementOnAxis) {
					sprite.setTexture(playerDiagonal);
					lastMovementOnAxis = false;
				}
			}
			else {
				tempX += (speed * speedScale * moveX);
				if (!lastMovementOnAxis) {
					sprite.setTexture(playerAxis);
					lastMovementOnAxis = true;
				}
				if (moveX == 1) {
					sprite.setRotation(90);
					attackArea.setRotation(90);
				}
				else {
					sprite.setRotation(270);
					attackArea.setRotation(270);
				}
			};
			collided = false;
			for (int i = 0; i < rooms.size(); i++) {
				if (rooms[i].checkCollisions(sf::FloatRect(tempX - width / 2, tempY - height / 2, width, height))) {
					collided = true;
				};
				if (rooms[i].checkDoorCollisions(sf::FloatRect(tempX - width / 2, tempY - height / 2, width, height), keys > 0)) {
					if (keys > 0) {
						keys--;
					}
					collided = true;
				}
			};
			if (!collided) {
				x = tempX;
				sprite.setPosition(x, y);
				attackArea.setPosition(x, y);
			}
			else {
				tempX = x;
			}
		}
		if (moveY != 0) {
			if (moveX != 0) {
				tempY += (sqrt(0.5 * speed * speed) * speedScale * moveY);
				if (moveY == -1 && moveX == 1) {
					sprite.setRotation(0);
					attackArea.setRotation(45);
				}
				else if (moveY == 1 && moveX == 1) {
					sprite.setRotation(90);
					attackArea.setRotation(135);
				}
				else if (moveY == 1 && moveX == -1) {
					sprite.setRotation(180);
					attackArea.setRotation(225);
				}
				else if (moveY == -1 && moveX == -1) {
					sprite.setRotation(270);
					attackArea.setRotation(315);
				}
			}
			else {
				tempY += (speed * speedScale * moveY);
				if (!lastMovementOnAxis) {
					sprite.setTexture(playerAxis);
					lastMovementOnAxis = true;
				}
				if (moveY == 1) {
					sprite.setRotation(180);
					attackArea.setRotation(180);
				}
				else {
					sprite.setRotation(0);
					attackArea.setRotation(0);
				}
			};
			
			collided = false;
			for (int i = 0; i < rooms.size(); i++) {
				if (rooms[i].checkCollisions(sf::FloatRect(tempX - width / 2, tempY - height / 2, width, height))) {
					collided = true;
				};
				if (rooms[i].checkDoorCollisions(sf::FloatRect(tempX - width / 2, tempY - height / 2, width, height), keys > 0)) {
					if (keys > 0) {
						keys--;
					}
					collided = true;
				}
			};
			if (!collided) {
				y = tempY;
				sprite.setPosition(x, y);
				attackArea.setPosition(x, y);
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

	void draw() {
		window.draw(sprite);
		if (attackTimer < attackEffectVisible) {
			window.draw(attackArea);
		}
	};

	sf::Vector2f getCentre() {
		return(sf::Vector2f(x + width / 2, y + width / 2));
	};

	void attack(std::vector<Room>& rooms) {
		if (attackTimer < attackCooldown) {
			attackTimer += timeForLastFrame;
		}
		else {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				attackTimer = 0;
				for (int i = 0; i < rooms.size(); i++) {
					rooms[i].attackEnemies(attackArea.getGlobalBounds(), 4);
				}
			}
		}
	};

	bool pickUpKeys(std::vector<Room>& rooms) {
		int keysPickedUp = 0;
		for (int i = 0; i < rooms.size(); i++) {
			if (rooms[i].checkKeyCollision(getGlobalBounds())) {
				keysPickedUp++;
			}
		};
		addKey(keysPickedUp);
		return (keysPickedUp > 0);
	};

	void takeDamage(int damage) {
		health -= damage;
	}

	bool isDead() {
		return health <= 0;
	}
};

