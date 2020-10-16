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

    public:
        void LogInfo(FString &message);

        CoreLog() noexcept;

        ~CoreLog() noexcept override;

    private:
        friend class ISingletonObject<CoreLog>;

        CoreLog(const CoreLog &);

        CoreLog &operator=(const CoreLog &);

    private:
        std::shared_ptr<spdlog::logger> logger;
    };
}


#endif //VISREAL_LOG_TRACE_H
