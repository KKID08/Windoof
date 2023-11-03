#version 400 core

layout (points) in;
layout (triangle_strip, max_vertices = 3) out;

//out vec3 fragPosition; // Pass interpolated vertex position to the fragment shader
//flat out int isOutline;    // Boolean flag to indicate if it's part of the outline
/*
flat out int isOutline;

struct Transform {
    float width;
    float height;
    float centerX;
    float centerY;
    float smoothness;
    float rotation;
};
uniform Transform start;
uniform Transform end;

uniform double startTime;
uniform double duration;
uniform double currentTime;
uniform float aspectRatio;

Transform current;

vec4 rotateVertex(vec2 vertex) {
    float distance = distance(vertex, vec2(0, 0));
    float angle = atan(vertex.y, vertex.x) - current.rotation;
    vec2 rotated;
    rotated.x = distance * cos(angle);
    rotated.y = distance * sin(angle);
    rotated.y *= aspectRatio;
    return vec4(rotated, 0.0, 1.0);
}
*/
void main() {
    //gl_in[0].gl_Position.xy;
/*
    // Calculate Progress
    float progress     = (duration == 0) ? 1 : float(clamp((currentTime - startTime) / duration, 0, 1));
    current.width      = mix(start.width,      end.width,      progress);
    current.height     = mix(start.height,     end.height,     progress);
    current.centerX    = mix(start.centerX,    end.centerX,    progress);
    current.centerY    = mix(start.centerY,    end.centerY,    progress);
    current.smoothness = mix(start.smoothness, end.smoothness, progress);
    current.rotation   = mix(start.rotation,   end.rotation,   progress);
*/
    // Normal Rectangle
    //vec2 delta = vec2(current.width / 2, current.height / 2);
    gl_Position = /*rotateVertex(delta * vec2(+1, +1));*/vec4(+1, +1, 0, 1);
    EmitVertex();
    gl_Position = /*rotateVertex(delta * vec2(+1, -1));*/vec4(+1, -1, 0, 1);
    EmitVertex();
    gl_Position = /*rotateVertex(delta * vec2(-1, +1));*/vec4(-1, +1, 0, 1);
    EmitVertex();

    //gl_Position = /*rotateVertex(delta * vec2(-1, -1));*/vec4(-1, -1, 0, 1);
    //EmitVertex();
    EndPrimitive();


    /*
    gl_Position = gl_in[0].gl_Position + vec4(-0.2, 0.0, 0.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.0, 0.0, 0.0);
    EmitVertex();

    EndPrimitive();
    */
}
