#ifndef VECTOR2I_H
#define VECTOR2I_H

class Vector2i {

public:
	Vector2i();
	Vector2i(const int xv, const int yv);
	~Vector2i();
	
	void set( const int xv, const int yv ) { m_x = xv; m_y = yv; }
	Vector2i operator+(const Vector2i &other) const;
	int	m_x;
	int	m_y;
private:

};

#endif
