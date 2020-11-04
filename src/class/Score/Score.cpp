#include "Score.hpp"

Score::Score(): _score(0)
{}

Score::Score(const Score &score)
{
	*this = score;
}

Score &Score::operator=(const Score &score)
{
	if (this != &score)
	{
		this->_score = score._score;
		this->_areaSize = score._areaSize;
		this->_noWall = score._noWall;
		this->_data = score._data;
		this->_speed = score._speed;
	}
	return *this;
}

Score::Score(const Options &options)
{
	this->_score = 0;
	this->_noWall = options.noWall;
	this->_areaSize = options.areaSize;
	this->_speed = options.speed;
	this->read();
}

Score::~Score()
{}

const char *Score::filePath = "scores.csv";

int Score::getScore() const
{
	return this->_score;
}

void Score::increment()
{
	this->_score++;
}

void Score::read()
{
	if (!std::filesystem::exists(Score::filePath))
		return;

	std::ifstream file(Score::filePath);
	std::string   line;

	if (!file.good())
		throw std::runtime_error(std::string("Cannot open file ") + Score::filePath);

	while (std::getline(file, line))
	{
		if (line == "")
			continue;
		std::replace(line.begin(), line.end(), ',', ' ');
		std::stringstream stream(line);
		std::string       buffer;

		int arr[5];
		int i;
		for (i = 0; stream >> buffer; i++)
			arr[i] = std::stoi(buffer);
		if (i != 5)
			throw std::runtime_error("File is corrupted");

		this->_data[{ { arr[0], arr[1] }, arr[2], arr[3] }] = arr[4];
	}
}

void Score::displayScore()
{
	const char *speeds[3] = { "fast", "normal", "slow" };

	if (this->_score > this->_data[{ this->_areaSize, this->_noWall, this->_speed }])
	{
		std::cout << "\033[0;36mNEW HIGHSCORE !\033[0m" << std::endl;
		this->store();
	}
	std::cout << "Score: \033[0;92m" << this->_score << "\033[0m";
	std::cout << " (" << this->_areaSize.width << "x" << this->_areaSize.height;
	std::cout << "," << (this->_noWall ? "no" : "") << " walls, ";
	std::cout << speeds[this->_speed] << ")" << std::endl;
}

void Score::displayHighScore() const
{
	const char *speeds[3] = { "fast", "normal", "slow" };
	int         score;

	try
	{
		score = this->_data.at({ this->_areaSize, this->_noWall, this->_speed });
	}
	catch (const std::exception &e)
	{
		score = 0;
	}
	std::cout << "HIGHSCORE: \033[0;92m" << score << "\033[0m";
	std::cout << " (" << this->_areaSize.width << "x" << this->_areaSize.height;
	std::cout << "," << (this->_noWall ? "no" : "") << " walls, ";
	std::cout << speeds[this->_speed] << ")" << std::endl;
}

void Score::store()
{
	std::ofstream file(Score::filePath, std::ios_base::out);

	this->_data[{ this->_areaSize, this->_noWall, this->_speed }] = this->_score;
	for (const auto &[key, score]: this->_data)
	{
		auto [areaSize, noWall, speed] = key;

		file << areaSize.width << "," << areaSize.height << ",";
		file << noWall << "," << speed << ",";
		file << score << std::endl;
	}
}
