#pragma once

#include "kernel/be_entity_interface.h"
#include <boost/shared_ptr.hpp>
#include "be_model_system.h"
#include "filesystem/be_filesystem.h"

	class BDepthMapViewer : public BEntity
	{
		public:
			BDepthMapViewer();
			virtual ~BDepthMapViewer() {};

			void construct();
			void process();
			void process_post();

			boost::shared_ptr<BeGraphicsEffect> m_effect_depthmap;

		private:
			BEntity* m_active;
			// depthmap viewer
			GLuint VAO;
			GLuint VBO;
	}; 

