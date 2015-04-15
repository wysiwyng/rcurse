/**
 * a statusbar to show messages in rcurse
 *
 * @author wysiwyng
 */

#ifndef STATUSBAR_H_
#define STATUSBAR_H_

#include <string>
#include "GameWindow.h"

class Statusbar : public GameWindow{
private:
	/**
	 * the displayed status text
	 */
	std::string _text;
public:
	/**
	 * Constructor for Statusbar
	 * @param nr_rows the y size of this Statusbar
	 * @param nr_cols the x size of this Statusbar
	 * @param row_0 the y coordinate of the upper left corner
	 * @param col_0 the x coordinate of the upper left corner
	 */
	Statusbar(int nr_rows, int nr_cols, int row_0, int col_0);

	/**
	 * Statusbar destructor
	 */
	virtual ~Statusbar();

	void refresh();

	/**
	 * sets the displayed status message
	 * @param text the message to display
	 * @param _refresh set to refresh immediately
	 */
	void set_status(std::string text, bool _refresh = true);

	/**
	 * accepts numerical input with backspaces
	 * @returns the entered number
	 */
	int read_num(std::string prompt = "");
};

#endif /* STATUSBAR_H_ */
