#include "ScoreDataKey.hpp"

std::size_t key_hash::operator()(const ScoreDataKey &k) const
{
	const auto &[size, noWall, speed] = k;

	size_t code = 0;
	code |= static_cast<size_t>(noWall) << 0;
	code |= static_cast<size_t>(speed) << 1;
	code |= static_cast<size_t>(size.width) << 3;
	code |= static_cast<size_t>(size.height) << 19;
	return code;
}

bool key_equal::operator()(const ScoreDataKey &v1, const ScoreDataKey &v2) const
{
	const auto &[size1, noWall1, speed1] = v1;
	const auto &[size2, noWall2, speed2] = v2;
	return size1.width == size2.width && size1.height == size2.height && noWall1 == noWall2 && speed1 == speed2;
}
