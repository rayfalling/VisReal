/**
 * Created by rayfalling on 2020/10/12.
 * */

#ifndef VISREAL_LOG_TRACE_H
#define VISREAL_LOG_TRACE_H

#include "Object/SingletonObject.h"
#include "Types/FString.h"
#include "Types/FTime.h"

#include <spdlog/logger.h>

namespace Engine::Core {
    class CoreLog final : public ISingletonObject<CoreLog> {
    protected:
        CoreLog() noexcept;

        ~CoreLog() noexcept override;

    private:
        friend class ISingletonObject<CoreLog>;

        CoreLog(const CoreLog &);

        CoreLog &operator=(const CoreLog &);

    private:
        /* Core logger */
        std::shared_ptr<spdlog::logger> logger;

        /* Module Names Register to CoreLog */
        /* TODO using custom map container*/

        /* Shared sinks between different loggers */
        std::vector<spdlog::sink_ptr> _sinks;

    public:
        void LogInfo(FString message);
        void LogInfo(FString &message);
        void Debug(FString message);
        void Debug(FString &message);
        void LogWarning(FString message);
        void LogWarning(FString &message);
        void LogError(FString message);
        void LogError(FString &message);

        void RegisterLoggerModule(FString &name);
    };
}


#endif //VISREAL_LOG_TRACE_H
