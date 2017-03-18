#include "model.h"

Representative::Model::Model(const std::size_t & n, const b2Vec2 & spawn_point, const std::vector<std::vector<float>> &newcoords) :
	size(n), pointOfSpawn(spawn_point), coords(newcoords)
{
	AddColors();
	AddTransparency();
	SetStartb2Pos();
	SetRevoluteJointPos();
}
Representative::Model::Model(const std::size_t & n, const b2Vec2 & spawn_point, const std::vector<std::vector<float>>& newcoords, const bool IsItPerfectModel) :
	size(n), pointOfSpawn(spawn_point), coords(newcoords)
{
	AddColors();
	AddPerfectTransparency();
	SetStartb2Pos();
	SetRevoluteJointPos();
}

auto Representative::Model::CreateNewPiece() -> void
{
	polys.push_back(Poly::Polygon());
	auto currIndex = polys.size()-1;

	polys.back().CreateSfpolygon(coords[currIndex], colors[currIndex], transparency[currIndex]);
	polys.back().CreateB2polygon(world, coords[currIndex], startb2Position[currIndex], static_cast<int>(categoryBit));

	if (polys.size() > 1) {
		auto anchor = polys[currIndex].poly->GetLocalPoint(polys[currIndex-1].poly->GetPosition());
		polys[currIndex - 1].CreateRevJoint(world, polys[currIndex].poly, anchor, b2_pi);
	}
}

auto Representative::Model::ToBorn() -> void
{
	for (std::size_t i = 0; i < size; ++i)
		CreateNewPiece();
}

auto Representative::Model::AddCoordinates(std::vector<float> &newCoords) -> void
{
	coords.push_back(newCoords);
}

auto Representative::Model::AddColors() -> void
{
	colors.push_back(sf::Color(0, 255, 0));
	colors.push_back(sf::Color(0, 0, 255));
	colors.push_back(sf::Color(255, 0, 0));
}

auto Representative::Model::AddTransparency() -> void
{
	for (std::size_t i = 0; i < size; i++) {
		auto tr = 30 - 10 * i;
		transparency.push_back(static_cast<sf::Uint8>(tr));
	}
}

auto Representative::Model::SetStartb2Pos() -> void
{
	auto x0_pos = pointOfSpawn.x;
	auto y0_pos = pointOfSpawn.y;
	startb2Position.push_back(b2Vec2(x0_pos, y0_pos));

	for (std::size_t i = 1; i < size; i++) {
		auto x_pos = startb2Position[i-1].x + coords[i-1][4];
		auto y_pos = startb2Position[i-1].y + coords[i-1][5];
		startb2Position.push_back(b2Vec2(x_pos, y_pos));
	}
}

auto Representative::Model::SetRevoluteJointPos() -> void
{
	for (std::size_t i = 0; i < size; i++) {
		auto x_pos = -coords[i][4];
		auto y_pos = -coords[i][5];
		revoluteJointPositions.push_back(b2Vec2(x_pos, y_pos));
	}
}

auto Representative::Model::AddPerfectTransparency() -> void
{
	for (std::size_t i = 0; i < size; i++) {
		auto tr = 255 - 10 * i;
		transparency.push_back(static_cast<sf::Uint8>(tr));
	}
}
