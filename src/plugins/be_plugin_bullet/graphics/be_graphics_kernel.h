#ifndef BE_GRAPHICS_KERNEL_H_INCLUDED
#define BE_GRAPHICS_KERNEL_H_INCLUDED

#include <GL/glew.h>
#include <GL/gl.h>

class BeGraphicsKernel
{
public:

	//
	//common
	//

	void clear(const GLbitfield mask);
	
	void flush();

	void enable(const GLenum cap);
	void disable(const GLenum cap);

	void hint(const GLenum target, const GLenum mode);

	void shadeModel(const GLenum mode);

	void cullFace(const GLenum mode);

	void drawArrays(const GLenum mode, const GLint first, const GLsizei count);

	void genFramebuffers(const GLsizei n, GLuint* const ids);
	void deleteFramebuffers(const GLsizei n, const GLuint* const ids);
	void bindFramebuffer(const GLenum target, const GLuint framebuffer);
	void framebufferTexture2D(const GLenum target, const GLenum attachment, const GLenum textarget, const GLuint texture, const GLint level);
	void framebufferRenderbuffer(const GLenum target, const GLenum attachment, const GLenum renderbuffertarget, const GLuint renderbuffer);
	GLenum checkFramebufferStatus(const GLenum target);
	void blitFramebuffer(const GLint srcX0, const GLint srcY0, const GLint srcX1, const GLint srcY1, const GLint dstX0, const GLint dstY0, const GLint dstX1, const GLint dstY1, const GLbitfield mask, const GLenum filter);

	void genRenderbuffers(const GLsizei n, GLuint* const ids);
	void deleteRenderbuffers(const GLsizei n, const GLuint* const ids);
	void bindRenderbuffer(const GLenum target, const GLuint renderbuffer);
	void renderbufferStorage(const GLenum target, const GLenum internalformat, const GLsizei width, const GLsizei height);
	void renderbufferStorageMultisample(const GLenum target, const GLsizei samples, const GLenum internalformat, const GLsizei width, const GLsizei height);

	void genTextures(const GLsizei n, GLuint* const textures);
	void deleteTextures(const GLsizei n, const GLuint* const textures);
	void bindTexture(const GLenum target, const GLuint texture);
	void bindMultiTexture(const GLint texunit, const GLenum target, const GLuint texture);
	void texParameteri(const GLenum target, const GLenum pname, const GLint param);
	void texImage2D(const GLenum target, const GLint level, const GLint internalformat, const GLsizei width, const GLsizei height, const GLint border, const GLenum format, const GLenum type, const GLvoid* const data);
	void generateMipmap(const GLenum target);

	void genBuffers(const GLsizei n, GLuint* const buffers);
	void deleteBuffers(const GLsizei n, const GLuint* const buffers);
	void bindBuffer(const GLenum target, const GLuint buffer);
	void bufferData(const GLenum target, const GLsizeiptr size, const GLvoid* const data, const GLenum usage);
	void bufferSubData(const GLenum target, const GLintptr offset, const GLsizeiptr size, const GLvoid* const data);
	void genVertexArrays(const GLsizei n, GLuint* const arrays);
	void deleteVertexArrays(const GLsizei n, const GLuint* const arrays);
	void bindVertexArray(const GLuint array);

	//
	//fixed function
	//

	void matrixMode(const GLenum mode);

	void pushMatrix();

	void popMatrix();
	void loadMatrix(const float* const m);
	void loadIdentity();

	void frustum(const GLdouble left, const GLdouble right, const GLdouble bottom, const GLdouble top, const GLdouble zNear, const GLdouble zFar);
	void ortho(const GLdouble left, const GLdouble right, const GLdouble bottom, const GLdouble top, const GLdouble zNear, const GLdouble zFar);

	void translate(const GLfloat x, const GLfloat y, const GLfloat z);
	void rotate(const GLfloat angle, const GLfloat x, const GLfloat y, const GLfloat z);

	void scale(const GLfloat x, const GLfloat y, const GLfloat z);
	void multMatrix(const GLfloat* const m);

	void lightModel(const GLenum pname, const GLfloat* const params);
	void lightModel(const GLenum pname, const GLint* const params);

	void light(const GLenum lightId, const GLenum pname, const GLfloat* const params);

	void material(const GLenum face, const GLenum pname, const GLfloat* const params);

	void enableClientState(const GLenum array);
	void disableClientState(const GLenum array);
	void vertexPointer(const GLint size, const GLenum type, const GLsizei stride, const GLsizei offset);
	void vertexPointer(const GLint size, const GLenum type, const GLsizei stride, const GLvoid* const pointer);
	void texCoordPointer(const GLint size, const GLenum type, const GLsizei stride, const GLsizei offset);
	void texCoordPointer(const GLint size, const GLenum type, const GLsizei stride, const GLvoid* const pointer);
	void normalPointer( const GLenum type, const GLsizei stride, const GLvoid* const pointer );
	void normalPointer( const GLenum type, const GLsizei stride, const GLsizei offset );

	//
	//programmable
	//

	GLuint createProgram();
	void deleteProgram(const GLuint program);
	GLuint createShader(const GLenum shaderType);
	void deleteShader(const GLuint shader);
	void shaderSource(const GLuint shader, const GLsizei count, const GLchar ** const strings, const GLint* const lengths);
	void compileShader(const GLuint shader);
	void getShaderInfoLog(const GLuint shader, const GLsizei bufSize, GLsizei *length, GLchar* const infoLog);
	void attachShader(const GLuint program, const GLuint shader);
	void linkProgram(const GLuint program);
	void getProgramInfoLog(const GLuint program, const GLsizei bufSize, GLsizei *length, GLchar* const infoLog);
	void useProgram(const GLuint program);
private:
};

#endif
