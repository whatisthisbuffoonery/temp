## what a[Ore these math formulas

		// pt[i].fx = ((pt[i].x * view.cosy) + (pt[i].z * view.siny)) * view.scale;
		// z = -(pt[i].x * view.siny) + (pt[i].z * view.cosy);
		// pt[i].fy = ((pt[i].y * view.cosx) + (z * view.sinx)) * view.scale;

		pt[i].fx = (pt[i].x * view.cosz) - (pt[i].y * view.sinz);
		pt[i].fy = (pt[i].x * view.sinz) + (pt[i].y * view.cosz);
		z = -(pt[i].fx * view.siny) + (pt[i].z * view.cosy);
		pt[i].fx = ((pt[i].fx * view.cosy) + (pt[i].z * view.siny)) * view.scale;
		pt[i].fy = ((pt[i].y * view.cosx) + (z * view.sinx)) * view.scale;

tan cos sin: toa cah soh. Grab a ruler and stick a 90deg angle in there, none of this works otherwise

how to convert 3d to 2d:
x /= z
y /= z

tada (thanks tsoding)
this brings coords closer to origin point based on distance

how to rotate?
y-angle (sideways, spinning around using the y axis as a handlebar):
	fx = x * cos(angle) + z * sin(angle)

	why? well, each of the formulas convert between angles and length ratios.
	cos angle grabs the two lines coming out of the screen (explain better)
	sin angle


## Description

This project takes a bitmap and displays it as a 3d wireframe in isometric projection.

Bonus features include:
	rotation
	zoom
	translation
	changing to perspective projection
	using multiple inputs at once (subject to user hardware)


## Instructions

make or make bonus, then pass in a bitmap file as an argument

rotation controls (bonus feature):
	q/e: yaw
	w/s: pitch
	a/d: roll
	mouse wheel: zoom
	arrow keys: translate

## Resources

An introductory perspective on 3d graphics for those trying out this project: https://youtu.be/qjWkNZ0SXfo
This shows that trigonometry is all that stands between 2d and 3d projection. Of course, as the project demands an
orthographic projection, we will not be dividing by z yet.

The formula for said trigonometry: https://en.wikipedia.org/wiki/Euler_angles
our formula: https://wikimedia.org/api/rest_v1/media/math/render/svg/c4d0ffc556cb223c1df3cf1f2bb542301dd3c9f2
...but I dont understand math-  
[really good explanation pt1](https://medium.com/@sepideh.92sh/part-i-how-robots-understand-space-kinematics-and-the-power-of-rotation-matrices-6b2ba5bc07be)  
[really good explanation pt2](https://medium.com/@sepideh.92sh/part-ii-inside-rotation-matrices-axes-frames-and-coordinate-transformations-f6d0810a804a)  
[really good explanation pt3](https://medium.com/@sepideh.92sh/part-iii-composing-rotations-euler-angles-and-roll-pitch-yaw-38aa816a5bcd)  
The three rows represent, from top to bottom: x, y, and z.
In code, 
[conventions?](https://math.stackexchange.com/questions/3290237/rotation-matrix-difference-between-row-vs-column-representations)  
[chained rotations?](https://en.wikipedia.org/wiki/Davenport_chained_rotations)
[even simpler matrix usage](https://www.youtube.com/watch?v=kYB8IZa5AuE)

(P.S. it is simple)
