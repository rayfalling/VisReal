/**
 * Created by Rayfalling on 2020/11/26.
 * */

#ifndef VISREAL_GENERIC_PLATFORM_TIME_H
#define VISREAL_GENERIC_PLATFORM_TIME_H
#include "Container/FString.h"

namespace Engine::Core {
	/** Contains CPU utilization data. */
	class FCpuTime {
		public:
			/** Initialization constructor. */
			FCpuTime(const float inCpuTimePct, const float inCpuTimePctRelative)
				: CpuTimePct(inCpuTimePct), CpuTimePctRelative(inCpuTimePctRelative) {
			}

			FCpuTime& operator+=(const FCpuTime& other) {
				CpuTimePct += other.CpuTimePct;
				CpuTimePctRelative += other.CpuTimePctRelative;
				return *this;
			}

			/** Percentage CPU utilization for the last interval. */
			float CpuTimePct;

			/** Percentage CPU utilization for the last interval relative to one core,
			 ** so if CPUTimePct is 8.0% and you have 6 core this value will be 48.0%. */
			float CpuTimePctRelative;
	};

	/**
	* Generic implementation for most platforms
	**/
	struct FGenericPlatformTime {
		/**
		 * Get the system date
		 *
		 * @param dest Destination buffer to copy to
		 * @param destSize Size of destination buffer in characters
		 * @return Date string
		 */
		static TCHAR* GetDate(TCHAR* dest, SIZE_T destSize);
		/**
		 * Get the system time
		 *
		 * @param Dest Destination buffer to copy to
		 * @param DestSize Size of destination buffer in characters
		 * @return Time string
		 */
		static TCHAR* GetTime(TCHAR* Dest, SIZE_T DestSize);

		/**
		 * Returns a timestamp string built from the current date and time.
		 * NOTE: Only one return value is valid at a time!
		 *
		 * @return timestamp string
		 */
		static const TCHAR* GetTimestamp();

		/**
		 * Returns a pretty-string for a time given in seconds. (I.e. "4:31 min", "2:16:30 hours", etc)
		 *
		 * @param Seconds Time in seconds
		 * @return Time in a pretty formatted string
		 */
		static Types::FString PrettyTime(double Seconds);

		/** Updates CPU utilization, called through a delegate from the Core ticker. */
		static bool UpdateCPUTime(float deltaTime) {
			return false;
		}

		/**
		 * @return structure that contains CPU utilization data.
		 */
		static FCpuTime GetCPUTime() {
			return FCpuTime(0.0f, 0.0f);
		}

		/**
		* @return seconds per cycle.
		*/
		static double GetSecondsPerCycle() {
			return SecondsPerCycle;
		}

		/** Converts cycles to milliseconds. */
		static float ToMilliseconds(const uint32 cycles) {
			return static_cast<float>(static_cast<double>(SecondsPerCycle * 1000.0 * cycles));
		}

		/** Converts cycles to seconds. */
		static float ToSeconds(const uint32 cycles) {
			return static_cast<float>(static_cast<double>(SecondsPerCycle * cycles));
		}

		/**
		 * @return seconds per cycle.
		 */
		static double GetSecondsPerCycle64();
		/** Converts cycles to milliseconds. */
		static double ToMilliseconds64(const uint64 Cycles) {
			return ToSeconds64(Cycles) * 1000.0;
		}

		/** Converts cycles to seconds. */
		static double ToSeconds64(const uint64 cycles) {
			return GetSecondsPerCycle64() * static_cast<double>(cycles);
		}

		protected:

			static double SecondsPerCycle;
			static double SecondsPerCycle64;
	};
}

#endif // VISREAL_GENERIC_PLATFORM_TIME_H
