#pragma once

#include "CherryTree/Core/Memory.hpp"

#include <Pulse/Enum/Enum.hpp>

#include "CherryTree/Core/Logging.hpp"

#include <vulkan/vulkan.h>

#define VK_CHECK_RESULT_HELPER_2(expr, exprStr, randomizedNr) \
VkResult result##randomizedNr = expr; \
if (result##randomizedNr != VK_SUCCESS) \
	CT_LOG_ERROR("Expression {0} failed with error code: {1}", exprStr, Pulse::Enum::Name(result##randomizedNr))

#define VK_CHECK_RESULT_HELPER(expr, exprStr, randomizedNr) VK_CHECK_RESULT_HELPER_2(expr, exprStr, randomizedNr)
#define VK_CHECK_RESULT(expr) VK_CHECK_RESULT_HELPER((expr), #expr, __COUNTER__)

namespace Ct
{



}