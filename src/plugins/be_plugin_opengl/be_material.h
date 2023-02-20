#ifndef BE_MATERIAL_H_INCLUDED
#define BE_MATERIAL_H_INCLUDED

#include "LinearMath/btVector3.h"

	class BeMaterial
	{
		public:
			BeMaterial() :
			m_ambient(1.0f, 1.0f, 1.0f),
			m_diffuse(1.0f, 1.0f ,1.0f),
			m_specular(0.0f, 0.0f, 0.0f),
			m_emission(0,0,0),
			m_shininess(0)
			{
			}

			BeMaterial(const BeMaterial& material) :
			m_ambient(material.m_ambient),
			m_diffuse(material.m_diffuse),
			m_specular(material.m_specular),
			m_emission(material.m_emission),
			m_shininess(material.m_shininess)
			{
			}
			
			void setAmbient(const btVector3& ambient) { m_ambient=ambient; }
			void setDiffuse(const btVector3& diffuse) { m_diffuse=diffuse; }
			void setSpecular(const btVector3& specular) { m_specular=specular;
		// 		m_ambient=specular;
		// 		m_diffuse=specular;
				
			}
			void setEmission(const btVector3& emission) { m_emission=emission; }
			void setShininess(const float shininess) { m_shininess=shininess; }

			btVector3& getAmbient() { return m_ambient; }
			btVector3& getDiffuse() { return m_diffuse; }
			btVector3& getSpecular() { return m_specular; }
			btVector3& getEmission() { return m_emission; }
			float& getShininess() { return m_shininess; }
			float* getShininessPointer() { return &m_shininess; }

			const btVector3& getAmbient() const { return m_ambient; }
			const btVector3& getDiffuse() const { return m_diffuse; }
			const btVector3& getSpecular() const { return m_specular; }
			const btVector3& getEmission() const { return m_emission; }
			float getShininess() const { return m_shininess; }
			const float* getShininessPointer() const { return &m_shininess; }

		private:
			btVector3	m_ambient;
			btVector3	m_diffuse;
			btVector3	m_specular;
			btVector3	m_emission;
			float		m_shininess;
	};

#endif
 
