# raytracer-basic
An Implementation of a raytracer.
It follows from "Ray Tracing in One Weekend" Series by Peter Shirley and also will add more features in the future.
To run it you just use start.sh file.
It includes for now:
1. Support for camera positioning from different perspectives and aperture. It also includes defocus blur(aka depth of field). 
2. Support for basic materials - matte, metal and glass(dielectric). For glass schlick's interpolation for reflectivity has been used.
3. Objects supported: Sphere.

In the future it will include:
1. CUDA / OpenMP implementation. The current implementation is very slow as it is single threaded implementation.
As raytracing can be easily parallelised it would be better to implement and get results on GPU/ multi core CPU.
2. Add support for more type of objects to create more impressive structures.
3. Surface Textures
4. Solid textures
5. Volumes and Media
6. Create a raytraced gif for animation.
7. Motion blur
8. Objects emitting light.
