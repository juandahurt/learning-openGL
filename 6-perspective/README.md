# Perspective

Maybe the title is not the best tbh.

So, in this example I was able to create a 3d camera and
render a cube that rotates around the y-axis. 
It is possible to move the camera using WASD and the arrows 
to move in the y-axis.

So, there's A LOT of things that I had to learn, but I think these are 
the most important:
- **MVP:** So, there are 3 main transformations: `Model` which is basically
the world transformation of a certain object (where that object is located in
our world), `View` the camera transformation indicates where the camera is located
at and where it is looking at and `Projection` that allows us to see the world projected 
using either a perspective projection or an orthogonal projection 
- **Camera movement:** 
  - **Keyboard:** Moving the camera in the x-axis was kind of hard to understand, 
  but pretty much what you have to do is make a `cross` product between the position
  and the up vector to get the orthogonal vector that points in the x-axis.
  - **Mouse:** In this case I had to use some `cos` and `sin` functions to get the right
  value in every axis. And I learned that in the y-axis the angle is called `pitch` and in the 
  x-axis is called `yawn`.

I think that's it :)

*PD: the yawn value starts equal to -90 degrees because our camera points
to the -z axis*