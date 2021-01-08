#version 150

in vec3 normal;
in vec3 fragPos;

uniform vec3 lightPos;

void main()
{
        //vec3 lightPos = vec3(0.0f, 0.0f, 15.0f);

        vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
        vec3 objColor = vec3(1.0f, 0.0f, 0.0f);

        vec3 ambient = 0.5f * lightColor;

        vec3 norm = normalize(normal);
        vec3 lightDir = normalize(lightPos - fragPos);

        float diff = max(dot(norm, lightDir), 0.0);

        vec3 diffuse = diff * lightColor;

        vec3 result = (ambient + diffuse) * objColor;

        gl_FragColor = vec4(result, 1.0f);
        //gl_FragColor = vec4(1.0f, 1.0f, 0.5f, 1.0f);
}
