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

class RadialButtons {
private:
	
public:
	RadialButtons(int number) {
		Button buttonArray[number];
	};
};