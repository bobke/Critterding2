#ifndef PHYSICSMODEL_RIGID_H_INCLUDED
#define PHYSICSMODEL_RIGID_H_INCLUDED

// #include "kernel/be_entity_interface.h"
#include "be_physics_material.h"
#include "bullet3/src/btBulletDynamicsCommon.h"
#include <boost/shared_ptr.hpp>
#include <iostream>
#include "kernel/be_entity_interface.h"

// class BeOutput;
// class BeEntity;
class BEntity;

	// TRANSFORM // FIXME A COPY TOO MUCH
		class transformEmitter: public BEntity
		{
			public:
				transformEmitter() {};
				const char* class_id() const { return "Bullet_Transform_Emitter"; }
				virtual ~transformEmitter() {};
				void construct();
				virtual bool apply( BEntity* e ) { return e->set( reinterpret_cast<const char*>(m_value) ); }
				virtual const char* get_string() { return reinterpret_cast<const char*>(m_value); }
				
				virtual bool set( const Bstring& id, const Bfloat& value );
				virtual Bfloat get_float( const Bstring& id );
				
				float m_value[16];
			private:
// 				char m_value_chars[64];
		};

class BeEventDrivenMotionState : public btDefaultMotionState
{
	public:
		BeEventDrivenMotionState( const btTransform& t ) : btDefaultMotionState(t), m_entity_transform(0) {};
		virtual ~BeEventDrivenMotionState() { };
		virtual void setWorldTransform(const btTransform& centerOfMassWorldTrans);
// 		void setOutput( boost::shared_ptr<BeOutput> output_pointer ) { m_output_pointer = output_pointer; }
		void setTransformEntity( BEntity* entity_transform ) { m_entity_transform = dynamic_cast<transformEmitter*>(entity_transform); }		
		BEntity* getTransformEntity() const { return m_entity_transform; }
	private:
// 		boost::shared_ptr<BeOutput> m_output_pointer;
		transformEmitter* m_entity_transform;
		float m_buffer_value[16];
};

// class BeEventDrivenMotionState : public btDefaultMotionState
// {
// 	public:
// 		BeEventDrivenMotionState( const btTransform& t )
// 		 : btDefaultMotionState(t), m_entity_transform(0) {};
// 		virtual ~BeEventDrivenMotionState() { };
// 		virtual void setWorldTransform(const btTransform& centerOfMassWorldTrans);
// // 		void setOutput( boost::shared_ptr<BeOutput> output_pointer ) { m_output_pointer = output_pointer; }
// 		void setTransformEntity( BeEntity* entity_transform ) { m_entity_transform = entity_transform; }
// 		BeEntity* getTransformEntity() const { return m_entity_transform; }
// 	private:
// // 		boost::shared_ptr<BeOutput> m_output_pointer;
// 		BeEntity* m_entity_transform;
// };

// class BeShape
// {
// protected:
//     BeShape(const boost::shared_ptr<btCollisionShape>& shape) : m_shape(shape) {};
//     virtual ~BeShape() { };
// private:
//     boost::shared_ptr<btCollisionShape> m_shape;
// };
// 
class BeRigidBody
{
	public:
		BeRigidBody() : m_localInertia(0.0f, 0.0f, 0.0f) {};
		virtual ~BeRigidBody() {};
		typedef boost::shared_ptr<BeRigidBody> ptr;
//         void setMaterial(const BePhysicsMaterial& material);
		btCollisionShape* getShape() const { return m_shape.get(); }
		void setShape( boost::shared_ptr<btCollisionShape> shape ) { m_shape = shape; }
		btRigidBody* getBody() const { return m_body.get(); }
		void setBody( boost::shared_ptr<btRigidBody> body ) { m_body = body; }
		boost::shared_ptr<BeEventDrivenMotionState> getMotionState() const { return m_motionState; }
		void setMotionState( boost::shared_ptr<BeEventDrivenMotionState> m ) { m_motionState = m; }
		const btTransform& getTransform() const
		{
// 			if ( m_motionState )
// 				return m_motionState->m_graphicsWorldTrans;
// 			else
				return m_body->getWorldTransform();
		}
		void setTransform( const btTransform& transform ) const
		{
// 			if ( m_motionState )
// 				m_motionState->m_graphicsWorldTrans = transform;
			return m_body->setWorldTransform(transform);
		}
		void generalSetup( const float weight, const btTransform& transform, const float linearDamping, const float angularDamping);
// 		virtual void reScale( const btVector3& scale ) { std::cout << "BeRigidBody::reScale fail" << std::endl;};
		
		btVector3 m_localInertia;
	protected:
        boost::shared_ptr<btCollisionShape> 	m_shape;
        boost::shared_ptr<btRigidBody> 			m_body;
    private:
		boost::shared_ptr<BeEventDrivenMotionState>	m_motionState;
};


#endif
 
