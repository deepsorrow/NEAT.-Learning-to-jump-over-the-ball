#pragma once
#include "SFML\Graphics.hpp"
#include "windowControl.h"

class KeyboardControl{

public:
	KeyboardControl() = default;
	auto Step(sf::RenderWindow &window) -> void;
	auto AdjustFramerate(sf::RenderWindow &window) -> void;
private:
	
};
