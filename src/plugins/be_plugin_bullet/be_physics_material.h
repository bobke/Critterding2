#ifndef BE_PHYSICS_MATERIAL_H_INCLUDED
#define BE_PHYSICS_MATERIAL_H_INCLUDED

class BePhysicsMaterial
{
public:
	BePhysicsMaterial() : m_friction(0.8f), m_restitution(0.8f) {}
	BePhysicsMaterial(const float friction, const float restitution) : m_friction(friction), m_restitution(restitution) {}
	float friction() const { return m_friction; }
	float restitution() const { return m_restitution; }
	void setFriction(const float friction) { m_friction=friction; }
	void setRestitution(const float restitution) { m_restitution=restitution; }
protected:
	float m_friction;
	float m_restitution;
};

#endif
 
