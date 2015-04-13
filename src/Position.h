/**
 * a struct to store a 2d position
 *
 * @author wysiwyng
 */

#ifndef POSITION_H_
#define POSITION_H_

/**
 * a struct to store a 2d position
 */
struct position{
	/**
	 * the y coordinate
	 */
	int y;

	/**
	 * the x coordinate
	 */
	int x;

	/**
	 * equals operator for use in data structures
	 */
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
