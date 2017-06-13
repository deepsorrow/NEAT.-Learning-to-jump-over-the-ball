#pragma once
#include "SFML\Graphics.hpp"
#include <vector>
#include <iostream>

class WindowControl {

public:
	explicit WindowControl();
	auto Step() -> void;
	auto KeyboardEvents() -> void;
	auto GetWindow() -> sf::RenderWindow& { return window; }
	auto IsSimulationSpeededUp() const -> bool const { return TrainingSpeed; }
	
	bool shouldIterationIncrement = true;
	bool isSpeciesVisible = false;
private:
	sf::RenderWindow window;
	sf::Event event;
	bool TrainingSpeed = false;
	

};
