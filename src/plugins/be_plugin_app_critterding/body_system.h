#pragma once

#include "kernel/be_entity_interface.h"

	//  SYSTEM
		class BodySystem : public BEntity
		{
			public:
				BodySystem() {};
				const char* class_id() const { return "CdBodySystem"; }
				virtual ~BodySystem() {};

				void construct();
// 				void process();

			private:
				// FOOD CONTAINER
				BEntity* m_unit_container;

				// BEntity* m_mutation_chance;
				// BEntity* m_mutationruns_min;
				// BEntity* m_mutationruns_max;
				// BEntity* m_bodypart_min;
				// BEntity* m_bodypart_max;
				// BEntity* m_head_min;
				// BEntity* m_head_max;
				// BEntity* m_eye_min;
				// BEntity* m_eye_max;
				// BEntity* m_eyes_connect_to_heads;
				// BEntity* m_spike_min;
				// BEntity* m_spike_max;
				// BEntity* m_bodypart_density;
				BEntity* m_bodypart_scale_x_min;
				BEntity* m_bodypart_scale_x_max;
				BEntity* m_bodypart_scale_y_min;
				BEntity* m_bodypart_scale_y_max;
				BEntity* m_bodypart_scale_z_min;
				BEntity* m_bodypart_scale_z_max;
				BEntity* m_bodypart_spacing;
				BEntity* m_bodypart_friction;
				BEntity* m_bodypart_restitution;
				BEntity* m_bodypart_density;

				// BEntity* m_mutationweight_bodypart_add;
				// BEntity* m_mutationweight_bodypart_remove;
				// BEntity* m_mutationweight_bodypart_rescale;
				// BEntity* m_mutationweight_head_add;
				// BEntity* m_mutationweight_head_remove;
				// BEntity* m_mutationweight_eye_add;
				// BEntity* m_mutationweight_eye_remove;
				// BEntity* m_mutationweight_spike_add;
				// BEntity* m_mutationweight_spike_remove;
				// BEntity* m_mutationweight_constraint_alter;
				// BEntity* m_mutationweight_constraint_change_angle;

				
		};

		class BodyFixed1Maker
		{
			public:
				BodyFixed1Maker() : m_rng(0) {};
				// const char* class_id() const { return "BodyFixed1"; }
				virtual ~BodyFixed1Maker() {};

				void make( BEntity* entity_parent );
				BEntity* tergite_simple( BEntity* body, float central_bodypart_position_x, float central_bodypart_position_y, float central_bodypart_position_z, float central_bodypart_scale_x, float central_bodypart_scale_y, float central_bodypart_scale_z, float extra_bodypart_scale_x, float extra_bodypart_scale_y, float extra_bodypart_scale_z );
				BEntity* tergite2( BEntity* body, float central_bodypart_position_x, float central_bodypart_position_y, float central_bodypart_position_z, float central_bodypart_scale_x, float central_bodypart_scale_y, float central_bodypart_scale_z, float center_bodypart_scale_x, float center_bodypart_scale_y, float center_bodypart_scale_z, float extra_bodypart_scale_x, float extra_bodypart_scale_y, float extra_bodypart_scale_z );
				BEntity* constructBodypart( BEntity* body, const char* name, BEntity* physics_world, float pos_x, float pos_y, float pos_z, float scale_x, float scale_y, float scale_z );
// 				void process();
				BEntity* m_rng;
		};
		
		
		class BodyFixed1 : public BEntity
		{
			public:
				BodyFixed1() : m_rng(0) {};
				const char* class_id() const { return "BodyFixed1"; }
				virtual ~BodyFixed1() {};

				void construct();
				BEntity* tergite_simple( float central_bodypart_position_x, float central_bodypart_position_y, float central_bodypart_position_z, float central_bodypart_scale_x, float central_bodypart_scale_y, float central_bodypart_scale_z, float extra_bodypart_scale_x, float extra_bodypart_scale_y, float extra_bodypart_scale_z );
				BEntity* tergite2( float central_bodypart_position_x, float central_bodypart_position_y, float central_bodypart_position_z, float central_bodypart_scale_x, float central_bodypart_scale_y, float central_bodypart_scale_z, float center_bodypart_scale_x, float center_bodypart_scale_y, float center_bodypart_scale_z, float extra_bodypart_scale_x, float extra_bodypart_scale_y, float extra_bodypart_scale_z );
				BEntity* constructBodypart( const char* name, BEntity* physics_world, float pos_x, float pos_y, float pos_z, float scale_x, float scale_y, float scale_z );
// 				void process();
				BEntity* m_rng;

				virtual BEntity* customCopy( BEntity* to_parent, BEntity* entity, std::map<BEntity*, BEntity*>& translation_map );
		};

