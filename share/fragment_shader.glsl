#version 330 core
out vec4 FragColor;

in vec4 FragPos; // FragPos from the vertex shader
in vec3 Normal;  // Normal from the vertex shader
in vec2 v_texCoord;

uniform sampler2D u_Texture;
uniform sampler2D depthMap;
uniform mat4 lightSpaceMatrix;

uniform vec4 u_Color;

    vec3 lightPos = vec3( 0.0, 50.0, -100.0 );

    void main()
    {
        // Convert coordinates to light space
        vec4 projCoords = lightSpaceMatrix * FragPos;
        vec3 lightCoords = projCoords.xyz / projCoords.w;

        // Map to [0,1] range
        lightCoords = 0.5 * lightCoords + 0.5;

        // Get depth value from the depth map
        float depthValue = texture(depthMap, lightCoords.xy).r;

        // Calculate distance between fragment and light source
        float distanceToLight = length(lightPos - FragPos.xyz);

        // Calculate diffuse lighting (replace with your own lighting model)
        vec3 normal = normalize(Normal);
        // vec3 lightDir = normalize(lightPos - FragPos.xyz);
        vec3 lightDir = vec3(0.0, 1.0, 0.0);
        float diff = max(dot(normal, lightDir), 0.0);

        // bias
        // float bias = 0.002;
        // Calculate bias to reduce shadow acne
        float bias = max(0.03 * (1.0 - dot(normal, lightCoords)), 0.002);

        // Soft shadow calculation using Percentage-Closer Filtering (PCF)
        float shadow = 0.0;
        vec2 texelSize = 1.0 / textureSize(depthMap, 0);
        for (int x = -1; x <= 1; ++x)
        {
            for (int y = -1; y <= 1; ++y)
            {
                float pcfDepth = texture(depthMap, lightCoords.xy + vec2(x, y) * texelSize).r;
                shadow += (lightCoords.z - bias > pcfDepth) ? 0.0 : 1.0;
            }
        }    
        shadow /= 9.0; // Assuming a 3x3 PCF kernel        

        // Apply shadow factor to diffuse lighting
        vec3 diffuse = diff * shadow * vec3(0.7);

    //     // Final color output
    //     FragColor = texture(u_Texture, v_texCoord) * vec4(diffuse, 1.0) * u_Color;
        
        // Calculate ambient color
        vec3 ambient_color = vec3(0.5); // You can adjust the ambient intensity here
        vec3 ambient = ambient_color * u_Color.rgb;

        // Final color output
        FragColor = texture(u_Texture, v_texCoord) * vec4(diffuse + ambient, 1.0);    
    }


// #version 330 core
// 
//     layout (location = 0) out vec4 color;
// 
//     in vec2 v_texCoord;
// 
//     uniform vec4 u_Color;
//     uniform sampler2D u_Texture;
//     uniform int u_textureSample = 1;
// 
//     void main()
//     {
//         if( u_textureSample == 1 )
//         {
//             // Texture present
//             color = texture(u_Texture, v_texCoord) * u_Color;
//         }
//         else
//         {
//             // Texture not present
//             color = u_Color;
//         }
//         
//     }



// struct Material {
//     sampler2D diffuse;
//     float shininess;
// };
// 
// struct Light {
//     vec3 position;
//     vec3 ambient;
//     vec3 diffuse;
//     vec3 specular;
// };
// 
// in vec3 fragPos;
// in vec3 fragNormal;
// in vec2 texCoord;
// 
// uniform Material material;
// uniform Light light;
// uniform vec3 viewPos;
// 
// out vec4 FragColor;
// 
// void main() {
//     // Ambient lighting
//     vec3 ambient = light.ambient * texture(material.diffuse, texCoord).rgb;
// 
//     // Diffuse lighting
//     vec3 norm = normalize(fragNormal);
//     vec3 lightDir = normalize(light.position - fragPos);
//     float diff = max(dot(norm, lightDir), 0.0);
//     vec3 diffuse = light.diffuse * diff * texture(material.diffuse, texCoord).rgb;
// 
//     // Specular lighting
//     vec3 viewDir = normalize(viewPos - fragPos);
//     vec3 reflectDir = reflect(-lightDir, norm);
//     float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//     vec3 specular = light.specular * spec * texture(material.diffuse, texCoord).rgb;
// 
//     vec3 result = ambient + diffuse + specular;
//     FragColor = vec4(result, 1.0);
// }
//  
