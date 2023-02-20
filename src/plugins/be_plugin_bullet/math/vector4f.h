#ifndef VECTOR4F_H_INCLUDED
#define VECTOR4F_H_INCLUDED

#include <cmath>

class Vector4f 
{

public:

	Vector4f()
	{
	}
	
	Vector4f(const Vector4f& v)
	{
		m_v[0]=v.m_v[0];
		m_v[1]=v.m_v[1];
		m_v[2]=v.m_v[2];
		m_v[3]=v.m_v[3];
	}
	
	Vector4f(const float x, const float y, const float z, const float w)
	{
		m_v[0]=x;
		m_v[1]=y;
		m_v[2]=z;
		m_v[3]=w;
	}
	
	float getX() const { return m_v[0]; }
	float getY() const { return m_v[1]; }
	float getZ() const { return m_v[2]; }
	float getW() const { return m_v[3]; }

	const float* getFloatPointer() const { return m_v; }

	void setX(const float x) { m_v[0]=x; }
	void setY(const float y) { m_v[1]=y; }
	void setZ(const float z) { m_v[2]=z; }
	void setW(const float w) { m_v[3]=w; }

	bool operator==(const Vector4f &v) const
	{
		if(m_v[0]==v.m_v[0]&&m_v[1]==v.m_v[1]&&m_v[2]==v.m_v[2]&&m_v[3]==v.m_v[3])
		{
			return true;
		}
		return false;
	}

private:

	float m_v[4];

};

#endif
