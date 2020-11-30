/* noise.h */

#ifndef PERLINNOISE_H
#define PERLINNOISE_H

#include <core/object.h>
#include <core/image.h>

//https://solarianprogrammer.com/2012/07/18/perlin-noise-cpp-11/
class NoiseGenerator  {

	protected:

		std::vector<int> p;
	public:
		NoiseGenerator();

		Ref<Image> getImage(Vector2i imageSize, Vector2i imageOffset, float scale);
		Ref<Image> getImage() { return getImage(Vector2i(100, 100), Vector2i(0, 0), 1.0f); }

		float noise(float x, float y, float z);

		float fade(float t);
		float lerp(float a, float b, float t);
		float grad(int hash, float x, float y, float z);
};


#endif // PERLINNOISE_H
