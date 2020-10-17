/**
 * Created by rayfalling on 2020/10/12.
 * */
#include "Marco/CoreLog.h"

#include <iostream>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

Engine::Core::CoreLog::CoreLog() noexcept {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::info);

    FString time = FTime::getCurrentTime();
    std::string out_file_path = fmt::format("Logs/log-{}.txt", time.toString());
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(out_file_path, true);
    file_sink->set_level(spdlog::level::info);

    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(console_sink);
    sinks.push_back(file_sink);

    logger = std::make_shared<spdlog::logger>("VisReal", begin(sinks), end(sinks));
    logger->set_level(spdlog::level::info);
}

void Engine::Core::CoreLog::LogInfo(FString &message) {
    logger->info(message.toString());
    logger->flush();
}

Engine::Core::CoreLog::~CoreLog() noexcept = default;
