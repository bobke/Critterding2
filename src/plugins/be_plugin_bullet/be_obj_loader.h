#ifndef BE_OBJ_LOADER_H_INCLUDED
#define BE_OBJ_LOADER_H_INCLUDED

#define BOOST_BIND_GLOBAL_PLACEHOLDERS

#include "be_material.h"
#include <boost/shared_ptr.hpp>
#include <boost/scoped_array.hpp>

	// class BeTexture2DResource;
	class BeFilesystem;
	class BeFile;
	class btTransform;

	//Andy - to be renamed, probably will become BeEffect eventually
	class Material
	{
		public:
			std::string m_imagePath;
			std::string m_imagePathBump;
			BeMaterial m_material;
			// boost::shared_ptr<BeTexture2DResource> m_imageTexture2D;
			// boost::shared_ptr<BeTexture2DResource> m_imageTexture2DBump;
			
			Material() {};
			~Material() {};
	};

	struct Facematerial
	{
		unsigned int faceindex_first;
		unsigned int faceindex_number;
		std::string material;
	};

	class BeObjLoader
	{
		public:
			// FIXME DISABLED FOR NOW
	// 		BeObjLoader( BeFilesystem& filesystem, BeFile& befile, const Vector3& scale );
			BeObjLoader( BeFilesystem& filesystem, BeFile& befile, const btVector3& scale, const btTransform& transform );
			~BeObjLoader();

			std::string m_filename;

			unsigned int getNumberVertices() const { return m_numberVertices; }
			unsigned int getNumberNormals() const { return m_numberNormals; }
			unsigned int getNumberTexCoor() const { return m_numberTexCoor; }
			unsigned int getNumberVIndices() const { return m_numberVIndices; }
	// 		unsigned int m_numberTIndices const { return m_numberTIndices; }
	// 		unsigned int m_numberNIndices const { return m_numberNIndices; }
			
			btScalar* gVertices;
			float* gNormals;
			float* gTexCoor;
			int* gVIndices;
			int* gTIndices;
			int* gNIndices;
			
			std::unordered_map<std::string, Material> matlist;
			typedef std::unordered_map <std::string, Material>::const_iterator matlist_iterator;
			matlist_iterator matit;

			std::vector<Facematerial> facematerials;
			void loadMaterialfile( BeFilesystem& filesystem, const std::string& mpath, const std::string& file );
			
		private:

			inline void addFace( const int vi1, const int vi2, const int vi3, const int ti1, const int ti2, const int ti3, const int ni1, const int ni2, const int ni3 );

			// FIXME check if all of these are needed
			unsigned int m_numberVertices;
			unsigned int m_numberNormals;
			unsigned int m_numberTexCoor;
			unsigned int m_numberVIndices;
			unsigned int m_numberTIndices;
			unsigned int m_numberNIndices;

	// 		BeLogDebug m_logDebug;
	};

#endif
 
