/* noise.h */

#ifndef TERRAINNOISE_H
#define TERRAINNOISE_H

#include <core/object.h>
#include <core/image.h>
#include <vector>
#include <core/reference.h>

//https://solarianprogrammer.com/2012/07/18/perlin-noise-cpp-11/
class NoiseGenerator : public Reference {
	GDCLASS(NoiseGenerator, Reference);
	protected:
		static void _bind_methods();
		std::vector<int> p;
	public:
		NoiseGenerator();

		Ref<Image> getImage(int imageSize, Vector2 imageOffset, float scale);

		float noise(float x, float y, float z);

		float fade(float t);
		float lerp(float a, float b, float t);
		float grad(int hash, float x, float y, float z);
};


#endif // TERRAINNOISE_H
