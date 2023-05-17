#include <SFML/Graphics.hpp>
#include <vector>
#include <SFML/Window/Event.hpp>
#include "TextureManager.h"
#include <vector>
using namespace std;
class Cell 
{
	sf::Vector2f position;
	sf::Sprite cell;
	vector<Cell*> next_to;

	bool l_clickable;
	bool r_clickable;

public:
	// Used to set cell graphic state
	enum class State{ HIDE, REVEAL, FLAG};
	State state;
	State getState();
	void setState(State state_change);
	enum class HiddenState{ EMPTY, MINE, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, FLAG };
	HiddenState h_state;
	HiddenState getHiddenState();
	void setHiddenState(HiddenState state_change);


	Cell(sf::Vector2f pos, const char* texture, HiddenState state);
	sf::Sprite& GetCellSprite();
	Cell* GetSurround(unsigned int num);

	void SetClickability(bool ans);
	void SetRightClickability(bool ans);
	void SetSprite(const char* texture);

	bool RevealCell();
	void ToggleFlag(bool flagged);
	unsigned int GetSurroundCount();
	void AddNextTo(Cell* cell);
};
