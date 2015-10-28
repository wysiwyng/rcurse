/**
 * An abstract curses window to use in rcurse
 *
 * @author wysiwyng
 */

#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

#include <curses.h>
namespace rcurse {
class GameWindow {
protected:
	/**
	 * the height of this window
	 */
	int _height;

	/**
	 * the width of this window
	 */
	int _width;

	/**
	 * the y coordinate of the top left corner
	 */
	int _row;

	/**
	 * the x coordinate of the top left corner
	 */
	int _col;

	/**
	 * set if window needs to be redrawn
	 */
	bool _needs_refresh;

	/**
	 * set if window needs to be cleared before being redrawn
	 */
	bool _needs_clear;

	/**
	 * pointer to the underlying curses window
	 */
	WINDOW *_w;
public:
	/**
	 * constructor for GameWindow
	 * @param nr_rows the window height
	 * @param nr_cols the window width
	 * @param row_0 y coordinate of top left corner
	 * @param col_0 x coordinate of top left corner
	 */
	GameWindow(int nr_rows, int nr_cols, int row_0, int col_0);

	/**
	 * destructor
	 */
	virtual ~GameWindow();

	/**
	 * gets the underlying window pointer
	 * @returns the window pointer
	 */
	WINDOW *win();

	/**
	 * gets the height
	 * @returns the height
	 */
	int height();

	/**
	 * gets the width
	 * @returns the width
	 */
	int width();

	/**
	 * gets the y coordinate of the top left corner
	 */
	int row();

	/**
	 * gets the x coordinate of the top left corner
	 */
	int col();

	/**
	 * refreshes the window
	 */
	virtual void refresh() = 0;
};
}
#endif /* GAMEWINDOW_H_ */
