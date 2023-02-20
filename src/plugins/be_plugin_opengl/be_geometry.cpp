#include "be_geometry.h"
#include "filesystem/be_filesystem.h"
#include <boost/make_shared.hpp>

	BeGeometry::BeGeometry()
	: m_numberVertices(0)
	, m_numberVIndices(0)
	{
	};
	
	void BeGeometry::setNumberVertices( unsigned int numberVertices ) 
	{ 
		m_numberVertices = numberVertices;
		vertices.reset(new btScalar[m_numberVertices]);
	}

	unsigned int BeGeometry::getNumberVertices() const
	{
		return m_numberVertices;
	}

	void BeGeometry::setNumberVIndices( unsigned int numberVIndices ) 
	{ 
		m_numberVIndices = numberVIndices;
		indices.reset(new int[m_numberVIndices]);
	}

	unsigned int BeGeometry::getNumberVIndices() const
	{
		return m_numberVIndices;
	} 

	
	boost::shared_ptr<BeGeometry> BeGeometrySystem::load(BeFilesystem& filesystem, const std::string& filename, const btVector3& scale, const btTransform& transform)
	{
	// 	// check if models exists
	// 	// 	cerr << "checking '" << filename << "'" << endl;
	// 	if ( m_resources[filename] )
	// 	{
	// 		// 		cerr << "texture '" << filename << "' is present" << endl;
	// 		return m_resources[filename];
	// 	}
		BeFile objBeFile;
		if ( filesystem.load(objBeFile, filename) )
		{
			const BeObjLoader obj( filesystem, objBeFile, scale, transform );
			boost::shared_ptr<BeGeometry> m(boost::make_shared<BeGeometry>());

			// copy materials
			m->m_materialMap = obj.matlist;
			// copy face materials
			m->facematerials = obj.facematerials;
			m->setNumberVertices( obj.getNumberVertices()*3 );
			m->setNumberVIndices( obj.getNumberVIndices() );
			
	// 		std::cout << "model: " << filename << std::endl;
	// 		std::cout << "number of triangles: " << (m->getNumberVertices()/3) << std::endl;

			
			
			for ( unsigned int i=0; i < obj.getNumberVIndices(); i++ )
			{
				m->indices[i] = obj.gVIndices[i] - 1;
			}
			
			memcpy(m->vertices.get(), obj.gVertices, obj.getNumberVertices()*sizeof(float)*3);
	// 		memcpy(m->vertices.get(), obj.gVertices, obj.getNumberVertices()*sizeof(float));
			
			m->buildElementArrayBuffer();
	// 		m_resources[filename]=m;
			return m;
		}
		return boost::shared_ptr<BeGeometry>();
	}

	void BeGeometry::buildElementArrayBuffer()
	{
		matlist_iterator it=m_materialMap.begin();
		for ( unsigned int i=0; i < m_materialMap.size(); ++i)
		{
			std::pair<const std::string, Material> pair=*it;
			unsigned int first=elementArrayBuffer.size();
			unsigned int count=0;
			for ( unsigned int j=0; j < facematerials.size(); j++ )
			{
				const Facematerial& facematerial = facematerials[j];
				if(facematerial.material==pair.first)
				{
					for( unsigned int k=0; k < facematerial.faceindex_number; ++k)
					{
						elementArrayBuffer.push_back(indices[facematerial.faceindex_first+k]);
						++count;
					}
				}
			}
			DrawCall drawCall;
			drawCall.m_first=first;
			drawCall.m_count=count;
			m_drawCalls.push_back(drawCall);
			++it;
		}
	}
		
