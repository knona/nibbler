#ifndef SCORE_HPP
#define SCORE_HPP

#include "Options.hpp"
#include "ScoreDataKey.hpp"
#include "Size.tpp"

#include <algorithm>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Score
{
	private:
	int       _score;
	bool      _noWall;
	Size<int> _areaSize;
	ScoreData _data;

	static const char *filePath;
	void               read();
	void               store();

	public:
	Score();
	Score(const Score &);
	Score &operator=(const Score &);
	Score(const Options &);
	~Score();

	int  getScore() const;
	void increment();
	void displayScore();
	void displayHighScore() const;
};

#endif // !SCORE_HPP
