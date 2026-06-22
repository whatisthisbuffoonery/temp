https://www.reddit.com/r/explainlikeimfive/comments/ig9253/eli5_the_difference_between_rasterization_ray/

perplexity: 
Ray tracing works by following light paths through a scene, but unlike basic Whitted ray tracing it can use many rays per pixel and many bounces to estimate more realistic lighting effects such as soft shadows, indirect light, and glossy reflections. [cs.purdue](https://www.cs.purdue.edu/homes/aliaga/_cs334-22spring/lectures/lec-raytracing1.pdf)
## Beyond one ray per pixel
In the simplest version, you shoot a ray through each pixel and use the first object it hits for color. More advanced ray tracing treats that hit as the start of a lighting calculation: from that point, it may cast new rays toward lights, toward reflective directions, or into the material to see what light contributes next. [cs.purdue](https://www.cs.purdue.edu/homes/aliaga/_cs334-22spring/lectures/lec-raytracing1.pdf)
## Common variants
- **Whitted ray tracing**: one primary ray per pixel, plus a few extra rays for perfect reflections, refractions, and hard shadows. [cs.purdue](https://www.cs.purdue.edu/homes/aliaga/_cs334-22spring/lectures/lec-raytracing1.pdf)
- **Distribution ray tracing**: shoots rays over a *range* of directions or positions to model blurrier, more realistic effects like soft shadows, glossy reflections, and depth of field. [graphics.stanford](https://graphics.stanford.edu/~boulos/papers/cook_gi07.pdf)
- **Path tracing**: shoots many random rays per pixel and lets them bounce multiple times, which approximates global illumination and indirect light much more completely. [developer.nvidia](https://developer.nvidia.com/discover/ray-tracing)
## What happens at a hit point
When a ray hits a surface, the renderer usually evaluates the material and lighting at that point. It may send shadow rays to lights, reflection rays along the mirror direction, refraction rays through transparent materials, or random bounce rays for indirect illumination, then combine all the returned contributions into the final pixel color. [cs.purdue](https://www.cs.purdue.edu/homes/aliaga/_cs334-22spring/lectures/lec-raytracing1.pdf)
## How it stays fast
Because testing every ray against every triangle would be too slow, real ray tracers use acceleration structures like bounding volume hierarchies so each ray only checks a small subset of the scene. Real-time systems also rely on denoising to make images look clean with fewer rays per pixel. [developer.nvidia](https://developer.nvidia.com/discover/ray-tracing)
## Mental model
A useful way to think about it is: rasterization asks, “which triangle covers this pixel?”, while ray tracing asks, “what light reaches this pixel if I follow rays through the scene?”. The more rays and bounces you allow, the closer you get to physically plausible lighting, at the cost of more computation. [cs.purdue](https://www.cs.purdue.edu/homes/aliaga/_cs334-22spring/lectures/lec-raytracing1.pdf)
