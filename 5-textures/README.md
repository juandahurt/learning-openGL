# Textures

So, in this example, I just rendered a minecraft "block".

To load the image into memory, we use the code from `stb_image.h`
and it basically gives us an array of bytes that represents that
image.

Once we have loaded the image, we pass it to OpenGL, using
the `glGenTextures(1, &someId)` and bind it.

### Projection
I applied some orthogonal projection in order for the texture
to look with the desired aspect ratio :)

---
### Output
![Image](res/textures.png)
