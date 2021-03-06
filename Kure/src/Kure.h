#pragma once

//for use by Kure applications
#include "krpch.h" //did he add this line in his code???

#include "Kure/Core/Application.h"
#include "Kure/Core/Layer.h" //already included by Application.h, but here for clarity
#include "Kure/Core/Log.h"

#include "Kure/Core/TimeStep.h"
#include "Kure/Renderer/OrthographicCameraController.h"

#include "Kure/Core/Input.h"
#include "Kure/Core/KeyCodes.h"
#include "Kure/Core/MouseButtonCodes.h"

//editor and scene
#include "Kure/Scene/Scene.h"
#include "Kure/Scene/Components.h"
#include "Kure/Scene/Entity.h"

//rendering
#include "Kure/Renderer/Buffer.h"
#include "Kure/Renderer/VertexArray.h"
#include "Kure/Renderer/Shader.h"
#include "Kure/Renderer/RenderCommand.h"
#include "Kure/Renderer/Renderer.h"
#include "Kure/Renderer/Renderer2D.h"
#include "Kure/Renderer/Camera.h"
#include "Kure/Renderer/Texture.h"
#include "Kure/Renderer/SubTexture2D.h"
#include "Kure/Renderer/FrameBuffer.h"

//ImGui
#include "Kure/ImGui/ImGuiLayer.h"

//platform specific
#include "Platform/OpenGL/OpenGLShader.h"

//Debug
#include "Kure/Debug/Instrumentor.h"


//-------entry point-------------
//currently in SandboxApp.cpp
//-------------------------------
