#ifndef BE_MODEL_SYSTEM_H_INCLUDED
#define BE_MODEL_SYSTEM_H_INCLUDED

#include "be_obj_loader.h"
#include <boost/scoped_ptr.hpp>
#include <GL/glew.h>

	class BeArrayBuffer;
	class BeElementArrayBuffer;
	class BeGraphicsSystem;
	class BeVertexArray;
	class BeProgram;
	class Material;
	class Texturestore;

	class BeGraphicsModel
	{
			friend class BGraphicsModelSystem;
			friend class BeGraphicsModelResource;
		public:
			BeGraphicsModel( boost::shared_ptr<BeGraphicsSystem> system, const std::string& filename );
			
// 			BeGraphicsModel( boost::shared_ptr<BeGraphicsSystem> system, const std::string& filename );
			virtual ~BeGraphicsModel();

			const std::string&	getFilename() const;
			
			void setNumberVertices( unsigned int numberVertices );
			unsigned int getNumberVertices() const;
			void setNumberNormals( unsigned int numberNormals );
			unsigned int getNumberNormals() const;
			void setNumberTexCoor( unsigned int numberTexCoor );
			unsigned int getNumberTexCoor() const;
			void setNumberVIndices( unsigned int numberVIndices ) ;
			unsigned int getNumberVIndices() const;

			boost::scoped_array<btScalar> vertices;
			boost::scoped_array<float> normals;
			boost::scoped_array<float> texcoor;
			boost::scoped_array<int> indices; 

			std::vector<GLint> elementArrayBuffer;

			std::unordered_map<std::string, Material> matlist;
			std::vector<Facematerial> facematerials;

			unsigned int 		numberOfMaterials();
// 			virtual void		draw( const btTransform& transform );
			void				draw();

		private:
			
			
			void			upload(Texturestore& textureStore);
			void 			buildElementArrayBuffer();
			std::string		m_filename;

			unsigned int m_numberVertices;
			unsigned int m_numberNormals;
			unsigned int m_numberTexCoor;
			unsigned int m_numberVIndices;
			
			boost::scoped_ptr<BeArrayBuffer>	m_arrayBuffer;
			boost::scoped_ptr<BeElementArrayBuffer>	m_elementArrayBuffer;
			boost::scoped_ptr<BeVertexArray>	m_vertexArray;
			GLint tex1Loc;

			boost::shared_ptr<BeGraphicsSystem> m_system;
			bool				m_draw_blend_is_disabled;
		public:
			typedef std::unordered_map <std::string, Material>::const_iterator matlist_iterator;
			matlist_iterator matit;

			struct DrawCall
			{
				unsigned int m_first;
				unsigned int m_count;
			};

			std::vector<DrawCall> m_drawCalls;

			void loadMaterialfile( const std::string& mpath, const std::string& file );

	};

	class BeGraphicsEffect
	{
		public:
			BeGraphicsEffect(BeFilesystem& fileSystem);
			BeGraphicsEffect(BeFilesystem& fileSystem, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
			~BeGraphicsEffect();
			void loadCompileAndAttachVertexShader(const std::string& path);
			void loadCompileAndAttachFragmentShader(const std::string& path);
			void link();

			boost::shared_ptr<BeProgram> m_program;
			BeFilesystem& m_fileSystem;
	};

#endif
