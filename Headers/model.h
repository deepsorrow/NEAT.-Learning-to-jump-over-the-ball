#pragma once
#include "environment.h"

namespace Representative {

class Model {
public:
	explicit Model() = default;
	explicit Model(const std::size_t &n, const b2Vec2 &spawn_point, const std::vector<std::vector<float>> &newcoords);
	explicit Model(const std::size_t &n, const b2Vec2 &spawn_point, const std::vector<std::vector<float>> &newcoords, const bool IsItPerfectModel);
	explicit Model(const std::size_t &n, const std::vector<Poly::Polygon> &newPolys) : size(n), polys(newPolys) {}
	auto CreateNewPiece() -> void;
	auto ToBorn() -> void;
	auto AddCoordinates(std::vector<float> &newCoords) -> void;
	auto SetCoordinates(std::vector<std::vector<float>> &newCoords) -> void { coords = newCoords; }
	auto AddColors(std::vector<sf::Color> &newColors) -> void { colors = newColors; }
	auto AddColors() -> void;
	auto AddTransparency(std::vector<sf::Uint8> &newTr) -> void { transparency = newTr; }
	auto AddTransparency() -> void;
	auto SetStartb2Pos(std::vector<b2Vec2> &newPos) -> void { startb2Position = newPos; }
	auto SetStartb2Pos() -> void;
	auto SetRevoluteJointPos(std::vector<b2Vec2> &newJoints) -> void { revoluteJointPositions = newJoints; }
	auto SetRevoluteJointPos() -> void;
	auto SetCategoryBits(std::size_t new_cb) -> void { categoryBit = new_cb; };
	auto SetSpawnPoint(b2Vec2 point) -> void { pointOfSpawn = point; };
	auto SetWorld(b2World *newWorld) ->  void { world = newWorld; }
	auto GetSpawnPoint() const -> b2Vec2 { return pointOfSpawn; }
	std::vector< Poly::Polygon > polys;

private:
	const std::size_t size;
	b2Vec2 pointOfSpawn;
	std::vector< sf::Uint8 > transparency;
	std::vector< b2Vec2 > startb2Position;
	std::vector< b2Vec2 > revoluteJointPositions;
	std::size_t categoryBit = 0x002;
	std::vector< sf::Color > colors;
	std::vector< std::vector<float> > coords;
	b2World *world;
	auto AddPerfectTransparency() -> void;
};

}
