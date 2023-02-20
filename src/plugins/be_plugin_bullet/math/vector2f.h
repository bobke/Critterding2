#ifndef VECTOR2F_H
#define VECTOR2F_H

class Vector2f {

	public:
		Vector2f();
		Vector2f(const float& xv, const float& yv);
		~Vector2f();
	
		void set( const float xv, const float yv ) { m_x = xv; m_y = yv; }
		Vector2f operator+(const Vector2f &other) const;
		Vector2f& operator+=(const Vector2f &other);
		float	m_x;
		float	m_y;

};

#endif
