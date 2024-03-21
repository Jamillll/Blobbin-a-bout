#pragma once

struct Vec2
{
    float x = 0, y = 0;
};

struct Vec3 
{
    float x, y, z;
};

struct Vec4
{
    float x, y, z, w;
};

struct Vertex
{
    Vec4 position;
    float textureX, textureY;
};

struct Rect
{
    Vec2 position;
    Vec2 size;
    Vec4 colour;
};