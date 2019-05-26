# PirkkBase
PirkkBase is a game library / engine I'm working on to help streamline the process of starting new games (which I do way too often). It's designed to be very accessible, easy to maintain and upgrade, and easy to use and understand. All parts of the library should work together seamlessly, which removes the trouble of working with many different libraries, however the library's sub-utilities have minimal dependencies between each other and can be used independently.

I don't know if anybody else is ever going to use this library, but I'm designing it as if someone will, just in case.

**This project is in its alpha stage! Many features are likely missing and possibly broken. All modules are still under development and are subject to change.**

## Modules
#### Graphics
Contains a wrapper to OpenGL and any rendering-related functions. Has support for both traditional and raytrace rendering.

#### Math
Contains general math functions, as well as support for vectors, matrices, and quaternions, fully overloaded and templated for ease of use and extensive freedom.

#### Noise
Noise functions templated for any dimension, such as perlin, simplex, and value.

#### Ticking
Manages event loops and timing to make game loop functions less verbose.

#### Util
Various utility functions.
