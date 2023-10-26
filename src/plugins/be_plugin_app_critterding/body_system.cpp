#include "body_system.h"
#include "kernel/be_entity_core_types.h"
#include <iostream>
 
	void BodySystem::construct()
	{
		auto settings = addChild( "settings", new BEntity() );
		m_unit_container = addChild( "unit_container", new BEntity() );

		// m_mutation_chance = settings->addChild( "mutation_chance", new BEntity_uint() );
		// m_mutationruns_min = settings->addChild( "mutationruns_min", new BEntity_uint() );
		// m_mutationruns_max = settings->addChild( "mutationruns_max", new BEntity_uint() );
		// m_bodypart_min = settings->addChild( "bodypart_min", new BEntity_uint() );
		// m_bodypart_max = settings->addChild( "bodypart_max", new BEntity_uint() );
		// m_head_min = settings->addChild( "head_min", new BEntity_uint() );
		// m_head_max = settings->addChild( "head_max", new BEntity_uint() );
		// m_eye_min = settings->addChild( "eye_min", new BEntity_uint() );
		// m_eye_max = settings->addChild( "eye_max", new BEntity_uint() );
		// m_eyes_connect_to_heads = settings->addChild( "eyes_connect_to_heads", new BEntity_bool() );
		// m_spike_min = settings->addChild( "spike_min", new BEntity_uint() );
		// m_spike_max = settings->addChild( "spike_max", new BEntity_uint() );
		// m_bodypart_density = settings->addChild( "bodypart_density", new BEntity_float() );
		m_bodypart_scale_x_min = settings->addChild( "bodypart_scale_x_min", new BEntity_float() );
		m_bodypart_scale_x_max = settings->addChild( "bodypart_scale_x_max", new BEntity_float() );
		m_bodypart_scale_y_min = settings->addChild( "bodypart_scale_y_min", new BEntity_float() );
		m_bodypart_scale_y_max = settings->addChild( "bodypart_scale_y_max", new BEntity_float() );
		m_bodypart_scale_z_min = settings->addChild( "bodypart_scale_z_min", new BEntity_float() );
		m_bodypart_scale_z_max = settings->addChild( "bodypart_scale_z_max", new BEntity_float() );
		m_bodypart_spacing = settings->addChild( "bodypart_spacing", new BEntity_float() );
		m_bodypart_friction = settings->addChild( "bodypart_friction", new BEntity_float() );
		m_bodypart_restitution = settings->addChild( "bodypart_restitution", new BEntity_float() );

		// auto mutation_weights = settings->addChild( "mutation_weights", new BEntity() );
		// m_mutationweight_bodypart_add = mutation_weights->addChild( "mutationweight_bodypart_add", new BEntity_uint() );
		// m_mutationweight_bodypart_remove = mutation_weights->addChild( "mutationweight_bodypart_remove", new BEntity_uint() );
		// m_mutationweight_bodypart_rescale = mutation_weights->addChild( "mutationweight_bodypart_rescale", new BEntity_uint() );
		// m_mutationweight_head_add = mutation_weights->addChild( "mutationweight_head_add", new BEntity_uint() );
		// m_mutationweight_head_remove = mutation_weights->addChild( "mutationweight_head_remove", new BEntity_uint() );
		// m_mutationweight_eye_add = mutation_weights->addChild( "mutationweight_eye_add", new BEntity_uint() );
		// m_mutationweight_eye_remove = mutation_weights->addChild( "mutationweight_eye_remove", new BEntity_uint() );
		// m_mutationweight_spike_add = mutation_weights->addChild( "mutationweight_spike_add", new BEntity_uint() );
		// m_mutationweight_spike_remove = mutation_weights->addChild( "mutationweight_spike_remove", new BEntity_uint() );
		// m_mutationweight_constraint_alter = mutation_weights->addChild( "mutationweight_constraint_alter", new BEntity_uint() );
		// m_mutationweight_constraint_change_angle = mutation_weights->addChild( "mutationweight_constraint_change_angle", new BEntity_uint() );
		
		// m_mutation_chance->set( Buint(20) );
		// m_mutationruns_min->set( Buint(2) );
		// m_mutationruns_max->set( Buint(10) );
		// m_bodypart_min->set( Buint( 1 ) );
		// m_bodypart_max->set( Buint( 10 ) );
		// m_head_min->set( Buint( 1 ) );
		// m_head_max->set( Buint( 1 ) );
		// m_eye_min->set( Buint(1) );
		// m_eye_max->set( Buint(1) );
		// m_eyes_connect_to_heads->set( true );
		// m_spike_min->set( Buint( 0 ) );
		// m_spike_max->set( Buint( 0 ) );
		// m_bodypart_density->set( 1.0f );
		m_bodypart_scale_x_min->set( 0.1f * 2 );
		m_bodypart_scale_x_max->set( 2.0f * 2 );
		m_bodypart_scale_y_min->set( 0.1f * 2 );
		m_bodypart_scale_y_max->set( 2.0f * 2 );
		m_bodypart_scale_z_min->set( 0.1f * 2 );
		m_bodypart_scale_z_max->set( 2.0f * 2 );
		m_bodypart_spacing->set( 0.07f );
		m_bodypart_friction->set( 0.95f );
		m_bodypart_restitution->set( 0.95f );

		// m_mutationweight_bodypart_add->set( Buint(5) );
		// m_mutationweight_bodypart_remove->set( Buint(6) );
		// m_mutationweight_bodypart_rescale->set( Buint(10) );
		// m_mutationweight_head_add->set( Buint(5) );
		// m_mutationweight_head_remove->set( Buint(6) );
		// m_mutationweight_eye_add->set( Buint(5) );
		// m_mutationweight_eye_remove->set( Buint(6) );
		// m_mutationweight_spike_add->set( Buint(5) );
		// m_mutationweight_spike_remove->set( Buint(6) );
		// m_mutationweight_constraint_alter->set( Buint(10) );
		// m_mutationweight_constraint_change_angle->set( Buint(10) );

			// SKIPPED ONES FOR REFERENCE
// 				t_body_eye_rays_min = entityType_UINT
// 				t_body_eye_rays_max _maxentityType_UINT
	}

	void BodyFixed1Maker::make( BEntity* entity_parent )
	{
		entity_parent->addChild( "bodyparts", new BEntity() );
		auto t_constraints = entity_parent->addChild( "constraints", new BEntity() );
		
		auto critterding = entity_parent->topParent()->getChild("Scene", 1)->getChild( "Critterding", 1 );
		if ( critterding )
		{
			// exit (0);
		}
		
		if ( m_rng == 0)
		{
			m_rng = critterding->getChild( "random_number_generator" ); // FIXME PREFETCH
		}

		auto physics_world = critterding->getChild( "physicsworld", 1 );
		auto settings = entity_parent->parent()->parent()->parent()->getChild( "settings", 1 );
		auto bodypart_spacing = settings->getChild( "bodypart_spacing", 1 )->get_float();
		auto dropzone = critterding->getChild( "critter_system", 1 )->getChild( "settings", 1 )->getChild( "dropzone", 1 );

		// CENTRAL BODYPART  
			m_rng->set( "min", (Bint)0 );
			m_rng->set( "max", (Bint)dropzone->getChild( "size_x", 1 )->get_float() );
			auto central_bodypart_position_x = dropzone->getChild( "position_x", 1 )->get_float() + m_rng->get_int();

			m_rng->set( "max", (Bint)dropzone->getChild( "size_y", 1 )->get_float() );
			auto central_bodypart_position_y = dropzone->getChild( "position_y", 1 )->get_float() + m_rng->get_int();

			m_rng->set( "max", (Bint)dropzone->getChild( "size_z", 1 )->get_float() );
			auto central_bodypart_position_z = dropzone->getChild( "position_z", 1 )->get_float() + m_rng->get_int();

		// SCALES 
			auto central_bodypart_scale_x = 0.4f;
			auto central_bodypart_scale_y = 0.2f;
			auto central_bodypart_scale_z = 0.4f;

			// EXTRA BODYPARTS
			auto joint_bodypart_scale_x = 0.1f;
			auto joint_bodypart_scale_y = 0.2f;
			auto joint_bodypart_scale_z = 0.2f;

			auto leg_bodypart_scale_x = 0.4f;
			auto leg_bodypart_scale_y = 0.2f;
			auto leg_bodypart_scale_z = 0.2f;
			
		// auto central_bodypart1 = tergite(
		// 	central_bodypart_position_x, central_bodypart_position_y, central_bodypart_position_z, central_bodypart_scale_x, central_bodypart_scale_y, central_bodypart_scale_z,
		// 	leg_bodypart_scale_x, leg_bodypart_scale_y, leg_bodypart_scale_z );

		auto central_bodypart1 = tergite2( entity_parent, 
			central_bodypart_position_x, central_bodypart_position_y, central_bodypart_position_z, central_bodypart_scale_x, central_bodypart_scale_y, central_bodypart_scale_z,
			joint_bodypart_scale_x, joint_bodypart_scale_y, joint_bodypart_scale_z,
			leg_bodypart_scale_x, leg_bodypart_scale_y, leg_bodypart_scale_z );
		
		central_bodypart_position_z = central_bodypart_position_z - central_bodypart_scale_x - bodypart_spacing;
		central_bodypart_scale_x = 0.7f;
		central_bodypart_scale_z = 0.7f;

		auto central_bodypart2 = tergite2( entity_parent, 
			central_bodypart_position_x, central_bodypart_position_y, central_bodypart_position_z, central_bodypart_scale_x, central_bodypart_scale_y, central_bodypart_scale_z,
			joint_bodypart_scale_x, joint_bodypart_scale_y, joint_bodypart_scale_z,
			leg_bodypart_scale_x, leg_bodypart_scale_y, leg_bodypart_scale_z );

		// CONNECT 2 CENTRAL BODYPARTS
		{
			// a hinge
			auto hinge_entity = physics_world->addChild( "hinge", "Constraint_Hinge" );

			// set A bodypart
			auto bodyA_ref = hinge_entity->addChild( "bodyA", new BEntity_reference() );
			bodyA_ref->set( central_bodypart1 );

			// set B bodypart
			auto bodyB_ref = hinge_entity->addChild( "bodyB", new BEntity_reference() );
			bodyB_ref->set( central_bodypart2 );

			// get A & B  transforms from hinge
			auto t_a = hinge_entity->getChild( "localA", 1 );
			auto t_b = hinge_entity->getChild( "localB", 1 );

			// hinge position
			t_a->set( "position_z", -central_bodypart1->get_float( "scale_x") / 2 - bodypart_spacing / 2 );
			t_b->set( "position_z", +central_bodypart2->get_float( "scale_x" ) / 2 + bodypart_spacing / 2 );
			t_a->set( "pitch", 1.57f );
			t_b->set( "pitch", 1.57f );
			
			// hinge properties
			hinge_entity->getChild( "limit_low", 1 )->set( -0.5f );
			hinge_entity->getChild( "limit_high", 1 )->set( 0.5f );
			hinge_entity->getChild( "softness", 1 )->set( 0.999f );
			hinge_entity->getChild( "biasfactor", 1 )->set( 0.999f );
			hinge_entity->getChild( "relaxationfactor", 1 )->set( 0.5f );
			hinge_entity->getChild( "bidirectional", 1 )->set( true );
			

			// pull create trigger
			hinge_entity->set( "create_hinge", true );
			
			// REFERENCE TO EXTERNAL CHILD
			// FIXME needs to be in seperate "constraints" parent entity
				t_constraints->addChild( "external_hinge", new BEntity_external() )->set( hinge_entity );
		}

		// 3RD TERGITE
		bool three_bodyparts = false;
		if ( three_bodyparts )
		{
			auto central_bodypart3 = tergite2( entity_parent, 
				central_bodypart_position_x, central_bodypart_position_y, central_bodypart_position_z, central_bodypart_scale_x, central_bodypart_scale_y, central_bodypart_scale_z,
				joint_bodypart_scale_x, joint_bodypart_scale_y, joint_bodypart_scale_z,
				leg_bodypart_scale_x, leg_bodypart_scale_y, leg_bodypart_scale_z );
		
			// CONNECT 2 OTHER CENTRAL BODYPARTS
			{
				// a hinge
				auto hinge_entity = physics_world->addChild( "hinge", "Constraint_Hinge" );

				// set A bodypart
				auto bodyA_ref = hinge_entity->addChild( "bodyA", new BEntity_reference() );
				bodyA_ref->set( central_bodypart2 );

				// set B bodypart
				auto bodyB_ref = hinge_entity->addChild( "bodyB", new BEntity_reference() );
				bodyB_ref->set( central_bodypart3 );

				// get A & B  transforms from hinge
				auto t_a = hinge_entity->getChild( "localA", 1 );
				auto t_b = hinge_entity->getChild( "localB", 1 );

				// hinge position
				t_a->set( "position_z", -central_bodypart3->get_float( "scale_x") / 2 - bodypart_spacing / 2 );
				t_b->set( "position_z", +central_bodypart3->get_float( "scale_x" ) / 2 + bodypart_spacing / 2 );
				t_a->set( "pitch", 1.57f );
				t_b->set( "pitch", 1.57f );
				
				// hinge properties
				hinge_entity->getChild( "limit_low", 1 )->set( -0.5f );
				hinge_entity->getChild( "limit_high", 1 )->set( 0.5f );
				hinge_entity->getChild( "softness", 1 )->set( 0.999f );
				hinge_entity->getChild( "biasfactor", 1 )->set( 0.999f );
				hinge_entity->getChild( "relaxationfactor", 1 )->set( 0.5f );
				hinge_entity->getChild( "bidirectional", 1 )->set( true );
				

				// pull create trigger
				hinge_entity->set( "create_hinge", true );
				
				// REFERENCE TO EXTERNAL CHILD
				// FIXME needs to be in seperate "constraints" parent entity
					t_constraints->addChild( "external_hinge", new BEntity_external() )->set( hinge_entity );
			}
		}
		
	}
	
	void BodyFixed1::construct()
	{
		BodyFixed1Maker m;
		m.make( this );
	}

	BEntity* BodyFixed1::customCopy( BEntity* to_parent, BEntity* entity, std::map<BEntity*, BEntity*>& translation_map )
	{
		auto entity_new = to_parent->addChild( entity->name(), new BodyFixed1() );
		
		// HACK SPECIAL CASE
		// LOOP ENTITY & ENTITY_NEW TO ADD THEM TO THE TRANSLATION_MAP
		translation_map.insert( std::make_pair( entity, entity_new ) );
		
		auto bodyparts = entity->getChild( "bodyparts", 1 );
		auto constraints = entity->getChild( "constraints", 1 );
		auto bodyparts_new = entity_new->getChild( "bodyparts", 1 );
		auto constraints_new = entity_new->getChild( "constraints", 1 );
		translation_map.insert( std::make_pair( bodyparts, bodyparts_new ) );
		translation_map.insert( std::make_pair( constraints, constraints_new ) );

		// TRANSLATION_MAP: BODYPARTS
		{
			const auto& children_vector_new = bodyparts_new->children();
			auto child_new = children_vector_new.begin();
			for_all_children_of( bodyparts )
			{
				if ( child_new != children_vector_new.end() )
				{
					translation_map.insert( std::make_pair( *child, *child_new ) );
					translation_map.insert( std::make_pair( (*child)->get_reference(), (*child_new)->get_reference() ) );
				}
				child_new++;
			}
		}
		
		// TRANSLATION_MAP: CONSTRAINTS
		{
			const auto& children_vector_new = constraints_new->children();
			auto child_new = children_vector_new.begin();
			for_all_children_of( constraints )
			{
				if ( child_new != children_vector_new.end() )
				{
					translation_map.insert( std::make_pair( *child, *child_new ) );
					translation_map.insert( std::make_pair( (*child)->get_reference(), (*child_new)->get_reference() ) );
					translation_map.insert( std::make_pair( (*child)->get_reference()->getChild("angle", 1), (*child_new)->get_reference()->getChild("angle", 1) ) );

					// do body a and b here
				}
				child_new++;
			}
		}
		return entity_new;
	}
	
	
	BEntity* BodyFixed1Maker::tergite2( BEntity* body, float central_bodypart_position_x, float central_bodypart_position_y, float central_bodypart_position_z, float central_bodypart_scale_x, float central_bodypart_scale_y, float central_bodypart_scale_z, float joint_bodypart_scale_x, float joint_bodypart_scale_y, float joint_bodypart_scale_z, float leg_bodypart_scale_x, float leg_bodypart_scale_y, float leg_bodypart_scale_z )
	{
		auto t_constraints = body->getChild( "constraints", 1 );

			// find physicsworld
		auto physics_world = body->parent()->parent()->parent()->parent()->getChild( "physicsworld", 1 );
		auto settings = body->parent()->parent()->parent()->getChild( "settings", 1 );

		if ( physics_world )
		{
			auto bodypart_spacing = settings->getChild( "bodypart_spacing", 1 )->get_float();
			
			float shift = (central_bodypart_scale_x/2) + (leg_bodypart_scale_x/2) + bodypart_spacing;
			
			// construct
			auto central_bodypart     = constructBodypart( body, "bodypart_central", physics_world, central_bodypart_position_x, central_bodypart_position_y, central_bodypart_position_z, central_bodypart_scale_x, central_bodypart_scale_y, central_bodypart_scale_z );
			auto joint_bodypart_right = constructBodypart( body, "joint_bodypart_right", physics_world, central_bodypart_position_x + shift, central_bodypart_position_y, central_bodypart_position_z, joint_bodypart_scale_x, joint_bodypart_scale_y, joint_bodypart_scale_z );
			auto joint_bodypart_left  = constructBodypart( body, "joint_bodypart_left", physics_world, central_bodypart_position_x - shift, central_bodypart_position_y, central_bodypart_position_z, joint_bodypart_scale_x, joint_bodypart_scale_y, joint_bodypart_scale_z );
			auto leg_bodypart_right = constructBodypart( body, "bodypart_right", physics_world, central_bodypart_position_x + joint_bodypart_scale_x + shift, central_bodypart_position_y, central_bodypart_position_z, leg_bodypart_scale_x, leg_bodypart_scale_y, leg_bodypart_scale_z );
			auto leg_bodypart_left  = constructBodypart( body, "bodypart_left", physics_world, central_bodypart_position_x - joint_bodypart_scale_x - shift, central_bodypart_position_y, central_bodypart_position_z, leg_bodypart_scale_x, leg_bodypart_scale_y, leg_bodypart_scale_z );

			auto friction = settings->getChild( "bodypart_friction", 1 )->get_float();
			central_bodypart->set("friction", friction);
			joint_bodypart_right->set("friction", friction);
			joint_bodypart_left->set("friction", friction);
			leg_bodypart_right->set("friction", friction);
			leg_bodypart_left->set("friction", friction);

			auto restitution = settings->getChild( "bodypart_restitution", 1 )->get_float();
			central_bodypart->set("restitution", restitution);
			joint_bodypart_right->set("restitution", restitution);
			joint_bodypart_left->set("restitution", restitution);
			leg_bodypart_right->set("restitution", restitution);
			leg_bodypart_left->set("restitution", restitution);

			// CONNECT RIGHT BODYPART
			{
				// HINGE INNER
				{
					// a hinge
					auto hinge_entity = physics_world->addChild( "hinge", "Constraint_Hinge" );

					// set A bodypart
					auto bodyA_ref = hinge_entity->addChild( "bodyA", new BEntity_reference() );
					bodyA_ref->set( central_bodypart );

					// set B bodypart
					auto bodyB_ref = hinge_entity->addChild( "bodyB", new BEntity_reference() );
					bodyB_ref->set( joint_bodypart_right );

					// get A & B  transforms from hinge
					auto t_a = hinge_entity->getChild( "localA", 1 );
					auto t_b = hinge_entity->getChild( "localB", 1 );

					// hinge position
					t_a->set( "position_x", +central_bodypart->get_float( "scale_x") / 2 + bodypart_spacing / 2 );
					t_b->set( "position_x", -joint_bodypart_right->get_float( "scale_x" ) / 2 - bodypart_spacing / 2 );
					t_a->set( "pitch", 1.57f );
					t_b->set( "pitch", 1.57f );
					
					// // hinge properties
					hinge_entity->getChild( "limit_low", 1 )->set( -0.5f );
					hinge_entity->getChild( "limit_high", 1 )->set( 0.5f );
					// hinge_entity->getChild( "softness", 1 )->set( 0.9f );
					// hinge_entity->getChild( "biasfactor", 1 )->set( 0.9f );
					// hinge_entity->getChild( "relaxationfactor", 1 )->set( 1.0f );
					hinge_entity->getChild( "bidirectional", 1 )->set( true );

					// pull create trigger
					hinge_entity->set( "create_hinge", true );
					
					// REFERENCE TO EXTERNAL CHILD
						t_constraints->addChild( "external_hinge", new BEntity_external() )->set( hinge_entity );
				}

				// HINGE OUTER
				{
					// a hinge
					auto hinge_entity = physics_world->addChild( "hinge", "Constraint_Hinge" );

					// set A bodypart
					auto bodyA_ref = hinge_entity->addChild( "bodyA", new BEntity_reference() );
					bodyA_ref->set( joint_bodypart_right );

					// set B bodypart
					auto bodyB_ref = hinge_entity->addChild( "bodyB", new BEntity_reference() );
					bodyB_ref->set( leg_bodypart_right );

					// get A & B  transforms from hinge
					auto t_a = hinge_entity->getChild( "localA", 1 );
					auto t_b = hinge_entity->getChild( "localB", 1 );

					// hinge position
					t_a->set( "position_x", +joint_bodypart_right->get_float( "scale_x") / 2 + bodypart_spacing / 2 );
					t_b->set( "position_x", -leg_bodypart_right->get_float( "scale_x" ) / 2 - bodypart_spacing / 2 );
					
					// // hinge properties
					// hinge_entity->getChild( "limit_low", 1 )->set( 0.4f );
					// hinge_entity->getChild( "limit_high", 1 )->set( 0.9f );
					// hinge_entity->getChild( "softness", 1 )->set( 0.9f );
					// hinge_entity->getChild( "biasfactor", 1 )->set( 0.9f );
					// hinge_entity->getChild( "relaxationfactor", 1 )->set( 1.0f );

					// pull create trigger
					hinge_entity->set( "create_hinge", true );
					
					// REFERENCE TO EXTERNAL CHILD
						t_constraints->addChild( "external_hinge", new BEntity_external() )->set( hinge_entity );
				}
			}

			// CONNECT LEFT BODYPART
			{
				// HINGE INNER
				{
					// a hinge
					auto hinge_entity = physics_world->addChild( "hinge", "Constraint_Hinge" );

					// set A bodypart
					auto bodyA_ref = hinge_entity->addChild( "bodyA", new BEntity_reference() );
					bodyA_ref->set( central_bodypart );

					// set B bodypart
					auto bodyB_ref = hinge_entity->addChild( "bodyB", new BEntity_reference() );
					bodyB_ref->set( joint_bodypart_left );

					// get A & B  transforms from hinge
					auto t_a = hinge_entity->getChild( "localA", 1 );
					auto t_b = hinge_entity->getChild( "localB", 1 );

					// hinge position, flip them to mirror (pitch)
					t_a->set( "position_x", -central_bodypart->get_float( "scale_x") / 2 - bodypart_spacing / 2 );
					t_b->set( "position_x", +joint_bodypart_left->get_float( "scale_x" ) / 2 + bodypart_spacing / 2 );
					// t_b->set( "pitch", 3.141593f );
					t_a->set( "pitch", 1.57f );
					t_b->set( "pitch", 1.57f );
					
					// // hinge properties
					hinge_entity->getChild( "limit_low", 1 )->set( -0.5f );
					hinge_entity->getChild( "limit_high", 1 )->set( 0.5f );
					// hinge_entity->getChild( "softness", 1 )->set( 0.9f );
					// hinge_entity->getChild( "biasfactor", 1 )->set( 0.9f );
					// hinge_entity->getChild( "relaxationfactor", 1 )->set( 1.0f );
					hinge_entity->getChild( "bidirectional", 1 )->set( true );

					// pull create trigger
					hinge_entity->set( "create_hinge", true );
					
					// REFERENCE TO EXTERNAL CHILD
						t_constraints->addChild( "external_hinge", new BEntity_external() )->set( hinge_entity );
				}

				// HINGE OUTER
				{
					// a hinge
					auto hinge_entity = physics_world->addChild( "hinge", "Constraint_Hinge" );

					// set A bodypart
					auto bodyA_ref = hinge_entity->addChild( "bodyA", new BEntity_reference() );
					bodyA_ref->set( joint_bodypart_left );

					// set B bodypart
					auto bodyB_ref = hinge_entity->addChild( "bodyB", new BEntity_reference() );
					bodyB_ref->set( leg_bodypart_left );

					// get A & B  transforms from hinge
					auto t_a = hinge_entity->getChild( "localA", 1 );
					auto t_b = hinge_entity->getChild( "localB", 1 );

					// hinge position, flip them to mirror (pitch)
					t_a->set( "position_x", -joint_bodypart_left->get_float( "scale_x") / 2 - bodypart_spacing / 2 );
					t_b->set( "position_x", +leg_bodypart_left->get_float( "scale_x" ) / 2 + bodypart_spacing / 2 );
					t_a->set( "pitch", 3.141593f );
					t_b->set( "pitch", 3.141593f );
					
					// // hinge properties
					// hinge_entity->getChild( "limit_low", 1 )->set( 0.4f );
					// hinge_entity->getChild( "limit_high", 1 )->set( 0.9f );
					// hinge_entity->getChild( "softness", 1 )->set( 0.9f );
					// hinge_entity->getChild( "biasfactor", 1 )->set( 0.9f );
					// hinge_entity->getChild( "relaxationfactor", 1 )->set( 1.0f );

					// pull create trigger
					hinge_entity->set( "create_hinge", true );
					
					// REFERENCE TO EXTERNAL CHILD
						t_constraints->addChild( "external_hinge", new BEntity_external() )->set( hinge_entity );
				}
			}
			
			return central_bodypart;
		}
		return 0;
	}
	
	BEntity* BodyFixed1Maker::tergite_simple(
		BEntity* body,
		float central_bodypart_position_x,
		float central_bodypart_position_y,
		float central_bodypart_position_z,
		float central_bodypart_scale_x,
		float central_bodypart_scale_y,
		float central_bodypart_scale_z,
		float leg_bodypart_scale_x,
		float leg_bodypart_scale_y,
		float leg_bodypart_scale_z )
	{
		auto t_constraints = body->getChild( "constraints", 1 );

			// find physicsworld
		auto physics_world = body->parent()->parent()->parent()->parent()->getChild( "physicsworld", 1 );
		auto settings = body->parent()->parent()->parent()->getChild( "settings", 1 );

		if ( physics_world )
		{
			auto bodypart_spacing = settings->getChild( "bodypart_spacing", 1 )->get_float();
			float shift = (central_bodypart_scale_x/2) + (leg_bodypart_scale_x/2) + bodypart_spacing;
			
			// construct
			auto central_bodypart     = constructBodypart( body, "bodypart_central", physics_world, central_bodypart_position_x, central_bodypart_position_y, central_bodypart_position_z, central_bodypart_scale_x, central_bodypart_scale_y, central_bodypart_scale_z );
			auto leg_bodypart_right = constructBodypart( body, "bodypart_right", physics_world, central_bodypart_position_x + shift, central_bodypart_position_y, central_bodypart_position_z, leg_bodypart_scale_x, leg_bodypart_scale_y, leg_bodypart_scale_z );
			auto leg_bodypart_left  = constructBodypart( body, "bodypart_left", physics_world, central_bodypart_position_x - shift, central_bodypart_position_y, central_bodypart_position_z, leg_bodypart_scale_x, leg_bodypart_scale_y, leg_bodypart_scale_z );

			auto friction = settings->getChild( "bodypart_friction", 1 )->get_float();
			central_bodypart->set("friction", friction);
			leg_bodypart_right->set("friction", friction);
			leg_bodypart_left->set("friction", friction);

			auto restitution = settings->getChild( "bodypart_restitution", 1 )->get_float();
			central_bodypart->set("restitution", restitution);
			leg_bodypart_right->set("restitution", restitution);
			leg_bodypart_left->set("restitution", restitution);

			// CONNECT RIGHT BODYPART
			{
				// a hinge
				auto hinge_entity = physics_world->addChild( "hinge", "Constraint_Hinge" );

				// set A bodypart
				auto bodyA_ref = hinge_entity->addChild( "bodyA", new BEntity_reference() );
				bodyA_ref->set( central_bodypart );

				// set B bodypart
				auto bodyB_ref = hinge_entity->addChild( "bodyB", new BEntity_reference() );
				bodyB_ref->set( leg_bodypart_right );

				// get A & B  transforms from hinge
				auto t_a = hinge_entity->getChild( "localA", 1 );
				auto t_b = hinge_entity->getChild( "localB", 1 );

				// hinge position
				t_a->set( "position_x", +central_bodypart->get_float( "scale_x") / 2 + bodypart_spacing / 2 );
				t_b->set( "position_x", -leg_bodypart_right->get_float( "scale_x" ) / 2 - bodypart_spacing / 2 );

				// pull create trigger
				hinge_entity->set( "create_hinge", true );
				
				// REFERENCE TO EXTERNAL CHILD
					t_constraints->addChild( "external_hinge", new BEntity_external() )->set( hinge_entity );
			}

			// CONNECT LEFT BODYPART
			{
				// a hinge
				auto hinge_entity = physics_world->addChild( "hinge", "Constraint_Hinge" );

				// set A bodypart
				auto bodyA_ref = hinge_entity->addChild( "bodyA", new BEntity_reference() );
				bodyA_ref->set( central_bodypart );

				// set B bodypart
				auto bodyB_ref = hinge_entity->addChild( "bodyB", new BEntity_reference() );
				bodyB_ref->set( leg_bodypart_left );

				// get A & B  transforms from hinge
				auto t_a = hinge_entity->getChild( "localA", 1 );
				auto t_b = hinge_entity->getChild( "localB", 1 );

				// hinge position, flip them to mirror (pitch)
				t_a->set( "position_x", -central_bodypart->get_float( "scale_x") / 2 - bodypart_spacing / 2 );
				t_a->set( "pitch", 3.141593f );
				
				t_b->set( "position_x", +leg_bodypart_right->get_float( "scale_x" ) / 2 + bodypart_spacing / 2 );
				t_b->set( "pitch", 3.141593f );

				// // hinge properties
				// hinge_entity->getChild( "limit_low", 1 )->set( 0.4f );
				// hinge_entity->getChild( "limit_high", 1 )->set( 0.9f );
				// hinge_entity->getChild( "softness", 1 )->set( 0.9f );
				// hinge_entity->getChild( "biasfactor", 1 )->set( 0.9f );
				// hinge_entity->getChild( "relaxationfactor", 1 )->set( 1.0f );

				// pull create trigger
				hinge_entity->set( "create_hinge", true );
				
				// REFERENCE TO EXTERNAL CHILD
					t_constraints->addChild( "external_hinge", new BEntity_external() )->set( hinge_entity );
			}
			
			return central_bodypart;
		}
		return 0;
	}

	BEntity* BodyFixed1Maker::constructBodypart( BEntity* body, const char* name, BEntity* physics_world, float pos_x, float pos_y, float pos_z, float scale_x, float scale_y, float scale_z )
	{
		auto t_bodyparts = body->getChild( "bodyparts", 1 );
		
		// PHYSICS
			auto new_bodypart = physics_world->addChild( name, "PhysicsEntity_Cube" );
			new_bodypart->addChild( "weight", new BEntity_float_property() )->set( 1.0f ); // FIXME SETTING
			// new_bodypart->set("weight", 1.0f); // FIXME SETTING
			new_bodypart->addChild( "wants_deactivation", new BEntity_bool_property() )->set( false ); // FIXME SETTING
			

			body->parent()->parent()->getChild( "settings", 1 );

			new_bodypart->addChild( "scale_x", new BEntity_float_property() )->set( scale_x ); // FIXME SETTING
			new_bodypart->addChild( "scale_y", new BEntity_float_property() )->set( scale_y ); // FIXME SETTING
			new_bodypart->addChild( "scale_z", new BEntity_float_property() )->set( scale_z ); // FIXME SETTING
			// new_bodypart->set("scale_y", scale_y); // FIXME SETTING
			// new_bodypart->set("scale_x", scale_x); // FIXME SETTING
			// new_bodypart->set("scale_z", scale_z); // FIXME SETTING
			auto physics_transform = new_bodypart->getChild( "transform", 1 );

			physics_transform->getChild("position_x", 1)->set( pos_x );
			physics_transform->getChild("position_y", 1)->set( pos_y );
			physics_transform->getChild("position_z", 1)->set( pos_z );
			
			// REFERENCE TO EXTERNAL CHILD
				// auto central_bodypart_external_reference = t_bodyparts->addChild( "_external_child", new BEntity_reference() );
				// central_bodypart_external_reference->set( new_bodypart );
				t_bodyparts->addChild( "external_bodypart_physics", new BEntity_external() )->set( new_bodypart );
				
		// GRAPHICS
			BEntity* graphics_transform(0);
			// auto graphicsmodelsystem = body->topParent()->getChild("Scene", 1)->getChild("GraphicsModelSystem");
			auto graphicsmodelsystem = body->topParent()->getChild("Scene", 1)->getChild("Critterding", 1)->getChild("SDL GLWindow", 1)->getChild("GraphicsModelSystem", 1);

			if ( graphicsmodelsystem )
			{
				// FIXME do the graphics entity upstairs in body_system, we're assuming we need a graphics entity for all anyway
				// LOAD MODEL IF NEEDED, ADD TRANSFORM
				auto graphics_entity_critter = graphicsmodelsystem->getChild( "graphics_entity_critter", 1 );
				if ( !graphics_entity_critter )
				{
					graphics_entity_critter = graphicsmodelsystem->addChild("graphics_entity_critter", "GraphicsModel");
					graphics_transform = graphics_entity_critter->addChild("transform", "Transform");
					graphics_entity_critter->set("filename", "../share/modules/cube-critter.obj");
					
					// std::cout << $0 << std::endl;
				}
				else
				{
					graphics_transform = graphics_entity_critter->addChild("transform", "Transform");
				}
				
				graphics_transform->getChild( "scale_x", 1 )->set( scale_x );
				graphics_transform->getChild( "scale_y", 1 )->set( scale_y );
				graphics_transform->getChild( "scale_z", 1 )->set( scale_z );
				// graphics_transform->addChild( "scale_x", new BEntity_float )->set( scale_x );
				// graphics_transform->addChild( "scale_y", new BEntity_float )->set( scale_y );
				// graphics_transform->addChild( "scale_z", new BEntity_float )->set( scale_z );

				// REFERENCE TO EXTERNAL CHILD
					// auto external_reference = t_bodyparts->addChild( "_external_child", new BEntity_reference() );
					// external_reference->set( graphics_transform );
					t_bodyparts->addChild( "external_bodypart_graphics", new BEntity_external() )->set( graphics_transform );
			}
			physics_transform->connectServerServer(graphics_transform);

			return new_bodypart;
	}

