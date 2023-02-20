#ifndef BE_GEOMETRY_H_INCLUDED
#define BE_GEOMETRY_H_INCLUDED

#include "be_material.h"
#include <unordered_map>
#include <string>
#include <GL/glew.h>
// #include <GL/gl.h>
#include "be_obj_loader.h"

	class BeGeometry
	{
		private:
			typedef std::unordered_map< std::string, Material > MaterialMap;
		public:
			BeGeometry();
			~BeGeometry() {};

			void setNumberVertices( unsigned int numberVertices );
			unsigned int getNumberVertices() const;

			void setNumberVIndices( unsigned int numberVIndices );
			unsigned int getNumberVIndices() const;

			boost::scoped_array<btScalar> vertices;
			boost::scoped_array<int> indices; 

			MaterialMap m_materialMap;
			std::vector<Facematerial> facematerials;

			std::vector<GLint> elementArrayBuffer;
// 			std::vector<GLint> elementArrayBuffer;

			struct DrawCall
			{
				unsigned int m_first;
				unsigned int m_count;
			};

			std::vector<DrawCall> m_drawCalls;

			typedef std::unordered_map <std::string, Material>::const_iterator matlist_iterator;

			void buildElementArrayBuffer();

		private:
			unsigned int m_numberVertices;
			unsigned int m_numberVIndices;
	};

	class BeGeometrySystem
	{
		public:
			boost::shared_ptr<BeGeometry> load( BeFilesystem& filesystem, const std::string& filename, const btVector3& scale, const btTransform& transform);
	};

 
#endif
