#ifndef POSITION_H_
#define POSITION_H_

struct position{
	int y;
	int x;

	bool operator==(const position &other) const {
		return x == other.x && y == other.y;
	}
};

namespace std {
template<>
struct hash<position> {
	std::size_t operator()(const position& k) const
	{
		return std::hash<long>()((k.x << 8) + k.y);
	}
};
}


#endif /* POSITION_H_ */
