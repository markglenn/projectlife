/* ----------------------------------------------------------------------------
Copyright (c) 2001-2002, Lev Povalahev
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, 
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, 
      this list of conditions and the following disclaimer in the documentation 
      and/or other materials provided with the distribution.
    * The name of the author may be used to endorse or promote products 
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
THE POSSIBILITY OF SUCH DAMAGE.
------------------------------------------------------------------------------*/
/* 
    Lev Povalahev

    levp@gmx.net
  
    http://www.uni-karlsruhe.de/~uli2/

*/                         

/* following extensions are supported:

GL_ARB_imaging
GL_ARB_depth_texture
GL_ARB_matrix_palette
GL_ARB_multisample
GL_ARB_multitexture
GL_ARB_point_parameters
GL_ARB_shadow
GL_ARB_shadow_ambient
GL_ARB_texture_compression
GL_ARB_texture_env_add
GL_ARB_texture_env_dot3
GL_ARB_texture_env_combine
GL_ARB_texture_env_crossbar
GL_ARB_texture_border_clamp
GL_ARB_texture_cube_map
GL_ARB_texture_mirrored_repeat
GL_ARB_transpose_matrix
GL_ARB_vertex_blend
GL_ARB_vertex_program
GL_ARB_window_pos
GL_EXT_abgr
GL_EXT_bgra
GL_EXT_blend_function_separate
GL_EXT_compiled_vertex_array
GL_EXT_cull_vertex
GL_EXT_draw_range_elements
GL_EXT_fog_coord
GL_EXT_multi_draw_arrays
GL_EXT_point_parameters
GL_EXT_secondary_color
GL_EXT_separate_specular_color
GL_EXT_shadow_funcs
GL_EXT_stencil_two_side
GL_EXT_stencil_wrap
GL_EXT_texture_compression_s3tc
GL_EXT_texture_filter_anisotropic
GL_EXT_texture_lod_bias
GL_EXT_vertex_shader
GL_EXT_vertex_weighting
GL_ATI_element_array
GL_ATI_envmap_bumpmap
GL_ATI_fragment_shader
GL_ATI_pn_triangles
GL_ATI_texture_mirror_once
GL_ATI_vertex_array_object;
GL_ATI_vertex_streams
GL_ATIX_point_sprites
GL_ATIX_texture_env_route
GL_HP_occlusion_test
GL_NV_blend_square
GL_NV_copy_depth_to_color
GL_NV_depth_clamp
GL_NV_evaluators
GL_NV_fence
GL_NV_fog_distance
GL_NV_light_max_exponent
GL_NV_occlusion_query
GL_NV_packed_depth_stencil
GL_NV_point_sprite
GL_NV_register_combiners
GL_NV_register_combiners2
GL_NV_texgen_reflection
GL_NV_texture_env_combine4
GL_NV_texture_rectangle
GL_NV_texture_shader
GL_NV_texture_shader2
GL_NV_texture_shader3
GL_NV_vertex_array_range
GL_NV_vertex_array_range2
GL_NV_vertex_program
GL_NV_vertex_program1_1
GL_SGIS_generate_mipmap
GL_SGIX_shadow
GL_SGIX_depth_texture
WGL_ARB_buffer_region
WGL_ARB_extensions_string
WGL_ARB_make_current_read;
WGL_ARB_multisample
WGL_ARB_pbuffer
WGL_ARB_pixel_format
WGL_ARB_render_texture 
WGL_EXT_extensions_string
WGL_EXT_swap_control
WGL_NV_render_depth_texture
WGL_NV_render_texture_rectangle

*/  
       
#include "extgl.h"
#include <stdio.h>
#include <string.h>

#ifndef _WIN32
#include <GL/glx.h>
#endif /* _WIN32 */

/* function variables */

/*-------------------------------------*/
/* WGL stuff */
/*-------------------------------------*/

#ifdef _WIN32

/* WGL_EXT_etxension_string */

#ifdef WGL_EXT_extensions_string
wglGetExtensionsStringEXTPROC wglGetExtensionsStringEXT = NULL;
#endif /* WGL_EXT_extension_string */

/* WGL_ARB_buffer_region */

#ifdef WGL_ARB_buffer_region
wglCreateBufferRegionARBPROC wglCreateBufferRegionARB = NULL;
wglDeleteBufferRegionARBPROC wglDeleteBufferRegionARB = NULL;
wglSaveBufferRegionARBPROC wglSaveBufferRegionARB = NULL;
wglRestoreBufferRegionARBPROC wglRestoreBufferRegionARB = NULL;
#endif /* WGL_ARB_buffer_region */

/* WGL_ARB_extension_string */


#ifdef WGL_ARB_extensions_string
wglGetExtensionsStringARBPROC wglGetExtensionsStringARB = NULL;
#endif /* WGL_ARB_extension_string */

/* WGL_ARB_pbuffer */

#ifdef WGL_ARB_pbuffer
wglCreatePbufferARBPROC wglCreatePbufferARB = NULL;
wglGetPbufferDCARBPROC wglGetPbufferDCARB = NULL;
wglReleasePbufferDCARBPROC wglReleasePbufferDCARB = NULL;
wglDestroyPbufferARBPROC wglDestroyPbufferARB = NULL;
wglQueryPbufferARBPROC wglQueryPbufferARB = NULL;
#endif /* WGL_ARB_pbuffer */

/* WGL_ARB_pixel_format */

#ifdef WGL_ARB_pixel_format
wglGetPixelFormatAttribivARBPROC wglGetPixelFormatAttribivARB = NULL;
wglGetPixelFormatAttribfvARBPROC wglGetPixelFormatAttribfvARB = NULL;
wglChoosePixelFormatARBPROC wglChoosePixelFormatARB = NULL;
#endif /* WGL_ARB_pixel_format */

/* WGL_ARB_render_texture */

#ifdef WGL_ARB_render_texture
wglBindTexImageARBPROC wglBindTexImageARB = NULL;
wglReleaseTexImageARBPROC wglReleaseTexImageARB = NULL;
wglSetPbufferAttribARBPROC wglSetPbufferAttribARB = NULL;
#endif /* WGL_ARB_render_texture */

/* WGL_EXT_swap_control */

#ifdef WGL_EXT_swap_control
wglSwapIntervalEXTPROC wglSwapIntervalEXT = NULL;
wglGetSwapIntervalEXTPROC wglGetSwapIntervalEXT = NULL;
#endif /* WGL_EXT_swap_control */

/* WGL_ARB_make_current_read */

#ifdef WGL_ARB_make_current_read
wglMakeContextCurrentARBPROC wglMakeContextCurrentARB = NULL;
wglGetCurrentReadDCARBPROC wglGetCurrentReadDCARB = NULL;
#endif /* WGL_ARB_make_current_read*/ 

/* VAR */

#ifdef GL_NV_vertex_array_range
wglAllocateMemoryNVPROC wglAllocateMemoryNV = NULL;
wglFreeMemoryNVPROC wglFreeMemoryNV = NULL;
#endif /* GL_NV_vertex_array_range */



#endif /* WIN32 */

/*-------------------------------------*/
/*---WGL STUFF END---------------------*/
/*-------------------------------------*/

#ifdef _WIN32

#ifdef GL_VERSION_1_2
glDrawRangeElementsPROC glDrawRangeElements = NULL;
glTexImage3DPROC glTexImage3D = NULL;
glTexSubImage3DPROC glTexSubImage3D = NULL;
glCopyTexSubImage3DPROC glCopyTexSubImage3D = NULL;
#endif /* GL_VERSION_1_2 */

#ifdef GL_ARB_imaging
glBlendColorPROC glBlendColor = NULL;
glBlendEquationPROC glBlendEquation = NULL;
glColorTablePROC glColorTable = NULL;
glColorTableParameterfvPROC glColorTableParameterfv = NULL;
glColorTableParameterivPROC glColorTableParameteriv = NULL;
glCopyColorTablePROC glCopyColorTable = NULL;
glGetColorTablePROC glGetColorTable = NULL;
glGetColorTableParameterfvPROC glGetColorTableParameterfv = NULL;
glGetColorTableParameterivPROC glGetColorTableParameteriv = NULL;
glColorSubTablePROC glColorSubTable = NULL;
glCopyColorSubTablePROC glCopyColorSubTable = NULL;
glConvolutionFilter1DPROC glConvolutionFilter1D = NULL;
glConvolutionFilter2DPROC glConvolutionFilter2D = NULL;
glConvolutionParameterfPROC glConvolutionParameterf = NULL;
glConvolutionParameterfvPROC glConvolutionParameterfv = NULL;
glConvolutionParameteriPROC glConvolutionParameteri = NULL;
glConvolutionParameterivPROC glConvolutionParameteriv = NULL;
glCopyConvolutionFilter1DPROC glCopyConvolutionFilter1D = NULL;
glCopyConvolutionFilter2DPROC glCopyConvolutionFilter2D = NULL;
glGetConvolutionFilterPROC glGetConvolutionFilter = NULL;
glGetConvolutionParameterfvPROC glGetConvolutionParameterfv = NULL;
glGetConvolutionParameterivPROC glGetConvolutionParameteriv = NULL;
glGetSeparableFilterPROC glGetSeparableFilter = NULL;
glSeparableFilter2DPROC glSeparableFilter2D = NULL;
glGetHistogramPROC glGetHistogram = NULL;
glGetHistogramParameterfvPROC glGetHistogramParameterfv = NULL;
glGetHistogramParameterivPROC glGetHistogramParameteriv = NULL;
glGetMinmaxPROC glGetMinmax = NULL;
glGetMinmaxParameterfvPROC glGetMinmaxParameterfv = NULL;
glGetMinmaxParameterivPROC glGetMinmaxParameteriv = NULL;
glHistogramPROC glHistogram = NULL;
glMinmaxPROC glMinmax = NULL;
glResetHistogramPROC glResetHistogram = NULL;
glResetMinmaxPROC glResetMinmax = NULL;
#endif /* GL_ARB_imaging */

/* 1.3 */

#ifdef GL_VERSION_1_3
glActiveTexturePROC glActiveTexture = NULL;
glClientActiveTexturePROC glClientActiveTexture = NULL;
glMultiTexCoord1dPROC glMultiTexCoord1d = NULL;
glMultiTexCoord1dvPROC glMultiTexCoord1dv = NULL;
glMultiTexCoord1fPROC glMultiTexCoord1f = NULL;
glMultiTexCoord1fvPROC glMultiTexCoord1fv = NULL;
glMultiTexCoord1iPROC glMultiTexCoord1i = NULL;
glMultiTexCoord1ivPROC glMultiTexCoord1iv = NULL;
glMultiTexCoord1sPROC glMultiTexCoord1s = NULL;
glMultiTexCoord1svPROC glMultiTexCoord1sv = NULL;
glMultiTexCoord2dPROC glMultiTexCoord2d = NULL;
glMultiTexCoord2dvPROC glMultiTexCoord2dv = NULL;
glMultiTexCoord2fPROC glMultiTexCoord2f = NULL;
glMultiTexCoord2fvPROC glMultiTexCoord2fv = NULL;
glMultiTexCoord2iPROC glMultiTexCoord2i = NULL;
glMultiTexCoord2ivPROC glMultiTexCoord2iv = NULL;
glMultiTexCoord2sPROC glMultiTexCoord2s = NULL;
glMultiTexCoord2svPROC glMultiTexCoord2sv = NULL;
glMultiTexCoord3dPROC glMultiTexCoord3d = NULL;
glMultiTexCoord3dvPROC glMultiTexCoord3dv = NULL;
glMultiTexCoord3fPROC glMultiTexCoord3f = NULL;
glMultiTexCoord3fvPROC glMultiTexCoord3fv = NULL;
glMultiTexCoord3iPROC glMultiTexCoord3i = NULL;
glMultiTexCoord3ivPROC glMultiTexCoord3iv = NULL;
glMultiTexCoord3sPROC glMultiTexCoord3s = NULL;
glMultiTexCoord3svPROC glMultiTexCoord3sv = NULL;
glMultiTexCoord4dPROC glMultiTexCoord4d = NULL;
glMultiTexCoord4dvPROC glMultiTexCoord4dv = NULL;
glMultiTexCoord4fPROC glMultiTexCoord4f = NULL;
glMultiTexCoord4fvPROC glMultiTexCoord4fv = NULL;
glMultiTexCoord4iPROC glMultiTexCoord4i = NULL;
glMultiTexCoord4ivPROC glMultiTexCoord4iv = NULL;
glMultiTexCoord4sPROC glMultiTexCoord4s = NULL;
glMultiTexCoord4svPROC glMultiTexCoord4sv = NULL;
glLoadTransposeMatrixfPROC glLoadTransposeMatrixf = NULL;
glLoadTransposeMatrixdPROC glLoadTransposeMatrixd = NULL;
glMultTransposeMatrixfPROC glMultTransposeMatrixf = NULL;
glMultTransposeMatrixdPROC glMultTransposeMatrixd = NULL;
glCompressedTexImage3DPROC glCompressedTexImage3D = NULL;
glCompressedTexImage2DPROC glCompressedTexImage2D = NULL;
glCompressedTexImage1DPROC glCompressedTexImage1D = NULL;
glCompressedTexSubImage3DPROC glCompressedTexSubImage3D = NULL;
glCompressedTexSubImage2DPROC glCompressedTexSubImage2D = NULL;
glCompressedTexSubImage1DPROC glCompressedTexSubImage1D = NULL;
glGetCompressedTexImagePROC glGetCompressedTexImage = NULL;
glSampleCoveragePROC glSampleCoverage = NULL;
#endif /* GL_VERSION_1_3 */

/* ARB_multitexture */

#ifdef GL_ARB_multitexture
glActiveTextureARBPROC glActiveTextureARB = NULL;
glClientActiveTextureARBPROC glClientActiveTextureARB = NULL;
glMultiTexCoord1dARBPROC glMultiTexCoord1dARB = NULL;
glMultiTexCoord1dvARBPROC glMultiTexCoord1dvARB = NULL;
glMultiTexCoord1fARBPROC glMultiTexCoord1fARB = NULL;
glMultiTexCoord1fvARBPROC glMultiTexCoord1fvARB = NULL;
glMultiTexCoord1iARBPROC glMultiTexCoord1iARB = NULL;
glMultiTexCoord1ivARBPROC glMultiTexCoord1ivARB = NULL;
glMultiTexCoord1sARBPROC glMultiTexCoord1sARB = NULL;
glMultiTexCoord1svARBPROC glMultiTexCoord1svARB = NULL;
glMultiTexCoord2dARBPROC glMultiTexCoord2dARB = NULL;
glMultiTexCoord2dvARBPROC glMultiTexCoord2dvARB = NULL;
glMultiTexCoord2fARBPROC glMultiTexCoord2fARB = NULL;
glMultiTexCoord2fvARBPROC glMultiTexCoord2fvARB = NULL;
glMultiTexCoord2iARBPROC glMultiTexCoord2iARB = NULL;
glMultiTexCoord2ivARBPROC glMultiTexCoord2ivARB = NULL;
glMultiTexCoord2sARBPROC glMultiTexCoord2sARB = NULL;
glMultiTexCoord2svARBPROC glMultiTexCoord2svARB = NULL;
glMultiTexCoord3dARBPROC glMultiTexCoord3dARB = NULL;
glMultiTexCoord3dvARBPROC glMultiTexCoord3dvARB = NULL;
glMultiTexCoord3fARBPROC glMultiTexCoord3fARB = NULL;
glMultiTexCoord3fvARBPROC glMultiTexCoord3fvARB = NULL;
glMultiTexCoord3iARBPROC glMultiTexCoord3iARB = NULL;
glMultiTexCoord3ivARBPROC glMultiTexCoord3ivARB = NULL;
glMultiTexCoord3sARBPROC glMultiTexCoord3sARB = NULL;
glMultiTexCoord3svARBPROC glMultiTexCoord3svARB = NULL;
glMultiTexCoord4dARBPROC glMultiTexCoord4dARB = NULL;
glMultiTexCoord4dvARBPROC glMultiTexCoord4dvARB = NULL;
glMultiTexCoord4fARBPROC glMultiTexCoord4fARB = NULL;
glMultiTexCoord4fvARBPROC glMultiTexCoord4fvARB = NULL;
glMultiTexCoord4iARBPROC glMultiTexCoord4iARB = NULL;
glMultiTexCoord4ivARBPROC glMultiTexCoord4ivARB = NULL;
glMultiTexCoord4sARBPROC glMultiTexCoord4sARB = NULL;
glMultiTexCoord4svARBPROC glMultiTexCoord4svARB = NULL;
#endif /* GL_ARB_multitexture */

#endif /* _WIN32 */

/* ARB_transpose_matrix */

#ifdef GL_ARB_transpose_matrix
glLoadTransposeMatrixfARBPROC glLoadTransposeMatrixfARB = NULL;
glLoadTransposeMatrixdARBPROC glLoadTransposeMatrixdARB = NULL;
glMultTransposeMatrixfARBPROC glMultTransposeMatrixfARB = NULL;
glMultTransposeMatrixdARBPROC glMultTransposeMatrixdARB = NULL;
#endif /* GL_ARB_transpose_matrix */

/* ARB_texture_compression */

#ifdef GL_ARB_texture_compression 
glCompressedTexImage3DARBPROC glCompressedTexImage3DARB = NULL;
glCompressedTexImage2DARBPROC glCompressedTexImage2DARB = NULL;
glCompressedTexImage1DARBPROC glCompressedTexImage1DARB = NULL; 
glCompressedTexSubImage3DARBPROC glCompressedTexSubImage3DARB = NULL;
glCompressedTexSubImage2DARBPROC glCompressedTexSubImage2DARB = NULL;
glCompressedTexSubImage1DARBPROC glCompressedTexSubImage1DARB = NULL;
glGetCompressedTexImageARBPROC glGetCompressedTexImageARB = NULL;
#endif /* GL_ARB_texture_compression */

/* EXT_secondary_color */

#ifdef GL_EXT_secondary_color
glSecondaryColor3bEXTPROC glSecondaryColor3bEXT = NULL;
glSecondaryColor3bvEXTPROC glSecondaryColor3bvEXT = NULL;
glSecondaryColor3dEXTPROC glSecondaryColor3dEXT = NULL;
glSecondaryColor3dvEXTPROC glSecondaryColor3dvEXT = NULL;
glSecondaryColor3fEXTPROC glSecondaryColor3fEXT = NULL;
glSecondaryColor3fvEXTPROC glSecondaryColor3fvEXT = NULL;
glSecondaryColor3iEXTPROC glSecondaryColor3iEXT = NULL;
glSecondaryColor3ivEXTPROC glSecondaryColor3ivEXT = NULL;
glSecondaryColor3sEXTPROC glSecondaryColor3sEXT = NULL;
glSecondaryColor3svEXTPROC glSecondaryColor3svEXT = NULL;
glSecondaryColor3ubEXTPROC glSecondaryColor3ubEXT = NULL;
glSecondaryColor3ubvEXTPROC glSecondaryColor3ubvEXT = NULL;
glSecondaryColor3uiEXTPROC glSecondaryColor3uiEXT = NULL;
glSecondaryColor3uivEXTPROC glSecondaryColor3uivEXT = NULL;
glSecondaryColor3usEXTPROC glSecondaryColor3usEXT = NULL;
glSecondaryColor3usvEXTPROC glSecondaryColor3usvEXT = NULL;
glSecondaryColorPointerEXTPROC glSecondaryColorPointerEXT = NULL;
#endif /* GL_EXT_secondary_color */

/* EXT_compiled_vertex_array */

#ifdef GL_EXT_compiled_vertex_array 
glLockArraysEXTPROC glLockArraysEXT = NULL;
glUnlockArraysEXTPROC glUnlockArraysEXT = NULL;
#endif /* GL_EXT_compiled_vertex_array */

/* EXT_fog_coord */

#ifdef GL_EXT_fog_coord
glFogCoordfEXTPROC glFogCoordfEXT = NULL;
glFogCoordfvEXTPROC glFogCoordfvEXT = NULL;
glFogCoorddEXTPROC glFogCoorddEXT = NULL;
glFogCoorddvEXTPROC glFogCoorddvEXT = NULL;
glFogCoordPointerEXTPROC glFogCoordPointerEXT = NULL;
#endif /* GL_EXT_for_color */

/* NV_vertex_array_range */

#ifdef GL_NV_vertex_array_range
glFlushVertexArrayRangeNVPROC glFlushVertexArrayRangeNV = NULL;
glVertexArrayRangeNVPROC glVertexArrayRangeNV = NULL;
#endif /* GL_NV_vertex_array_range */

/* EXT_point_parameters */

#ifdef GL_EXT_point_parameters
glPointParameterfEXTPROC glPointParameterfEXT = NULL;
glPointParameterfvEXTPROC glPointParameterfvEXT = NULL;
#endif /* GL_EXT_point_parameters */

/* NV_register_combiners */

#ifdef GL_NV_register_combiners
glCombinerParameterfvNVPROC glCombinerParameterfvNV = NULL;
glCombinerParameterfNVPROC  glCombinerParameterfNV = NULL;
glCombinerParameterivNVPROC glCombinerParameterivNV = NULL;
glCombinerParameteriNVPROC glCombinerParameteriNV = NULL;
glCombinerInputNVPROC glCombinerInputNV = NULL;
glCombinerOutputNVPROC glCombinerOutputNV = NULL;
glFinalCombinerInputNVPROC glFinalCombinerInputNV = NULL;
glGetCombinerInputParameterfvNVPROC glGetCombinerInputParameterfvNV = NULL;
glGetCombinerInputParameterivNVPROC glGetCombinerInputParameterivNV = NULL;
glGetCombinerOutputParameterfvNVPROC glGetCombinerOutputParameterfvNV = NULL;
glGetCombinerOutputParameterivNVPROC glGetCombinerOutputParameterivNV = NULL;
glGetFinalCombinerInputParameterfvNVPROC glGetFinalCombinerInputParameterfvNV = NULL;
glGetFinalCombinerInputParameterivNVPROC glGetFinalCombinerInputParameterivNV = NULL;
#endif /* GL_NV_register_combiners */

/* ARB_multisample */

#ifdef GL_ARB_multisample
glSampleCoverageARBPROC glSampleCoverageARB = NULL;
#endif /* GL_ARB_multisample */

/* EXT_vertex_weighting */

#ifdef GL_EXT_vertex_weighting
glVertexWeightfEXTPROC glVertexWeightfEXT = NULL;
glVertexWeightfvEXTPROC glVertexWeightfvEXT = NULL;
glVertexWeightPointerEXTPROC glVertexWeightPointerEXT = NULL;
#endif /* GL_EXT_vertex_weighting */

/* NV_vertex_program */

#ifdef GL_NV_vertex_program
glBindProgramNVPROC glBindProgramNV = NULL;
glDeleteProgramsNVPROC glDeleteProgramsNV = NULL;
glExecuteProgramNVPROC glExecuteProgramNV = NULL;
glGenProgramsNVPROC glGenProgramsNV = NULL;
glAreProgramsResidentNVPROC glAreProgramsResidentNV = NULL;
glRequestResidentProgramsNVPROC glRequestResidentProgramsNV = NULL;
glGetProgramParameterfvNVPROC glGetProgramParameterfvNV = NULL;
glGetProgramParameterdvNVPROC glGetProgramParameterdvNV = NULL;
glGetProgramivNVPROC glGetProgramivNV = NULL;
glGetProgramStringNVPROC glGetProgramStringNV = NULL;
glGetTrackMatrixivNVPROC glGetTrackMatrixivNV = NULL;
glGetVertexAttribdvNVPROC glGetVertexAttribdvNV = NULL;
glGetVertexAttribfvNVPROC glGetVertexAttribfvNV = NULL;
glGetVertexAttribivNVPROC glGetVertexAttribivNV = NULL;
glGetVertexAttribPointervNVPROC glGetVertexAttribPointervNV = NULL;
glIsProgramNVPROC glIsProgramNV = NULL;
glLoadProgramNVPROC glLoadProgramNV = NULL;
glProgramParameter4fNVPROC glProgramParameter4fNV = NULL;
glProgramParameter4dNVPROC glProgramParameter4dNV = NULL;
glProgramParameter4dvNVPROC glProgramParameter4dvNV = NULL;
glProgramParameter4fvNVPROC glProgramParameter4fvNV = NULL;
glProgramParameters4dvNVPROC glProgramParameters4dvNV = NULL;
glProgramParameters4fvNVPROC glProgramParameters4fvNV = NULL;
glTrackMatrixNVPROC glTrackMatrixNV = NULL;
glVertexAttribPointerNVPROC glVertexAttribPointerNV = NULL;
glVertexAttrib1sNVPROC glVertexAttrib1sNV = NULL;
glVertexAttrib1fNVPROC glVertexAttrib1fNV = NULL;
glVertexAttrib1dNVPROC glVertexAttrib1dNV = NULL;
glVertexAttrib2sNVPROC glVertexAttrib2sNV = NULL;
glVertexAttrib2fNVPROC glVertexAttrib2fNV = NULL;
glVertexAttrib2dNVPROC glVertexAttrib2dNV = NULL;
glVertexAttrib3sNVPROC glVertexAttrib3sNV = NULL;
glVertexAttrib3fNVPROC glVertexAttrib3fNV = NULL;
glVertexAttrib3dNVPROC glVertexAttrib3dNV = NULL;
glVertexAttrib4sNVPROC glVertexAttrib4sNV = NULL;
glVertexAttrib4fNVPROC glVertexAttrib4fNV = NULL;
glVertexAttrib4dNVPROC glVertexAttrib4dNV = NULL;
glVertexAttrib4ubNVPROC glVertexAttrib4ubNV = NULL;
glVertexAttrib1svNVPROC glVertexAttrib1svNV = NULL;
glVertexAttrib1fvNVPROC glVertexAttrib1fvNV = NULL;
glVertexAttrib1dvNVPROC glVertexAttrib1dvNV = NULL;
glVertexAttrib2svNVPROC glVertexAttrib2svNV = NULL;
glVertexAttrib2fvNVPROC glVertexAttrib2fvNV = NULL;
glVertexAttrib2dvNVPROC glVertexAttrib2dvNV = NULL;
glVertexAttrib3svNVPROC glVertexAttrib3svNV = NULL;
glVertexAttrib3fvNVPROC glVertexAttrib3fvNV = NULL;
glVertexAttrib3dvNVPROC glVertexAttrib3dvNV = NULL;
glVertexAttrib4svNVPROC glVertexAttrib4svNV = NULL;
glVertexAttrib4fvNVPROC glVertexAttrib4fvNV = NULL;
glVertexAttrib4dvNVPROC glVertexAttrib4dvNV = NULL;
glVertexAttrib4ubvNVPROC glVertexAttrib4ubvNV = NULL;
glVertexAttribs1svNVPROC glVertexAttribs1svNV = NULL;
glVertexAttribs1fvNVPROC glVertexAttribs1fvNV = NULL;
glVertexAttribs1dvNVPROC glVertexAttribs1dvNV = NULL;
glVertexAttribs2svNVPROC glVertexAttribs2svNV = NULL;
glVertexAttribs2fvNVPROC glVertexAttribs2fvNV = NULL;
glVertexAttribs2dvNVPROC glVertexAttribs2dvNV = NULL;
glVertexAttribs3svNVPROC glVertexAttribs3svNV = NULL;
glVertexAttribs3fvNVPROC glVertexAttribs3fvNV = NULL;
glVertexAttribs3dvNVPROC glVertexAttribs3dvNV = NULL;
glVertexAttribs4svNVPROC glVertexAttribs4svNV = NULL;
glVertexAttribs4fvNVPROC glVertexAttribs4fvNV = NULL;
glVertexAttribs4dvNVPROC glVertexAttribs4dvNV = NULL;
glVertexAttribs4ubvNVPROC glVertexAttribs4ubvNV = NULL;
#endif /* GL_NV_vertex_program */

/* NV_fence */

#ifdef GL_NV_fence
glGenFencesNVPROC glGenFencesNV = NULL;
glDeleteFencesNVPROC glDeleteFencesNV = NULL;
glSetFenceNVPROC glSetFenceNV = NULL;
glTestFenceNVPROC glTestFenceNV = NULL;
glFinishFenceNVPROC glFinishFenceNV = NULL;
glIsFenceNVPROC glIsFenceNV = NULL;
glGetFenceivNVPROC glGetFenceivNV = NULL;
#endif /* GL_NV_fence */

/* NV_register_combiners2 */

#ifdef GL_NV_register_combiners2
glCombinerStageParameterfvNVPROC glCombinerStageParameterfvNV = NULL;
glGetCombinerStageParameterfvNVPROC glGetCombinerStageParameterfvNV = NULL;
#endif /* GL_NV_register_combiners2 */

/* NV_evaluators */

#ifdef GL_NV_evaluators
glMapControlPointsNVPROC glMapControlPointsNV = NULL;
glMapParameterivNVPROC glMapParameterivNV = NULL;
glMapParameterfvNVPROC glMapParameterfvNV = NULL;
glGetMapControlPointsNVPROC glGetMapControlPointsNV = NULL;
glGetMapParameterivNVPROC glGetMapParameterivNV = NULL;
glGetMapParameterfvNVPROC glGetMapParameterfvNV = NULL;
glGetMapAttribParameterivNVPROC glGetMapAttribParameterivNV = NULL;
glGetMapAttribParameterfvNVPROC glGetMapAttribParameterfvNV = NULL;
glEvalMapsNVPROC glEvalMapsNV = NULL;
#endif /* GL_NV_evaluators */

/* ATI_pn_triangles */

#ifdef GL_ATI_pn_triangles 
glPNTrianglesiATIPROC glPNTrianglesiATI = NULL;
glPNTrianglesfATIPROC glPNTrianglesfATI = NULL;
#endif /* GL_ATI_pn_triangles */

/* ARB_point_parameters */

#ifdef GL_ARB_point_parameters
glPointParameterfARBPROC glPointParameterfARB = NULL;
glPointParameterfvARBPROC glPointParameterfvARB = NULL;
#endif /* GL_ABR_point_parameters */

/* ARB_vertex_blend */

#ifdef GL_ARB_vertex_blend
glWeightbvARBPROC glWeightbvARB = NULL;
glWeightsvARBPROC glWeightsvARB = NULL;
glWeightivARBPROC glWeightivARB = NULL;
glWeightfvARBPROC glWeightfvARB = NULL;
glWeightdvARBPROC glWeightdvARB = NULL;
glWeightubvARBPROC glWeightubvARB = NULL;
glWeightusvARBPROC glWeightusvARB = NULL;
glWeightuivARBPROC glWeightuivARB = NULL;
glWeightPointerARBPROC glWeightPointerARB = NULL;
glVertexBlendARBPROC glVertexBlendARB = NULL;
#endif /* GL_ARB_vertex_blend */

/* EXT_multi_draw_arrays */

#ifdef GL_EXT_multi_draw_arrays
glMultiDrawArraysEXTPROC glMultiDrawArraysEXT = NULL;
glMultiDrawElementsEXTPROC glMultiDrawElementsEXT = NULL;
#endif /* GL_EXT_multi_draw_arrays */

/* ARB_matrix_palette */

#ifdef GL_ARB_matrix_palette
glCurrentPaletteMatrixARBPROC glCurrentPaletteMatrixARB = NULL;
glMatrixIndexubvARBPROC glMatrixIndexubvARB = NULL;
glMatrixIndexusvARBPROC glMatrixIndexusvARB = NULL;
glMatrixIndexuivARBPROC glMatrixIndexuivARB = NULL;
glMatrixIndexPointerARBPROC glMatrixIndexPointerARB = NULL;
#endif /* GL_ARB_matrix_palette */

/* EXT_vertex_shader */

#ifdef GL_EXT_vertex_shader
glBeginVertexShaderEXTPROC glBeginVertexShaderEXT = NULL;
glEndVertexShaderEXTPROC glEndVertexShaderEXT = NULL;
glBindVertexShaderEXTPROC glBindVertexShaderEXT = NULL;
glGenVertexShadersEXTPROC glGenVertexShadersEXT = NULL;
glDeleteVertexShaderEXTPROC glDeleteVertexShaderEXT = NULL;
glShaderOp1EXTPROC glShaderOp1EXT = NULL;
glShaderOp2EXTPROC glShaderOp2EXT = NULL;
glShaderOp3EXTPROC glShaderOp3EXT = NULL;
glSwizzleEXTPROC glSwizzleEXT = NULL;
glWriteMaskEXTPROC glWriteMaskEXT = NULL;
glInsertComponentEXTPROC glInsertComponentEXT = NULL;
glExtractComponentEXTPROC glExtractComponentEXT = NULL;
glGenSymbolsEXTPROC glGenSymbolsEXT = NULL;
glSetInvariantEXTPROC glSetInvariantEXT = NULL;
glSetLocalConstantEXTPROC glSetLocalConstantEXT = NULL;
glVariantbvEXTPROC glVariantbvEXT = NULL;
glVariantsvEXTPROC glVariantsvEXT = NULL;
glVariantivEXTPROC glVariantivEXT = NULL;
glVariantfvEXTPROC glVariantfvEXT = NULL;
glVariantdvEXTPROC glVariantdvEXT = NULL;
glVariantubvEXTPROC glVariantubvEXT = NULL;
glVariantusvEXTPROC glVariantusvEXT = NULL;
glVariantuivEXTPROC glVariantuivEXT = NULL;
glVariantPointerEXTPROC glVariantPointerEXT = NULL;
glEnableVariantClientStateEXTPROC glEnableVariantClientStateEXT = NULL;
glDisableVariantClientStateEXTPROC glDisableVariantClientStateEXT = NULL;
glBindLightParameterEXTPROC glBindLightParameterEXT = NULL;
glBindMaterialParameterEXTPROC glBindMaterialParameterEXT = NULL;
glBindTexGenParameterEXTPROC glBindTexGenParameterEXT = NULL;
glBindTextureUnitParameterEXTPROC glBindTextureUnitParameterEXT = NULL;
glBindParameterEXTPROC glBindParameterEXT = NULL;
glIsVariantEnabledEXTPROC glIsVariantEnabledEXT = NULL;
glGetVariantBooleanvEXTPROC glGetVariantBooleanvEXT = NULL;

glGetVariantIntegervEXTPROC glGetVariantIntegervEXT = NULL;
glGetVariantFloatvEXTPROC glGetVariantFloatvEXT = NULL;
glGetVariantPointervEXTPROC glGetVariantPointervEXT = NULL;
glGetInvariantBooleanvEXTPROC glGetInvariantBooleanvEXT = NULL;
glGetInvariantIntegervEXTPROC glGetInvariantIntegervEXT = NULL;
glGetInvariantFloatvEXTPROC glGetInvariantFloatvEXT = NULL;
glGetLocalConstantBooleanvEXTPROC glGetLocalConstantBooleanvEXT = NULL;
glGetLocalConstantIntegervEXTPROC glGetLocalConstantIntegervEXT = NULL;
glGetLocalConstantFloatvEXTPROC glGetLocalConstantFloatvEXT = NULL;
#endif /* GL_EXT_vertex_shader */

/* ATI_envmap_bumpmap */

#ifdef GL_ATI_envmap_bumpmap
glTexBumpParameterivATIPROC glTexBumpParameterivATI = NULL;
glTexBumpParameterfvATIPROC glTexBumpParameterfvATI = NULL;
glGetTexBumpParameterivATIPROC glGetTexBumpParameterivATI = NULL;
glGetTexBumpParameterfvATIPROC glGetTexBumpParameterfvATI = NULL;
#endif /* GL_ATI_envmap_bumpmap */

/* ATI_fragment_shader */

#ifdef GL_ATI_fragment_shader
glGenFragmentShadersATIPROC glGenFragmentShadersATI = NULL;
glBindFragmentShaderATIPROC glBindFragmentShaderATI = NULL;
glDeleteFragmentShaderATIPROC glDeleteFragmentShaderATI = NULL;
glBeginFragmentShaderATIPROC glBeginFragmentShaderATI = NULL;
glEndFragmentShaderATIPROC glEndFragmentShaderATI = NULL;
glPassTexCoordATIPROC glPassTexCoordATI = NULL;
glSampleMapATIPROC glSampleMapATI = NULL;
glColorFragmentOp1ATIPROC glColorFragmentOp1ATI = NULL;
glColorFragmentOp2ATIPROC glColorFragmentOp2ATI = NULL;
glColorFragmentOp3ATIPROC glColorFragmentOp3ATI = NULL;
glAlphaFragmentOp1ATIPROC glAlphaFragmentOp1ATI = NULL;
glAlphaFragmentOp2ATIPROC glAlphaFragmentOp2ATI = NULL;
glAlphaFragmentOp3ATIPROC glAlphaFragmentOp3ATI = NULL;
glSetFragmentShaderConstantATIPROC glSetFragmentShaderConstantATI = NULL;
#endif /* GL_ATI_fragment_shader */

/* ATI_element_array */

#ifdef GL_ATI_element_array 
glElementPointerATIPROC glElementPointerATI = NULL;
glDrawElementArrayATIPROC glDrawElementArrayATI = NULL;
glDrawRangeElementArrayATIPROC glDrawRangeElementArrayATI = NULL;
#endif /* GL_ATI_element_array */

/* ATI_vertex_streams */

#ifdef GL_ATI_vertex_streams
glClientActiveVertexStreamATIPROC glClientActiveVertexStreamATI = NULL;
glVertexBlendEnviATIPROC glVertexBlendEnviATI = NULL;
glVertexBlendEnvfATIPROC glVertexBlendEnvfATI = NULL;
glVertexStream2sATIPROC glVertexStream2sATI = NULL;
glVertexStream2svATIPROC glVertexStream2svATI = NULL;
glVertexStream2iATIPROC glVertexStream2iATI = NULL;
glVertexStream2ivATIPROC glVertexStream2ivATI = NULL;
glVertexStream2fATIPROC glVertexStream2fATI = NULL;
glVertexStream2fvATIPROC glVertexStream2fvATI = NULL;
glVertexStream2dATIPROC glVertexStream2dATI = NULL;
glVertexStream2dvATIPROC glVertexStream2dvATI = NULL;
glVertexStream3sATIPROC glVertexStream3sATI = NULL;
glVertexStream3svATIPROC glVertexStream3svATI = NULL;
glVertexStream3iATIPROC glVertexStream3iATI = NULL;
glVertexStream3ivATIPROC glVertexStream3ivATI = NULL;
glVertexStream3fATIPROC glVertexStream3fATI = NULL;
glVertexStream3fvATIPROC glVertexStream3fvATI = NULL;
glVertexStream3dATIPROC glVertexStream3dATI = NULL;
glVertexStream3dvATIPROC glVertexStream3dvATI = NULL;
glVertexStream4sATIPROC glVertexStream4sATI = NULL;
glVertexStream4svATIPROC glVertexStream4svATI = NULL;
glVertexStream4iATIPROC glVertexStream4iATI = NULL;
glVertexStream4ivATIPROC glVertexStream4ivATI = NULL;
glVertexStream4fATIPROC glVertexStream4fATI = NULL;
glVertexStream4fvATIPROC glVertexStream4fvATI = NULL;
glVertexStream4dATIPROC glVertexStream4dATI = NULL;
glVertexStream4dvATIPROC glVertexStream4dvATI = NULL;
glNormalStream3bATIPROC glNormalStream3bATI = NULL;
glNormalStream3bvATIPROC glNormalStream3bvATI = NULL;
glNormalStream3sATIPROC glNormalStream3sATI = NULL;
glNormalStream3svATIPROC glNormalStream3svATI = NULL;
glNormalStream3iATIPROC glNormalStream3iATI = NULL;
glNormalStream3ivATIPROC glNormalStream3ivATI = NULL;
glNormalStream3fATIPROC glNormalStream3fATI = NULL;
glNormalStream3fvATIPROC glNormalStream3fvATI = NULL;
glNormalStream3dATIPROC glNormalStream3dATI = NULL;
glNormalStream3dvATIPROC glNormalStream3dvATI = NULL;
#endif /* GL_ATI_vertex_streams */

/* ATI_vertex_array_object */

#ifdef GL_ATI_vertex_array_object
glNewObjectBufferATIPROC glNewObjectBufferATI = NULL;
glIsObjectBufferATIPROC glIsObjectBufferATI = NULL;
glUpdateObjectBufferATIPROC glUpdateObjectBufferATI = NULL;
glGetObjectBufferfvATIPROC glGetObjectBufferfvATI = NULL;
glGetObjectBufferivATIPROC glGetObjectBufferivATI = NULL;
glFreeObjectBufferATIPROC glFreeObjectBufferATI = NULL;
glArrayObjectATIPROC glArrayObjectATI = NULL;
glGetArrayObjectfvATIPROC glGetArrayObjectfvATI = NULL;
glGetArrayObjectivATIPROC glGetArrayObjectivATI = NULL;
glVariantArrayObjectATIPROC glVariantArrayObjectATI = NULL;
glGetVariantArrayObjectfvATIPROC glGetVariantArrayObjectfvATI = NULL;
glGetVariantArrayObjectivATIPROC glGetVariantArrayObjectivATI = NULL;
#endif /* GL_ATI_vertex_array_object */

/* NV_occlusion_query */

#ifdef GL_NV_occlusion_query
glGenOcclusionQueriesNVPROC glGenOcclusionQueriesNV = NULL;
glDeleteOcclusionQueriesNVPROC glDeleteOcclusionQueriesNV = NULL;
glIsOcclusionQueryNVPROC glIsOcclusionQueryNV = NULL;
glBeginOcclusionQueryNVPROC glBeginOcclusionQueryNV = NULL;
glEndOcclusionQueryNVPROC glEndOcclusionQueryNV = NULL;
glGetOcclusionQueryivNVPROC glGetOcclusionQueryivNV = NULL;
glGetOcclusionQueryuivNVPROC glGetOcclusionQueryuivNV = NULL;
#endif /* GL_NV_occlusion_query */

/* NV_point_sprite */

#ifdef GL_NV_point_sprite
glPointParameteriNVPROC glPointParameteriNV = NULL;
glPointParameterivNVPROC glPointParameterivNV = NULL;
#endif /* GL_NV_point_sprite */

/* ARB_window_pos */

#ifdef GL_ARB_window_pos
glWindowPos2dARBPROC glWindowPos2dARB = NULL;
glWindowPos2fARBPROC glWindowPos2fARB = NULL;
glWindowPos2iARBPROC glWindowPos2iARB = NULL;
glWindowPos2sARBPROC glWindowPos2sARB = NULL;
glWindowPos2dvARBPROC glWindowPos2dvARB = NULL;
glWindowPos2fvARBPROC glWindowPos2fvARB = NULL;
glWindowPos2ivARBPROC glWindowPos2ivARB = NULL;
glWindowPos2svARBPROC glWindowPos2svARB = NULL;
glWindowPos3dARBPROC glWindowPos3dARB = NULL;
glWindowPos3fARBPROC glWindowPos3fARB = NULL;
glWindowPos3iARBPROC glWindowPos3iARB = NULL;
glWindowPos3sARBPROC glWindowPos3sARB = NULL;
glWindowPos3dvARBPROC glWindowPos3dvARB = NULL;
glWindowPos3fvARBPROC glWindowPos3fvARB = NULL;
glWindowPos3ivARBPROC glWindowPos3ivARB = NULL;
glWindowPos3svARBPROC glWindowPos3svARB = NULL;
#endif /* GL_ARB_window_pos */

/* EXT_draw_range_elements */

#ifdef GL_EXT_draw_range_elements
glDrawRangeElementsEXTPROC glDrawRangeElementsEXT = NULL;
#endif /* GL_EXT_draw_range_elements  */

/* EXT_stencil_two_side */

#ifdef GL_EXT_stencil_two_side
glActiveStencilFaceEXTPROC glActiveStencilFaceEXT = NULL;
#endif /* GL_EXT_stencil_two_side */

/* ARB_vertex_program */

#ifdef GL_ARB_vertex_program
glVertexAttrib1sARBPROC glVertexAttrib1sARB = NULL;
glVertexAttrib1fARBPROC glVertexAttrib1fARB = NULL;
glVertexAttrib1dARBPROC glVertexAttrib1dARB = NULL;
glVertexAttrib2sARBPROC glVertexAttrib2sARB = NULL;
glVertexAttrib2fARBPROC glVertexAttrib2fARB = NULL;
glVertexAttrib2dARBPROC glVertexAttrib2dARB = NULL;
glVertexAttrib3sARBPROC glVertexAttrib3sARB = NULL;
glVertexAttrib3fARBPROC glVertexAttrib3fARB = NULL;
glVertexAttrib3dARBPROC glVertexAttrib3dARB = NULL;
glVertexAttrib4sARBPROC glVertexAttrib4sARB = NULL;
glVertexAttrib4fARBPROC glVertexAttrib4fARB = NULL;
glVertexAttrib4dARBPROC glVertexAttrib4dARB = NULL;
glVertexAttrib4NubARBPROC glVertexAttrib4NubARB = NULL;
glVertexAttrib1svARBPROC glVertexAttrib1svARB = NULL;
glVertexAttrib1fvARBPROC glVertexAttrib1fvARB = NULL;
glVertexAttrib1dvARBPROC glVertexAttrib1dvARB = NULL;
glVertexAttrib2svARBPROC glVertexAttrib2svARB = NULL;
glVertexAttrib2fvARBPROC glVertexAttrib2fvARB = NULL;
glVertexAttrib2dvARBPROC glVertexAttrib2dvARB = NULL;
glVertexAttrib3svARBPROC glVertexAttrib3svARB = NULL;
glVertexAttrib3fvARBPROC glVertexAttrib3fvARB = NULL;
glVertexAttrib3dvARBPROC glVertexAttrib3dvARB = NULL;
glVertexAttrib4bvARBPROC glVertexAttrib4bvARB = NULL;
glVertexAttrib4svARBPROC glVertexAttrib4svARB = NULL;
glVertexAttrib4ivARBPROC glVertexAttrib4ivARB = NULL;
glVertexAttrib4ubvARBPROC glVertexAttrib4ubvARB = NULL;
glVertexAttrib4usvARBPROC glVertexAttrib4usvARB = NULL;
glVertexAttrib4uivARBPROC glVertexAttrib4uivARB = NULL;
glVertexAttrib4fvARBPROC glVertexAttrib4fvARB = NULL;
glVertexAttrib4dvARBPROC glVertexAttrib4dvARB = NULL;
glVertexAttrib4NbvARBPROC glVertexAttrib4NbvARB = NULL;
glVertexAttrib4NsvARBPROC glVertexAttrib4NsvARB = NULL;
glVertexAttrib4NivARBPROC glVertexAttrib4NivARB = NULL;
glVertexAttrib4NubvARBPROC glVertexAttrib4NubvARB = NULL;
glVertexAttrib4NusvARBPROC glVertexAttrib4NusvARB = NULL;
glVertexAttrib4NuivARBPROC glVertexAttrib4NuivARB = NULL;
glVertexAttribPointerARBPROC glVertexAttribPointerARB = NULL;
glEnableVertexAttribArrayARBPROC glEnableVertexAttribArrayARB = NULL;
glDisableVertexAttribArrayARBPROC glDisableVertexAttribArrayARB = NULL;
glProgramStringARBPROC glProgramStringARB = NULL;
glBindProgramARBPROC glBindProgramARB = NULL;
glDeleteProgramsARBPROC glDeleteProgramsARB = NULL;
glGenProgramsARBPROC glGenProgramsARB = NULL;
glProgramEnvParameter4dARBPROC glProgramEnvParameter4dARB = NULL;
glProgramEnvParameter4dvARBPROC glProgramEnvParameter4dvARB = NULL;
glProgramEnvParameter4fARBPROC glProgramEnvParameter4fARB = NULL;
glProgramEnvParameter4fvARBPROC glProgramEnvParameter4fvARB = NULL;
glProgramLocalParameter4dARBPROC glProgramLocalParameter4dARB = NULL;
glProgramLocalParameter4dvARBPROC glProgramLocalParameter4dvARB = NULL;
glProgramLocalParameter4fARBPROC glProgramLocalParameter4fARB = NULL;
glProgramLocalParameter4fvARBPROC glProgramLocalParameter4fvARB = NULL;
glGetProgramEnvParameterdvARBPROC glGetProgramEnvParameterdvARB = NULL;
glGetProgramEnvParameterfvARBPROC glGetProgramEnvParameterfvARB = NULL;
glGetProgramLocalParameterdvARBPROC glGetProgramLocalParameterdvARB = NULL;
glGetProgramLocalParameterfvARBPROC glGetProgramLocalParameterfvARB = NULL;
glGetProgramivARBPROC glGetProgramivARB = NULL;
glGetProgramStringARBPROC glGetProgramStringARB = NULL;
glGetVertexAttribdvARBPROC glGetVertexAttribdvARB = NULL;
glGetVertexAttribfvARBPROC glGetVertexAttribfvARB = NULL;
glGetVertexAttribivARBPROC glGetVertexAttribivARB = NULL;
glGetVertexAttribPointervARBPROC glGetVertexAttribPointervARB = NULL;
glIsProgramARBPROC glIsProgramARB = NULL;
#endif /* GL_ARB_vertex_program */

/* EXT_cull_vertex */

#ifdef GL_EXT_cull_vertex
glCullParameterfvEXTPROC glCullParameterfvEXT = NULL;
glCullParameterdvEXTPROC glCullParameterdvEXT = NULL;
#endif /* GL_EXT_cull_vertex */

#ifdef GL_EXT_blend_function_sepatate
glBlendFuncSeparateEXTPROC glBlendFuncSeparateEXT = NULL;
glBlendFuncSeparateINGRPROC glBlendFuncSeparateINGR = NULL;
#endif /* GL_EXT_blend_func_separate */


#ifdef GL_VERSION_1_4

/* OpenGL 1.4 stuff here */

#endif /* GL_VERSION_1_4 */

/* misc  */

static int error = 0;

struct ExtensionTypes extgl_Extensions;

struct ExtensionTypes SupportedExtensions;

/* getProcAddress */

void *lglGetProcAddress(char *name)
{
#ifdef _WIN32
    void *t = wglGetProcAddress(name);
/*    char err[1000];*/
    if (t == NULL)
    {
        /*sprintf(err, "wglGetProcAddress on %s failed", name);*/
        error = 1;  /*      MessageBox(0, err, "Error", MB_OK | MB_ICONHAND);*/
    }
    return t;
#else
    void *t = glXGetProcAddressARB((char*)name);
    if (t == NULL)
    {
        error = 1;
    }
    return t;
#endif
}

/*-----------------------------------------------------*/
/* WGL stuff */
/*-----------------------------------------------------*/

#ifdef _WIN32

static HDC _dc = 0;

#endif /* WIN32 */

#ifdef _WIN32

/* set the DC you will be working with */

/** returns true if the extention is available */
int QueryWGLExtension(const char *name)
{
    const GLubyte *extensions = NULL;
    const GLubyte *start;
    GLubyte *where, *terminator;

    /* Extension names should not have spaces. */
    where = (GLubyte *) strchr(name, ' ');
    if (where || *name == '\0')
        return 0;
    if ((wglGetExtensionsStringARB == NULL) || (_dc == 0))
        if (wglGetExtensionsStringEXT == NULL)
            return 0;
        else
            extensions = wglGetExtensionsStringEXT();
    else
        extensions = wglGetExtensionsStringARB(_dc);
    /* It takes a bit of care to be fool-proof about parsing the
         OpenGL extensions string. Don't be fooled by sub-strings,
        etc. */
    start = extensions;
    for (;;) 
    {
        where = (GLubyte *) strstr((const char *) start, name);
        if (!where)
            break;
        terminator = where + strlen(name);
        if (where == start || *(where - 1) == ' ')
            if (*terminator == ' ' || *terminator == '\0')
                return 1;
        start = terminator;
    }
    return 0;
}

void InitWGLARBBufferRegion()
{
#ifdef WGL_ARB_buffer_region    
    if (!extgl_Extensions.wgl.ARB_buffer_region)
        return;
    wglCreateBufferRegionARB = (wglCreateBufferRegionARBPROC) lglGetProcAddress("wglCreateBufferRegionARB");
    wglDeleteBufferRegionARB = (wglDeleteBufferRegionARBPROC) lglGetProcAddress("wglDeleteBufferRegionARB");
    wglSaveBufferRegionARB = (wglSaveBufferRegionARBPROC) lglGetProcAddress("wglSaveBufferRegionARB");
    wglRestoreBufferRegionARB = (wglRestoreBufferRegionARBPROC) lglGetProcAddress("wglRestoreBufferRegionARB");
#endif
}

void InitWGLARBPbuffer()
{
#ifdef WGL_ARB_pbuffer
    if (!extgl_Extensions.wgl.ARB_pbuffer)
        return;
    wglCreatePbufferARB = (wglCreatePbufferARBPROC) lglGetProcAddress("wglCreatePbufferARB");
    wglGetPbufferDCARB = (wglGetPbufferDCARBPROC) lglGetProcAddress("wglGetPbufferDCARB");
    wglReleasePbufferDCARB = (wglReleasePbufferDCARBPROC) lglGetProcAddress("wglReleasePbufferDCARB");
    wglDestroyPbufferARB = (wglDestroyPbufferARBPROC) lglGetProcAddress("wglDestroyPbufferARB");
    wglQueryPbufferARB = (wglQueryPbufferARBPROC) lglGetProcAddress("wglQueryPbufferARB");
#endif
}

void InitWGLARBPixelFormat()
{
#ifdef WGL_ARB_pixel_format
    if (!extgl_Extensions.wgl.ARB_pixel_format)
        return;
    wglGetPixelFormatAttribivARB = (wglGetPixelFormatAttribivARBPROC) lglGetProcAddress("wglGetPixelFormatAttribivARB");
    wglGetPixelFormatAttribfvARB = (wglGetPixelFormatAttribfvARBPROC) lglGetProcAddress("wglGetPixelFormatAttribfvARB");
    wglChoosePixelFormatARB = (wglChoosePixelFormatARBPROC) lglGetProcAddress("wglChoosePixelFormatARB");
#endif
}

void InitWGLARBRenderTexture()
{
#ifdef WGL_ARB_render_texture
    if (!extgl_Extensions.wgl.ARB_render_texture)
        return;
    wglBindTexImageARB = (wglBindTexImageARBPROC) lglGetProcAddress("wglBindTexImageARB");
    wglReleaseTexImageARB = (wglReleaseTexImageARBPROC) lglGetProcAddress("wglReleaseTexImageARB");
    wglSetPbufferAttribARB = (wglSetPbufferAttribARBPROC) lglGetProcAddress("wglSetPbufferAttribARB");
#endif
}

void InitWGLEXTSwapControl()
{
#ifdef WGL_EXT_swap_control
    if (!extgl_Extensions.wgl.EXT_swap_control)
        return;
    wglSwapIntervalEXT = (wglSwapIntervalEXTPROC) lglGetProcAddress("wglSwapIntervalEXT");
    wglGetSwapIntervalEXT = (wglGetSwapIntervalEXTPROC) lglGetProcAddress("wglGetSwapIntervalEXT");
#endif
}

void InitWGLARBMakeCurrentRead()
{
#ifdef WGL_ARB_make_current_read
    if (!extgl_Extensions.wgl.ARB_make_current_read)
        return;
    wglMakeContextCurrentARB = (wglMakeContextCurrentARBPROC) lglGetProcAddress("wglMakeContextCurrentARB");
    wglGetCurrentReadDCARB = (wglGetCurrentReadDCARBPROC) lglGetProcAddress("wglGetCurrentReadDCARB");
#endif
}

void InitSupportedWGLExtensions()
{
    extgl_Extensions.wgl.ARB_buffer_region = QueryWGLExtension("WGL_ARB_buffer_region");
    extgl_Extensions.wgl.ARB_make_current_read = QueryWGLExtension("WGL_ARB_make_current_read");
    extgl_Extensions.wgl.ARB_multisample = QueryWGLExtension("WGL_ARB_multisample");
    extgl_Extensions.wgl.ARB_pbuffer = QueryWGLExtension("WGL_ARB_pbuffer");
    extgl_Extensions.wgl.ARB_pixel_format = QueryWGLExtension("WGL_ARB_pixel_format");
    extgl_Extensions.wgl.ARB_render_texture = QueryWGLExtension("WGL_ARB_render_texture");
    extgl_Extensions.wgl.EXT_swap_control = QueryWGLExtension("WGL_EXT_swap_control");
    extgl_Extensions.wgl.NV_render_depth_texture = QueryWGLExtension("WGL_NV_render_depth_texture");
    extgl_Extensions.wgl.NV_render_texture_rectangle = QueryWGLExtension("WGL_NV_render_texture_rectangle");
}

void extgl_SetDC(HDC dc)
{
    _dc = dc;
}


void _wglSetDC(HDC dc)
{
    extgl_SetDC(dc);
}

int wglInitialize(HDC dc)
{
    _dc = dc;    
    error = 0;
    wglGetExtensionsStringARB = (wglGetExtensionsStringARBPROC) lglGetProcAddress("wglGetExtensionsStringARB");
    wglGetExtensionsStringEXT = (wglGetExtensionsStringEXTPROC) lglGetProcAddress("wglGetExtensionsStringEXT");
    extgl_Extensions.wgl.ARB_extensions_string = wglGetExtensionsStringARB != NULL;
    extgl_Extensions.wgl.EXT_extensions_string = wglGetExtensionsStringEXT != NULL;
    error = 0;

    InitSupportedWGLExtensions();
   

    InitWGLARBMakeCurrentRead();
    InitWGLEXTSwapControl();
    InitWGLARBRenderTexture();
    InitWGLARBPixelFormat();
    InitWGLARBPbuffer();
    InitWGLARBBufferRegion();
    
    return error;
}

#endif /* WIN32 */

/*-----------------------------------------------------*/
/* WGL stuff END*/
/*-----------------------------------------------------*/

/** returns true if the extention is available */
int QueryExtension(const char *name)
{
    const GLubyte *extensions = NULL;
    const GLubyte *start;
    GLubyte *where, *terminator;

    /* Extension names should not have spaces. */
    where = (GLubyte *) strchr(name, ' ');
    if (where || *name == '\0')
        return 0;
    extensions = glGetString(GL_EXTENSIONS);
    /* It takes a bit of care to be fool-proof about parsing the
         OpenGL extensions string. Don't be fooled by sub-strings,
        etc. */
    start = extensions;
    for (;;) 
    {
        where = (GLubyte *) strstr((const char *) start, name);
        if (!where)
            break;
        terminator = where + strlen(name);
        if (where == start || *(where - 1) == ' ')
            if (*terminator == ' ' || *terminator == '\0')
                return 1;
        start = terminator;
    }
    return 0;
    
/*    char *s = (char*)glGetString(GL_EXTENSIONS);
    char *temp = strstr(s, name);
    return temp!=NULL;*/
}
 
void InitEXTBlendFunctionSeparate()
{
#ifdef GL_EXT_blend_function_separate
    if (!extgl_Extensions.EXT_blend_func_separate)
        return;
    glBlendFuncSeparateEXT = (glBlendFuncSeparateEXTPROC) lglGetProcAddress("glBlendFuncSeparateEXT");
    glBlendFuncSeparateINGR = (glBlendFuncSeparateINGRPROC) lglGetProcAddress("glBlendFuncSeparateINGR");
#endif
}

void InitEXTCullVertex()
{
#ifdef GL_EXT_cull_vertex
    if (!extgl_Extensions.EXT_cull_vertex)
        return;
    glCullParameterfvEXT = (glCullParameterfvEXTPROC) lglGetProcAddress("glCullParameterfvEXT");
    glCullParameterdvEXT = (glCullParameterdvEXTPROC) lglGetProcAddress("glCullParameterdvEXT");
#endif
}

void InitARBVertexProgram()
{
#ifdef GL_ARB_vertex_program
    if (!extgl_Extensions.ARB_vertex_program)
        return;
    glVertexAttrib1sARB = (glVertexAttrib1sARBPROC) lglGetProcAddress("glVertexAttrib1sARB");
    glVertexAttrib1fARB = (glVertexAttrib1fARBPROC) lglGetProcAddress("glVertexAttrib1fARB");
    glVertexAttrib1dARB = (glVertexAttrib1dARBPROC) lglGetProcAddress("glVertexAttrib1dARB");
    glVertexAttrib2sARB = (glVertexAttrib2sARBPROC) lglGetProcAddress("glVertexAttrib2sARB");
    glVertexAttrib2fARB = (glVertexAttrib2fARBPROC) lglGetProcAddress("glVertexAttrib2fARB");
    glVertexAttrib2dARB = (glVertexAttrib2dARBPROC) lglGetProcAddress("glVertexAttrib2dARB");
    glVertexAttrib3sARB = (glVertexAttrib3sARBPROC) lglGetProcAddress("glVertexAttrib3sARB");
    glVertexAttrib3fARB = (glVertexAttrib3fARBPROC) lglGetProcAddress("glVertexAttrib3fARB");
    glVertexAttrib3dARB = (glVertexAttrib3dARBPROC) lglGetProcAddress("glVertexAttrib3dARB");
    glVertexAttrib4sARB = (glVertexAttrib4sARBPROC) lglGetProcAddress("glVertexAttrib4sARB");
    glVertexAttrib4fARB = (glVertexAttrib4fARBPROC) lglGetProcAddress("glVertexAttrib4fARB");
    glVertexAttrib4dARB = (glVertexAttrib4dARBPROC) lglGetProcAddress("glVertexAttrib4dARB");
    glVertexAttrib4NubARB = (glVertexAttrib4NubARBPROC) lglGetProcAddress("glVertexAttrib4NubARB");
    glVertexAttrib1svARB = (glVertexAttrib1svARBPROC) lglGetProcAddress("glVertexAttrib1svARB");
    glVertexAttrib1fvARB = (glVertexAttrib1fvARBPROC) lglGetProcAddress("glVertexAttrib1fvARB");
    glVertexAttrib1dvARB = (glVertexAttrib1dvARBPROC) lglGetProcAddress("glVertexAttrib1dvARB");
    glVertexAttrib2svARB = (glVertexAttrib2svARBPROC) lglGetProcAddress("glVertexAttrib2svARB");
    glVertexAttrib2fvARB = (glVertexAttrib2fvARBPROC) lglGetProcAddress("glVertexAttrib2fvARB");
    glVertexAttrib2dvARB = (glVertexAttrib2dvARBPROC) lglGetProcAddress("glVertexAttrib2dvARB");
    glVertexAttrib3svARB = (glVertexAttrib3svARBPROC) lglGetProcAddress("glVertexAttrib3svARB");
    glVertexAttrib3fvARB = (glVertexAttrib3fvARBPROC) lglGetProcAddress("glVertexAttrib3fvARB");
    glVertexAttrib3dvARB = (glVertexAttrib3dvARBPROC) lglGetProcAddress("glVertexAttrib3dvARB");
    glVertexAttrib4bvARB = (glVertexAttrib4bvARBPROC) lglGetProcAddress("glVertexAttrib4bvARB");
    glVertexAttrib4svARB = (glVertexAttrib4svARBPROC) lglGetProcAddress("glVertexAttrib4svARB");
    glVertexAttrib4ivARB = (glVertexAttrib4ivARBPROC) lglGetProcAddress("glVertexAttrib4ivARB");
    glVertexAttrib4ubvARB = (glVertexAttrib4ubvARBPROC) lglGetProcAddress("glVertexAttrib4ubvARB");
    glVertexAttrib4usvARB = (glVertexAttrib4usvARBPROC) lglGetProcAddress("glVertexAttrib4usvARB");
    glVertexAttrib4uivARB = (glVertexAttrib4uivARBPROC) lglGetProcAddress("glVertexAttrib4uivARB");
    glVertexAttrib4fvARB = (glVertexAttrib4fvARBPROC) lglGetProcAddress("glVertexAttrib4fvARB");
    glVertexAttrib4dvARB = (glVertexAttrib4dvARBPROC) lglGetProcAddress("glVertexAttrib4dvARB");
    glVertexAttrib4NbvARB = (glVertexAttrib4NbvARBPROC) lglGetProcAddress("glVertexAttrib4NbvARB");
    glVertexAttrib4NsvARB = (glVertexAttrib4NsvARBPROC) lglGetProcAddress("glVertexAttrib4NsvARB");
    glVertexAttrib4NivARB = (glVertexAttrib4NivARBPROC) lglGetProcAddress("glVertexAttrib4NivARB");
    glVertexAttrib4NubvARB = (glVertexAttrib4NubvARBPROC) lglGetProcAddress("glVertexAttrib4NubvARB");
    glVertexAttrib4NusvARB = (glVertexAttrib4NusvARBPROC) lglGetProcAddress("glVertexAttrib4NusvARB");
    glVertexAttrib4NuivARB = (glVertexAttrib4NuivARBPROC) lglGetProcAddress("glVertexAttrib4NuivARB");
    glVertexAttribPointerARB = (glVertexAttribPointerARBPROC) lglGetProcAddress("glVertexAttribPointerARB");
    glEnableVertexAttribArrayARB = (glEnableVertexAttribArrayARBPROC) lglGetProcAddress("glEnableVertexAttribArrayARB");
    glDisableVertexAttribArrayARB = (glDisableVertexAttribArrayARBPROC) lglGetProcAddress("glDisableVertexAttribArrayARB");
    glProgramStringARB = (glProgramStringARBPROC) lglGetProcAddress("glProgramStringARB");
    glBindProgramARB = (glBindProgramARBPROC) lglGetProcAddress("glBindProgramARB");
    glDeleteProgramsARB = (glDeleteProgramsARBPROC) lglGetProcAddress("glDeleteProgramsARB");
    glGenProgramsARB = (glGenProgramsARBPROC) lglGetProcAddress("glGenProgramsARB");
    glProgramEnvParameter4dARB = (glProgramEnvParameter4dARBPROC) lglGetProcAddress("glProgramEnvParameter4dARB");
    glProgramEnvParameter4dvARB = (glProgramEnvParameter4dvARBPROC) lglGetProcAddress("glProgramEnvParameter4dvARB");
    glProgramEnvParameter4fARB = (glProgramEnvParameter4fARBPROC) lglGetProcAddress("glProgramEnvParameter4fARB");
    glProgramEnvParameter4fvARB = (glProgramEnvParameter4fvARBPROC) lglGetProcAddress("glProgramEnvParameter4fvARB");
    glProgramLocalParameter4dARB = (glProgramLocalParameter4dARBPROC) lglGetProcAddress("glProgramLocalParameter4dARB");
    glProgramLocalParameter4dvARB = (glProgramLocalParameter4dvARBPROC) lglGetProcAddress("glProgramLocalParameter4dvARB");
    glProgramLocalParameter4fARB = (glProgramLocalParameter4fARBPROC) lglGetProcAddress("glProgramLocalParameter4fARB");
    glProgramLocalParameter4fvARB = (glProgramLocalParameter4fvARBPROC) lglGetProcAddress("glProgramLocalParameter4fvARB");
    glGetProgramEnvParameterdvARB = (glGetProgramEnvParameterdvARBPROC) lglGetProcAddress("glGetProgramEnvParameterdvARB");
    glGetProgramEnvParameterfvARB = (glGetProgramEnvParameterfvARBPROC) lglGetProcAddress("glGetProgramEnvParameterfvARB");
    glGetProgramLocalParameterdvARB = (glGetProgramLocalParameterdvARBPROC) lglGetProcAddress("glGetProgramLocalParameterdvARB");
    glGetProgramLocalParameterfvARB = (glGetProgramLocalParameterfvARBPROC) lglGetProcAddress("glGetProgramLocalParameterfvARB");
    glGetProgramivARB = (glGetProgramivARBPROC) lglGetProcAddress("glGetProgramivARB");
    glGetProgramStringARB = (glGetProgramStringARBPROC) lglGetProcAddress("glGetProgramStringARB");
    glGetVertexAttribdvARB = (glGetVertexAttribdvARBPROC) lglGetProcAddress("glGetVertexAttribdvARB");
    glGetVertexAttribfvARB = (glGetVertexAttribfvARBPROC) lglGetProcAddress("glGetVertexAttribfvARB");
    glGetVertexAttribivARB = (glGetVertexAttribivARBPROC) lglGetProcAddress("glGetVertexAttribivARB");
    glGetVertexAttribPointervARB = (glGetVertexAttribPointervARBPROC) lglGetProcAddress("glGetVertexAttribPointervARB");
    glIsProgramARB = (glIsProgramARBPROC) lglGetProcAddress("glIsProgramARB");
#endif
}

void InitEXTStencilTwoSide()
{
#ifdef GL_EXT_stencil_two_side
    if (!extgl_Extensions.EXT_stencil_two_side)
        return;
    glActiveStencilFaceEXT = (glActiveStencilFaceEXTPROC) lglGetProcAddress("glActiveStencilFaceEXT");
#endif
}

void InitARBWindowPos()
{
#ifdef GL_ARB_window_pos
    if (!extgl_Extensions.ARB_window_pos)
        return;
    glWindowPos2dARB = (glWindowPos2dARBPROC) lglGetProcAddress("glWindowPos2dARB");
    glWindowPos2fARB = (glWindowPos2fARBPROC) lglGetProcAddress("glWindowPos2fARB");
    glWindowPos2iARB = (glWindowPos2iARBPROC) lglGetProcAddress("glWindowPos2iARB");
    glWindowPos2sARB = (glWindowPos2sARBPROC) lglGetProcAddress("glWindowPos2sARB");
    glWindowPos2dvARB = (glWindowPos2dvARBPROC) lglGetProcAddress("glWindowPos2dvARB");
    glWindowPos2fvARB = (glWindowPos2fvARBPROC) lglGetProcAddress("glWindowPos2fvARB");
    glWindowPos2ivARB = (glWindowPos2ivARBPROC) lglGetProcAddress("glWindowPos2ivARB");
    glWindowPos2svARB = (glWindowPos2svARBPROC) lglGetProcAddress("glWindowPos2svARB");
    glWindowPos3dARB = (glWindowPos3dARBPROC) lglGetProcAddress("glWindowPos3dARB");
    glWindowPos3fARB = (glWindowPos3fARBPROC) lglGetProcAddress("glWindowPos3fARB");
    glWindowPos3iARB = (glWindowPos3iARBPROC) lglGetProcAddress("glWindowPos3iARB");
    glWindowPos3sARB = (glWindowPos3sARBPROC) lglGetProcAddress("glWindowPos3sARB");
    glWindowPos3dvARB = (glWindowPos3dvARBPROC) lglGetProcAddress("glWindowPos3dvARB");
    glWindowPos3fvARB = (glWindowPos3fvARBPROC) lglGetProcAddress("glWindowPos3fvARB");
    glWindowPos3ivARB = (glWindowPos3ivARBPROC) lglGetProcAddress("glWindowPos3ivARB");
    glWindowPos3svARB = (glWindowPos3svARBPROC) lglGetProcAddress("glWindowPos3svARB");
#endif 
}

void InitARBTextureCompression()
{
#ifdef GL_ARB_texture_compression
    if (!extgl_Extensions.ARB_texture_compression)
        return;
    glCompressedTexImage3DARB = (glCompressedTexImage3DARBPROC) lglGetProcAddress("glCompressedTexImage3DARB");
    glCompressedTexImage2DARB = (glCompressedTexImage2DARBPROC) lglGetProcAddress("glCompressedTexImage2DARB");
    glCompressedTexImage1DARB = (glCompressedTexImage1DARBPROC) lglGetProcAddress("glCompressedTexImage1DARB");
    glCompressedTexSubImage3DARB = (glCompressedTexSubImage3DARBPROC) lglGetProcAddress("glCompressedTexSubImage3DARB");
    glCompressedTexSubImage2DARB = (glCompressedTexSubImage2DARBPROC) lglGetProcAddress("glCompressedTexSubImage2DARB");
    glCompressedTexSubImage1DARB = (glCompressedTexSubImage1DARBPROC) lglGetProcAddress("glCompressedTexSubImage1DARB");
    glGetCompressedTexImageARB = (glGetCompressedTexImageARBPROC) lglGetProcAddress("glGetCompressedTexImageARB");
#endif
}

void InitNVPointSprite()
{
#ifdef GL_NV_point_sprite
    if (!extgl_Extensions.NV_point_sprite)
        return;
    glPointParameteriNV = (glPointParameteriNVPROC) lglGetProcAddress("glPointParameteriNV");
    glPointParameterivNV = (glPointParameterivNVPROC) lglGetProcAddress("glPointParameterivNV");
#endif
}

void InitNVOcclusionQuery()
{
#ifdef GL_NV_occlusion_query
    if (!extgl_Extensions.NV_occlusion_query)
        return;
    glGenOcclusionQueriesNV = (glGenOcclusionQueriesNVPROC) lglGetProcAddress("glGenOcclusionQueriesNV");
    glDeleteOcclusionQueriesNV = (glDeleteOcclusionQueriesNVPROC) lglGetProcAddress("glDeleteOcclusionQueriesNV");
    glIsOcclusionQueryNV = (glIsOcclusionQueryNVPROC) lglGetProcAddress("glIsOcclusionQueryNV");
    glBeginOcclusionQueryNV = (glBeginOcclusionQueryNVPROC) lglGetProcAddress("glBeginOcclusionQueryNV");
    glEndOcclusionQueryNV = (glEndOcclusionQueryNVPROC) lglGetProcAddress("glEndOcclusionQueryNV");
    glGetOcclusionQueryivNV = (glGetOcclusionQueryivNVPROC) lglGetProcAddress("glGetOcclusionQueryivNV");
    glGetOcclusionQueryuivNV = (glGetOcclusionQueryuivNVPROC) lglGetProcAddress("glGetOcclusionQueryuivNV");
#endif
}

void InitATIVertexArrayObject()
{
#ifdef GL_ATI_vertex_array_object
    if (!extgl_Extensions.ATI_vertex_array_object)
        return;
    glNewObjectBufferATI = (glNewObjectBufferATIPROC) lglGetProcAddress("glNewObjectBufferATI");
    glIsObjectBufferATI = (glIsObjectBufferATIPROC) lglGetProcAddress("glIsObjectBufferATI");
    glUpdateObjectBufferATI = (glUpdateObjectBufferATIPROC) lglGetProcAddress("glUpdateObjectBufferATI");
    glGetObjectBufferfvATI = (glGetObjectBufferfvATIPROC) lglGetProcAddress("glGetObjectBufferfvATI");
    glGetObjectBufferivATI = (glGetObjectBufferivATIPROC) lglGetProcAddress("glGetObjectBufferivATI");
    glFreeObjectBufferATI = (glFreeObjectBufferATIPROC) lglGetProcAddress("glFreeObjectBufferATI");
    glArrayObjectATI = (glArrayObjectATIPROC) lglGetProcAddress("glArrayObjectATI");
    glGetArrayObjectfvATI = (glGetArrayObjectfvATIPROC) lglGetProcAddress("glGetArrayObjectfvATI");
    glGetArrayObjectivATI = (glGetArrayObjectivATIPROC) lglGetProcAddress("glGetArrayObjectivATI");
    glVariantArrayObjectATI = (glVariantArrayObjectATIPROC) lglGetProcAddress("glVariantArrayObjectATI");
    glGetVariantArrayObjectfvATI = (glGetVariantArrayObjectfvATIPROC) lglGetProcAddress("glGetVariantArrayObjectfvATI");
    glGetVariantArrayObjectivATI = (glGetVariantArrayObjectivATIPROC) lglGetProcAddress("glGetVariantArrayObjectivATI");
#endif
}

void InitATIVertexStreams()
{
#ifdef GL_ATI_vertex_streams
    if (!extgl_Extensions.ATI_vertex_streams)
        return;
    glClientActiveVertexStreamATI = (glClientActiveVertexStreamATIPROC) lglGetProcAddress("glClientActiveVertexStreamATI");
    glVertexBlendEnviATI = (glVertexBlendEnviATIPROC) lglGetProcAddress("glVertexBlendEnviATI");
    glVertexBlendEnvfATI = (glVertexBlendEnvfATIPROC) lglGetProcAddress("glVertexBlendEnvfATI");
    glVertexStream2sATI = (glVertexStream2sATIPROC) lglGetProcAddress("glVertexStream2sATI");
    glVertexStream2svATI = (glVertexStream2svATIPROC) lglGetProcAddress("glVertexStream2svATI");
    glVertexStream2iATI = (glVertexStream2iATIPROC) lglGetProcAddress("glVertexStream2iATI");
    glVertexStream2ivATI = (glVertexStream2ivATIPROC) lglGetProcAddress("glVertexStream2ivATI");
    glVertexStream2fATI = (glVertexStream2fATIPROC) lglGetProcAddress("glVertexStream2fATI");
    glVertexStream2fvATI = (glVertexStream2fvATIPROC) lglGetProcAddress("glVertexStream2fvATI");
    glVertexStream2dATI = (glVertexStream2dATIPROC) lglGetProcAddress("glVertexStream2dATI");
    glVertexStream2dvATI = (glVertexStream2dvATIPROC) lglGetProcAddress("glVertexStream2dvATI");
    glVertexStream3sATI = (glVertexStream3sATIPROC) lglGetProcAddress("glVertexStream3sATI");
    glVertexStream3svATI = (glVertexStream3svATIPROC) lglGetProcAddress("glVertexStream3svATI");
    glVertexStream3iATI = (glVertexStream3iATIPROC) lglGetProcAddress("glVertexStream3iATI");
    glVertexStream3ivATI = (glVertexStream3ivATIPROC) lglGetProcAddress("glVertexStream3ivATI");
    glVertexStream3fATI = (glVertexStream3fATIPROC) lglGetProcAddress("glVertexStream3fATI");
    glVertexStream3fvATI = (glVertexStream3fvATIPROC) lglGetProcAddress("glVertexStream3fvATI");
    glVertexStream3dATI = (glVertexStream3dATIPROC) lglGetProcAddress("glVertexStream3dATI");
    glVertexStream3dvATI = (glVertexStream3dvATIPROC) lglGetProcAddress("glVertexStream3dvATI");
    glVertexStream4sATI = (glVertexStream4sATIPROC) lglGetProcAddress("glVertexStream4sATI");
    glVertexStream4svATI = (glVertexStream4svATIPROC) lglGetProcAddress("glVertexStream4svATI");
    glVertexStream4iATI = (glVertexStream4iATIPROC) lglGetProcAddress("glVertexStream4iATI");
    glVertexStream4ivATI = (glVertexStream4ivATIPROC) lglGetProcAddress("glVertexStream4ivATI");
    glVertexStream4fATI = (glVertexStream4fATIPROC) lglGetProcAddress("glVertexStream4fATI");
    glVertexStream4fvATI = (glVertexStream4fvATIPROC) lglGetProcAddress("glVertexStream4fvATI");
    glVertexStream4dATI = (glVertexStream4dATIPROC) lglGetProcAddress("glVertexStream4dATI");
    glVertexStream4dvATI = (glVertexStream4dvATIPROC) lglGetProcAddress("glVertexStream4dvATI");
    glNormalStream3bATI = (glNormalStream3bATIPROC) lglGetProcAddress("glNormalStream3bATI");
    glNormalStream3bvATI = (glNormalStream3bvATIPROC) lglGetProcAddress("glNormalStream3bvATI");
    glNormalStream3sATI = (glNormalStream3sATIPROC) lglGetProcAddress("glNormalStream3sATI");
    glNormalStream3svATI = (glNormalStream3svATIPROC) lglGetProcAddress("glNormalStream3svATI");
    glNormalStream3iATI = (glNormalStream3iATIPROC) lglGetProcAddress("glNormalStream3iATI");
    glNormalStream3ivATI = (glNormalStream3ivATIPROC) lglGetProcAddress("glNormalStream3ivATI");
    glNormalStream3fATI = (glNormalStream3fATIPROC) lglGetProcAddress("glNormalStream3fATI");
    glNormalStream3fvATI = (glNormalStream3fvATIPROC) lglGetProcAddress("glNormalStream3fvATI");
    glNormalStream3dATI = (glNormalStream3dATIPROC) lglGetProcAddress("glNormalStream3dATI");
    glNormalStream3dvATI = (glNormalStream3dvATIPROC) lglGetProcAddress("glNormalStream3dvATI");
#endif
}

void InitATIElementArray()
{
#ifdef GL_ATI_element_array
    if (!extgl_Extensions.ATI_element_array)
        return;
    glElementPointerATI = (glElementPointerATIPROC) lglGetProcAddress("glElementPointerATI");
    glDrawElementArrayATI = (glDrawElementArrayATIPROC) lglGetProcAddress("glDrawElementArrayATI");
    glDrawRangeElementArrayATI = (glDrawRangeElementArrayATIPROC) lglGetProcAddress("glDrawRangeElementArrayATI");
#endif
}

void InitATIFragmentShader()
{
#ifdef GL_ATI_fragment_shader
    if (!extgl_Extensions.ATI_fragment_shader)
        return;
    glGenFragmentShadersATI = (glGenFragmentShadersATIPROC) lglGetProcAddress("glGenFragmentShadersATI");
    glBindFragmentShaderATI = (glBindFragmentShaderATIPROC) lglGetProcAddress("glBindFragmentShaderATI");
    glDeleteFragmentShaderATI = (glDeleteFragmentShaderATIPROC) lglGetProcAddress("glDeleteFragmentShaderATI");
    glBeginFragmentShaderATI = (glBeginFragmentShaderATIPROC) lglGetProcAddress("glBeginFragmentShaderATI");
    glEndFragmentShaderATI = (glEndFragmentShaderATIPROC) lglGetProcAddress("glEndFragmentShaderATI");
    glPassTexCoordATI = (glPassTexCoordATIPROC) lglGetProcAddress("glPassTexCoordATI");
    glSampleMapATI = (glSampleMapATIPROC) lglGetProcAddress("glSampleMapATI");
    glColorFragmentOp1ATI = (glColorFragmentOp1ATIPROC) lglGetProcAddress("glColorFragmentOp1ATI");
    glColorFragmentOp2ATI = (glColorFragmentOp2ATIPROC) lglGetProcAddress("glColorFragmentOp2ATI");
    glColorFragmentOp3ATI = (glColorFragmentOp3ATIPROC) lglGetProcAddress("glColorFragmentOp3ATI");
    glAlphaFragmentOp1ATI = (glAlphaFragmentOp1ATIPROC) lglGetProcAddress("glAlphaFragmentOp1ATI");
    glAlphaFragmentOp2ATI = (glAlphaFragmentOp2ATIPROC) lglGetProcAddress("glAlphaFragmentOp2ATI");
    glAlphaFragmentOp3ATI = (glAlphaFragmentOp3ATIPROC) lglGetProcAddress("glAlphaFragmentOp3ATI");
    glSetFragmentShaderConstantATI = (glSetFragmentShaderConstantATIPROC) lglGetProcAddress("glSetFragmentShaderConstantATI");
#endif
}


void InitATIEnvmapBumpmap()
{
#ifdef GL_ATI_envmap_bumpmap
    if (!extgl_Extensions.ATI_envmap_bumpmap)
        return;
    glTexBumpParameterivATI = (glTexBumpParameterivATIPROC) lglGetProcAddress("glTexBumpParameterivATI");
    glTexBumpParameterfvATI = (glTexBumpParameterfvATIPROC) lglGetProcAddress("glTexBumpParameterfvATI");
    glGetTexBumpParameterivATI = (glGetTexBumpParameterivATIPROC) lglGetProcAddress("glGetTexBumpParameterivATI");
    glGetTexBumpParameterfvATI = (glGetTexBumpParameterfvATIPROC) lglGetProcAddress("glGetTexBumpParameterfvATI");
#endif
}

void InitEXTVertexShader()
{
#ifdef GL_EXT_vertex_shader
    if (!extgl_Extensions.EXT_vertex_shader)
        return;
    glBeginVertexShaderEXT = (glBeginVertexShaderEXTPROC) lglGetProcAddress("glBeginVertexShaderEXT");
    glEndVertexShaderEXT = (glEndVertexShaderEXTPROC) lglGetProcAddress("glEndVertexShaderEXT");
    glBindVertexShaderEXT = (glBindVertexShaderEXTPROC) lglGetProcAddress("glBindVertexShaderEXT");
    glGenVertexShadersEXT = (glGenVertexShadersEXTPROC) lglGetProcAddress("glGenVertexShadersEXT");
    glDeleteVertexShaderEXT = (glDeleteVertexShaderEXTPROC) lglGetProcAddress("glDeleteVertexShaderEXT");
    glShaderOp1EXT = (glShaderOp1EXTPROC) lglGetProcAddress("glShaderOp1EXT");
    glShaderOp2EXT = (glShaderOp2EXTPROC) lglGetProcAddress("glShaderOp2EXT");
    glShaderOp3EXT = (glShaderOp3EXTPROC) lglGetProcAddress("glShaderOp3EXT");
    glSwizzleEXT = (glSwizzleEXTPROC) lglGetProcAddress("glSwizzleEXT");
    glWriteMaskEXT = (glWriteMaskEXTPROC) lglGetProcAddress("glWriteMaskEXT");
    glInsertComponentEXT = (glInsertComponentEXTPROC) lglGetProcAddress("glInsertComponentEXT");
    glExtractComponentEXT = (glExtractComponentEXTPROC) lglGetProcAddress("glExtractComponentEXT");
    glGenSymbolsEXT = (glGenSymbolsEXTPROC) lglGetProcAddress("glGenSymbolsEXT");
    glSetInvariantEXT = (glSetInvariantEXTPROC) lglGetProcAddress("glSetInvarianceEXT");
    glSetLocalConstantEXT = (glSetLocalConstantEXTPROC) lglGetProcAddress("glSetLocalConstantEXT");
    glVariantbvEXT = (glVariantbvEXTPROC) lglGetProcAddress("glVariantbvEXT");
    glVariantsvEXT = (glVariantsvEXTPROC) lglGetProcAddress("glVariantsvEXT");
    glVariantivEXT = (glVariantivEXTPROC) lglGetProcAddress("glVariantivEXT");
    glVariantfvEXT = (glVariantfvEXTPROC) lglGetProcAddress("glVariantfvEXT");
    glVariantdvEXT = (glVariantdvEXTPROC) lglGetProcAddress("glVariantdvEXT");
    glVariantubvEXT = (glVariantubvEXTPROC) lglGetProcAddress("glVariantubvEXT");
    glVariantusvEXT = (glVariantusvEXTPROC) lglGetProcAddress("glVariantusvEXT");
    glVariantuivEXT = (glVariantuivEXTPROC) lglGetProcAddress("glVariantuivEXT");
    glVariantPointerEXT = (glVariantPointerEXTPROC) lglGetProcAddress("glVariantPointerEXT");
    glEnableVariantClientStateEXT = (glEnableVariantClientStateEXTPROC) lglGetProcAddress("glEnableVariantClientStateEXT");
    glDisableVariantClientStateEXT = (glDisableVariantClientStateEXTPROC) lglGetProcAddress("glDisableVariantClientStateEXT");
    glBindLightParameterEXT = (glBindLightParameterEXTPROC) lglGetProcAddress("glBindLightParameterEXT");
    glBindMaterialParameterEXT = (glBindMaterialParameterEXTPROC) lglGetProcAddress("glBindMaterialParameterEXT");
    glBindTexGenParameterEXT = (glBindTexGenParameterEXTPROC) lglGetProcAddress("glBindTexGenParameterEXT");
    glBindTextureUnitParameterEXT = (glBindTextureUnitParameterEXTPROC) lglGetProcAddress("glBindTextureUnitParameterEXT");
    glBindParameterEXT = (glBindParameterEXTPROC) lglGetProcAddress("glBindParameterEXT");
    glIsVariantEnabledEXT = (glIsVariantEnabledEXTPROC) lglGetProcAddress("glIsVariantEnabledEXT");
    glGetVariantBooleanvEXT = (glGetVariantBooleanvEXTPROC) lglGetProcAddress("glGetVariantBooleanvEXT");
    glGetVariantIntegervEXT = (glGetVariantIntegervEXTPROC) lglGetProcAddress("glGetVariantIntegervEXT");
    glGetVariantFloatvEXT = (glGetVariantFloatvEXTPROC) lglGetProcAddress("glGetVariantFloatvEXT");
    glGetVariantPointervEXT = (glGetVariantPointervEXTPROC) lglGetProcAddress("glGetVariantPointervEXT");
    glGetInvariantBooleanvEXT = (glGetInvariantBooleanvEXTPROC) lglGetProcAddress("glGetInvariantBooleanvEXT");
    glGetInvariantIntegervEXT = (glGetInvariantIntegervEXTPROC) lglGetProcAddress("glGetInvariantIntegervEXT");
    glGetInvariantFloatvEXT = (glGetInvariantFloatvEXTPROC) lglGetProcAddress("glGetInvariantFloatvEXT");
    glGetLocalConstantBooleanvEXT = (glGetLocalConstantBooleanvEXTPROC) lglGetProcAddress("glGetLocalConstantBooleanvEXT");
    glGetLocalConstantIntegervEXT = (glGetLocalConstantIntegervEXTPROC) lglGetProcAddress("glGetLocalConstantIntegervEXT");
    glGetLocalConstantFloatvEXT = (glGetLocalConstantFloatvEXTPROC) lglGetProcAddress("glGetLocalConstantFloatvEXT");
#endif
}

void InitARBMatrixPalette()
{
#ifdef GL_ARB_matrix_palette
    if (!extgl_Extensions.ARB_matrix_palette)
        return;
    glCurrentPaletteMatrixARB = (glCurrentPaletteMatrixARBPROC) lglGetProcAddress("glCurrentPaletteMatrixARB");
    glMatrixIndexubvARB = (glMatrixIndexubvARBPROC) lglGetProcAddress("glMatrixIndexubvARB");
    glMatrixIndexusvARB = (glMatrixIndexusvARBPROC) lglGetProcAddress("glMatrixIndexusvARB");
    glMatrixIndexuivARB = (glMatrixIndexuivARBPROC) lglGetProcAddress("glMatrixIndexuivARB");
    glMatrixIndexPointerARB = (glMatrixIndexPointerARBPROC) lglGetProcAddress("glMatrixIndexPointerARB");
#endif
}

void InitEXTMultiDrawArrays()
{
#ifdef GL_EXT_multi_draw_arrays
    if (!extgl_Extensions.EXT_multi_draw_arrays)
        return;
    glMultiDrawArraysEXT = (glMultiDrawArraysEXTPROC) lglGetProcAddress("glMultiDrawArraysEXT");
    glMultiDrawElementsEXT = (glMultiDrawElementsEXTPROC) lglGetProcAddress("glMultiDrawElementsEXT");
#endif
}

void InitARBVertexBlend()
{
#ifdef GL_ARB_vertex_blend
    if (!extgl_Extensions.ARB_vertex_blend)
        return;
    glWeightbvARB = (glWeightbvARBPROC) lglGetProcAddress("glWeightbvARB");
    glWeightsvARB = (glWeightsvARBPROC) lglGetProcAddress("glWeightsvARB");
    glWeightivARB = (glWeightivARBPROC) lglGetProcAddress("glWeightivARB");
    glWeightfvARB = (glWeightfvARBPROC) lglGetProcAddress("glWeightfvARB");
    glWeightdvARB = (glWeightdvARBPROC) lglGetProcAddress("glWeightdvARB");
    glWeightubvARB = (glWeightubvARBPROC) lglGetProcAddress("glWeightubvARB");
    glWeightusvARB = (glWeightusvARBPROC) lglGetProcAddress("glWeightusvARB");
    glWeightuivARB = (glWeightuivARBPROC) lglGetProcAddress("glWeightuivARB");
    glWeightPointerARB = (glWeightPointerARBPROC) lglGetProcAddress("glWeightPointerARB");
    glVertexBlendARB = (glVertexBlendARBPROC) lglGetProcAddress("glVertexBlendARB");
#endif
}

void InitARBPointParameters()
{
#ifdef GL_ARB_point_parameters
    if (!extgl_Extensions.ARB_point_parameters)
        return;
    glPointParameterfARB = (glPointParameterfARBPROC) lglGetProcAddress("glPointParameterfARB");
    glPointParameterfvARB = (glPointParameterfvARBPROC) lglGetProcAddress("glPointParameterfvARB");
#endif
}

void InitATIPNTriangles()
{
#ifdef GL_ATI_pn_triangles
    if (!extgl_Extensions.ATI_pn_triangles)
        return;
    glPNTrianglesiATI = (glPNTrianglesiATIPROC) lglGetProcAddress("glPNTrianglesiATI");
    glPNTrianglesfATI = (glPNTrianglesfATIPROC) lglGetProcAddress("glPNTrianglesfATI");
#endif
}

void InitNVEvaluators()
{
#ifdef GL_NV_evaluators
    if (!extgl_Extensions.NV_evaluators)
        return;
    glMapControlPointsNV = (glMapControlPointsNVPROC) lglGetProcAddress("glMapControlPointsNV");
    glMapParameterivNV = (glMapParameterivNVPROC) lglGetProcAddress("glMapParameterivNV");
    glMapParameterfvNV = (glMapParameterfvNVPROC) lglGetProcAddress("glMapParameterfvNV");
    glGetMapControlPointsNV = (glGetMapControlPointsNVPROC) lglGetProcAddress("glGetMapControlPointsNV");
    glGetMapParameterivNV = (glGetMapParameterivNVPROC) lglGetProcAddress("glGetMapParameterivNV");
    glGetMapParameterfvNV = (glGetMapParameterfvNVPROC) lglGetProcAddress("glGetMapParameterfvNV");
    glGetMapAttribParameterivNV = (glGetMapAttribParameterivNVPROC) lglGetProcAddress("glGetMapAttribParameterivNV");
    glGetMapAttribParameterfvNV = (glGetMapAttribParameterfvNVPROC) lglGetProcAddress("glGetMapAttribParameterfvNV");
    glEvalMapsNV = (glEvalMapsNVPROC) lglGetProcAddress("glEvalMapsNV");
#endif
}

void InitNVRegisterCombiners2()
{
#ifdef GL_NV_register_combiners
    if (!extgl_Extensions.NV_register_combiners2)
        return;
    glCombinerStageParameterfvNV = (glCombinerStageParameterfvNVPROC) lglGetProcAddress("glCombinerStageParameterfvNV");
    glGetCombinerStageParameterfvNV = (glGetCombinerStageParameterfvNVPROC) lglGetProcAddress("glGetCombinerStageParameterfvNV");
#endif
}

void InitNVFence()
{
#ifdef GL_NV_fence
    if (!extgl_Extensions.NV_fence)
        return;
    glGenFencesNV = (glGenFencesNVPROC) lglGetProcAddress("glGenFencesNV");
    glDeleteFencesNV = (glDeleteFencesNVPROC) lglGetProcAddress("glDeleteFencesNV");
    glSetFenceNV = (glSetFenceNVPROC) lglGetProcAddress("glSetFenceNV");
    glTestFenceNV = (glTestFenceNVPROC) lglGetProcAddress("glTestFenceNV");
    glFinishFenceNV = (glFinishFenceNVPROC) lglGetProcAddress("glFinishFenceNV");
    glIsFenceNV = (glIsFenceNVPROC) lglGetProcAddress("glIsFenceNV");
    glGetFenceivNV = (glGetFenceivNVPROC) lglGetProcAddress("glGetFenceivNV");
#endif
}

void InitNVVertexProgram()
{
#ifdef GL_NV_vertex_program
    if (!extgl_Extensions.NV_vertex_program)
        return;
    glBindProgramNV = (glBindProgramNVPROC) lglGetProcAddress("glBindProgramNV");
    glDeleteProgramsNV = (glDeleteProgramsNVPROC) lglGetProcAddress("glDeleteProgramsNV");
    glExecuteProgramNV = (glExecuteProgramNVPROC) lglGetProcAddress("glExecuteProgramNV");
    glGenProgramsNV = (glGenProgramsNVPROC) lglGetProcAddress("glGenProgramsNV");
    glAreProgramsResidentNV = (glAreProgramsResidentNVPROC) lglGetProcAddress("glAreProgramsResidentNV");
    glRequestResidentProgramsNV = (glRequestResidentProgramsNVPROC) lglGetProcAddress("glRequestResidentProgramsNV");
    glGetProgramParameterfvNV = (glGetProgramParameterfvNVPROC) lglGetProcAddress("glGetProgramParameterfvNV");
    glGetProgramParameterdvNV = (glGetProgramParameterdvNVPROC) lglGetProcAddress("glGetProgramParameterdvNV");
    glGetProgramivNV = (glGetProgramivNVPROC) lglGetProcAddress("glGetProgramivNV");
    glGetProgramStringNV = (glGetProgramStringNVPROC) lglGetProcAddress("glGetProgramStringNV");
    glGetTrackMatrixivNV = (glGetTrackMatrixivNVPROC) lglGetProcAddress("glGetTrackMatrixivNV");
    glGetVertexAttribdvNV = (glGetVertexAttribdvNVPROC) lglGetProcAddress("glGetVertexAttribdvNV");
    glGetVertexAttribfvNV = (glGetVertexAttribfvNVPROC) lglGetProcAddress("glGetVertexAttribfvNV");
    glGetVertexAttribivNV = (glGetVertexAttribivNVPROC) lglGetProcAddress("glGetVertexAttribivNV");
    glGetVertexAttribPointervNV = (glGetVertexAttribPointervNVPROC) lglGetProcAddress("glGetVertexAttribPointervNV");
    glIsProgramNV = (glIsProgramNVPROC) lglGetProcAddress("glIsProgramNV");
    glLoadProgramNV = (glLoadProgramNVPROC) lglGetProcAddress("glLoadProgramNV");
    glProgramParameter4fNV = (glProgramParameter4fNVPROC) lglGetProcAddress("glProgramParameter4fNV");
    glProgramParameter4dNV = (glProgramParameter4dNVPROC) lglGetProcAddress("glProgramParameter4dNV");
    glProgramParameter4dvNV = (glProgramParameter4dvNVPROC) lglGetProcAddress("glProgramParameter4dvNV");
    glProgramParameter4fvNV = (glProgramParameter4fvNVPROC) lglGetProcAddress("glProgramParameter4fvNV");
    glProgramParameters4dvNV = (glProgramParameters4dvNVPROC) lglGetProcAddress("glProgramParameters4dvNV");
    glProgramParameters4fvNV = (glProgramParameters4fvNVPROC) lglGetProcAddress("glProgramParameters4fvNV");
    glTrackMatrixNV = (glTrackMatrixNVPROC) lglGetProcAddress("glTrackMatrixNV");
    glVertexAttribPointerNV = (glVertexAttribPointerNVPROC) lglGetProcAddress("glVertexAttribPointerNV");
    glVertexAttrib1sNV = (glVertexAttrib1sNVPROC) lglGetProcAddress("glVertexAttrib1sNV");
    glVertexAttrib1fNV = (glVertexAttrib1fNVPROC) lglGetProcAddress("glVertexAttrib1fNV");
    glVertexAttrib1dNV = (glVertexAttrib1dNVPROC) lglGetProcAddress("glVertexAttrib1dNV");
    glVertexAttrib2sNV = (glVertexAttrib2sNVPROC) lglGetProcAddress("glVertexAttrib2sNV");
    glVertexAttrib2fNV = (glVertexAttrib2fNVPROC) lglGetProcAddress("glVertexAttrib2fNV");
    glVertexAttrib2dNV = (glVertexAttrib2dNVPROC) lglGetProcAddress("glVertexAttrib2dNV");
    glVertexAttrib3sNV = (glVertexAttrib3sNVPROC) lglGetProcAddress("glVertexAttrib3sNV");
    glVertexAttrib3fNV = (glVertexAttrib3fNVPROC) lglGetProcAddress("glVertexAttrib3fNV");
    glVertexAttrib3dNV = (glVertexAttrib3dNVPROC) lglGetProcAddress("glVertexAttrib3dNV");
    glVertexAttrib4sNV = (glVertexAttrib4sNVPROC) lglGetProcAddress("glVertexAttrib4sNV");
    glVertexAttrib4fNV = (glVertexAttrib4fNVPROC) lglGetProcAddress("glVertexAttrib4fNV");
    glVertexAttrib4dNV = (glVertexAttrib4dNVPROC) lglGetProcAddress("glVertexAttrib4dNV");
    glVertexAttrib4ubNV = (glVertexAttrib4ubNVPROC) lglGetProcAddress("glVertexAttrib4ubNV");
    glVertexAttrib1svNV = (glVertexAttrib1svNVPROC) lglGetProcAddress("glVertexAttrib1svNV");
    glVertexAttrib1fvNV = (glVertexAttrib1fvNVPROC) lglGetProcAddress("glVertexAttrib1fvNV");
    glVertexAttrib1dvNV = (glVertexAttrib1dvNVPROC) lglGetProcAddress("glVertexAttrib1dvNV");
    glVertexAttrib2svNV = (glVertexAttrib2svNVPROC) lglGetProcAddress("glVertexAttrib2svNV");
    glVertexAttrib2fvNV = (glVertexAttrib2fvNVPROC) lglGetProcAddress("glVertexAttrib2fvNV");
    glVertexAttrib2dvNV = (glVertexAttrib2dvNVPROC) lglGetProcAddress("glVertexAttrib2dvNV");
    glVertexAttrib3svNV = (glVertexAttrib3svNVPROC) lglGetProcAddress("glVertexAttrib3svNV");
    glVertexAttrib3fvNV = (glVertexAttrib3fvNVPROC) lglGetProcAddress("glVertexAttrib3fvNV");
    glVertexAttrib3dvNV = (glVertexAttrib3dvNVPROC) lglGetProcAddress("glVertexAttrib3dvNV");
    glVertexAttrib4svNV = (glVertexAttrib4svNVPROC) lglGetProcAddress("glVertexAttrib4svNV");
    glVertexAttrib4fvNV = (glVertexAttrib4fvNVPROC) lglGetProcAddress("glVertexAttrib4fvNV");
    glVertexAttrib4dvNV = (glVertexAttrib4dvNVPROC) lglGetProcAddress("glVertexAttrib4dvNV");
    glVertexAttrib4ubvNV = (glVertexAttrib4ubvNVPROC) lglGetProcAddress("glVertexAttrib4ubvNV");
    glVertexAttribs1svNV = (glVertexAttribs1svNVPROC) lglGetProcAddress("glVertexAttribs1svNV");
    glVertexAttribs1fvNV = (glVertexAttribs1fvNVPROC) lglGetProcAddress("glVertexAttribs1fvNV");
    glVertexAttribs1dvNV = (glVertexAttribs1dvNVPROC) lglGetProcAddress("glVertexAttribs1dvNV");
    glVertexAttribs2svNV = (glVertexAttribs2svNVPROC) lglGetProcAddress("glVertexAttribs2svNV");
    glVertexAttribs2fvNV = (glVertexAttribs2fvNVPROC) lglGetProcAddress("glVertexAttribs2fvNV");
    glVertexAttribs2dvNV = (glVertexAttribs2dvNVPROC) lglGetProcAddress("glVertexAttribs2dvNV");
    glVertexAttribs3svNV = (glVertexAttribs3svNVPROC) lglGetProcAddress("glVertexAttribs3svNV");
    glVertexAttribs3fvNV = (glVertexAttribs3fvNVPROC) lglGetProcAddress("glVertexAttribs3fvNV");
    glVertexAttribs3dvNV = (glVertexAttribs3dvNVPROC) lglGetProcAddress("glVertexAttribs3dvNV");
    glVertexAttribs4svNV = (glVertexAttribs4svNVPROC) lglGetProcAddress("glVertexAttribs4svNV");
    glVertexAttribs4fvNV = (glVertexAttribs4fvNVPROC) lglGetProcAddress("glVertexAttribs4fvNV");
    glVertexAttribs4dvNV = (glVertexAttribs4dvNVPROC) lglGetProcAddress("glVertexAttribs4dvNV");
    glVertexAttribs4ubvNV = (glVertexAttribs4ubvNVPROC) lglGetProcAddress("glVertexAttribs4ubvNV");
#endif
}

void InitEXTVertexWeighting()
{
#ifdef GL_EXT_vertex_weighting
    if (!extgl_Extensions.EXT_vertex_weighting)
        return;
    glVertexWeightfEXT = (glVertexWeightfEXTPROC) lglGetProcAddress("glVertexWeightfEXT");
    glVertexWeightfvEXT = (glVertexWeightfvEXTPROC) lglGetProcAddress("glVertexWeightfvEXT");
    glVertexWeightPointerEXT = (glVertexWeightPointerEXTPROC) lglGetProcAddress("glVertexWeightPointerEXT");
#endif
}

void InitARBMultisample()
{
#ifdef GL_ARB_multisample
    if (!extgl_Extensions.ARB_multisample)
        return;
    glSampleCoverageARB = (glSampleCoverageARBPROC) lglGetProcAddress("glSampleCoverageARB");
#endif
}

void InitNVRegisterCombiners()
{
#ifdef GL_NV_register_combiners
    if (!extgl_Extensions.NV_register_combiners)
        return;
    glCombinerParameterfvNV = (glCombinerParameterfvNVPROC) lglGetProcAddress("glCombinerParameterfvNV");
    glCombinerParameterfNV = (glCombinerParameterfNVPROC) lglGetProcAddress("glCombinerParameterfNV");
    glCombinerParameterivNV = (glCombinerParameterivNVPROC) lglGetProcAddress("glCombinerParameterivNV");
    glCombinerParameteriNV = (glCombinerParameteriNVPROC) lglGetProcAddress("glCombinerParameteriNV");
    glCombinerInputNV = (glCombinerInputNVPROC) lglGetProcAddress("glCombinerInputNV");
    glCombinerOutputNV = (glCombinerOutputNVPROC) lglGetProcAddress("glCombinerOutputNV");
    glFinalCombinerInputNV = (glFinalCombinerInputNVPROC) lglGetProcAddress("glFinalCombinerInputNV");
    glGetCombinerInputParameterfvNV = (glGetCombinerInputParameterfvNVPROC) lglGetProcAddress("glGetCombinerInputParameterfvNV");
    glGetCombinerInputParameterivNV = (glGetCombinerInputParameterivNVPROC) lglGetProcAddress("glGetCombinerInputParameterivNV");
    glGetCombinerOutputParameterfvNV = (glGetCombinerOutputParameterfvNVPROC) lglGetProcAddress("glGetCombinerOutputParameterfvNV");
    glGetCombinerOutputParameterivNV = (glGetCombinerOutputParameterivNVPROC) lglGetProcAddress("glGetCombinerOutputParameterivNV");
    glGetFinalCombinerInputParameterfvNV = (glGetFinalCombinerInputParameterfvNVPROC) lglGetProcAddress("glGetFinalCombinerInputParameterfvNV");
    glGetFinalCombinerInputParameterivNV = (glGetFinalCombinerInputParameterivNVPROC) lglGetProcAddress("glGetFinalCombinerInputParameterivNV");
#endif
}

void InitEXTPointParameters()
{
#ifdef GL_EXT_point_parameters
    if (!extgl_Extensions.EXT_point_parameters)
        return;
    glPointParameterfEXT = (glPointParameterfEXTPROC) lglGetProcAddress("glPointParameterfEXT");
    glPointParameterfvEXT = (glPointParameterfvEXTPROC) lglGetProcAddress("glPointParameterfvEXT");
#endif
}

void InitNVVertexArrayRange()
{
#ifdef GL_NV_vertex_array_range
    if (!extgl_Extensions.NV_vertex_array_range)
        return;
    glFlushVertexArrayRangeNV = (glFlushVertexArrayRangeNVPROC) lglGetProcAddress("glFlushVertexArrayRangeNV");
    glVertexArrayRangeNV = (glVertexArrayRangeNVPROC) lglGetProcAddress("glVertexArrayRangeNV");
#ifdef _WIN32
    wglAllocateMemoryNV = (wglAllocateMemoryNVPROC) lglGetProcAddress("wglAllocateMemoryNV");
    wglFreeMemoryNV = (wglFreeMemoryNVPROC) lglGetProcAddress("wglFreeMemoryNV");
#endif /* WIN32 */
#endif
}
 
void InitEXTFogCoord()
{
#ifdef GL_EXT_fog_coord
    if (!extgl_Extensions.EXT_fog_coord)
        return;
    glFogCoordfEXT = (glFogCoordfEXTPROC) lglGetProcAddress("glFogCoordfEXT");
    glFogCoordfvEXT = (glFogCoordfvEXTPROC) lglGetProcAddress("glFogCoordfvEXT");
    glFogCoorddEXT = (glFogCoorddEXTPROC) lglGetProcAddress("glFogCoorddEXT");
    glFogCoorddvEXT = (glFogCoorddvEXTPROC) lglGetProcAddress("glFogCoorddvEXT");
    glFogCoordPointerEXT = (glFogCoordPointerEXTPROC) lglGetProcAddress("glFogCoordPointerEXT");
#endif
}

void InitEXTSecondaryColor()
{
#ifdef GL_EXT_secondary_color
    if (!extgl_Extensions.EXT_secondary_color)
        return;
    glSecondaryColor3bEXT = (glSecondaryColor3bEXTPROC) lglGetProcAddress("glSecondaryColor3bEXT");
    glSecondaryColor3bvEXT = (glSecondaryColor3bvEXTPROC) lglGetProcAddress("glSecondaryColor3bvEXT");
    glSecondaryColor3dEXT = (glSecondaryColor3dEXTPROC) lglGetProcAddress("glSecondaryColor3dEXT");
    glSecondaryColor3dvEXT = (glSecondaryColor3dvEXTPROC) lglGetProcAddress("glSecondaryColor3dvEXT");
    glSecondaryColor3fEXT = (glSecondaryColor3fEXTPROC) lglGetProcAddress("glSecondaryColor3fEXT");
    glSecondaryColor3fvEXT = (glSecondaryColor3fvEXTPROC) lglGetProcAddress("glSecondaryColor3fvEXT");
    glSecondaryColor3iEXT = (glSecondaryColor3iEXTPROC) lglGetProcAddress("glSecondaryColor3iEXT");
    glSecondaryColor3ivEXT = (glSecondaryColor3ivEXTPROC) lglGetProcAddress("glSecondaryColor3ivEXT");
    glSecondaryColor3sEXT = (glSecondaryColor3sEXTPROC) lglGetProcAddress("glSecondaryColor3sEXT");
    glSecondaryColor3svEXT = (glSecondaryColor3svEXTPROC) lglGetProcAddress("glSecondaryColor3svEXT");
    glSecondaryColor3ubEXT = (glSecondaryColor3ubEXTPROC) lglGetProcAddress("glSecondaryColor3ubEXT");
    glSecondaryColor3ubvEXT = (glSecondaryColor3ubvEXTPROC) lglGetProcAddress("glSecondaryColor3ubvEXT");
    glSecondaryColor3uiEXT = (glSecondaryColor3uiEXTPROC) lglGetProcAddress("glSecondaryColor3uiEXT");
    glSecondaryColor3uivEXT = (glSecondaryColor3uivEXTPROC) lglGetProcAddress("glSecondaryColor3uivEXT");
    glSecondaryColor3usEXT = (glSecondaryColor3usEXTPROC) lglGetProcAddress("glSecondaryColor3usEXT");
    glSecondaryColor3usvEXT = (glSecondaryColor3usvEXTPROC) lglGetProcAddress("glSecondaryColor3usvEXT");
    glSecondaryColorPointerEXT = (glSecondaryColorPointerEXTPROC) lglGetProcAddress("glSecondaryColorPointerEXT");
#endif
}

void InitEXTCompiledVertexArray()
{
#ifdef GL_EXT_compiled_vertex_array
    if (!extgl_Extensions.EXT_compiled_vertex_array)
        return;
    glLockArraysEXT = (glLockArraysEXTPROC) lglGetProcAddress("glLockArraysEXT");
    glUnlockArraysEXT = (glUnlockArraysEXTPROC) lglGetProcAddress("glUnlockArraysEXT");
#endif
}

void InitARBTransposeMatrix()
{
#ifdef GL_ARB_transpose_matrix
    if (!extgl_Extensions.ARB_transpose_matrix)
        return;
    glLoadTransposeMatrixfARB = (glLoadTransposeMatrixfARBPROC) lglGetProcAddress("glLoadTransposeMatrixfARB");
    glLoadTransposeMatrixdARB = (glLoadTransposeMatrixdARBPROC) lglGetProcAddress("glLoadTransposeMatrixdARB");
    glMultTransposeMatrixfARB = (glMultTransposeMatrixfARBPROC) lglGetProcAddress("glMultTransposeMatrixfARB");
    glMultTransposeMatrixdARB = (glMultTransposeMatrixdARBPROC) lglGetProcAddress("glMultTransposeMatrixdARB");
#endif
}

void InitEXTDrawRangeElements()
{
#ifdef GL_EXT_draw_range_elements
    if (!extgl_Extensions.EXT_draw_range_elements)
        return;
    glDrawRangeElementsEXT = (glDrawRangeElementsEXTPROC) lglGetProcAddress("glDrawRangeElementsEXT");
#endif
}

void InitARBMultitexture()
{
#ifdef GL_ARB_multitexture
    if (!extgl_Extensions.ARB_multitexture)
        return;
#ifdef _WIN32
    glActiveTextureARB = (glActiveTextureARBPROC) lglGetProcAddress("glActiveTextureARB");
    glClientActiveTextureARB = (glClientActiveTextureARBPROC) lglGetProcAddress("glClientActiveTextureARB");

    glMultiTexCoord1dARB = (glMultiTexCoord1dARBPROC) lglGetProcAddress("glMultiTexCoord1dARB");
    glMultiTexCoord1dvARB = (glMultiTexCoord1dvARBPROC) lglGetProcAddress("glMultiTexCoord1dvARB");
    glMultiTexCoord1fARB = (glMultiTexCoord1fARBPROC) lglGetProcAddress("glMultiTexCoord1fARB");
    glMultiTexCoord1fvARB = (glMultiTexCoord1fvARBPROC) lglGetProcAddress("glMultiTexCoord1fvARB");
    glMultiTexCoord1iARB = (glMultiTexCoord1iARBPROC) lglGetProcAddress("glMultiTexCoord1iARB");
    glMultiTexCoord1ivARB = (glMultiTexCoord1ivARBPROC) lglGetProcAddress("glMultiTexCoord1ivARB");
    glMultiTexCoord1sARB = (glMultiTexCoord1sARBPROC) lglGetProcAddress("glMultiTexCoord1sARB");
    glMultiTexCoord1svARB = (glMultiTexCoord1svARBPROC) lglGetProcAddress("glMultiTexCoord1svARB");

    glMultiTexCoord2dARB = (glMultiTexCoord2dARBPROC) lglGetProcAddress("glMultiTexCoord2dARB");
    glMultiTexCoord2dvARB = (glMultiTexCoord2dvARBPROC) lglGetProcAddress("glMultiTexCoord2dvARB");
    glMultiTexCoord2fARB = (glMultiTexCoord2fARBPROC) lglGetProcAddress("glMultiTexCoord2fARB");
    glMultiTexCoord2fvARB = (glMultiTexCoord2fvARBPROC) lglGetProcAddress("glMultiTexCoord2fvARB");
    glMultiTexCoord2iARB = (glMultiTexCoord2iARBPROC) lglGetProcAddress("glMultiTexCoord2iARB");
    glMultiTexCoord2ivARB = (glMultiTexCoord2ivARBPROC) lglGetProcAddress("glMultiTexCoord2ivARB");
    glMultiTexCoord2sARB = (glMultiTexCoord2sARBPROC) lglGetProcAddress("glMultiTexCoord2sARB");
    glMultiTexCoord2svARB = (glMultiTexCoord2svARBPROC) lglGetProcAddress("glMultiTexCoord2svARB");

    glMultiTexCoord3dARB = (glMultiTexCoord3dARBPROC) lglGetProcAddress("glMultiTexCoord3dARB");
    glMultiTexCoord3dvARB = (glMultiTexCoord3dvARBPROC) lglGetProcAddress("glMultiTexCoord3dvARB");
    glMultiTexCoord3fARB = (glMultiTexCoord3fARBPROC) lglGetProcAddress("glMultiTexCoord3fARB");
    glMultiTexCoord3fvARB = (glMultiTexCoord3fvARBPROC) lglGetProcAddress("glMultiTexCoord3fvARB");
    glMultiTexCoord3iARB = (glMultiTexCoord3iARBPROC) lglGetProcAddress("glMultiTexCoord3iARB");
    glMultiTexCoord3ivARB = (glMultiTexCoord3ivARBPROC) lglGetProcAddress("glMultiTexCoord3ivARB");
    glMultiTexCoord3sARB = (glMultiTexCoord3sARBPROC) lglGetProcAddress("glMultiTexCoord3sARB");
    glMultiTexCoord3svARB = (glMultiTexCoord3svARBPROC) lglGetProcAddress("glMultiTexCoord3svARB");

    glMultiTexCoord4dARB = (glMultiTexCoord4dARBPROC) lglGetProcAddress("glMultiTexCoord4dARB");
    glMultiTexCoord4dvARB = (glMultiTexCoord4dvARBPROC) lglGetProcAddress("glMultiTexCoord4dvARB");
    glMultiTexCoord4fARB = (glMultiTexCoord4fARBPROC) lglGetProcAddress("glMultiTexCoord4fARB");
    glMultiTexCoord4fvARB = (glMultiTexCoord4fvARBPROC) lglGetProcAddress("glMultiTexCoord4fvARB");
    glMultiTexCoord4iARB = (glMultiTexCoord4iARBPROC) lglGetProcAddress("glMultiTexCoord4iARB");
    glMultiTexCoord4ivARB = (glMultiTexCoord4ivARBPROC) lglGetProcAddress("glMultiTexCoord4ivARB");
    glMultiTexCoord4sARB = (glMultiTexCoord4sARBPROC) lglGetProcAddress("glMultiTexCoord4sARB");
    glMultiTexCoord4svARB = (glMultiTexCoord4svARBPROC) lglGetProcAddress("glMultiTexCoord4svARB");
#endif /* _WIN32 */
#endif /* GL_ARB_multitexture */
}

void InitOpenGL1_2()
{
#ifdef GL_VERSION_1_2
#ifdef _WIN32
    if (!extgl_Extensions.OpenGL12)
        return;
    glTexImage3D = (glTexImage3DPROC) lglGetProcAddress("glTexImage3D");
    glTexSubImage3D = (glTexSubImage3DPROC) lglGetProcAddress("glTexSubImage3D");
    glCopyTexSubImage3D = (glCopyTexSubImage3DPROC) lglGetProcAddress("glCopyTexSubImage3D");
    glDrawRangeElements = (glDrawRangeElementsPROC) lglGetProcAddress("glDrawRangeElements");
#endif /* _WIN32 */
#endif /* GL_VERSION_1_2 */
}

void InitARBImaging()
{
#ifdef GL_ARB_imaging
    if (!extgl_Extensions.ARB_imaging)
        return;
    glBlendColor = (glBlendColorPROC) lglGetProcAddress("glBlendColor");
    glBlendEquation = (glBlendEquationPROC) lglGetProcAddress("glBlendEquation");
    glColorTable = (glColorTablePROC) lglGetProcAddress("glColorTable");
    glColorTableParameterfv = (glColorTableParameterfvPROC) lglGetProcAddress("glColorTableParameterfv");
    glColorTableParameteriv = (glColorTableParameterivPROC) lglGetProcAddress("glColorTableParameteriv");
    glCopyColorTable = (glCopyColorTablePROC) lglGetProcAddress("glCopyColorTable");
    glGetColorTable = (glGetColorTablePROC) lglGetProcAddress("glGetColorTable");
    glGetColorTableParameterfv = (glGetColorTableParameterfvPROC) lglGetProcAddress("glGetColorTableParameterfv");
    glGetColorTableParameteriv = (glGetColorTableParameterivPROC) lglGetProcAddress("glGetColorTableParameteriv");
    glColorSubTable = (glColorSubTablePROC) lglGetProcAddress("glColorSubTable");
    glCopyColorSubTable = (glCopyColorSubTablePROC) lglGetProcAddress("glCopyColorSubTable");
    glConvolutionFilter1D = (glConvolutionFilter1DPROC) lglGetProcAddress("glConvolutionFilter1D");
    glConvolutionFilter2D = (glConvolutionFilter2DPROC) lglGetProcAddress("glConvolutionFilter2D");
    glConvolutionParameterf = (glConvolutionParameterfPROC) lglGetProcAddress("glConvolutionParameterf");
    glConvolutionParameterfv = (glConvolutionParameterfvPROC) lglGetProcAddress("glConvolutionParameterfv");
    glConvolutionParameteri = (glConvolutionParameteriPROC) lglGetProcAddress("glConvolutionParameteri");
    glConvolutionParameteriv = (glConvolutionParameterivPROC) lglGetProcAddress("glConvolutionParameteriv");
    glCopyConvolutionFilter1D = (glCopyConvolutionFilter1DPROC) lglGetProcAddress("glCopyConvolutionFilter1D");
    glCopyConvolutionFilter2D = (glCopyConvolutionFilter2DPROC) lglGetProcAddress("glCopyConvolutionFilter2D");
    glGetConvolutionFilter = (glGetConvolutionFilterPROC) lglGetProcAddress("glGetConvolutionFilter");
    glGetConvolutionParameterfv = (glGetConvolutionParameterfvPROC) lglGetProcAddress("glGetConvolutionParameterfv");
    glGetConvolutionParameteriv = (glGetConvolutionParameterivPROC) lglGetProcAddress("glGetConvolutionParameteriv");
    glGetSeparableFilter = (glGetSeparableFilterPROC) lglGetProcAddress("glGetSeparableFilter");
    glSeparableFilter2D = (glSeparableFilter2DPROC) lglGetProcAddress("glSeparableFilter2D");
    glGetHistogram = (glGetHistogramPROC) lglGetProcAddress("glGetHistogram");
    glGetHistogramParameterfv = (glGetHistogramParameterfvPROC) lglGetProcAddress("glGetHistogramParameterfv");
    glGetHistogramParameteriv = (glGetHistogramParameterivPROC) lglGetProcAddress("glGetHistogramParameteriv");
    glGetMinmax = (glGetMinmaxPROC) lglGetProcAddress("glGetMinmax");
    glGetMinmaxParameterfv = (glGetMinmaxParameterfvPROC) lglGetProcAddress("glGetMinmaxParameterfv");
    glGetMinmaxParameteriv = (glGetMinmaxParameterivPROC) lglGetProcAddress("glGetMinmaxParameteriv");
    glHistogram = (glHistogramPROC) lglGetProcAddress("glHistogram");
    glMinmax = (glMinmaxPROC) lglGetProcAddress("glMinmax");
    glResetHistogram = (glResetHistogramPROC) lglGetProcAddress("glResetHistogram");
    glResetMinmax = (glResetMinmaxPROC) lglGetProcAddress("glResetMinmax");
#endif
}

void InitOpenGL1_3()
{
#ifdef GL_VERSION_1_3
#ifdef _WIN32    
    if (!extgl_Extensions.OpenGL13)
        return;
    glActiveTexture = (glActiveTexturePROC) lglGetProcAddress("glActiveTexture");
    glClientActiveTexture = (glClientActiveTexturePROC) lglGetProcAddress("glClientActiveTexture");

    glMultiTexCoord1d = (glMultiTexCoord1dPROC) lglGetProcAddress("glMultiTexCoord1d");
    glMultiTexCoord1dv = (glMultiTexCoord1dvPROC) lglGetProcAddress("glMultiTexCoord1dv");
    glMultiTexCoord1f = (glMultiTexCoord1fPROC) lglGetProcAddress("glMultiTexCoord1f");
    glMultiTexCoord1fv = (glMultiTexCoord1fvPROC) lglGetProcAddress("glMultiTexCoord1fv");
    glMultiTexCoord1i = (glMultiTexCoord1iPROC) lglGetProcAddress("glMultiTexCoord1i");
    glMultiTexCoord1iv = (glMultiTexCoord1ivPROC) lglGetProcAddress("glMultiTexCoord1iv");
    glMultiTexCoord1s = (glMultiTexCoord1sPROC) lglGetProcAddress("glMultiTexCoord1s");
    glMultiTexCoord1sv = (glMultiTexCoord1svPROC) lglGetProcAddress("glMultiTexCoord1sv");

    glMultiTexCoord2d = (glMultiTexCoord2dPROC) lglGetProcAddress("glMultiTexCoord2d");
    glMultiTexCoord2dv = (glMultiTexCoord2dvPROC) lglGetProcAddress("glMultiTexCoord2dv");
    glMultiTexCoord2f = (glMultiTexCoord2fPROC) lglGetProcAddress("glMultiTexCoord2f");
    glMultiTexCoord2fv = (glMultiTexCoord2fvPROC) lglGetProcAddress("glMultiTexCoord2fv");
    glMultiTexCoord2i = (glMultiTexCoord2iPROC) lglGetProcAddress("glMultiTexCoord2i");
    glMultiTexCoord2iv = (glMultiTexCoord2ivPROC) lglGetProcAddress("glMultiTexCoord2iv");
    glMultiTexCoord2s = (glMultiTexCoord2sPROC) lglGetProcAddress("glMultiTexCoord2s");
    glMultiTexCoord2sv = (glMultiTexCoord2svPROC) lglGetProcAddress("glMultiTexCoord2sv");

    glMultiTexCoord3d = (glMultiTexCoord3dPROC) lglGetProcAddress("glMultiTexCoord3d");
    glMultiTexCoord3dv = (glMultiTexCoord3dvPROC) lglGetProcAddress("glMultiTexCoord3dv");
    glMultiTexCoord3f = (glMultiTexCoord3fPROC) lglGetProcAddress("glMultiTexCoord3f");
    glMultiTexCoord3fv = (glMultiTexCoord3fvPROC) lglGetProcAddress("glMultiTexCoord3fv");
    glMultiTexCoord3i = (glMultiTexCoord3iPROC) lglGetProcAddress("glMultiTexCoord3i");
    glMultiTexCoord3iv = (glMultiTexCoord3ivPROC) lglGetProcAddress("glMultiTexCoord3iv");
    glMultiTexCoord3s = (glMultiTexCoord3sPROC) lglGetProcAddress("glMultiTexCoord3s");
    glMultiTexCoord3sv = (glMultiTexCoord3svPROC) lglGetProcAddress("glMultiTexCoord3sv");

    glMultiTexCoord4d = (glMultiTexCoord4dPROC) lglGetProcAddress("glMultiTexCoord4d");
    glMultiTexCoord4dv = (glMultiTexCoord4dvPROC) lglGetProcAddress("glMultiTexCoord4dv");
    glMultiTexCoord4f = (glMultiTexCoord4fPROC) lglGetProcAddress("glMultiTexCoord4f");
    glMultiTexCoord4fv = (glMultiTexCoord4fvPROC) lglGetProcAddress("glMultiTexCoord4fv");
    glMultiTexCoord4i = (glMultiTexCoord4iPROC) lglGetProcAddress("glMultiTexCoord4i");
    glMultiTexCoord4iv = (glMultiTexCoord4ivPROC) lglGetProcAddress("glMultiTexCoord4iv");
    glMultiTexCoord4s = (glMultiTexCoord4sPROC) lglGetProcAddress("glMultiTexCoord4s");
    glMultiTexCoord4sv = (glMultiTexCoord4svPROC) lglGetProcAddress("glMultiTexCoord4sv");

    glLoadTransposeMatrixf = (glLoadTransposeMatrixfPROC) lglGetProcAddress("glLoadTransposeMatrixf");
    glLoadTransposeMatrixd = (glLoadTransposeMatrixdPROC) lglGetProcAddress("glLoadTransposeMatrixd");
    glMultTransposeMatrixf = (glMultTransposeMatrixfPROC) lglGetProcAddress("glMultTransposeMatrixf");
    glMultTransposeMatrixd = (glMultTransposeMatrixdPROC) lglGetProcAddress("glMultTransposeMatrixd");
    glCompressedTexImage3D = (glCompressedTexImage3DPROC) lglGetProcAddress("glCompressedTexImage3D");
    glCompressedTexImage2D = (glCompressedTexImage2DPROC) lglGetProcAddress("glCompressedTexImage2D");
    glCompressedTexImage1D = (glCompressedTexImage1DPROC) lglGetProcAddress("glCompressedTexImage1D");
    glCompressedTexSubImage3D = (glCompressedTexSubImage3DPROC) lglGetProcAddress("glCompressedTexSubImage3D");
    glCompressedTexSubImage2D = (glCompressedTexSubImage2DPROC) lglGetProcAddress("glCompressedTexSubImage2D");
    glCompressedTexSubImage1D = (glCompressedTexSubImage1DPROC) lglGetProcAddress("glCompressedTexSubImage1D");
    glGetCompressedTexImage = (glGetCompressedTexImagePROC) lglGetProcAddress("glGetCompressedTexImage");

    glSampleCoverage = (glSampleCoveragePROC) lglGetProcAddress("glSampleCoverage");
#endif /* _WIN32 */
#endif /* GL_VERSION_1_3 */
}

void InitOpenGL1_4()
{
#ifdef GL_VERSION_1_4
#ifdef _WIN32    
    if (!extgl_Extensions.OpenGL14)
        return;


#endif /* _WIN32 */
#endif /* GL_VERSION_1_4 */
}

void InitSupportedExtensions()
{
    char *s = (char*) glGetString(GL_VERSION);
    if (!s)
        return;
    s = strstr(s, "1.");
    if (s == NULL)
    {
        extgl_Extensions.OpenGL12 = 0;    
        extgl_Extensions.OpenGL13 = 0;    
        extgl_Extensions.OpenGL14 = 0;
    }
    else
    {
        if (s[2] <= '4')
        {
            extgl_Extensions.OpenGL12 = 1;    
            extgl_Extensions.OpenGL13 = 1;    
            extgl_Extensions.OpenGL14 = 1;    
        }
        if (s[2] <= '3')
        {
            extgl_Extensions.OpenGL12 = 1;    
            extgl_Extensions.OpenGL13 = 1;    
            extgl_Extensions.OpenGL14 = 0;    
        }
        if (s[2] <= '2')
        {
            extgl_Extensions.OpenGL12 = 1;    
            extgl_Extensions.OpenGL13 = 0;    
            extgl_Extensions.OpenGL14 = 0;    
        }
        if (s[2] < '2')
        {
            extgl_Extensions.OpenGL12 = 0;    
            extgl_Extensions.OpenGL13 = 0;    
            extgl_Extensions.OpenGL14 = 0;    
        }
    }
    extgl_Extensions.ARB_depth_texture = QueryExtension("GL_ARB_depth_texture");
    extgl_Extensions.ARB_imaging = QueryExtension("GL_ARB_imaging");
    extgl_Extensions.ARB_matrix_palette = QueryExtension("GL_ARB_matrix_palette");
    extgl_Extensions.ARB_multisample = QueryExtension("GL_ARB_multisample");
    extgl_Extensions.ARB_multitexture = QueryExtension("GL_ARB_multitexture");
    extgl_Extensions.ARB_point_parameters = QueryExtension("GL_ARB_point_parameters");
    extgl_Extensions.ARB_shadow = QueryExtension("GL_ARB_shadow");
    extgl_Extensions.ARB_shadow_ambient = QueryExtension("GL_ARB_shadow_ambient");
    extgl_Extensions.ARB_texture_border_clamp = QueryExtension("GL_ARB_texture_border_clamp");
    extgl_Extensions.ARB_texture_compression = QueryExtension("GL_ARB_texture_compression");
    extgl_Extensions.ARB_texture_cube_map = QueryExtension("GL_ARB_texture_cube_map");
    extgl_Extensions.ARB_texture_env_add = QueryExtension("GL_ARB_texture_env_add");
    extgl_Extensions.ARB_texture_env_combine = QueryExtension("GL_ARB_texture_env_combine");
    extgl_Extensions.ARB_texture_env_crossbar = QueryExtension("GL_ARB_texture_env_crossbar");
    extgl_Extensions.ARB_texture_env_dot3 = QueryExtension("GL_ARB_texture_env_dot3");
    extgl_Extensions.ARB_texture_mirrored_repeat = QueryExtension("GL_ARB_texture_mirrored_repeat");
    extgl_Extensions.ARB_transpose_matrix = QueryExtension("GL_ARB_transpose_matrix");
    extgl_Extensions.ARB_vertex_blend = QueryExtension("GL_ARB_vertex_blend");
    extgl_Extensions.ARB_vertex_program = QueryExtension("GL_ARB_vertex_program");
    extgl_Extensions.ARB_window_pos = QueryExtension("GL_ARB_window_pos");
    extgl_Extensions.EXT_abgr = QueryExtension("GL_EXT_abgr");
    extgl_Extensions.EXT_bgra = QueryExtension("GL_EXT_bgra");
    extgl_Extensions.EXT_blend_func_separate = QueryExtension("GL_EXT_blend_function_separate");
    extgl_Extensions.EXT_compiled_vertex_array = QueryExtension("GL_EXT_compiled_vertex_array");
    extgl_Extensions.EXT_cull_vertex = QueryExtension("GL_EXT_cull_vertex");
    extgl_Extensions.EXT_draw_range_elements = QueryExtension("GL_EXT_draw_range_elements");
    extgl_Extensions.EXT_fog_coord = QueryExtension("GL_EXT_fog_coord");
    extgl_Extensions.EXT_multi_draw_arrays = QueryExtension("GL_EXT_multi_draw_arrays");
    extgl_Extensions.EXT_point_parameters = QueryExtension("GL_EXT_point_parameters");
    extgl_Extensions.EXT_secondary_color = QueryExtension("GL_EXT_secondary_color");
    extgl_Extensions.EXT_separate_specular_color = QueryExtension("GL_EXT_separate_specular_color");
    extgl_Extensions.EXT_shadow_funcs = QueryExtension("GL_EXT_shadow_funcs");
    extgl_Extensions.EXT_stencil_two_side = QueryExtension("GL_EXT_stencil_two_side");
    extgl_Extensions.EXT_stencil_wrap = QueryExtension("GL_EXT_stencil_wrap");
    extgl_Extensions.EXT_texture_compression_s3tc = QueryExtension("GL_EXT_texture_compression_s3tc");
    extgl_Extensions.EXT_texture_filter_anisotropic = QueryExtension("GL_EXT_texture_filter_anisotropic");
    extgl_Extensions.EXT_texture_lod_bias = QueryExtension("GL_EXT_texture_lod_bias");
    extgl_Extensions.EXT_vertex_shader = QueryExtension("GL_EXT_vertex_shader");
    extgl_Extensions.EXT_vertex_weighting = QueryExtension("GL_EXT_vertex_weighting");
    extgl_Extensions.ATI_element_array = QueryExtension("GL_ATI_element_array");
    extgl_Extensions.ATI_envmap_bumpmap = QueryExtension("GL_ATI_envmap_bumpmap");
    extgl_Extensions.ATI_fragment_shader = QueryExtension("GL_ATI_fragment_shader");
    extgl_Extensions.ATI_pn_triangles = QueryExtension("GL_ATI_pn_triangles");
    extgl_Extensions.ATI_point_cull_mode = QueryExtension("GL_ATI_point_cull_mode");
    extgl_Extensions.ATI_texture_mirror_once = QueryExtension("GL_ATI_texture_mirror_once");
    extgl_Extensions.ATI_vertex_array_object = QueryExtension("GL_ATI_vertex_array_object");
    extgl_Extensions.ATI_vertex_streams = QueryExtension("GL_ATI_vertex_streams");
    extgl_Extensions.ATIX_point_sprites = QueryExtension("GL_ATIX_point_sprites");
    extgl_Extensions.ATIX_texture_env_route = QueryExtension("GL_ATIX_texture_env_route");
    extgl_Extensions.HP_occlusion_test = QueryExtension("GL_HP_occlusion_test");
    extgl_Extensions.NV_blend_square = QueryExtension("GL_NV_blend_square");
    extgl_Extensions.NV_copy_depth_to_color = QueryExtension("GL_NV_copy_depth_to_color");
    extgl_Extensions.NV_depth_clamp = QueryExtension("GL_NV_depth_clamp");
    extgl_Extensions.NV_evaluators = QueryExtension("GL_NV_evaluators");
    extgl_Extensions.NV_fence = QueryExtension("GL_NV_fence");
    extgl_Extensions.NV_fog_distance = QueryExtension("GL_NV_fog_distance");
    extgl_Extensions.NV_light_max_exponent = QueryExtension("GL_NV_light_max_exponent");
    extgl_Extensions.NV_occlusion_query = QueryExtension("GL_NV_occlusion_query");
    extgl_Extensions.NV_packed_depth_stencil = QueryExtension("GL_NV_packed_depth_stencil");
    extgl_Extensions.NV_point_sprite = QueryExtension("GL_NV_point_sprite");
    extgl_Extensions.NV_register_combiners = QueryExtension("GL_NV_register_combiners");
    extgl_Extensions.NV_register_combiners2 = QueryExtension("GL_NV_register_combiners2");
    extgl_Extensions.NV_texgen_reflection = QueryExtension("GL_NV_texgen_reflection");
    extgl_Extensions.NV_texture_env_combine4 = QueryExtension("GL_NV_texture_env_combine4");
    extgl_Extensions.NV_texture_rectangle = QueryExtension("GL_NV_texture_rectangle");
    extgl_Extensions.NV_texture_shader = QueryExtension("GL_NV_texture_shader");
    extgl_Extensions.NV_texture_shader2 = QueryExtension("GL_NV_texture_shader2");
    extgl_Extensions.NV_texture_shader3 = QueryExtension("GL_NV_texture_shader3");
    extgl_Extensions.NV_vertex_array_range = QueryExtension("GL_NV_vertex_array_range");
    extgl_Extensions.NV_vertex_array_range2 = QueryExtension("GL_NV_vertex_array_range2");
    extgl_Extensions.NV_vertex_program = QueryExtension("GL_NV_vertex_program");
    extgl_Extensions.NV_vertex_program1_1 = QueryExtension("GL_NV_vertex_program1_1");
    extgl_Extensions.SGIS_generate_mipmap = QueryExtension("GL_SGIS_generate_mipmap");
    extgl_Extensions.SGIX_depth_texture = QueryExtension("GL_SGIX_depth_texture");
    extgl_Extensions.SGIX_shadow = QueryExtension("GL_SGIX_shadow");
}


int glInitialize()
{
    fprintf(stderr, "glInitialize() is deprecated, please use extgl_Initialize() instead\n");
    return extgl_Initialize();
}


/* init the extensions and load all the functions */
int extgl_Initialize()
{
    error = 0;
    InitSupportedExtensions();
    
    /* first load the etensions */
    InitARBTransposeMatrix();
    InitARBMultisample();
    InitEXTCompiledVertexArray();
    InitEXTSecondaryColor();
    InitEXTFogCoord();
    InitNVVertexArrayRange();
    InitEXTPointParameters();
    InitNVRegisterCombiners();
    InitEXTVertexWeighting();
    InitNVVertexProgram();
    InitNVFence();
    InitNVRegisterCombiners2();
    InitATIPNTriangles();
    InitARBPointParameters();
    InitARBVertexBlend();
    InitEXTMultiDrawArrays();
    InitARBMatrixPalette();
    InitEXTVertexShader();
    InitATIEnvmapBumpmap();
    InitATIFragmentShader();
    InitATIElementArray();
    InitATIVertexStreams();
    InitATIVertexArrayObject();
    InitNVOcclusionQuery();
    InitNVPointSprite();
    InitARBWindowPos();
    InitARBTextureCompression();
    InitEXTDrawRangeElements();
    InitEXTStencilTwoSide();
    InitARBVertexProgram();
    InitEXTCullVertex();
    InitEXTBlendFunctionSeparate();

#ifdef _WIN32
    InitARBImaging();
    InitARBMultitexture();
    /* now load core opengl */
    InitOpenGL1_2();
    InitOpenGL1_3();
    InitOpenGL1_4();
    wglInitialize(_dc);
#endif
    SupportedExtensions = extgl_Extensions;
    return error;
}

