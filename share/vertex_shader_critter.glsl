// #version 330 core
// 
//     layout (location = 0) in vec3 inPosition;
// 
//     uniform mat4 ProjectionViewMatrix_Camera;
//     uniform mat4 ModelMatrix_Model;
// //     uniform mat4 ProjectionViewModelMatrix_Model;
//     uniform mat4 u_Scale;
// 
//     void main()
//     {
//         gl_Position =  ProjectionViewMatrix_Camera * ModelMatrix_Model * u_Scale * vec4(inPosition, 1.0);        
// //         gl_Position =  ProjectionViewModelMatrix_Model * u_Scale * inPosition;        
//     }

#version 330 core

    layout (location = 0) in vec3 inPosition;
//     layout (location = 3) in mat4 InstanceModelMatrix;
//     layout (location = 4) in vec3 InstanceScale;

    uniform mat4 ProjectionViewMatrix_Camera;
    uniform mat4 ModelMatrix_Model;
    uniform mat4 u_Scale;
//     uniform mat4 ProjectionViewModelMatrix_Model;

    void main()
    {
//         gl_Position =  ProjectionViewMatrix_Camera * InstanceModelMatrix * vec4(inPosition, 1.0);
//         gl_Position =  ProjectionViewMatrix_Camera * ModelMatrix_Model * vec4(inPosition, 1.0);        
        gl_Position =  ProjectionViewMatrix_Camera * ModelMatrix_Model * u_Scale * vec4(inPosition, 1.0);        
    }

