/**
 * Created by rayfalling on 2020/10/12.
 * */

#pragma once
#pragma warning(disable:4068)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "exit-time-destructors"

#include "Logger/CoreLog.h"
#include "Marco/Constant.h"
#include "Container/FTime.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

/* static shared_ptr to share logger in different library */
std::shared_ptr<spdlog::logger> Engine::Core::CoreLog::_logger = std::shared_ptr<spdlog::logger>();
std::vector<spdlog::sink_ptr>   Engine::Core::CoreLog::_sinks = std::vector<spdlog::sink_ptr>();

Engine::Core::CoreLog::CoreLog() noexcept {
	if (_logger != nullptr)return;
	/* Create sinks for logger */
	auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	consoleSink->set_level(spdlog::level::debug);

	auto time = FTime::getCurrentTime();
	auto outFilePath = fmt::format("Logs/log-{}.txt", time.toString());
	auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(outFilePath, true);
	fileSink->set_level(spdlog::level::debug);

	_sinks.emplace_back(consoleSink);
	_sinks.emplace_back(fileSink);

	/* register core logger */
	_logger = std::make_shared<spdlog::logger>(CORE_LOG_NAME.toString(), begin(_sinks), end(_sinks));
	/* TODO using custom map container*/
	//_registerLoggers.insert(std::make_pair(coreLog,logger));
	_logger->set_level(spdlog::level::info);
}

void Engine::Core::CoreLog::LogInfo(FString message) {
	_logger->info(message.toString());
	_logger->flush();
}

void Engine::Core::CoreLog::LogInfo(FString& message) {
	_logger->info(message.toString());
	_logger->flush();
}

void Engine::Core::CoreLog::LogWarning(FString message) {
	_logger->warn(message.toString());
	_logger->flush();
}

void Engine::Core::CoreLog::LogWarning(FString& message) {
	_logger->warn(message.toString());
	_logger->flush();
}

void Engine::Core::CoreLog::LogError(FString message) {
	_logger->error(message.toString());
	_logger->flush();
}

void Engine::Core::CoreLog::LogError(FString& message) {
	_logger->error(message.toString());
	_logger->flush();
}

void Engine::Core::CoreLog::LogDebug(FString message) {
	_logger->debug(message.toString());
	_logger->flush();
}

void Engine::Core::CoreLog::LogDebug(FString& message) {
	_logger->debug(message.toString());
	_logger->flush();
}

void Engine::Core::CoreLog::RegisterLoggerModule(FString& name) {

}

void Engine::Core::CoreLog::SetLogLevel(const LogLevel logLevel) {
	switch (logLevel) {
		case LogLevel::Debug:
			_logger->set_level(spdlog::level::debug);
			break;
		case LogLevel::Info:
			_logger->set_level(spdlog::level::info);
			break;
		case LogLevel::Warning:
			_logger->set_level(spdlog::level::warn);
			break;
		case LogLevel::Error:
			_logger->set_level(spdlog::level::err);
			break;
	}
}

Engine::Core::CoreLog::~CoreLog() noexcept = default;

#pragma clang diagnostic pop
#pragma clang diagnostic pop
