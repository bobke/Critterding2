#include "vector2f.h"

Vector2f::Vector2f() :
 m_x(0.0f),
 m_y(0.0f)
{
}

Vector2f::Vector2f(const float& xv, const float& yv) :
 m_x(xv),
 m_y(yv)
{
}


Vector2f Vector2f::operator+(const Vector2f& other) const
{
	return Vector2f( m_x+other.m_x, m_y+other.m_y );
}

Vector2f& Vector2f::operator+=(const Vector2f& other)
{
	m_x += other.m_x;
	m_y += other.m_y;
        return *this;
}

Vector2f::~Vector2f()
{
}
