#version 440 core

uniform float windowHeight;
out vec4 fragColor;

void main()
{
    // pixel por encima de la mitad de la ventana
    if(gl_FragCoord.y >= windowHeight / 2.0)
    {
        fragColor = vec4(1.0, 1.0, 0.0, 1.0); // Amarillo
    }
    else
    {
        fragColor = vec4(1.0, 0.5, 0.0, 1.0); // Naranja
    }
}
