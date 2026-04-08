#version 440 core
layout (triangles) in;
layout (triangle_strip, max_vertices =6) out;

void main()
{
	for(int i = 0; i < gl_in.length(); i++)
	{
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();

	for(int i = 0; i < gl_in.length(); i++)
	{
		gl_Position = vec4(-gl_in[i].gl_Position.xy, gl_in[i].gl_Position.zw);

		gl_Position += vec4(-0.01f, 0.0, 0.0, 0.0);
		EmitVertex();
	}
	EndPrimitive();



	for(int i = 0; i < gl_in.length(); i++)
	{
		//gl_Position = vec4(0.5, 0.0, 0.0, 0.0);
		//gl_Position = + vec4(-gl_in[0].gl_Position.x * 2, gl_in[2].gl_Position.y, gl_in[0].gl_Position.z, gl_in[0].gl_Position.w);
	}
}