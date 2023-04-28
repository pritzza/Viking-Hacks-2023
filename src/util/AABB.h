#pragma once

struct AABB
{
	float x, y, w, h;

    float top() const { return y; }
    float bottom() const { return y + h; }
    float left() const { return x; }
    float right() const { return x + w; }
};

bool collide(const AABB& a, const AABB& b)
{
    return  a.left()   < b.right()  &&
            a.right()  > b.left()   &&
            a.top()    < b.bottom() &&
            a.bottom() > b.top();
}