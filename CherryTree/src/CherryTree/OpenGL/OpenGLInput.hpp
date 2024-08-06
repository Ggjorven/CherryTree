#pragma once

#include "CherryTree/Core/Memory.hpp"
#include "CherryTree/Core/Input/KeyCodes.hpp"
#include "CherryTree/Core/Input/MouseCodes.hpp"

#include "CherryTree/Renderer/RendererSpecification.hpp"

#include <glm/glm.hpp>

namespace Ct
{

	template<RenderingAPI API>
	class Input;

	template<>
	class Input<RenderingAPI::OpenGL> : public RefCounted
	{
	public:
		Input(void* window);
		~Input() = default;

		bool IsKeyPressed(Key keycode);
		bool IsMousePressed(MouseButton button);

		glm::vec2 GetCursorPosition();
		void SetCursorPosition(glm::vec2 position);

		void SetCursorMode(CursorMode mode);

	private:
		void* m_Window;
	};

}
