#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

class Image {
public:
	sf::Sprite sprite;

	Image() { };

	Image(sf::RenderWindow& window, sf::Texture& texture, float xPosition, float yPosition, float width, float height) {
		sf::Vector2u windowSize = window.getSize();
		sprite.setTexture(texture);
		sprite.setPosition(xPosition * windowSize.x, yPosition * windowSize.y);
		sf::FloatRect bounds = sprite.getLocalBounds();
		sprite.setScale((width * windowSize.x) / bounds.width, (height * windowSize.y) / bounds.height);
	};

	void changeTexture(sf::Texture& texture) {
		sprite.setTexture(texture);
	};

	void draw(sf::RenderWindow& window) {
		window.draw(sprite);
	};
};

class Label {
public:
	sf::Sprite sprite;
	sf::Texture Texture;
	sf::Text text;

	Label() { };

	Label(sf::RenderWindow& window, sf::Texture& texture, std::string message, sf::Font& messageFont, float buttonX, float buttonY, float buttonWidth, float buttonHeight) {
		text.setString(message);
		text.setFont(messageFont);
		text.setCharacterSize(300);

		sf::Vector2u windowSize = window.getSize();
		sprite.setTexture(texture);
		sprite.setPosition(buttonX * windowSize.x, buttonY * windowSize.y);
		sf::FloatRect bounds = sprite.getLocalBounds();
		sprite.setScale((buttonWidth * windowSize.x) / bounds.width, (buttonHeight * windowSize.y) / bounds.height);
		positionText();
	};

	void positionText() {
		sf::FloatRect bounds = sprite.getGlobalBounds();
		sf::FloatRect textBounds = text.getGlobalBounds();
		if (bounds.height / textBounds.height <= bounds.width / textBounds.width) {
			text.setScale((bounds.height / textBounds.height) * 0.90, (bounds.height / textBounds.height) * 0.90);
		}
		else {
			text.setScale((bounds.width / textBounds.width) * 0.90, (bounds.width / textBounds.width) * 0.90);
		}

		textBounds = text.getLocalBounds();
		text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);

		bounds = sprite.getGlobalBounds();
		textBounds = text.getGlobalBounds();
		text.setPosition(bounds.left + (bounds.width / 2), bounds.top + (bounds.height / 2));
	};

	void setText(std::string message) {
		text.setScale(1, 1);
		text.setString(message);
		positionText();
	};

	void draw(sf::RenderWindow& window) {
		window.draw(sprite);
		window.draw(text);
	};
};

class Button {
public:
	bool enabled = false;
	sf::Sprite sprite;
	sf::Text text;
	bool mouseDown = false;

	Button() { };

	Button(sf::RenderWindow& window, sf::Texture& buttonOffTexture, sf::Texture& buttonOnTexture, bool state, std::string message, sf::Font& messageFont, float buttonX, float buttonY, float buttonWidth, float buttonHeight) {
		text.setString(message);
		text.setFont(messageFont);
		text.setCharacterSize(300);
		enabled = state;

		sf::Vector2u windowSize = window.getSize();
		if (enabled) {
			sprite.setTexture(buttonOnTexture);
		}
		else {
			sprite.setTexture(buttonOffTexture);
		}
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

		textBounds = text.getLocalBounds();
		text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);

		bounds = sprite.getGlobalBounds();
		textBounds = text.getGlobalBounds();
		text.setPosition((buttonX * windowSize.x) + (bounds.width / 2), (buttonY * windowSize.y) + (bounds.height / 2));
	};

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

	void updateTexture(sf::Texture& buttonOnTexture, sf::Texture& buttonOffTexture) {
		if (enabled) {
			sprite.setTexture(buttonOnTexture);
		}
		else {
			sprite.setTexture(buttonOffTexture);
		}
	};

	bool getState() {
		return enabled;
	};
};


class Bar {
public:
	sf::Sprite sprite;

	Bar() {};

	Bar(sf::Texture& texture, int xPosition, int yPosition, int width, int height) {
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
		if (mousePosition.x < bounds.left + bounds.width && mousePosition.x > bounds.left &&
			mousePosition.y < bounds.top + bounds.height && mousePosition.y > bounds.top) {
			return true;
		}
		return false;
	}

	sf::FloatRect getBounds() {
		return sprite.getGlobalBounds();
	}
};


class Pointer {
public:
	sf::Sprite sprite;

	Pointer() {};

	Pointer(sf::Texture& texture, int xPosition, int yPosition, int width, int height) {
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
		if (newXPosition < barBounds.left) {
			sprite.setPosition(barBounds.left, sprite.getPosition().y);
		}
		else if (newXPosition > barBounds.left + barBounds.width) {
			sprite.setPosition(barBounds.left + barBounds.width, sprite.getPosition().y);
		}
		else {
			sprite.setPosition(newXPosition, sprite.getPosition().y);
		}
	}
	
	sf::Vector2f getPosition() {
		return sprite.getPosition();
	}

	sf::FloatRect getBounds() {
		return sprite.getGlobalBounds();
	}

	bool inBounds(sf::RenderWindow& window) {
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		sf::FloatRect bounds = sprite.getGlobalBounds();
		if (mousePosition.x < bounds.left + bounds.width && mousePosition.x > bounds.left &&
			mousePosition.y < bounds.top + bounds.height && mousePosition.y > bounds.top) {
			return true;
		}
		return false;
	}
};


class Slider {
private:
	float value = 0;
	Bar sliderBar;
	Pointer sliderPointer;
	bool moving = false;
	float minimumValue = 0;
	float maximumValue = 1;

public:
	Slider() { };

	Slider(sf::RenderWindow& window, sf::Texture& texture, sf::Texture& texture2, float minValue, float maxValue, float initialValue, float sliderX, float sliderY, float sliderWidth, float sliderHeight) {
		minimumValue = minValue;
		maximumValue = maxValue;
		sf::Vector2u windowSize = window.getSize();
		int barX = windowSize.x * (sliderX + 0.070555 * sliderWidth);
		int barY = windowSize.y * (sliderY + 0.212355 * sliderHeight);
		int barWidth = 0.8929 * sliderWidth * windowSize.x;
		int barHeight = 0.1482 * sliderHeight * windowSize.y;
		sliderBar = Bar(texture, barX, barY, barWidth, barHeight);
		if (initialValue < minimumValue) {
			initialValue = minimumValue;
		}
		else if (initialValue > maximumValue) {
			initialValue = maximumValue;
		};
		int pointerWidth = 0.03 * sliderWidth * windowSize.x;
		sliderPointer = Pointer(texture2, barX + barWidth * ((initialValue - minimumValue) / (maximumValue - minimumValue)), barY + barHeight / 2, pointerWidth, pointerWidth);
	};

	void draw(sf::RenderWindow& window) {
		sliderBar.draw(window);
		sliderPointer.draw(window);
	};

	float getValue() {
		sf::FloatRect barBounds = sliderBar.getBounds();
		value = roundf((sliderPointer.getPosition().x - barBounds.left) * 100 / barBounds.width) /100;
		return minimumValue + value * (maximumValue - minimumValue);
	};

	void update(sf::RenderWindow& window) {
		if (sliderPointer.inBounds(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			moving = true;
		};
		if (moving) {
			sliderPointer.movePointer(window, sliderBar.getBounds());
		};
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			moving = false;
		};
	}
};