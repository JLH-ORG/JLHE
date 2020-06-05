#include "jlhepch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace JLHE {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}