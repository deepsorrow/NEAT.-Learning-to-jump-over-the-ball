#include "WindowControl.h"

WindowControl::WindowControl()
{
	window.create(sf::VideoMode(1280, 720, 60), "Neural Network");
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);
}

auto WindowControl::Step() -> void
{
	KeyboardEvents();
}

auto WindowControl::KeyboardEvents() -> void
{
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();

		if (event.type == sf::Event::KeyPressed)
			if (event.key.code == sf::Keyboard::R)
				TrainingSpeed = !TrainingSpeed;

		if (event.type == sf::Event::KeyPressed)
			if (event.key.code == sf::Keyboard::S)
				shouldIterationIncrement = !shouldIterationIncrement;

		if (event.type == sf::Event::KeyPressed)
			if (event.key.code == sf::Keyboard::S)
				isSpeciesVisible = !isSpeciesVisible;
	}

	if (TrainingSpeed)
		window.setFramerateLimit(9999999);
	else
		window.setFramerateLimit(60);
}