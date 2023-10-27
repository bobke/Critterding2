#include "food_system.h"
#include "critter_system.h"
#include "kernel/be_entity_core_types.h"
#include <iostream>
#include "plugins/be_plugin_bullet/be_entity_mousepicker.h"
 
	void CdFoodSystem::construct()
	{
		auto settings = addChild( "settings", new BEntity() );
		m_unit_container = addChild( "unit_container", new BEntity() );
		
		m_number_of_units = settings->addChild( "number_of_units", new BEntity_uint() );
		m_maximum_age = settings->addChild( "maximum_age", new BEntity_uint() );
		m_intitial_energy = settings->addChild( "intitial_energy", new BEntity_float() );
		
		auto dropzone = settings->addChild( "dropzone", new BEntity() );
		m_dropzone_position_x = dropzone->addChild( "position_x", new BEntity_float() );
		m_dropzone_position_y = dropzone->addChild( "position_y", new BEntity_float() );
		m_dropzone_position_z = dropzone->addChild( "position_z", new BEntity_float() );
		m_dropzone_size_x = dropzone->addChild( "size_x", new BEntity_float() );
		m_dropzone_size_y = dropzone->addChild( "size_y", new BEntity_float() );
		m_dropzone_size_z = dropzone->addChild( "size_z", new BEntity_float() );
		
		m_number_of_units->set( Buint(1200) );
		m_intitial_energy->set( Bfloat(1500.0f) );
		m_maximum_age->set( Buint(16000) );
		m_dropzone_position_x->set( Bfloat(-70.0f) );
		m_dropzone_position_y->set( Bfloat(-17.0f) );
		m_dropzone_position_z->set( Bfloat(-170.0f) );
		m_dropzone_size_x->set( Bfloat(140.0f) );
		m_dropzone_size_y->set( Bfloat(2.2f) );
		m_dropzone_size_z->set( Bfloat(140.0f) );
		
		// m_number_of_units->set( Buint(1) );
		// m_intitial_energy->set( Bfloat(1500.0f) );
		// m_maximum_age->set( Buint(16000) );
		// m_dropzone_position_x->set( Bfloat(-95.0f) );
		// m_dropzone_position_y->set( Bfloat(-17.0f) );
		// m_dropzone_position_z->set( Bfloat(-195.0f) );
		// m_dropzone_size_x->set( Bfloat(190.0f) );
		// m_dropzone_size_y->set( Bfloat(2.2f) );
		// m_dropzone_size_z->set( Bfloat(190.0f) );
		
		m_insert_frame_interval = settings->addChild( "insert_frame_interval", new BEntity_uint() ); // FIXME why?
		m_insert_frame_interval->set( (Buint)2 );

		m_collisions = parent()->getChild("physicsworld", 1)->getChild("collisions", 1);
		m_mouse_picker = dynamic_cast<BMousePicker*>( parent()->getChild("external_mousepicker", 1)->get_reference() );
	}
	
	void CdFoodSystem::process()
	{
		// std::cout << "CdFoodSystem::process() : " << id() << std::endl;
		
		// AGE ALL UNITS WITH A DAY, COUNT UP ALL ENERGY FROM UNITS (FIXME ACCOUNT FOR CRITTERS, MAKE GLOBAL VARIABLE FOR TOTAL ENERGY)
			float total_energy_in_entities(0.0f);
			for_all_children_of( m_unit_container )
			{
				auto food_unit = dynamic_cast<CdFood*>( *child );
				if ( food_unit )
				{
					food_unit->setAge( 1+food_unit->age() );
					total_energy_in_entities += food_unit->energy();
				}
			}

			if ( m_critter_unit_container == 0 )
			{
				m_critter_unit_container = parent()->getChild( "critter_system", 1 )->getChild( "unit_container", 1 );
			}

			if ( ++m_framecount == m_insert_frame_interval->get_uint() || m_insert_frame_interval->get_uint() == 0 )
			{
				// std::cout << "yes" << std::endl;
				m_framecount = 0;
				// FIXME OPTIMIZE, COUNT UP ENERGY IN CRITTER SYSTEM
				{
					for_all_children_of2( m_critter_unit_container )
					{
						auto critter_unit = dynamic_cast<CdCritter*>( *child2 );
						if ( critter_unit )
						{
							total_energy_in_entities += critter_unit->energy();
						}
					}
				}

				// INSERT NEW FOOD UNITS 
				const float maximum_energy_in_system = m_intitial_energy->get_float() * m_number_of_units->get_uint();

				float missing_energy_in_system = maximum_energy_in_system - total_energy_in_entities;
				if ( missing_energy_in_system >= m_intitial_energy->get_float() )
				{
					auto food_unit = new CdFood();
					m_unit_container->addChild( "food_unit", food_unit );
					food_unit->setEnergy( m_intitial_energy->get_float() );

					// FIXME looking up by _external_child name isn't ok, we are lucky it's first of the children
					auto physics = food_unit->getChild("external_physics", 1)->get_reference();
					auto physics_transform = food_unit->getChild("external_physics", 1)->get_reference()->getChild( "transform" );

					physics->set("restitution", 0.5f);

					if ( m_rng == 0)
						m_rng = parent()->getChild( "random_number_generator" ); // FIXME PREFETCH

					if ( m_rng )
					{
						m_rng->set( "min", (Bint)0 );
						m_rng->set( "max", (Bint)m_dropzone_size_x->get_float() );
						float rand_x = m_rng->get_int();
						m_rng->set( "max", (Bint)m_dropzone_size_y->get_float() );
						float rand_y = m_rng->get_int();
						m_rng->set( "max", (Bint)m_dropzone_size_z->get_float() );
						float rand_z = m_rng->get_int();
						// std::cout << "randx : " << rand_x << " randy : " << rand_y << " randz : " << rand_z << std::endl;

						physics_transform->getChild("position_x", 1)->set( m_dropzone_position_x->get_float() + rand_x );
						physics_transform->getChild("position_y", 1)->set( m_dropzone_position_y->get_float() + rand_y );
						physics_transform->getChild("position_z", 1)->set( m_dropzone_position_z->get_float() + rand_z );
						physics_transform->getChild("rotation_euler_x", 1)->set( 0.0f );
						physics_transform->getChild("rotation_euler_y", 1)->set( 0.0f );
						physics_transform->getChild("rotation_euler_z", 1)->set( 0.0f );
					}

					// PREVENT FURTHER DELETION OR INSERTION OF FOOD IN THIS FRAME
						return;
				}
			}
			// else
			// {
				// std::cout << "no" << std::endl;
			// }

		// DIE FROM OLD AGE OR ENERGY DEPLETION
			for_all_children_of2( m_unit_container )
			{
				auto food_unit = dynamic_cast<CdFood*>( *child2 );
				if ( food_unit )
				{
					// reached max age or energy is depleted
					if ( food_unit->age() >= m_maximum_age->get_uint() || food_unit->energy() <= 0.0f )
					{
						removeFood( food_unit );

						// PREVENT FURTHER DELETION OR INSERTION OF FOOD IN THIS FRAME
							return; 
					}
				}
			}
	}

	void CdFoodSystem::removeFood( BEntity* entity )
	{
		// HACK first external child one is body
		auto bodypart = entity->getChild( "external_physics", 1 )->get_reference();
		
		// COLLISIONS
			while ( removeFromCollisions( bodypart ) ) {;}

		// MOUSEPICKER
			m_mouse_picker->removeGrabbedEntity( bodypart );

		// ACTUAL REMOVAL
			m_unit_container->removeChild( entity );
	}

	bool CdFoodSystem::removeFromCollisions( BEntity* to_remove )
	{
		for_all_children_of( m_collisions )
		{
			auto e1 = (*child)->getChild( "entity1", 1 )->get_reference();
			auto e2 = (*child)->getChild( "entity2", 1 )->get_reference();
			
			if ( e1 == to_remove || e2 == to_remove )
			{
				// std::cout << "removing food" << std::endl;
				m_collisions->removeChild( *child );
				// std::cout << "removing food done" << std::endl;
				return true;
			}
		}
		return false;
	}	

	void CdFood::construct()
	{
		m_age = addChild( "age", new BEntity_uint() );
		m_energy = addChild( "energy", new BEntity_float() );

		// PHYSICS ENTITY
			auto physicsworld = parent()->parent()->parent()->getChild("physicsworld", 1);
			BEntity* physics_transform(0);
			if ( physicsworld )
			{
				auto food_physics_entity = physicsworld->addChild( "physics_entity_food", "PhysicsEntity_Cube" );
// 				auto food_physics_entity = physicsworld->addChild( "physics_entity_food", "PhysicsEntity" );
// 				food_physics_entity->set("filename", "/projects/bengine-new/share/stuntcoureur/modules/cube-food.obj");
				food_physics_entity->set("weight", 1.0f); // FIXME SETTING
				physics_transform = food_physics_entity->getChild( "transform" );

				if ( physics_transform )
				{
// 					physics_transform->getChild("position_x", 1)->set( 0.0f );
// 					physics_transform->getChild("position_y", 1)->set( 20.0f );
// 					physics_transform->getChild("position_z", 1)->set( -100.0f );
				}

				// REFERENCE TO EXTERNAL CHILD
					addChild( "external_physics", new BEntity_external() )->set( food_physics_entity );
			}

		// GRAPHICS ENTITY
			BEntity* graphics_transform(0);
			auto graphicsmodelsystem = topParent()->getChild("Scene", 1)->getChild("Critterding", 1)->getChild("SDL GLWindow", 1)->getChild("GraphicsModelSystem", 1);
			if ( graphicsmodelsystem )
			{
				// LOAD MODEL IF NEEDED, ADD TRANSFORM
				auto graphics_entity_food = graphicsmodelsystem->getChild( "graphics_entity_food", 1 );
				if ( !graphics_entity_food )
				{
					graphics_entity_food = graphicsmodelsystem->addChild("graphics_entity_food", "GraphicsModel");
					// BEntity* color = graphics_entity_food->addChild("BglColor3f", "glColor3f");
					// color->set("R", 0.0f);
					// color->set("G", 1.0f);
					// color->set("B", 0.0f);

					graphics_transform = graphics_entity_food->addChild("transform", "Transform");
					graphics_entity_food->set("filename", "../share/modules/cube-food.obj");
				}
				else
				{
					graphics_transform = graphics_entity_food->addChild("transform", "Transform");
				}

				// REFERENCE TO EXTERNAL CHILD
					addChild( "external_graphics", new BEntity_external() )->set( graphics_transform );
			}

			physics_transform->connectServerServer(graphics_transform);
	}
	
	
	
	
	
	
	
// 	BeRand::BeRand()
// 	{
// 		// Seed
// 		srand( 111 );
// 	}
// 
// 	const int BeRand::get(const int minimum, const int maximum) const
// 	{
// 		if ( maximum > minimum )
// 		{
// 			return ((rand() % (maximum-minimum+1)) + minimum);
// 		}
// 		else
// 		{
// 			return minimum;
// 		}
// 	}
