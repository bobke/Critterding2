 
#ifndef BE_TEXTURE_H_INCLUDED
#define BE_TEXTURE_H_INCLUDED

// #include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>

// #include <QtOpenGL>
// #include <QtOpenGL/QGLWidget>
class BeTexture
{
public:
protected:
	BeTexture(const GLenum target);
	~BeTexture();
public:
	GLuint handle() const { return m_handle; }

	void bind();
	void unbind();

	void parameter(const GLenum name, const GLint param);
	void parameter(const GLenum name, const GLfloat param);
	void data(const GLint level, const GLint internalformat, const GLsizei width, const GLsizei height, const GLint border, const GLenum format, const GLenum type, const GLvoid* const data);
	void generateMipmap();
private:
	const GLenum	m_target;
	GLuint			m_handle;
};

class BeTexture2D : public BeTexture
{
public:
	BeTexture2D() : BeTexture(GL_TEXTURE_2D) {}
	BeTexture2D(const GLenum internalFormat, const GLsizei width, const GLsizei height);
	~BeTexture2D() {}
};

// class BeImageTexture2D : public BeTexture2D
// {
// public:
// 	BeImageTexture2D(const std::string& path)
// 	{
// 		QImage image(path.c_str());
// 		if(!image.isNull())
// 		{
// 			image=QGLWidget::convertToGLFormat(image);
// // 			data(0, 4, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
// //             parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
// //             parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// //             parameter(GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
// 			std::cout << "LOOKS LIKE I'M BEGIN USED" << std::endl;
//             generateMipmap();
// 		}
// 	}
// };

#endif
