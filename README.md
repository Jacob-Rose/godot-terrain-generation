# Godot Terrain Generation

---

Module created by:

Jake Rose | @Jacob-Rose

Simon Steele | @simonsteele24

Chun Tao Lin | @ChunTaoLin

## Project Overview

---

Godot has more recently gained support for 3D tools, and this terrain module will allow for dynamic, procedural terrain generation. 

This terrain generation solution uses a strategy similar to games like Minecraft, with chunks that generate based on the distance to the player. A heightmap is generated, then a colormap is generated from that based on the said heightmap. A custom mesh is then generated using this heightmap as well as customizable chunk settings to get the user's desired effects.

## Features

---

* Perlin noise function with advanced parameter controls
* Chunk Generation and Mesh Construction
* Chunk Manager and Organized Spawning of Chunks
* Color output options for height maps
* Dynamic Chunk Generation at Runtime
* Many customization options for the user in-editor.

Video of it running: *Warning, recorded on laptop with lower CPU specs and Intel Graphics*

[![Watch the video](https://img.youtube.com/vi/NpJRWa6171k/0.jpg)](https://youtu.be/NpJRWa6171k)

## Improvements for the Future

---

Currently, the biggest issue with the chunk generation is that it runs on the main thread that is tied to framerate. Putting this process onto a different thread should not be too difficult, but it fell out of scope as we just had enough time to get this *Proof of Concept* developed.

The color selection is currently a bit limited, but converting this function to the gradient structure would be a worthwhile pursuit in the future if time permitted.

Physics is currently not in the build. However, since the module uses the Mesh Instance class, Godot's built in collision could probably be applied with relative ease to get the desired effect.

## Legalese

---

Godot is an open source software distributed under the MIT License, requiring that any code used from the program also includes the license file associated with it. This is maintained, and the real purpose of this repository is to show the custom terrain generation module associated with Godot.

Perlin Noise C++ Header .hpp file provided under MIT License by Ryo Suzuki.