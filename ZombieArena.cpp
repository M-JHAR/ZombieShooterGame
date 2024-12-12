#include "ZombieArena.h"

int createBackground(sf::VertexArray& rVA, sf::IntRect arena)
{
	const int TILE_SIZE = 50;
	const int TILE_TYPES = 3;
	const int VERTS_IN_QUAD = 4;

	int worldWidth = arena.width / TILE_SIZE;
	int worldHeight = arena.height / TILE_SIZE;

	rVA.setPrimitiveType(sf::PrimitiveType::Quads);

	rVA.resize((unsigned)worldWidth * worldHeight * VERTS_IN_QUAD);

	unsigned int currentVertex = 0;
	for (int w = 0; w < worldWidth; w++)
	{
		for (int h = 0; h < worldHeight; h++)
		{
			rVA[currentVertex + 0].position = sf::Vector2f((float)w * TILE_SIZE, (float)h * TILE_SIZE);

			rVA[currentVertex + 1].position = sf::Vector2f((float)w * TILE_SIZE + TILE_SIZE, (float)h * TILE_SIZE);

			rVA[currentVertex + 2].position = sf::Vector2f((float)w * TILE_SIZE + TILE_SIZE, (float)h * TILE_SIZE + TILE_SIZE);

			rVA[currentVertex + 3].position = sf::Vector2f((float)w * TILE_SIZE, (float)h * TILE_SIZE + TILE_SIZE);

			if (h == 0 || h == worldHeight - 1 || w == 0 || w == worldWidth - 1)
			{
				// Use the wall texture
				rVA[currentVertex + 0].texCoords = sf::Vector2f((float)0, 0 + (float)TILE_TYPES * TILE_SIZE);

				rVA[currentVertex + 1].texCoords = sf::Vector2f((float)TILE_SIZE, 0 + (float)TILE_TYPES * TILE_SIZE);

				rVA[currentVertex + 2].texCoords = sf::Vector2f((float)TILE_SIZE, TILE_SIZE + (float)TILE_TYPES * TILE_SIZE);

				rVA[currentVertex + 3].texCoords = sf::Vector2f((float)0, TILE_SIZE + (float)TILE_TYPES * TILE_SIZE);
			}
			else
			{
				srand(unsigned(time(0) + h * w - h));
				int mOrG = (rand() % TILE_TYPES);
				int verticalOffset = mOrG * TILE_SIZE;

				rVA[currentVertex + 0].texCoords = sf::Vector2f(0.0f, 0.0f + verticalOffset);

				rVA[currentVertex + 1].texCoords = sf::Vector2f((float)TILE_SIZE, 0.0f + verticalOffset);

				rVA[currentVertex + 2].texCoords = sf::Vector2f((float)TILE_SIZE, (float)TILE_SIZE + verticalOffset);

				rVA[currentVertex + 3].texCoords = sf::Vector2f(0.0f, (float)TILE_SIZE + verticalOffset);
			}

			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}
	return TILE_SIZE;

}

