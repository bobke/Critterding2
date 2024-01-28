#version 330 core

    layout (location = 0) in vec3 inPosition;
    layout (location = 8) in vec2 texCoord; // this is wrong, returns jibberish

//     uniform mat4 ProjectionMatrix_Camera;
//     uniform mat4 ViewMatrix_Camera;
    uniform mat4 ProjectionViewMatrix_Camera;
    uniform mat4 ModelMatrix_Model;
//     uniform mat4 ProjectionMatrix_Model;
//     uniform mat4 ViewMatrix_Model;
//     uniform mat4 ViewModelMatrix_Model;
//     uniform mat4 ProjectionViewMatrix_Model;
//     uniform mat4 ProjectionViewModelMatrix_Model;
    
    uniform mat4 u_Scale;

    out vec2 v_texCoord;
    
    void main()
    {
//         gl_Position =  ProjectionMatrix_Camera * ViewMatrix_Camera * ModelMatrix_Model * u_Scale * inPosition;
//         gl_Position =  ProjectionMatrix_Model  * ViewMatrix_Model  * ModelMatrix_Model * u_Scale * inPosition;
//         gl_Position =  ProjectionMatrix_Camera * ViewModelMatrix_Model * u_Scale * inPosition;
//         gl_Position =  ProjectionMatrix_Model * ViewModelMatrix_Model * u_Scale * inPosition;
//         gl_Position =  ProjectionViewMatrix_Model * ModelMatrix_Model * u_Scale * inPosition;        
//      
        gl_Position =  ProjectionViewMatrix_Camera * ModelMatrix_Model * u_Scale * vec4(inPosition, 1.0);
//         gl_Position =  ProjectionViewModelMatrix_Model * u_Scale * inPosition;        

        v_texCoord = texCoord;
    }
