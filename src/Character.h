
#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
	int _row, _col;
	int _old_row, _old_col;
	bool _redraw;
	char _symbol;
public:
	// Create a character
	Character(char symbol, int y, int x);
	// Change the character position
	void pos(int y, int x);

	void move(int dy, int dx);
	// Get character's row (y) position
	int y();
	// Get character's col (x) position
	int x();

	int oldy();

	int oldx();
	// Get the symbol of the character
	char symbol();

	bool needs_redraw();
	void reset_redraw();
	void set_redraw();
};

#endif
