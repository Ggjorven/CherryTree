#pragma once

#include "CherryTree/Core/Memory.hpp"

#include "CherryTree/Renderer/RendererSpecification.hpp"

#include <Pulse/Types/Concepts.hpp>

namespace Ct
{

    ////////////////////////////////////////////////////////////
    // Template specialization for API selection
    ////////////////////////////////////////////////////////////
    template<typename Context>
    class RenderingContext;

    class OpenGLRenderingContext;
    class VulkanRenderingContext;


    template<RenderingAPI API>
    struct RenderingContextSelector;

    template<>
    struct RenderingContextSelector<RenderingAPI::OpenGL> { using Type = RenderingContext<OpenGLRenderingContext>; };
    template<>
    struct RenderingContextSelector<RenderingAPI::Vulkan> { using Type = RenderingContext<VulkanRenderingContext>; };

    template<RenderingAPI API>
    using RenderingContextType = typename RenderingContextSelector<API>::Type;

    ////////////////////////////////////////////////////////////
    // Base class template using CRTP
    ////////////////////////////////////////////////////////////
    template<typename Context>
    class RenderingContext : public RefCounted
    {
    public:
        RenderingContext() = default;
        virtual ~RenderingContext() = default;

        void Init();
        void Destroy();
    };

    template<RenderingAPI API>
    Ref<RenderingContextType<API>> Create() { return nullptr; }

    // Specialization for Create
    template<>
    Ref<RenderingContextType<RenderingAPI::OpenGL>> Create<RenderingAPI::OpenGL>();

    ////////////////////////////////////////////////////////////
    // Method definitions using CRTP
    ////////////////////////////////////////////////////////////
    template<typename Context>
    inline void RenderingContext<Context>::Init()
    {
        static_cast<Context*>(this)->InitImpl();
    }

    template<typename Context>
    inline void RenderingContext<Context>::Destroy()
    {
        static_cast<Context*>(this)->DestroyImpl();
    }

}
