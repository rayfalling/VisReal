/**
 * Created by rayfalling on 2020/10/12.
 * */

// ReSharper disable CppMemberFunctionMayBeStatic

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

#include "spdlog/spdlog.h"

/* static shared_ptr to share logger in different library */
std::shared_ptr<spdlog::logger> Engine::Core::CoreLog::_logger = std::shared_ptr<spdlog::logger>();
std::vector<spdlog::sink_ptr> Engine::Core::CoreLog::_sinks = std::vector<spdlog::sink_ptr>();

Engine::Core::CoreLog::CoreLog() {
	if (_logger != nullptr)return;
	/* Create sinks for logger */
	#ifdef _WIN32
	auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	#else
	auto consoleSink = std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>();
	#endif
	consoleSink->set_level(spdlog::level::debug);

	auto time = Types::FTime::CurrentTime();
	const auto outFilePath = fmt::format("Logs/log-{}.txt", time.ToString());
	auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(Types::FString::String2Wstring(outFilePath), true);
	fileSink->set_level(spdlog::level::debug);

	_sinks.emplace_back(consoleSink);
	_sinks.emplace_back(fileSink);

	/* register core logger */
	_logger = std::make_shared<spdlog::logger>(C_CORE_LOG_NAME.ToString(), begin(_sinks), end(_sinks));
	/* TODO using custom map container*/
	//_registerLoggers.insert(std::make_pair(coreLog,logger));
	_logger->set_level(spdlog::level::info);
	spdlog::flush_every(std::chrono::seconds(3));
	_logger->enable_backtrace(1024);
}

void Engine::Core::CoreLog::LogInfo(Types::FString& message) {
	_logger->info(message.ToString());
	_logger->flush();
}

void Engine::Core::CoreLog::LogInfo(Types::FString&& message) {
	_logger->info(message.ToString());
	_logger->flush();
}

void Engine::Core::CoreLog::LogInfo(const Types::FString& message) {
	_logger->info(message.ToString());
	_logger->flush();
}

void Engine::Core::CoreLog::LogWarning(Types::FString& message) {
	_logger->warn(message.ToString());
	_logger->flush();
}

void Engine::Core::CoreLog::LogWarning(Types::FString&& message) {
	_logger->warn(message.ToString());
	_logger->flush();
}

void Engine::Core::CoreLog::LogWarning(const Types::FString& message) {
	_logger->warn(message.ToString());
	_logger->flush();
}

void Engine::Core::CoreLog::LogError(Types::FString& message) {
	_logger->error(message.ToString());
	_logger->flush();
}

void Engine::Core::CoreLog::LogError(Types::FString&& message) {
	_logger->error(message.ToString());
	_logger->flush();
}

void Engine::Core::CoreLog::LogError(const Types::FString& message) {
	_logger->error(message.ToString());
	_logger->flush();
}

void Engine::Core::CoreLog::LogDebug(Types::FString& message) {
	_logger->debug(message.ToString());
	_logger->flush();
}

void Engine::Core::CoreLog::LogDebug(Types::FString&& message) {
	_logger->debug(message.ToString());
	_logger->flush();
}

void Engine::Core::CoreLog::LogDebug(const Types::FString& message) {
	_logger->debug(message.ToString());
	_logger->flush();
}

void Engine::Core::CoreLog::RegisterLoggerModule(Types::FString& name) {

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

void Engine::Core::CoreLog::FlushAll() {
	_logger->flush();
}

Engine::Core::CoreLog::~CoreLog() noexcept = default;

#pragma clang diagnostic pop
#pragma clang diagnostic pop
