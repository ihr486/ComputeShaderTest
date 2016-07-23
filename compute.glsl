#version 430
#extension ARB_compute_shader : enable
#extension ARB_shader_image_load_store : enable
#extension ARB_explicit_uniform_location : enable

layout(binding=0, rgba8) uniform writeonly image2D output;
layout(local_size_x = 8, local_size_y = 8) in;

void main()
{
    imageStore(output, ivec2(gl_GlobalInvocationID), ivec4(255, 255, 255, 255));
}
