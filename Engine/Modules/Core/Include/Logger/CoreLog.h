/**
 * Created by rayfalling on 2020/10/12.
 * */

#pragma once

#ifndef VISREAL_LOG_TRACE_H
#define VISREAL_LOG_TRACE_H

#include "Object/ISingletonObject.h"
#include "Container/FString.h"
#include "Container/FTime.h"

#include <spdlog/logger.h>

#include "EngineCoreExport.generate.h"

namespace Engine::Core {
	class CoreLog final : public ISingletonObject<CoreLog> {
		friend class ISingletonObject<CoreLog>;

		protected:
			CoreLog() noexcept;
			~CoreLog() noexcept override;

		private:
			CoreLog(const CoreLog&);
			CoreLog& operator=(const CoreLog&);

		private:
			/* Core logger */
			static std::shared_ptr<spdlog::logger> logger;

			/* Module Names Register to CoreLog */
			/* TODO using custom map container*/

			/* Shared sinks between different loggers */
			static std::vector<spdlog::sink_ptr> _sinks;

		public:
			void LogInfo(FString message);
			void LogInfo(FString& message);
			void Debug(FString message);
			void Debug(FString& message);
			void LogWarning(FString message);
			void LogWarning(FString& message);
			void LogError(FString message);
			void LogError(FString& message);

			void RegisterLoggerModule(FString& name);
	};
}

#endif //VISREAL_LOG_TRACE_H
