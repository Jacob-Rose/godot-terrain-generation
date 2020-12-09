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
	public:
		NoiseGenerator();

		Ref<Image> getImage(int imageSize, Vector2 imageOffset, float scale, int octaves, float persistance, float lacunarity);
		Ref<Image> getImageSimple(int imageSize, Vector2 imageOffset, float scale);
		void getImageVoid(int imageSize, Vector2 imageOffset, float scale);

		float fade(float t);
		float lerp(float a, float b, float t);
		float grad(int hash, float x, float y, float z);
		float inverseLerp(float x, float y, float val);

		//https://www.oreilly.com/library/view/c-cookbook/0596007612/ch11s07.html
		static float randFloat01();
};


#endif // TERRAINNOISE_H
