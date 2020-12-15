/* noise.h */

#ifndef TERRAINNOISE_H
#define TERRAINNOISE_H

#include <core/object.h>
#include <core/image.h>
#include <vector>
#include <core/reference.h>
#include <scene/resources/gradient.h>

//https://solarianprogrammer.com/2012/07/18/perlin-noise-cpp-11/
class NoiseGenerator : public Reference {
	GDCLASS(NoiseGenerator, Reference);
	protected:
		static void _bind_methods();
	public:
		NoiseGenerator();


		/// <summary>
		/// Returns heightmap in a 1D array
		/// Access the right pixel by using (y * imageSize) + x
		/// </summary>
		/// <param name="imageSize">size of heightmap | size * size </param>
		/// <param name="imageOffset">offset of noise</param>
		/// <param name="scale">base is 100</param>
		/// <param name="octaves">number of interations / complexity</param>
		/// <param name="persistance">how much each octave affects the image</param>
		/// <param name="lacunarity">something else</param>
		/// <returns></returns>
		Ref<Image> getHeightmap(int imageSize, Vector2 imageOffset, float scale, int octaves, float persistance, float lacunarity);
		Ref<Image> getColorFromHeightmap(Ref<Image> heightMap, int heightMapSize, Gradient& colorMap);
		Ref<Image> getColorHeightmap(int imageSize, Vector2 imageOffset, Ref<Gradient> colorMap);

		float fade(float t);
		float lerp(float a, float b, float t);
		float grad(int hash, float x, float y, float z);
		float inverseLerp(float x, float y, float val);

		//https://www.oreilly.com/library/view/c-cookbook/0596007612/ch11s07.html
		static float randFloat01();
};


#endif // TERRAINNOISE_H
