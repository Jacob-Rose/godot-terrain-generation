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

		/// <summary>
		/// 
		/// </summary>
		/// <param name="imageSize">Size in pixels of image</param>
		/// <param name="imageOffset">Offset in pixels of noise origin</param>
		/// <param name="scale">The zoom factor for the perlin noise</param>
		/// <param name="octaves">The number of octaves to include in the noise, created finer details</param>
		/// <param name="persistance">How clear the octaves show in the noise</param>
		/// <param name="lacunarity">How clear the octaves show in the noise</param>
		///
		/// <example>getImage(100,Vector2(0,0), 1.0f, 3, 0.8, 2.0)</example>
		/// <returns>Noise Image</returns>
		Ref<Image> getImage(int imageSize, Vector2 imageOffset, float scale, int octaves, float persistance, float lacunarity);

		float fade(float t);
		float lerp(float a, float b, float t);
		float grad(int hash, float x, float y, float z);
		float inverseLerp(float x, float y, float val);

		//https://www.oreilly.com/library/view/c-cookbook/0596007612/ch11s07.html
		static float randFloat01();
};


#endif // TERRAINNOISE_H
