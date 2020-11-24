/**
 * Created by rayfalling on 2020/11/24.
 * */

// ReSharper disable CppMemberFunctionMayBeStatic
#include "EventLoop.h"

#include "Constant.h"

using namespace Engine::Core;
using namespace Engine::Event;

Types::TArray<EventLoop::Func> EventLoop::_queue = Types::TArray<std::function<void()>>(16);

void EventLoop::RegisterEvent(Func& function) {
	_queue.Add(function);
}

void EventLoop::UnregisterEvent(Func& function) {
	const auto index = _queue.IndexOf(function, FuncEqual);
	if (index == -1)
		CoreLog::GetInstance().LogError(FUNCTION_NOT_REGISTER);
	else
		_queue.RemoveAt(index);
}

void EventLoop::Run() const {
	while (!_shouldExit) {
		if (!_queue.Empty()) {
			for (auto index = 0; index < _queue.GetSize(); index++) {
				_queue[index]();
			}
		}
	}
}

void EventLoop::Stop() {
	_shouldExit = true;
}

void EventLoop::Clear() {
	_queue.Clear();
}

EventLoop::EventLoop() = default;

EventLoop::~EventLoop() {
	_queue.Clear();
}

bool EventLoop::FuncEqual(const Func& a, const Func& b) {
	return a.target<Func>() == b.target<Func>();
}
