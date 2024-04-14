# Blobbin a'bout

A game created for my collage game dev unit.

This game makes use of a variety of different libraries, this is because I've decided against using a game engine or even a game framework, both tools I've used before. While I was able to make simple prototypes rather quickly with game engines (in the form of Unity) and game frameworks (in the form of monogame) I prefer to create the game and the systems running it at a lower level. 

The systems I have made for this game are rather basic and not at all robust but achieve what I need them to for the purpose of this game. For example, the renderer only renders basic quads, with the option of them being textured and while I could create and plug in uniquely designed index buffers and shaders for other purposes, they aren't directly supported by the renderer. This means if I want to add particles at any point in development I'll need to either add to the renderer, or have it rendered as a series of rectangles. I have performed some minimal stress testing on my renderer however so as long as there are only a couple thousand particles at once the game should be able to handle it without a heavy decrease. 

## The list of libraries used are as follows:

GLFW - This is for window management and user input

GLEW - This is for retrieving the OpenGL functions I will be using for graphics rendering

GLM - an OpenGL maths libary that I use to primarily handle matrix math for me 

Box2D - This is for 2D physics and collision which will save me a lot of time in having to write my own rudimentary physics implimentation

Dear ImGui - This is a simple GUI library that I use for debugging purposes due to how quick and easy it is to get it running.
