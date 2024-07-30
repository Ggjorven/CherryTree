#pragma once

#include <string>
#include <string_view>
#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <Pulse/Core/Core.hpp>
#include <Pulse/Text/Format.hpp>

namespace Ct
{

	class Log
	{
	public:
		enum class Level : uint8_t
		{
			Trace = 0, Info, Warn, Error, Fatal, None = 255
		};

		static void Init();

		template<typename ... Args>
		static void LogMessage(Log::Level level, std::string_view fmt, const Args&... args);

		#ifndef CT_CONFIG_DIST
			#define CT_LOG_TRACE(...)	Ct::Log::LogMessage(Ct::Log::Level::Trace, __VA_ARGS__);
			#define CT_LOG_INFO(...)	Ct::Log::LogMessage(Ct::Log::Level::Info, __VA_ARGS__);
			#define CT_LOG_WARN(...)	Ct::Log::LogMessage(Ct::Log::Level::Warn, __VA_ARGS__);
			#define CT_LOG_ERROR(...)	Ct::Log::LogMessage(Ct::Log::Level::Error, __VA_ARGS__);
			#define CT_LOG_FATAL(...)	Ct::Log::LogMessage(Ct::Log::Level::Fatal, __VA_ARGS__);
		#else
			#define CT_LOG_TRACE(...)
			#define CT_LOG_INFO(...)
			#define CT_LOG_WARN(...)
			#define CT_LOG_ERROR(...)
			#define CT_LOG_FATAL(...)
		#endif

		static std::shared_ptr<spdlog::logger>& GetLogger();

	private:
		static std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> s_Sink;
		static std::shared_ptr<spdlog::logger> s_Logger;
	};

	template<typename ... Args>
	void Log::LogMessage(Log::Level level, std::string_view fmt, const Args&... args)
	{
		switch (level)
		{
		case Level::Trace:
			spdlog::trace(Pulse::Text::Format(fmt, args...));
			break;
		case Level::Info:
			spdlog::info(Pulse::Text::Format(fmt, args...));
			break;
		case Level::Warn:
			spdlog::warn(Pulse::Text::Format(fmt, args...));
			break;
		case Level::Error:
			spdlog::error(Pulse::Text::Format(fmt, args...));
			break;
		case Level::Fatal:
			spdlog::critical(Pulse::Text::Format(fmt, args...));
			break;
		}
	}

	#ifndef CT_CONFIG_DIST
		#define CT_VERIFY(value, ...) if (!value) \
			{ \
				CT_LOG_FATAL(__VA_ARGS__); \
			} 
	#else
		#define CT_VERIFY(value, ...)
	#endif

	#ifdef CT_CONFIG_DEBUG
		#define CT_ASSERT(value, ...) if (!value) \
			{ \
				CT_LOG_FATAL(__VA_ARGS__); \
				PULSE_DEBUG_BREAK(); \
			}
	#elif defined(CT_RELEASE)
		#define CT_ASSERT(value, ...) if (!value) \
			{ \
				CT_LOG_FATAL(__VA_ARGS__); \
			}
	#else
		#define CT_ASSERT(value, ...)
	#endif

}