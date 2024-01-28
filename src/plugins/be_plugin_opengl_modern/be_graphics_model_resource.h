#ifndef BE_GRAPHICS_MODEL_RESOURCE_H_INCLUDED
#define BE_GRAPHICS_MODEL_RESOURCE_H_INCLUDED

// #include "be_texture.h"
// #include "be_model_system.h"
// #include "be_entity_graphics_model_system.h"

#include <boost/shared_ptr.hpp>
#include <boost/thread/future.hpp>
// #include "LinearMath/btVector3.h"
#include "LinearMath/btTransform.h"

	class BeFilesystem;
	class BeGraphicsModel;
	class BGraphicsModelSystem;
	class BeWorkerPool;
	class BeGraphicsSystem;
	class btTransform;

	template<typename T>
	class BeUnalign
	{
		public:
			BeUnalign(const T& value)
			{
				m_value = new T;
				*m_value = value;
			}
			BeUnalign(const BeUnalign& other)
			{
				m_value = new T;
				*m_value = *other.m_value;
			}
			~BeUnalign()
			{
				delete m_value;
			}
			operator T&()
			{
				return *m_value;
			}
		private:
			T* m_value;
	};

	class BeGraphicsModelResource
	{
		public:
			enum Status
			{
				eStatusLoading,
				eStatusError,
				eStatusReady
			};

			BeGraphicsModelResource(BeFilesystem& filesystem, boost::shared_ptr<BeWorkerPool> threadPool, const std::string& path, boost::shared_ptr<BeGraphicsSystem> graphicsSystem, BGraphicsModelSystem* graphicsModelSystem, const btVector3& scale, const btTransform& transform);
			boost::shared_ptr<BeGraphicsModel> get();
			void update();
			bool isReady();

		private:
			boost::shared_ptr<BeGraphicsModel> loadModel( boost::shared_ptr<BeGraphicsSystem> graphicsSystem, BeFilesystem& filesystem, const std::string& path, const btVector3& scale, const btTransform& transform );

			Status m_status;
			//boost::shared_ptr<BeTexture2D> m_texture;
			boost::shared_future< boost::shared_ptr<BeGraphicsModel> > m_futureGraphicsModel;
			boost::shared_ptr<BeGraphicsModel> m_graphicsModel;
			BGraphicsModelSystem* m_graphicsModelSystem;

	};

#endif 
