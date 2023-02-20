#ifndef BE_MESH_H_INCLUDED
#define BE_MESH_H_INCLUDED

#include "be_vertex_array.h"

#include <vector>
// #include <cassert>

class BeMesh
{
public:
	void drawArrays(BeVertexArray* const vertexArray, const GLenum mode, const GLint first, const GLsizei count);
private:
	class DrawArrays
	{
	public:
		DrawArrays(BeVertexArray* const vertexArray, const GLenum mode, const GLint first, const GLsizei count);
	private:
		BeVertexArray*	m_vertexArray;
		GLenum			m_mode;
		GLint			m_first;
		GLsizei			m_count;
	};
	std::vector<DrawArrays*> m_drawArrays;
};

#endif

