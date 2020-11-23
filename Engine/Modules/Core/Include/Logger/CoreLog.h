/**
 * Created by rayfalling on 2020/10/12.
 * */

#pragma once

#ifndef VISREAL_LOG_TRACE_H
#define VISREAL_LOG_TRACE_H

#include "Object/ISingletonObject.h"
#include "Container/FString.h"

#include <spdlog/logger.h>

namespace Engine::Core {
	enum class LogLevel {
		Debug = 1,
		Info = 2,
		Warning = 3,
		Error = 4
	};

	class CoreLog final : public ISingletonObject<CoreLog> {
		friend class ISingletonObject<CoreLog>;

		protected:
			CoreLog();
			~CoreLog() noexcept override;

		public:
			CoreLog(const CoreLog&) = delete;
			CoreLog(const CoreLog&&) = delete;
			CoreLog& operator=(const CoreLog&) = delete;
			CoreLog& operator=(CoreLog&&) = delete;

		private:
			/* Core logger, static for over dll use */
			static std::shared_ptr<spdlog::logger> _logger;

			/* Module Names Register to CoreLog */
			/* TODO using custom map container*/

			/* Shared sinks between different loggers */
			static std::vector<spdlog::sink_ptr> _sinks;

		public:
			/**
			 * Log debug info
			 * */
			void LogDebug(Types::FString& message);
			void LogDebug(Types::FString&& message);
			void LogDebug(const Types::FString& message);

			/**
			 * Log default info
			 * */
			void LogInfo(Types::FString& message);
			void LogInfo(Types::FString&& message);
			void LogInfo(const Types::FString& message);

			/**
			 * Log warning info
			 * */
			void LogWarning(Types::FString& message);
			void LogWarning(Types::FString&& message);
			void LogWarning(const Types::FString& message);

			/**
			 * Log error info
			 * */
			void LogError(Types::FString& message);
			void LogError(Types::FString&& message);
			void LogError(const Types::FString& message);

			void RegisterLoggerModule(Types::FString& name);
			void SetLogLevel(LogLevel logLevel);

			/* Flush all */
			void FlushAll();
	};
}

#endif //VISREAL_LOG_TRACE_H
