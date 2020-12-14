#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Button {
private:
	bool enabled;
	sf::Sprite sprite;
	sf::Texture disabledTexture;
	sf::Texture enabledTexture;
	sf::Text text;
	bool mouseDown = false;

	bool inBounds(sf::RenderWindow& window) {
		sf::Vector2i position = sf::Mouse::getPosition(window);
		sf::FloatRect bounds = sprite.getGlobalBounds();
		if (position.x < bounds.left || position.x > bounds.left + bounds.width) {
			return false;
		}
		if (position.y < bounds.top || position.y > bounds.top + bounds.height) {
			return false;
		}
		return true;
	};

public:
	Button(sf::RenderWindow& window, sf::Texture& buttonOffTexture, sf::Texture& buttonOnTexture, bool state, std::string message, sf::Font& messageFont, float buttonX, float buttonY, float buttonWidth, float buttonHeight) {
		text.setString(message);
		text.setFont(messageFont);
		text.setCharacterSize(90);
		enabled = state;
		disabledTexture = buttonOffTexture;
		enabledTexture = buttonOnTexture;

		sf::Vector2u windowSize = window.getSize();
		sprite.setTexture(buttonOffTexture);
		sprite.setPosition(buttonX * windowSize.x, buttonY * windowSize.y);
		sf::FloatRect bounds = sprite.getLocalBounds();
		sprite.setScale((buttonWidth * windowSize.x) / bounds.width, (buttonHeight * windowSize.y) / bounds.height);
		sf::FloatRect textBounds = text.getGlobalBounds();
		
		bounds = sprite.getGlobalBounds();
		if (bounds.height / textBounds.height <= bounds.width / textBounds.width) {
			text.setScale((bounds.height / textBounds.height) * 0.90, (bounds.height / textBounds.height) * 0.90);
		}
		else {
			text.setScale((bounds.width / textBounds.width) * 0.90, (bounds.width / textBounds.width) * 0.90);
		}

		textBounds = text.getGlobalBounds();
		text.setPosition((buttonX * windowSize.x) + (bounds.width - textBounds.width) / 2, (buttonY * windowSize.y) + (bounds.height - textBounds.height) / 2);
	};

	bool isPressed(sf::RenderWindow& window) {
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			mouseDown = false;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && inBounds(window) && !mouseDown) {
			mouseDown = true;
			return true;
		}
		else {
			return false;
		}
	};

	void draw(sf::RenderWindow& window) {
		window.draw(sprite);
		window.draw(text);
	};

	void setState(bool state) {
		enabled = state;
	};

	void toggleState() {
		if (enabled) {
			enabled = false;
		}
		else {
			enabled = true;
		}
	};

	void updateTexture() {
		if (enabled) {
			sprite.setTexture(enabledTexture);
		}
		else {
			sprite.setTexture(disabledTexture);
		}

	};
};


class bar {
public:
	sf::Sprite sprite;

	bar() {};
	bar(sf::Texture& texture, int xPosition, int yPosition, int width, int height) {
		sprite.setTexture(texture);
		sf::FloatRect spriteBounds = sprite.getGlobalBounds();
		sprite.setScale(width / spriteBounds.width, height / spriteBounds.height);
		sprite.setPosition(xPosition, yPosition);
	};

	void draw(sf::RenderWindow& window) {
		window.draw(sprite);
	};

	bool inBounds(sf::RenderWindow& window) {
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		sf::FloatRect bounds = sprite.getGlobalBounds();
		if (mousePosition.x < bounds.left + bounds.width && mousePosition.x > bounds.width &&
			mousePosition.y < bounds.top + bounds.height && mousePosition.y > bounds.top) {
			return true;
		}
		return false;
	}

	sf::FloatRect getBounds() {
		return sprite.getGlobalBounds();
	}
};


class pointer {
public:
	sf::Sprite sprite;

	pointer() {};
	pointer(sf::Texture& texture, int xPosition, int yPosition, int width, int height) {
		sprite.setTexture(texture);
		sf::FloatRect spriteBounds = sprite.getGlobalBounds();
		sprite.setScale(width / spriteBounds.width, height / spriteBounds.height);
		sprite.setPosition(xPosition, yPosition);
		sprite.setOrigin(spriteBounds.width / 2, spriteBounds.height / 2);
	};

	void draw(sf::RenderWindow& window) {
		window.draw(sprite);
	};

	void movePointer(sf::RenderWindow& window, sf::FloatRect barBounds) {
		int newXPosition = sf::Mouse::getPosition(window).x;
		if (newXPosition > barBounds.left && newXPosition < barBounds.left + barBounds.width) {
			sprite.setPosition(newXPosition, sprite.getPosition().y);
		}
	}
};


class slider {
private:
	float value;
	bar sliderBar;
	pointer sliderPointer;

public:
	slider(sf::RenderWindow& window, sf::Texture& texture, sf::Texture& texture2, float sliderX, float sliderY, float sliderWidth, float sliderHeight) {
		sf::Vector2u windowSize = window.getSize();
		int barX = windowSize.x * (sliderX + 0.070555 * sliderWidth);
		int barY = windowSize.y * (sliderY + 0.212355 * sliderHeight);
		int barWidth = 0.8929 * sliderWidth * windowSize.x;
		int barHeight = 0.1482 * sliderHeight * windowSize.y;
		sliderBar = bar(texture, barX, barY, barWidth, barHeight);
		int pointerWidth = 0.03 * sliderWidth * windowSize.x;
		sliderPointer = pointer(texture2, barX + barWidth / 2, barY + barHeight / 2, pointerWidth, pointerWidth);
	};

	void draw(sf::RenderWindow& window) {
		update(window);
		sliderBar.draw(window);
		sliderPointer.draw(window);
	};

	void update(sf::RenderWindow& window) {
		if (sliderBar.inBounds(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sliderPointer.movePointer(window, sliderBar.getBounds());
		}
	}
};