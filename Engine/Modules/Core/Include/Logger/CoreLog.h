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
		friend class std::shared_ptr<CoreLog>;

		protected:
			CoreLog() noexcept;
			~CoreLog() noexcept override;

		private:
			CoreLog(const CoreLog&);
			CoreLog& operator=(const CoreLog&);

		private:
			/* Core logger, static for over dll use */
			static std::shared_ptr<spdlog::logger> _logger;

			/* Module Names Register to CoreLog */
			/* TODO using custom map container*/

			/* Shared sinks between different loggers */
			static std::vector<spdlog::sink_ptr> _sinks;

		public:
			void LogInfo(FString message);
			void LogInfo(FString& message);
			void LogDebug(FString message);
			void LogDebug(FString& message);
			void LogWarning(FString message);
			void LogWarning(FString& message);
			void LogError(FString message);
			void LogError(FString& message);

			void RegisterLoggerModule(FString& name);
			void SetLogLevel(LogLevel logLevel);
	};
}

#endif //VISREAL_LOG_TRACE_H
