/* noise.cpp */

#include "noise.h"
#include <random>
#include <algorithm>
#include <numeric>
#include <core/method_bind.h>
#include <core/method_bind_ext.gen.inc> //wow this is necessary for functions over five parameters to bind
#include "PerlinNoise.hpp"

void NoiseGenerator::_bind_methods() {
	//ClassDB::bind_method(D_METHOD("createImage"), &NoiseGenerator::createImage);
	ClassDB::bind_method(D_METHOD("getImageSimple", "imageSize", "imageOffset", "scale"), &NoiseGenerator::getImageSimple);
	ClassDB::bind_method(D_METHOD("getImage", "imageSize", "imageOffset", "scale", "octaves", "persistance", "lacunarity"), &NoiseGenerator::getImage);
}

NoiseGenerator::NoiseGenerator() {


}


//Based of Sebastian Lague tutorial in Unity https://www.youtube.com/watch?v=MRNFcywkUSA&t=568s
Ref<Image> NoiseGenerator::getImage(int imageSize, Vector2 imageOffset, float scale, int octaves, float persistance, float lacunarity) {
	
	Ref<Image> img = memnew(Image);
	img->create(imageSize, imageSize, false, Image::Format::FORMAT_RGBA8);
	img->lock();
	
	siv::PerlinNoise noiseGen;
	noiseGen.reseed(1234); //or any seed
	
	Vector2* octaveOffsets = new Vector2[octaves];

	float *noiseMap = new float[imageSize * imageSize];

	for (short i = 0; i < octaves; ++i) {
		octaveOffsets[i].x = (randFloat01() * 20000.0f) - 10000.0f;
		octaveOffsets[i].y = (randFloat01() * 20000.0f) - 10000.0f;
	}

	
	float maxNoiseHeight = -2.5; //approximation, this is not done with normalization as that creates inconsistancies between noise maps
	float minNoiseHeight = 2.5; //good nuf

	for (int x = 0; x < imageSize; ++x) {
		for (int y = 0; y < imageSize; ++y) {
			float amplitude = 1.0f;
			float frequency = 1.0f;
			float noiseHeight = 0.0f;

			for (int k =0; k < octaves; ++k) {
				float xPos = ((x) / scale * frequency + octaveOffsets[k].x) + (imageOffset.x * frequency);
				float yPos = ((y) / scale * frequency + octaveOffsets[k].y) + (imageOffset.y * frequency);

				float noiseVal = (noiseGen.noise2D_0_1(xPos, yPos) * 2.0f) - 1.0f;
				noiseHeight += noiseVal * amplitude;

				amplitude *= persistance;
				frequency *= lacunarity;
			}

			/*
			if (noiseHeight > maxNoiseHeight) {
				maxNoiseHeight = noiseHeight;
			} else if (noiseHeight < minNoiseHeight) {
				minNoiseHeight = noiseHeight;
			}
			*/

			noiseMap[(y * imageSize) + x] = noiseHeight;
		}
	}

	for (int x = 0; x < imageSize; ++x) {
		for (int y = 0; y < imageSize; ++y) {
			noiseMap[x + (y * imageSize)] = inverseLerp(minNoiseHeight, maxNoiseHeight, noiseMap[x + (y * imageSize)]), 0.0f, 1.0f;
			noiseMap[x + (y * imageSize)] = std::max(0.0f, std::min(noiseMap[x + (y * imageSize)], 1.0f)); //clamp 01			
			img->set_pixel(x, y, Color(noiseMap[x + (y * imageSize)], noiseMap[x + (y * imageSize)], noiseMap[x + (y * imageSize)]));
		}
	}
	img->unlock();
	delete[] noiseMap;
	delete[] octaveOffsets;

	return img;
	
	return nullptr;
}

Ref<Image> NoiseGenerator::getImageSimple(int imageSize, Vector2 imageOffset, float scale) {
	return getImage(imageSize, imageOffset, scale, 3, 0.5f, 2.0f);
}

void NoiseGenerator::getImageVoid(int imageSize, Vector2 imageOffset, float scale) {
	getImage(imageSize, imageOffset, scale, 3, 0.5f, 2.0f);
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
//https://forums.unrealengine.com/development-discussion/c-gameplay-programming/1496259-looking-for-something-like-inverselerp
float NoiseGenerator::inverseLerp(float x, float y, float val) {
	return (val - x) / (y - x);
}

float NoiseGenerator::randFloat01() {
	//return float(rand()) / (float(RAND_MAX) + 1.0);
	return 0.0f;
}
