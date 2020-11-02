#ifndef SCORE_DATA_KEY_HPP
#define SCORE_DATA_KEY_HPP

#include "Size.tpp"

#include <tuple>
#include <unordered_map>

typedef std::tuple<Size<int>, int> ScoreDataKey;

struct key_hash: public std::unary_function<ScoreDataKey, std::size_t>
{
	std::size_t operator()(const ScoreDataKey &k) const;
};

struct key_equal: public std::binary_function<ScoreDataKey, ScoreDataKey, bool>
{
	bool operator()(const ScoreDataKey &v1, const ScoreDataKey &v2) const;
};

typedef std::unordered_map<std::tuple<Size<int>, int>, int, key_hash, key_equal> ScoreData;

#endif // !SCORE_DATA_KEY_HPP
