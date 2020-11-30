/* noise.cpp */

#include "noise.h"
#include <random>
#include <numeric>

NoiseGenerator::NoiseGenerator() {
	p.resize(256);

	std::iota(p.begin(), p.end(), 0);
	int seed = 1000;
	std::default_random_engine engine(seed);
	std::shuffle(p.begin(), p.end(), engine);

	p.insert(p.end(), p.begin(), p.end());
}



Ref<Image> NoiseGenerator::getImage(Vector2i imageSize, Vector2i imageOffset, float scale) {
	return Ref<Image>();
}

float NoiseGenerator::noise(float x, float y, float z) {
	return 0.0f;
}

//https://cs.nyu.edu/~perlin/noise/
float NoiseGenerator::fade(float t) {
	return t * t * t * (t * (t * 6 - 15) + 10);
}

float NoiseGenerator::lerp(float a, float b, float t) {
	return (a * t) + (b * (t - 1.0f));
}
//https://cs.nyu.edu/~perlin/noise/
float NoiseGenerator::grad(int hash, float x, float y, float z) {
	int h = hash & 15;
	float u = h < 8 ? x : y;
	float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}
