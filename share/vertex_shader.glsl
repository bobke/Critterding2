#version 330 core

    layout (location = 0) in vec3 inPosition;
    layout (location = 1) in vec3 normal;
    layout (location = 2) in vec2 inTexCoord;
    layout (location = 3) in mat4 InstanceModelMatrix;  // Per-instance model matrix

//     layout (location = 3) in mat4 InstanceModelMatrix;
//     layout (location = 4) in vec3 InstanceScale;
    
//     in vec3 InstanceScale;        // Per-instance scale

    uniform mat4 ProjectionViewMatrix_Camera;
//     uniform mat4 ModelMatrix_Model;
//     uniform mat4 u_Scale;
//     uniform mat4 lightSpaceMatrix;
    out vec2 v_texCoord;
    out vec4 FragPos; // Output the fragment position in world space
    out vec3 Normal;  // Output the normal in world space

    void main()
    {
        // Transform vertex position and normal to world space
        FragPos = InstanceModelMatrix * vec4(inPosition, 1.0);
        Normal = mat3(transpose(inverse(InstanceModelMatrix))) * normal;
        
    // Transform to light space for shadow mapping
//         gl_Position = lightSpaceMatrix * vec4(FragPos.xyz, 1.0);

        // Transform to clip space for rendering the scene
        // (view and projection matrices are applied here)        
        gl_Position =  ProjectionViewMatrix_Camera * InstanceModelMatrix * vec4(inPosition, 1.0);
//         gl_Position =  ProjectionViewMatrix_Camera * ModelMatrix_Model * u_Scale * vec4(inPosition, 1.0);
        v_texCoord = inTexCoord;
    }

// #version 330 core
// 
//     layout (location = 0) in vec3 inPosition;
//     layout (location = 1) in vec3 normals;
//     layout (location = 2) in vec2 texCoord;
// 
// //     uniform mat4 ProjectionMatrix_Camera;
// //     uniform mat4 ViewMatrix_Camera;
//     uniform mat4 ProjectionViewMatrix_Camera;
//     uniform mat4 ModelMatrix_Model;
// //     uniform mat4 ProjectionMatrix_Model;
// //     uniform mat4 ViewMatrix_Model;
// //     uniform mat4 ViewModelMatrix_Model;
// //     uniform mat4 ProjectionViewMatrix_Model;
// //     uniform mat4 ProjectionViewModelMatrix_Model;
//     
//     uniform mat4 u_Scale;
// 
//     out vec2 v_texCoord;
//     
//     void main()
//     {
// //         gl_Position =  ProjectionMatrix_Camera * ViewMatrix_Camera * ModelMatrix_Model * u_Scale * inPosition;
// //         gl_Position =  ProjectionMatrix_Model  * ViewMatrix_Model  * ModelMatrix_Model * u_Scale * inPosition;
// //         gl_Position =  ProjectionMatrix_Camera * ViewModelMatrix_Model * u_Scale * inPosition;
// //         gl_Position =  ProjectionMatrix_Model * ViewModelMatrix_Model * u_Scale * inPosition;
// //         gl_Position =  ProjectionViewMatrix_Model * ModelMatrix_Model * u_Scale * inPosition;        
// //      
//         gl_Position =  ProjectionViewMatrix_Camera * ModelMatrix_Model * u_Scale * vec4(inPosition, 1.0);
// //         gl_Position =  ProjectionViewModelMatrix_Model * u_Scale * inPosition;        
// 
//         v_texCoord = texCoord;
//     }
