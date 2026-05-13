#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Custom uniform values
uniform float seconds;

// Output fragment color
out vec4 finalColor;

void main()
{
    // Calculate distortion offset
    float distortionX = sin(fragTexCoord.y * 20.0 + seconds * 2.0) * 0.005;
    float distortionY = cos(fragTexCoord.x * 20.0 + seconds * 2.0) * 0.005;
    
    // Apply distortion to texture coordinates
    vec2 distortedTexCoord = fragTexCoord + vec2(distortionX, distortionY);
    
    // Get pixel color from texture
    vec4 texelColor = texture(texture0, distortedTexCoord);
    
    // Final color calculation
    finalColor = texelColor * colDiffuse * fragColor;
}
