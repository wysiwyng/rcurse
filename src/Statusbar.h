/*
 * Statusbar.h
 *
 *  Created on: Mar 3, 2015
 *      Author: wysiwyng
 */

#ifndef STATUSBAR_H_
#define STATUSBAR_H_

#include "GameWindow.h"

class Statusbar : public GameWindow{
private:
	const char* _text;
public:
	Statusbar(int nr_rows, int nr_cols, int row_0, int col_0);
	virtual ~Statusbar();

	void refresh();
	void set_status(const char* text, bool _refresh = true);
};

#endif /* STATUSBAR_H_ */
