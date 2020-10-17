/**
 * Created by rayfalling on 2020/10/12.
 * */
#include "Marco/CoreLog.h"

#include <iostream>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

Engine::Core::CoreLog::CoreLog() noexcept {
    /* Create sinks for logger */
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::info);

    FString time = FTime::getCurrentTime();
    std::string out_file_path = fmt::format("Logs/log-{}.txt", time.toString());
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(out_file_path, true);
    file_sink->set_level(spdlog::level::info);

    _sinks.emplace_back(console_sink);
    _sinks.emplace_back(file_sink);

    /* register core logger */
    FString coreLog = FString("VisReal Core");
    logger = std::make_shared<spdlog::logger>(coreLog.toString(), begin(_sinks), end(_sinks));
    /* TODO using custom map container*/
//    _registerLoggers.insert(std::make_pair(coreLog,logger));
    logger->set_level(spdlog::level::info);
}

void Engine::Core::CoreLog::LogInfo(FString &message) {
    logger->info(message.toString());
    logger->flush();
}

void Engine::Core::CoreLog::LogWarning(FString &message) {
    logger->warn(message.toString());
    logger->flush();
}

void Engine::Core::CoreLog::LogError(FString &message) {
    logger->error(message.toString());
    logger->flush();
}

void Engine::Core::CoreLog::Debug(FString &message) {
    logger->debug(message.toString());
    logger->flush();
}

Engine::Core::CoreLog::~CoreLog() noexcept = default;
