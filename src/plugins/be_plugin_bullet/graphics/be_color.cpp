#include "common/be_rand.h"
#include "be_color.h"

BeColor::BeColor()
{
	m_r = 0.0f;
	m_g = 0.0f;
	m_b = 0.0f;
	m_a = 0.0f;
}

BeColor::BeColor( const float nr, const float ng, const float nb, const float na )
{
	m_r = nr;
	m_g = ng;
	m_b = nb;
	m_a = na;
}

BeColor BeColor::randomBeColorRGB()
{
	return BeColor(
		  (float)BeRand::Instance()->get( 1,1000 ) / 1000.0f
		, (float)BeRand::Instance()->get( 1,1000 ) / 1000.0f
		, (float)BeRand::Instance()->get( 1,1000 ) / 1000.0f
		, 1.0f
	);
	
// 	BeColor c;
// 	c.r = (float)BeRand::Instance()->get( 1,100 ) / 100.0f;
// 	c.g = (float)BeRand::Instance()->get( 1,100 ) / 100.0f;
// 	c.b = (float)BeRand::Instance()->get( 1,100 ) / 100.0f;
// 	c.a = 0.0f;
// 	
// 	return c;
}

void BeColor::normalize(BeColor* c)
{
	float highest = c->r();

	if ( c->g() > highest )
		highest = c->g();
	if ( c->b() > highest )
		highest = c->b();
	if ( c->a() > highest )
		highest = c->a();

	c->setR( c->r() / highest );
	c->setG( c->g() / highest );
	c->setB( c->b() / highest );
	c->setA( c->a() / highest );
/*	
	c->r /= highest;
	c->g /= highest;
	c->b /= highest;
	c->a /= highest;*/
}

BeColor BeColor::getNormalized()
{
	float highest = r();
	if ( g() > highest )
		highest = g();
	if ( b() > highest )
		highest = b();
	if ( a() > highest )
		highest = a();

	return BeColor(
		  r()/highest
		, g()/highest
		, b()/highest
		, a()/highest
	);
	
// 	BeColor c;
// 	c.r = r/highest;
// 	c.g = g/highest;
// 	c.b = b/highest;
// 	c.a = a/highest;
// 	return c;
}

void BeColor::normalize()
{
	float highest = r();
	if ( g() > highest )
		highest = g();
	if ( b() > highest )
		highest = b();
	if ( a() > highest )
		highest = a();

	m_r /= highest;
	m_g /= highest;
	m_b /= highest;
	m_a /= highest;
}

BeColor& BeColor::operator=(const BeColor& other)
{
	m_r = other.r();
	m_g = other.g();
	m_b = other.b();
	m_a = other.a();
	return (*this);
}

bool BeColor::operator!=(const BeColor& other) const
{
	if ( r() == other.r() )
		if ( g() == other.g() )
			if ( b() == other.b() )
				if ( a() == other.a() )
					return false;
	return true;
}

BeColor::~BeColor()
{
}


