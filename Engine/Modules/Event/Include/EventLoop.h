/**
 * Created by rayfalling on 2020/11/24.
 * */

#pragma once

#ifndef VISREAL_EVENT_LOOP_H
#define VISREAL_EVENT_LOOP_H

#include "Container/TArray.h"

namespace Engine::Event {
	class EventLoop final : public Core::ISingletonObject<EventLoop> {
		// ReSharper disable once CppRedundantQualifier
		friend class Engine::Core::ISingletonObject<EventLoop>;

		protected:
			typedef std::function<void()> Func;

		public:
			/* register function need to execute */
			void RegisterEvent(Func& function);

			/* unregister function need to execute */
			void UnregisterEvent(Func& function);

			/* run event loop */
			void Run() const;

			/* stop event loop */
			void Stop();

			/* clear event queue */
			void Clear();

		protected:
			EventLoop();
			~EventLoop();

			/* control if the event loop should stop */
			bool _shouldExit = false;

			/* register function list */
			static Core::Types::TArray<Func> _queue;

			/* judge two functions are equal  */
			static bool FuncEqual(const Func& a, const Func& b);

		public:
			EventLoop(const EventLoop&) = delete;
			EventLoop(const EventLoop&&) = delete;
			EventLoop operator=(const EventLoop&) = delete;
			EventLoop operator=(const EventLoop&&) = delete;
	};
}

#endif // VISREAL_EVENT_LOOP_H
