#include "Cell.h"


Cell::Cell(sf::Vector2f pos, const char* texture, HiddenState state) {
	cell = sf::Sprite(TextureManager::GetTexture(texture));
	cell.setPosition(pos.x, pos.y);
	position = pos;
	this->state = State::HIDE;
	h_state = state;
	l_clickable = true;
	r_clickable = true;
}

Cell::State Cell::getState() {
	return state;
}

Cell::HiddenState Cell::getHiddenState() {
	return h_state;
}

void Cell::setState(State state_change) {
	state = state_change;
}

void Cell::setHiddenState(HiddenState state_change) {
	h_state = state_change;
}

sf::Sprite& Cell::GetCellSprite() {
	return cell;
}

void Cell::SetSprite(const char* texture) {
	cell.setTexture(TextureManager::GetTexture(texture));
	cell.setPosition(position);
}

bool Cell::RevealCell() {
	// If clickable and mine, returns true

	if (l_clickable) {
		if (state == State::HIDE) {
			state = State::REVEAL;
			if (h_state == HiddenState::MINE) {
				SetSprite("mine");
				return true;
			}
			else if (h_state == HiddenState::ONE) {
				SetSprite("number_1");
				return false;
			}
			else if (h_state == HiddenState::TWO) {
				SetSprite("number_2");
				return false;
			}
			else if (h_state == HiddenState::THREE) {
				SetSprite("number_3");
				return false;
			}
			else if (h_state == HiddenState::FOUR) {
				SetSprite("number_4");
				return false;
			}
			else if (h_state == HiddenState::FIVE) {
				SetSprite("number_5");
				return false;
			}
			else if (h_state == HiddenState::SIX) {
				SetSprite("number_6");
				return false;
			}
			else if (h_state == HiddenState::SEVEN) {
				SetSprite("number_7");
				return false;
			}
			else if (h_state == HiddenState::EIGHT) {
				SetSprite("number_8");
				return false;
			}
			else {
				SetSprite("tile_revealed");
				for (unsigned int i = 0; i < GetSurroundCount(); i++)
					GetSurround(i)->RevealCell();
				return false;
			}
		}
	}
	return false;
}

void Cell::SetClickability(bool ans) {
	if (ans== true)
		l_clickable = true;
	else if (ans == false)
		l_clickable = false;
}

void Cell::SetRightClickability(bool ans) {
	if (ans == true)
		r_clickable = true;
	else if (ans == false)
		r_clickable = false;
}

void Cell::ToggleFlag(bool flagged) {
	if (r_clickable) {
		if (state == State::HIDE) {
			l_clickable = false;
			state = State::FLAG;
			SetSprite("flag");
		}
		else if (state == State::FLAG && flagged && h_state == HiddenState::MINE) {
			l_clickable = true;
			state = State::HIDE;
			SetSprite("mine");
		}
		else if (state == State::FLAG) {
			l_clickable = true;
			state = State::HIDE;
			SetSprite("tile_hidden");
		}
	}
}

unsigned int Cell::GetSurroundCount() {
	return next_to.size();
}


void Cell::AddNextTo(Cell* cell) {
	next_to.push_back(cell);
}

Cell* Cell::GetSurround(unsigned int num) {
	return next_to.at(num);
}