#version 330 core

    layout (location = 0) out vec4 color;

    in vec2 v_texCoord;

    uniform vec4 u_Color;
    uniform sampler2D u_Texture;
    uniform int u_textureSample = 1;

    void main()
    {
        if( u_textureSample == 1 )
        {
            // Texture present
            vec4 texColor = 
            color = texture(u_Texture, v_texCoord) * u_Color;
        }
        else
        {
            // Texture not present
            color = u_Color;
        }
        
    }



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
