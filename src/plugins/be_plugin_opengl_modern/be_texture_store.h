#ifndef TEXTURESTORE_H_INCLUDED
#define TEXTURESTORE_H_INCLUDED

#include <string>
#include <boost/shared_ptr.hpp>

	class BeTexture2DResource;
	class BeWorkerPool;
	
	class Texturestore
	{
		public:
// 			Texturestore(boost::shared_ptr<BeWorkerPool> threadPool) : m_threadPool(threadPool) {};
			Texturestore(boost::shared_ptr<BeWorkerPool> threadPool) : m_threadPool(threadPool) {};
			~Texturestore() {};
			boost::shared_ptr<BeTexture2DResource> load(const std::string& filename);
			boost::shared_ptr<BeWorkerPool> m_threadPool; 
	// 		std::map<std::string, boost::shared_ptr<BeTexture2DResource> > m_resources;
	};

#endif
