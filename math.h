#ifndef MATH_H
#define MATH_H

#include <math.h>

// structs, types
union v3
{
    struct 
    {
        r32 x, y, z;
    };

    struct 
    {
        r32 r, g, b;
    };

    r32 E[3];
};

typedef v3 point3;

union pixel_color {
    struct 
    {
        u8 r, g, b;
    };

    u8 E[3];
};

// v3 operations
v3 operator*(r32 a, v3 v) 
{
    v3 result;
    result.x = a * v.x;
    result.y = a * v.y;
    result.z = a * v.z;

    return result;
}

v3 operator*(v3 v, r32 a) 
{
    v3 result = a * v;
    
    return result;
}

v3& operator*=(v3& v, r32 a) 
{
    v = a * v;

    return v;
}

v3 operator/(v3 v, r32 a) 
{
    v3 result;
    if(a != 0.0f) {
        result.x = 1.0f / a * v.x;
        result.y = 1.0f / a * v.y;
        result.z = 1.0f / a * v.z;
    }

    return result;
}

v3& operator/=(v3& v, r32 a) 
{
    v = v / a;

    return v;
}

v3 operator-(v3 v) 
{
    v3 result;
    result.x = -v.x;
    result.y = -v.y;
    result.z = -v.z;

    return result;
}

v3 operator+(v3 a, v3 b) 
{
    v3 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;

    return result;
}

v3 operator-(v3 a, v3 b) 
{
    v3 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;

    return result;
}

v3& operator+=(v3 &a, v3 b) 
{
    a.x = a.x + b.x;
    a.y = a.y + b.y;
    a.z = a.z + b.z;

    return a;
}

v3& operator-=(v3 &a, v3 b) 
{
    a.x = a.x - b.x;
    a.y = a.y - b.y;
    a.z = a.z - b.z;

    return a;
}

r32 DotProduct(v3 a, v3 b) 
{
    r32 result;
    result = a.x * b.x + a.y * b.y + a.z * b.z;

    return result;
}

r32 SquareRoot(r32 r)
{
    r32 result = sqrtf(r);
    return result;
}

r32 LengthSquared(v3 a) 
{
    r32 result;
    result = DotProduct(a, a);
    
    return result;
}

r32 Length(v3 a) 
{
    r32 result;
    result = SquareRoot(LengthSquared(a));
    
    return result;
}

v3 Normalize(v3 a) 
{
    v3 result;
    result = a * (1.0f / Length(a));

    return result;
}

#endif