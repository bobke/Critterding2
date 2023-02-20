// #include "common/be_image.h"
#include "be_texture_store.h"
#include "be_texture_2d_resource.h"
// #include "be_worker_pool.h"


boost::shared_ptr<BeTexture2DResource> Texturestore::load(const std::string& filename)
{
// 	if ( m_resources[filename] )
// 	{
// 		return m_resources[filename];
// 	}
// 	else
// 	{
		boost::shared_ptr<BeTexture2DResource> t( new BeTexture2DResource(m_threadPool, filename.c_str()) );
// 		m_resources[filename]=t;
		return t;
// 	}
}


