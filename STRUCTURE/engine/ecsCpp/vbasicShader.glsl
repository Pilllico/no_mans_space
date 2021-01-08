#version 150

uniform mat4 model_matrix, view_matrix, projection_matrix;

in vec3 a_position;
in vec3 a_normal;

out vec3 normal;
out vec3 fragPos;

void main()
{
    // Calculate vertex position in screen space

    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(a_position, 1.0f);
    fragPos = vec3(model_matrix * vec4(a_position, 1.0f));
    normal = mat3(transpose(inverse(model_matrix))) * a_normal;
}
