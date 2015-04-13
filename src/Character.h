#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
	int _row, _col;
	int _old_row, _old_col;
	bool _redraw, _out_of_bounds;
	char _symbol;
public:
	Character(char symbol, int y, int x);
	void pos(int y, int x);

	void move(int dy, int dx);
	int y();
	int x();

	int oldy();

	int oldx();
	char symbol();

	bool needs_redraw();
	void reset_redraw();
	void set_redraw();

	bool is_visible();
	void set_visible();
	void reset_visible();
};

#endif
