#pragma once
#include <Windows.h>
#include "Rolle.h"

namespace SSDK {
	class Color {
	public:
		// constructors
		Color() {
			*((int*)this) = 0;
		}
		Color(uint8_t r, uint8_t g, uint8_t b) {
			SetColor(r, g, b, 255);
		}
		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
			SetColor(r, g, b, a);
		}
		void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0) {
			_color[0] = (uint8_t)r;
			_color[1] = (uint8_t)g;
			_color[2] = (uint8_t)b;
			_color[3] = (uint8_t)a;
		}

		void GetColor(uint8_t& r, uint8_t& g, uint8_t& b, uint8_t& a) const {
			r = _color[0];
			g = _color[1];
			b = _color[2];
			a = _color[3];
		}

		static Color FromARGB(unsigned long color) {
			int a = (color & 0xFF000000) >> 24;
			int r = (color & 0x00FF0000) >> 16;
			int g = (color & 0x0000FF00) >> 8;
			int b = (color & 0x000000FF);

			return Color(r, g, b, a);
		}

		void SetARGB(unsigned long color) {
			int a = (color & 0xFF000000) >> 24;
			int r = (color & 0x00FF0000) >> 16;
			int g = (color & 0x0000FF00) >> 8;
			int b = (color & 0x000000FF);

			SetColor(r, g, b, a);
		}

		DWORD GetARGB() const {
			int a = (_color[3]) >> 24;
			int r = (_color[0]) >> 16;
			int g = (_color[1]) >> 8;
			int b = (_color[2]);

			return a | r | g | b;
		}



		uint8_t& operator[](int index) {
			return _color[index];
		}

		const uint8_t& operator[](int index) const {
			return _color[index];
		}

		bool operator == (const Color& rhs) const {
			return (*((int*)this) == *((int*)&rhs));
		}

		bool operator != (const Color& rhs) const {
			return !(operator==(rhs));
		}

		int r() { return _color[0]; }
		int g() { return _color[1]; }
		int b() { return _color[2]; }
		int a() { return _color[3]; }

		int GetR() { return _color[0]; }
		int GetG() { return _color[1]; }
		int GetB() { return _color[2]; }
		int GetA() { return _color[3]; }

		void SetR(uint8_t _i) { _color[0] = _i; }
		void SetG(uint8_t _i) { _color[1] = _i; }
		void SetB(uint8_t _i) { _color[2] = _i; }
		void SetA(uint8_t _i) { _color[3] = _i; }

		float* base()
		{
			float clr[3];

			clr[0] = (float)_color[0] / 255.f;
			clr[1] = (float)_color[1] / 255.f;
			clr[2] = (float)_color[2] / 255.f;

			return clr;
		}

		float rBase()
		{
			return (float)_color[0] / 255.f;
		}
		float gBase()
		{
			return (float)_color[1] / 255.f;
		}
		float bBase()
		{
			return (float)_color[2] / 255.f;
		}
		float aBase()
		{
			return (float)_color[3] / 255.f;
		}

		static Color Red() { return Color(255, 0, 0); }
		static Color Green() { return Color(0, 255, 0); }
		static Color Blue() { return Color(0, 0, 255); }
		static Color LightBlue() { return Color(100, 100, 255); }
		static Color Grey() { return Color(128, 128, 128); }
		static Color DarkGrey() { return Color(45, 45, 45); }
		static Color Black() { return Color(0, 0, 0); }
		static Color White() { return Color(255, 255, 255); }
		static Color Purple() { return Color(220, 0, 220); }
		static Color Yellow() { return Color(255, 255, 0); }
		static Color Orange() { return Color(255, 128, 0); }
		static Color Cyan() { return Color(0, 178, 178); }

		Color& operator=(const Color& rhs) {
			*(int*)(&_color[0]) = *(int*)&rhs._color[0];
			return *this;
		}



		Color operator+(const Color& rhs) const {
			int red = _color[0] + rhs._color[0];
			int green = _color[1] + rhs._color[1];
			int blue = _color[2] + rhs._color[2];
			int alpha = _color[3] + rhs._color[3];

			red = red > 255 ? 255 : red;
			green = green > 255 ? 255 : green;
			blue = blue > 255 ? 255 : blue;
			alpha = alpha > 255 ? 255 : alpha;

			return Color(red, green, blue, alpha);
		}

		Color operator-(const Color& rhs) const {
			int red = _color[0] - rhs._color[0];
			int green = _color[1] - rhs._color[1];
			int blue = _color[2] - rhs._color[2];
			int alpha = _color[3] - rhs._color[3];

			red = red < 0 ? 0 : red;
			green = green < 0 ? 0 : green;
			blue = blue < 0 ? 0 : blue;
			alpha = alpha < 0 ? 0 : alpha;
			return Color(red, green, blue, alpha);
		}

		int GetU32()
		{
			return ((_color[3] & 0xff) << 24) + ((_color[2] & 0xff) << 16) + ((_color[1] & 0xff) << 8)
				+ (_color[0] & 0xff);
			//return (ImU32)(((_color[3] & 0xff) << 24) + ((_color[0] & 0xff) << 16) + ((_color[1] & 0xff) << 8) + (_color[2] & 0xff));
		}

		static Color FromHSB(float hue, float saturation, float brightness)
		{
			float h = hue == 1.0f ? 0 : hue * 6.0f;
			float f = h - (int)h;
			float p = brightness * (1.0f - saturation);
			float q = brightness * (1.0f - saturation * f);
			float t = brightness * (1.0f - (saturation * (1.0f - f)));

			if (h < 1)
			{
				return Color(
					(unsigned char)(brightness * 255),
					(unsigned char)(t * 255),
					(unsigned char)(p * 255)
				);
			}
			else if (h < 2)
			{
				return Color(
					(unsigned char)(q * 255),
					(unsigned char)(brightness * 255),
					(unsigned char)(p * 255)
				);
			}
			else if (h < 3)
			{
				return Color(
					(unsigned char)(p * 255),
					(unsigned char)(brightness * 255),
					(unsigned char)(t * 255)
				);
			}
			else if (h < 4)
			{
				return Color(
					(unsigned char)(p * 255),
					(unsigned char)(q * 255),
					(unsigned char)(brightness * 255)
				);
			}
			else if (h < 5)
			{
				return Color(
					(unsigned char)(t * 255),
					(unsigned char)(p * 255),
					(unsigned char)(brightness * 255)
				);
			}
			else
			{
				return Color(
					(unsigned char)(brightness * 255),
					(unsigned char)(p * 255),
					(unsigned char)(q * 255)
				);
			}


		}



		operator const uint8_t* () {
			return (uint8_t*)(&_color[0]);


		}
	private:
		uint8_t _color[4];
	};



}