#include "Render.h"

Render::Render(GameData* data) : _data(data)
{
	initscr(); // Переход в curses-режим
	keypad(stdscr, true);
	
	auto win = stdscr;
	win->_sync = true;
	//delay_output(100);
}

int Render::Rendering()
{
	int H = _data->FrameRows();
	int W = _data->FrameCols();

	clear();

	char** frame = _data->Frame();

	for (int r = 0; r < H; r++)
	{
		addstr(frame[r]);
	}

	refresh();
	
	/*
	if (_data->_log.is_open())
	{
		_data->_log << "Render" << std::endl;
	}
	*/
	return 0;
}

Render::~Render()
{
	endwin();
	_data = nullptr;
}

