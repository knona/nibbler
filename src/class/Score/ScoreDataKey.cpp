#include "ScoreDataKey.hpp"

std::size_t key_hash::operator()(const ScoreDataKey &k) const
{
	const auto &[size, score] = k;

	size_t code = 0;
	code |= static_cast<size_t>(size.width);
	code |= static_cast<size_t>(size.height) << 16;
	code |= static_cast<size_t>(score) << 32;
	return code;
}

bool key_equal::operator()(const ScoreDataKey &v1, const ScoreDataKey &v2) const
{
	const auto &[size1, score1] = v1;
	const auto &[size2, score2] = v2;
	return size1.width == size2.width && size1.height == size2.height && score1 == score2;
}
