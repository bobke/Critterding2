#ifndef BE_GRAPHICS_MODEL_SYSTEM_H_INCLUDED
#define BE_GRAPHICS_MODEL_SYSTEM_H_INCLUDED

#include "kernel/be_entity_interface.h"
#include "filesystem/be_filesystem.h"
#include <boost/shared_ptr.hpp>
// #include "LinearMath/btTransform.h"
#include "be_model_system.h"

	class BeGraphicsModelResource;
	class BeWorkerPool;
	class Texturestore;
	class BeGraphicsSystem;

	class BGraphicsModelSystem : public BEntity
	{
		friend class BeGraphicsModelResource;
		public:
			BGraphicsModelSystem();
			virtual ~BGraphicsModelSystem();
			
			boost::shared_ptr<BeGraphicsModelResource> load( const std::string& filename, boost::shared_ptr<BeGraphicsSystem> graphicsSystem, BGraphicsModelSystem* instance, const btVector3& scale, const btTransform& transform );
			boost::shared_ptr<BeGraphicsSystem> m_graphicsSystem;
			boost::shared_ptr<BeGraphicsEffect> m_effect;

		private:
			BeFilesystem m_filesystem;
			boost::shared_ptr<BeWorkerPool> m_workerPool;
			Texturestore* m_textureStore;
	// 		typedef std::unordered_map<std::string, boost::shared_ptr<BeGraphicsModelResource> > ResourceMap;
	// 		ResourceMap m_resources;
	}; 

#endif
