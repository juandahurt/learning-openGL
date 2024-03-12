# Error handling
In this particular example, what I did was basically to wrap some 
openGL function calls using a `macro`

```c++
// for example
GLCall(glSomeFunc())
```

So, to get the openGL errors, we need the function `glGetError`, it will
return an integer value that will indicate the kind of error that we have.

It is possible to have multiple errors, that's why we have to call
this inside a loop to get all of them.

*note: this function works as a stack, every time an error is get, is
"removed" from the stack*

### Error in this example
See that, if we run this example in debugging mode, we will get an assertion failure
because we are trying to draw elements of type `GL_INT`, but we are using 
`unsinged int`.