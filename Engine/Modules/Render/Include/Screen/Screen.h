/**
 * Created by rayfalling on 2020/11/23.
 * */

#ifndef VISREAL_SCREEN_H
#define VISREAL_SCREEN_H

#include "Platform/PlatformTypes.h"

namespace Engine::Render {
	/**
	 * Store screen size without dpi scale
	 * */
	class Screen {
		private:
			/* screen width */
			uint32 _width;

			/* screen height */
			uint32 _height;

			/* position in x axis */
			uint32 _positionX;

			/* position in y axis */
			uint32 _positionY;

			/* screen dpi scale */
			float _dpiScale;

		public:
			/* construct */
			Screen();
			explicit Screen(int32 width, int32 height, int32 posX, int32 posY, float dpi);

			/* set raw height without scale */
			void SetRawHeight(int32 height);

			/* set raw width without scale */
			void SetRawWidth(int32 width);

			/* set dpi scale */
			void SetDpi(float dpi);

			/* set height */
			void SetHeight(int32 height);

			/* set width */
			void SetWidth(int32 width);

			/* set start position in x axis */
			void SetPositionX(int32 x);

			/* set start position in y axis */
			void SetPositionY(int32 y);

			/* get raw height without scale */
			[[nodiscard]] uint32 GetRawHeight() const;

			/* get raw width without scale */
			[[nodiscard]] uint32 GetRawWidth() const;

			/* get height with default value which will be set if height is 0 */
			[[nodiscard]] uint32 GetHeight(int32 defaultHeight);

			/* get width with default value which will be set if height is 0 */
			[[nodiscard]] uint32 GetWidth(int32 defaultWidth);

			/* get start position in x axis */
			[[nodiscard]] uint32 GetPositionX() const;

			/* get start position in y axis */
			[[nodiscard]] uint32 GetPositionY() const;
	};

	inline Screen::Screen() :
		_width(0), _height(0), _positionX(0), _positionY(0), _dpiScale(1.f) {
	}

	inline Screen::Screen(const int32 width, const int32 height, const int32 posX, const int32 posY, const float dpi = 1.f) :
		_width(width), _height(height), _positionX(posX), _positionY(posY), _dpiScale(dpi) {
	}

	inline void Screen::SetRawHeight(const int32 height) {
		_height = height;
	}

	inline void Screen::SetRawWidth(const int32 width) {
		_width = width;
	}

	inline void Screen::SetDpi(const float dpi) {
		_dpiScale = dpi;
	}

	inline void Screen::SetHeight(const int32 height) {
		_height = static_cast<uint32>(static_cast<float>(height) * _dpiScale);
	}

	inline void Screen::SetWidth(const int32 width) {
		_width = static_cast<uint32>(static_cast<float>(width) * _dpiScale);
	}

	inline void Screen::SetPositionX(int32 x) {
		_positionX = x;
	}

	inline void Screen::SetPositionY(int32 y) {
		_positionX = y;
	}

	inline uint32 Screen::GetRawHeight() const {
		return _height;
	}

	inline uint32 Screen::GetRawWidth() const {
		return _width;
	}

	inline uint32 Screen::GetHeight(const int32 defaultHeight = 1280) {
		if (_height == 0) _height = defaultHeight;
		return static_cast<uint32>(static_cast<float>(_height) / _dpiScale);
	}

	inline uint32 Screen::GetWidth(const int32 defaultWidth = 720) {
		if (_width == 0) _width = defaultWidth;
		return static_cast<uint32>(static_cast<float>(_width) / _dpiScale);
	}

	inline uint32 Screen::GetPositionX() const {
		return _positionX;
	}

	inline uint32 Screen::GetPositionY() const {
		return _positionY;
	}
}

#endif //VISREAL_SCREEN_H
