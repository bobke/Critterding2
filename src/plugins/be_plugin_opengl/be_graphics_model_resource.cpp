#include "be_graphics_model_resource.h"
#include "be_model_system.h"
#include "be_entity_graphics_model_system.h"
#include "be_worker_pool.h"

	BeGraphicsModelResource::BeGraphicsModelResource(BeFilesystem& filesystem, boost::shared_ptr<BeWorkerPool> threadPool, const std::string& path, boost::shared_ptr<BeGraphicsSystem> graphicsSystem, BGraphicsModelSystem* graphicsModelSystem, const btVector3& scale, const btTransform& transform)
	: m_status(eStatusLoading)
	, m_graphicsModelSystem(graphicsModelSystem)
	{
		m_futureGraphicsModel=threadPool->schedule< boost::shared_ptr<BeGraphicsModel> >(boost::bind(&BeGraphicsModelResource::loadModel, this, graphicsSystem, filesystem, path, BeUnalign<btVector3>(scale), BeUnalign<btTransform>(transform)));
	}
	
	boost::shared_ptr<BeGraphicsModel> BeGraphicsModelResource::get()
	{
		return isReady() ? m_graphicsModel : boost::shared_ptr<BeGraphicsModel>();
	}

	bool BeGraphicsModelResource::isReady()
	{
		update();
		return m_status==eStatusReady;
	}


	void BeGraphicsModelResource::update()
	{
		if(m_status==eStatusLoading)
		{
			if(m_futureGraphicsModel.is_ready())
			{
				boost::shared_ptr<BeGraphicsModel> testGraphicsModel=m_futureGraphicsModel.get();
				if ( testGraphicsModel )
				{

					m_graphicsModel=testGraphicsModel;
					m_graphicsModel->upload(*m_graphicsModelSystem->m_textureStore);
					m_status=eStatusReady;
				}
				else
				{
					m_status=eStatusError;
					// std::cout << "client model: loading failed" << std::endl;
				}
			}
		}
	}

	boost::shared_ptr<BeGraphicsModel> BeGraphicsModelResource::loadModel( boost::shared_ptr<BeGraphicsSystem> graphicsSystem, BeFilesystem& filesystem, const std::string& path, const btVector3& scale, const btTransform& transform )
	{
// 		std::cout << "client model: started loading : '" << path << "'" << std::endl;
		BeFile objBeFile;
		if ( filesystem.load(objBeFile, path) )
		{
			BeObjLoader obj( filesystem, objBeFile, scale, transform );
			boost::shared_ptr<BeGraphicsModel> m(new BeGraphicsModel( graphicsSystem, path ));

			// 	cerr << "model: " << m->name << endl;
			// 	cerr << "number of triangles: " << (m->m_numberVIndices/3) << endl;

			// copy materials
			m->matlist = obj.matlist;
			// copy face materials
			m->facematerials = obj.facematerials;

			m->setNumberVertices( obj.getNumberVIndices()*3 );
			m->setNumberNormals( obj.getNumberVIndices()*3 );
			m->setNumberTexCoor( obj.getNumberVIndices()*2 );
			m->setNumberVIndices( obj.getNumberVIndices() );

			for ( unsigned int i=0; i < obj.getNumberVIndices(); i++ )
			{
				m->indices[i] = i;
				if ( obj.gVIndices[i] > 0 )
				{
					const int index = (obj.gVIndices[i] - 1) * 3;
					memcpy(&m->vertices[(i*3)], &obj.gVertices[index], sizeof(float)*3);
				}
				else
				{
					memset(&m->vertices[(i*3)], 0, sizeof(float)*3);
				}
				if ( obj.gTIndices[i] > 0 )
				{
					const int tindex = (obj.gTIndices[i] - 1) * 2;
					memcpy(&m->texcoor[(i*2)], &obj.gTexCoor[(tindex)], sizeof(float)*2);
				}
				else
				{
					memset(&m->texcoor[(i*2)], 0, sizeof(float)*2);
				}
				if ( obj.gNIndices[i] > 0 )
				{
					const int nindex = (obj.gNIndices[i] - 1) * 3;
					memcpy(&m->normals[(i*3)], &obj.gNormals[nindex], sizeof(float)*3);
				}
				else
				{
					memset(&m->normals[(i*3)], 0, sizeof(float)*3);
				}
			}
// 			std::cout << "client model: loading ok: '" << path << "'" << std::endl;
			return m;
		}
		else
		{
			std::cout << "WARNING client model: loading failed: '" << path << "'" << std::endl;
		}
		
		m_status = eStatusError;
		return boost::shared_ptr<BeGraphicsModel>();
	}
