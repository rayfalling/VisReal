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
    class CoreLog : public ISingletonObject<CoreLog> {
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
//        static std::unordered_map<FString, std::shared_ptr<spdlog::logger>> _registerLoggers;

        /* Shared sinks between different loggers */
        std::vector<spdlog::sink_ptr> _sinks;

    public:
        void LogInfo(FString &message);
        void Debug(FString &message);
        void LogWarning(FString &message);
        void LogError(FString &message);

    };
}


#endif //VISREAL_LOG_TRACE_H
