/**
 * Created by rayfalling on 2020/10/12.
 * */

#pragma warning(disable:4068)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"

#include "Logger/CoreLog.h"
#include "Marco/Constant.h"

#include <iostream>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

/* static shared_ptr to share logger in different library */
std::shared_ptr<spdlog::logger> Engine::Core::CoreLog::logger = std::shared_ptr<spdlog::logger>();
std::vector<spdlog::sink_ptr>   Engine::Core::CoreLog::_sinks = std::vector<spdlog::sink_ptr>();

Engine::Core::CoreLog::CoreLog() noexcept {
	if (logger != nullptr)return;
	/* Create sinks for logger */
	auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	console_sink->set_level(spdlog::level::info);

	FString     time          = FTime::getCurrentTime();
	std::string out_file_path = fmt::format("Logs/log-{}.txt", time.toString());
	auto        file_sink     = std::make_shared<spdlog::sinks::basic_file_sink_mt>(out_file_path, true);
	file_sink->set_level(spdlog::level::info);

	_sinks.emplace_back(console_sink);
	_sinks.emplace_back(file_sink);

	/* register core logger */
	logger = std::make_shared<spdlog::logger>(CORE_LOG_NAME.toString(), begin(_sinks), end(_sinks));
	/* TODO using custom map container*/
	//_registerLoggers.insert(std::make_pair(coreLog,logger));
	logger->set_level(spdlog::level::info);
}

void Engine::Core::CoreLog::LogInfo(FString message) {
	logger->info(message.toString());
	logger->flush();
}

void Engine::Core::CoreLog::LogInfo(FString& message) {
	logger->info(message.toString());
	logger->flush();
}

void Engine::Core::CoreLog::LogWarning(FString message) {
	logger->warn(message.toString());
	logger->flush();
}

void Engine::Core::CoreLog::LogWarning(FString& message) {
	logger->warn(message.toString());
	logger->flush();
}

void Engine::Core::CoreLog::LogError(FString message) {
	logger->error(message.toString());
	logger->flush();
}

void Engine::Core::CoreLog::LogError(FString& message) {
	logger->error(message.toString());
	logger->flush();
}

void Engine::Core::CoreLog::Debug(FString message) {
	logger->debug(message.toString());
	logger->flush();
}

void Engine::Core::CoreLog::Debug(FString& message) {
	logger->debug(message.toString());
	logger->flush();
}

void Engine::Core::CoreLog::RegisterLoggerModule(FString& name) {

}

Engine::Core::CoreLog::~CoreLog() noexcept = default;

#pragma clang diagnostic pop
