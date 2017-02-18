#version 330 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 txtrCrd;

//out vec3 myColor;
out vec2 myTxtrCrd;
uniform mat4 rotation;
uniform mat4 model;
uniform mat4 projection;
uniform mat4 camera;

void main()
{
    gl_Position = projection * camera * model * rotation * vec4(position, 1.0f);
    myTxtrCrd = vec2(txtrCrd.x, 1.0f - txtrCrd.y); //Flipping y coordinates.
}