# Godot Terrain Generation

---

Module created by:

Jake Rose | @Jacob-Rose

Simon Steele | @simonsteele24

Chun Tao Lin | @ChunTaoLin

## Project Overview

---

Godot has more recently gained support for 3D tools, and this terrain module will allow for dynamic, procedural terrain generation.

## Features

---

* Perlin noise function with advanced parameter controls
* Chunk Generation and Mesh Construction
* Chunk Manager and Organized Spawning of Chunks

## Improvements for the Future

---

Currently, the biggest issue with the chunk generation is that it runs on the main thread that is tied to framerate. Putting this process onto a different thread should not be too difficult, but it fell out of scope as we just had enough time to get this *Proof of Concept* developed.



## Legalese

---

Godot is an open source software distributed under the MIT License, requiring that any code used from the program also includes the license file associated with it. This is maintained, and the real purpose of this repository is to show the custom terrain generation module associated with Godot.

Perlin Noise C++ Header .hpp file provided under MIT License by Ryo Suzuki.