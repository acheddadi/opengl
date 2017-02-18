#version 330 core
layout (location = 0) in vec3 position;
//layout (location = 1) in vec3 color;
layout (location = 2) in vec2 txtrCrd;

//out vec3 myColor;
out vec2 myTxtrCrd;
//uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 model;
//uniform mat4 view;
uniform mat4 projection;
uniform mat4 camera;

void main()
{
    gl_Position = projection * camera * model * rotation * vec4(position, 1.0f);
    //myColor = color;
    myTxtrCrd = vec2(txtrCrd.x, 1.0f - txtrCrd.y); //Flipping y coordinates.
}