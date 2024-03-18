#version 330 core

	out vec4 FragColor;
	in vec2 texCoord;
	uniform sampler2D depthMap;

	void main()
	{
		float depthValue = texture(depthMap, texCoord).r;
		FragColor = vec4(vec3(depthValue), 1.0); // Displaying depth as grayscale
	} 
