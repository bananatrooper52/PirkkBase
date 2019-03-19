# PirkkBase
PirkkBase is a game library / engine I'm working on to help streamline the process of starting new games (which I do way too often). It's designed to be very accessible, easy to maintain and upgrade, and easy to use and understand. All parts of the library should work together seamlessly, which removes the trouble of working with many different libraries, however the library's sub-utilities have minimal dependencies between each other, which keeps it light-weight.

I don't know if anybody else is ever going to use this library, but I'm designing it as if someone will, just in case.

## Features
### Custom math library
+ Templated vectors and matrices with overloaded operators
+ Matrix transformation (scale, rotation, translation, etc.)
+ Quaternions <i>(coming soon)</i>

#### Example
```
#include "math/Math.h";

using namespace PirkkBase;

Math::Vec3f vec(1, 2, 3);
Math::Mat4f mat = Math::translate(Math::Vec3f(10, 5, 3));
Math::Vec4f mul = mat * vec;
```

### Object-oriented OpenGL wrapper with GLEW and GLFW
- Vertex buffer wrapper class <i>(in progress)</i>
- Vertex array / model wrapper class <i>(in progress)</i>
- GLFW Window wrapper class <i>(ongoing)</i>
- Texture loading <i>(coming soon)</i>
- Shader loader and wrapper class <i>(coming soon)</i>

### Tick / update manager
- Add interval functions (tick, render, etc.) in a single line
	
## Plans
- Built-in raytrace rendering support
	- Voxel traversal
	- Geometry-based (triangles, spheres, etc.)
	- Shadow generation (possibly)
- Distribute library in modules to reduce bloat
- Physics
	- Collision detection and response
	- Raycasting
- Noise generation
	- Different algorithms (perlin, simplex, etc.)
	- Generation options
- Networking
	- Different connections (sockets, WebSockets, possibly others)
- Cross-platform
	- Windows, Mac, and Linux
- Text rendering
	- Possibly add generic font loading
