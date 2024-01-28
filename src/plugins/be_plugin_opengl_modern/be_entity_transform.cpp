#include "be_entity_transform.h"

	BTransform::BTransform() : BEntity()
	{
		m_tranform.setIdentity();
	};
	
	const btTransform& BTransform::getTransform() const
	{
		return m_tranform;
	}
	
	void BTransform::setTransform( const btTransform& transform )
	{
		m_tranform = transform;
	}
