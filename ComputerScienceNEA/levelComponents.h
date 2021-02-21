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
	float x = 0;
	float y = 0;

	HUDTextElement(std::string message, float xPosition, float yPosition) {
		x = xPosition;
		y = yPosition;
		text.setString(message);
		text.setPosition(0, 0);
		text.setFont(arialRounded);
		text.setCharacterSize(60);
		text.setFillColor(sf::Color::Black);
		updateDefaultPosition();
	}

	void updateDefaultPosition() {
		sf::Vector2f viewCentre = window.getView().getCenter();
		sf::Vector2f viewSize = window.getView().getSize();
		sf::FloatRect textBounds = text.getGlobalBounds();
		defaultPosition = sf::Vector2i(viewCentre.x + viewSize.x * (x - 0.5), viewCentre.y + viewSize.y * (y - 0.5));
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
		text.setFillColor(sf::Color::Black);
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
		sprite.setTexture(obstacleTexture);
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

class Projectile {
public:
	float xChange = 0;
	float yChange = 0;
	float initialX = 0;
	float initialY = 0;
	float x = 0;
	float y = 0;
	sf::RectangleShape shape;

	Projectile() { };

	Projectile(float xPosition, float yPosition, float speed, float angle, int size = 20) {
		initialX = xPosition;
		initialY = yPosition;
		x = xPosition;
		y = yPosition;
		shape.setSize(sf::Vector2f(size, size));
		shape.setFillColor(sf::Color::Black);
		yChange = -speed * cos((angle / 180.0) * 3.1415);
		xChange = speed * sin((angle / 180.0) * 3.1415);
	}

	bool update() {
		float deltaTime = ((float)timeForLastFrame / 1000000);
		x += xChange * deltaTime;
		y += yChange * deltaTime;
		shape.setPosition(x, y);
		return false;
	}

	void draw() {
		window.draw(shape);
	}

	bool collidedWithEntity(sf::FloatRect player) {
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
	std::vector<Projectile> visionProjectiles;
	std::vector<Projectile> damageProjectiles;
	int failedSearchAttempts = 0;
	long searchTimer = 0;
	long searchDelay = 500000;
	bool lastMovementOnAxis = true;
	float stoppingDistanceFromTarget = 100;
	float attackingDistance = 150;
	sf::Vector2f lastKnownPlayerPosition;

	long attackCooldown = 2000000;
	long attackTimer = 0;
	bool attacking = false;
	int spriteNumber = 0;
	int currentSpriteNumber = 0;
	long attackEffectDuration = 400000;
	long attackEffectTimer = attackEffectDuration + 1;
	int roundedRotation = 0;

	bool rangedEnemy = true;
	long rangedAttackCooldown = 2000000;
	long rangedAttackTimer = 0;


	Enemy() { };

	Enemy(int xPosition, int yPosition, int width, int height, float enemySpeed, int maxHealth, int hitStrength, Key key, bool ranged = false) {
		rangedEnemy = ranged;
		heldKey = key;
		hasKey = true;
		defaultConstructor(xPosition, yPosition, width, height, enemySpeed, maxHealth, hitStrength);
	};

	Enemy(int xPosition, int yPosition, int width, int height, int enemySpeed, int maxHealth, int hitStrength, bool ranged = false) {
		rangedEnemy = ranged;
		defaultConstructor(xPosition, yPosition, width, height, enemySpeed, maxHealth, hitStrength);
	};

	void defaultConstructor(int xPosition, int yPosition, int width, int height, int enemySpeed, int maxHealth, int hitStrength) {
		attackingDistance = (rangedEnemy) ? 500 : 150;
		stoppingDistanceFromTarget = (rangedEnemy) ? 350 : 100;
		sprite.setPosition(xPosition, yPosition);
		lastKnownPlayerPosition = sf::Vector2f(xPosition, yPosition);
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
					visionProjectiles.push_back(Projectile(sprite.getPosition().x, sprite.getPosition().y, 1000, i));
				}
				searching = true;
			}
			bool foundPlayer = false;
			std::vector<int> toRemove;
			for (int i = 0; i < visionProjectiles.size(); i++) {
				bool collided = false;
				visionProjectiles[i].update();
				/*
				visionProjectiles[i].draw();
				*/
				if (visionProjectiles[i].collidedWithEntity(player)) {
					foundPlayer = true;
					lastKnownPlayerPosition = visionProjectiles[i].shape.getPosition();
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

	void move(float speedScale, sf::Vector2f playerPosition, std::vector<Wall>& walls, std::vector<Obstacle>& obstacles, bool movingEnabled = true) {
		if (health > 0) {
			if (failedSearchAttempts > 2) {
				rotation += rand() % 150 + 30;
				failedSearchAttempts = 0;
			}
			float tanValue;
			bool move = false;
			if (playerInSight && distanceFrom(playerPosition) > stoppingDistanceFromTarget) {
				tanValue = atan2(playerPosition.y - sprite.getPosition().y, playerPosition.x - sprite.getPosition().x) / 3.1415 * 180 + 90;
				rotation = tanValue;
				move = true;
			}
			if (!playerInSight && distanceFrom(lastKnownPlayerPosition) > 10) {
				tanValue = atan2(lastKnownPlayerPosition.y - sprite.getPosition().y, lastKnownPlayerPosition.x - sprite.getPosition().x) / 3.1415 * 180 + 90;
				rotation = tanValue;
				move = true;
			}
			if (move && movingEnabled) {
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
				if (damageTimer < damageCooldown) {
					damageTimer += timeForLastFrame;
				}
				if (damageTimer > damageCooldown) {
					onDamageCooldown = false;
				}
			}

			int lower = ((int)rotation / 45) * 45;
			int higher = lower + 45;
			roundedRotation = (rotation - lower > higher - rotation) ? higher : lower;
			if (roundedRotation % 2 == 0) {
				if (!lastMovementOnAxis) {
					lastMovementOnAxis = true;
					spriteNumber--;
				}
				sprite.setRotation(roundedRotation);
			}
			else {
				if (lastMovementOnAxis) {
					lastMovementOnAxis = false;
					spriteNumber++;
				}
				sprite.setRotation(roundedRotation - 45);
			}

			if (spriteNumber != currentSpriteNumber) {
				switch (spriteNumber) {
				case 0:
					sprite.setTexture(enemyAxis);
					break;
				case 1:
					sprite.setTexture(enemyDiagonal);
					break; 
				case 2:
					sprite.setTexture(enemyAttackingAxis);
					break;
				case 3:
					sprite.setTexture(enemyAttackingDiagonal);
					break;
				case 4:
					sprite.setTexture(enemyAttackedAxis);
					break;
				case 5:
					sprite.setTexture(enemyAttackedDiagonal);
					break;
				case 6:
					sprite.setTexture(enemyDamageCooldownAxis);
					break;
				case 7:
					sprite.setTexture(enemyDamageCooldownDiagonal);
					break;
				default:
					sprite.setTexture(redTexture);
					break;
				}
				currentSpriteNumber = spriteNumber;
			}
		}
	}

	bool inRangeOf(sf::Vector2f position) {
		float distance = distanceFrom(position);
		return (distance <= attackingDistance);
	}

	int attackPlayer(sf::Vector2f position, sf::FloatRect playerBounds, std::vector<Wall>& walls, std::vector<Obstacle>& obstacles) {
		if (attackTimer < attackCooldown && attacking) {
			attackTimer += timeForLastFrame;
		}
		if (attackEffectTimer <= attackEffectDuration) {
			attackEffectTimer += timeForLastFrame;
		}
		if (rangedAttackTimer < rangedAttackCooldown) {
			rangedAttackTimer += timeForLastFrame;
		}
		if (inRangeOf(position)) {
			if (rangedEnemy) {
				attacking = true;
				if (playerInSight && !onDamageCooldown) {
					if (roundedRotation % 2 == 0) {
						spriteNumber = 2;
					}
					else {
						spriteNumber = 3;
					}
					if (rangedAttackTimer >= rangedAttackCooldown) {
						rangedAttackTimer = 0;
						sf::Vector2f pos = sprite.getPosition();
						float angle = atan2(position.y - pos.y, position.x - pos.x) / 3.1415 * 180 + 90;
						damageProjectiles.push_back(Projectile(pos.x, pos.y, 1000, angle, 20));
					}
				}
			}
			else {
				attacking = true;
				if (playerInSight && !onDamageCooldown) {
					if (roundedRotation % 2 == 0) {
						spriteNumber = 2;
					}
					else {
						spriteNumber = 3;
					}
					if (attackTimer >= attackCooldown) {
						attackEffectTimer = 0;
						attackTimer = 0;
						return strength;
					}
				}
			}
		}
		else {
			if (!onDamageCooldown) {
				if (roundedRotation % 2 == 0) {
					spriteNumber = 0;
				}
				else {
					spriteNumber = 1;
				}
			}
			attackTimer = 0;
			attacking = false;
		}
		if (attackEffectTimer < attackEffectDuration && !onDamageCooldown) {
			if (roundedRotation % 2 == 0) {
				spriteNumber = 4;
			}
			else {
				spriteNumber = 5;
			}
		}
		int damage = 0;
		std::vector<int> toRemove = {};
		for (int i = 0; i < damageProjectiles.size(); i++) {
			bool hitSomething = false;
			damageProjectiles[i].update();
			damageProjectiles[i].draw();
			if (damageProjectiles[i].collidedWithEntity(playerBounds)) {
				damage += strength;
				toRemove.push_back(i);
				hitSomething = true;
			}
			if (hitSomething) {
				continue;
			}
			for (int j = 0; j < walls.size(); j++) {
				if (walls[j].checkCollision(damageProjectiles[i].shape.getGlobalBounds())) {
					toRemove.push_back(i);
					hitSomething = true;
					break;
				}
			}
			if (hitSomething) {
				continue;
			}
			for (int j = 0; j < obstacles.size(); j++) {
				if (obstacles[j].checkCollision(damageProjectiles[i].shape.getGlobalBounds())) {
					toRemove.push_back(i);
					hitSomething = true;
					break;
				}
			}
			if (damageProjectiles[i].travelledFurtherThan(1000) && !hitSomething) {
				toRemove.push_back(i);
			}
		}
		for (int i = toRemove.size() - 1; i >= 0; i--) {
			damageProjectiles.erase(damageProjectiles.begin() + toRemove[i]);
		}
		return damage;
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
			attackTimer = 0;
			rangedAttackTimer = 0;
			health -= damage;
			onDamageCooldown = true;
			damageTimer = 0;
			if (roundedRotation % 2 == 0) {
				spriteNumber = 6;
			}
			else {
				spriteNumber = 7;
			}
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
	int enemiesKilledInLastAttack = 0;

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

	sf::FloatRect getViewBounds() {
		sf::Vector2f viewSize = window.getView().getSize();
		sf::Vector2f viewCentre = window.getView().getCenter();
		return sf::FloatRect(viewCentre.x - viewSize.x / 2, viewCentre.y - viewSize.y / 2, viewSize.x, viewSize.y);
	}

	void draw() {
		if (bounds.intersects(getViewBounds())) {
			for (int i = 0; i < walls.size(); i++) {
				walls[i].draw();
			};
			for (int i = 0; i < obstacles.size(); i++) {
				obstacles[i].draw();
			};
			key.draw();
		}
		if (!door.isOpened()) {
			door.draw();
		}
		else {
			for (int i = 0; i < enemies.size(); i++) {
				enemies[i].draw();
			}
		};
	};

	bool checkCollisions(sf::FloatRect entity) {
		if (bounds.intersects(getViewBounds())) {
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
		}
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

	int attackEnemies(sf::FloatRect entity, int attackDamage = 0) {
		int hitEnemy = false;
		if (bounds.intersects(getViewBounds())) {
			for (int i = 0; i < enemies.size(); i++) {
				if (enemies[i].checkCollision(entity) && attackDamage != 0) {
					hitEnemy = true;
					enemies[i].damage(attackDamage);
					if (enemies[i].isDead()) {
						enemiesKilledInLastAttack++;
					}
					if (enemies[i].droppingKey()) {
						key = enemies[i].dropKey();
					}
				}
			}
		}
		return hitEnemy;
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
	int maximumHealth = 0;
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
	long attackCooldown = 1000000;
	long attackEffectVisible = 80000;
	long attackTimer = attackEffectVisible;
	long rangedAttackCooldown = 2000000;
	long rangedAttackTimer = 0;
	std::vector<Projectile> projectiles;
	int ammo;
	int doorsOpened;
	float meleeDamage;
	float rangedDamage;

	Player() { };

	Player(int xPosition, int yPosition, int playerWidth, int playerHeight, int playerSpeed, int maxHealth, int startingAmmo, 
		float meleeAttackDamage, long meleeAttackCooldown, float rangedAttackDamage, long rangedAttackCooldown) {
		ammo = startingAmmo;
		maximumHealth = maxHealth;
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
		for (int i = 0; i < projectiles.size(); i++) {
			projectiles[i].draw();
		}
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
		if (rangedAttackTimer < rangedAttackCooldown) {
			rangedAttackTimer += timeForLastFrame;
		}
		else {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && ammo > 0) {
				ammo--;
				rangedAttackTimer = 0;
				sf::Vector2i mp = sf::Mouse::getPosition(window);
				sf::Vector2f view = window.getView().getSize();
				float angle = atan2(mp.y - view.y / 2, mp.x - view.x / 2) / 3.1415 * 180 + 90;
				projectiles.push_back(Projectile(x, y, 1000, angle, 20));
			}
		}
		std::vector<int> toRemove = {};
		for (int i = 0; i < projectiles.size(); i++) {
			projectiles[i].update();
			bool hitSomething = false;
			for (int j = 0; j < rooms.size(); j++) {
				if (rooms[j].attackEnemies(projectiles[i].shape.getGlobalBounds(), 10)) {
					hitSomething = true;
				}
				else if (rooms[j].checkCollisions(projectiles[i].shape.getGlobalBounds())) {
					hitSomething = true;
				}
				else if (rooms[j].checkDoorCollisions(projectiles[i].shape.getGlobalBounds())) {
					hitSomething = true;
				}
			}
			if (projectiles[i].travelledFurtherThan(1000) || hitSomething) {
				toRemove.push_back(i);
			}
		}
		for (int i = toRemove.size() - 1; i >= 0; i--) {
			projectiles.erase(projectiles.begin() + toRemove[i]);
		}
	};

	int tallyDead(std::vector<Room>& rooms) {
		int total = 0;
		for (int i = 0; i < rooms.size(); i++) {
			total += rooms[i].enemiesKilledInLastAttack;
			rooms[i].enemiesKilledInLastAttack = 0;
		}
		return total;
	}

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

	void pickUpAmmo(int amount) {
		ammo += amount;
	}

	void pickUpHealth(int amount) {
		if (!(health + amount > maximumHealth)) {
			health += amount;
		}
	}

	int getAmmoCount() {
		return ammo;
	}

	int getHealth() {
		return health;
	}

	int updateDoorsOpened(std::vector<Room>& rooms) {
		// Returns how many new doors are opened
		int total = 0;
		for (Room room : rooms) {
			if (room.door.isOpened()) {
				total++;
			}
		}
		int oldDoorsOpened = doorsOpened;
		doorsOpened = total;
		return total - oldDoorsOpened;
	}

	int getDoorsOpened() {
		return doorsOpened;
	}
};

