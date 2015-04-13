/**
 * a perlin noise generator implemented after the java reference implementation
 *
 * @author wysiwyng
 */

#ifndef PERLINNOISE_H
#define PERLINNOISE_H

#include <vector>

class PerlinNoise {
	/**
	 * the internal permutation vector
	 */
	std::vector<int> p;
public:
	/**
	 * the default constructor, uses the actual time as seed
	 */
	PerlinNoise();

	/**
	 * constructor with user specified seed
	 * @param seed the seed to use
	 */
	PerlinNoise(unsigned int seed);

	/**
	 * generates the noise value for a specified 3d point
	 * @param x the x coordinate
	 * @param y the y coordinate
	 * @param z the z coordinate
	 */
	double noise(double x, double y, double z);
private:
	/**
	 * calculate fade curve
	 */
	double fade(double t);
	double lerp(double t, double a, double b);
	double grad(int hash, double x, double y, double z);
};

#endif
