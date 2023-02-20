#include "vector2i.h"

Vector2i::Vector2i() :
 m_x(0),
 m_y(0)
{
}

Vector2i::Vector2i(const int xv, const int yv) :
 m_x(xv),
 m_y(yv)
{
}

Vector2i Vector2i::operator+(const Vector2i& other) const
{
	return Vector2i( m_x+other.m_x, m_y+other.m_y );
}

Vector2i::~Vector2i()
{
}
