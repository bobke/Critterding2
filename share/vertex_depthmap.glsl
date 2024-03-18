#version 330 core

	layout (location = 0) in vec3 inPosition;
	layout (location = 3) in mat4 InstanceModelMatrix;  // Per-instance model matrix
	uniform mat4 lightSpaceMatrix;

	void main()
	{
		gl_Position = lightSpaceMatrix * InstanceModelMatrix * vec4(inPosition, 1.0);
	} 
