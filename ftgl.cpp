// PyFTGL
// Copyright (c) 2007, Anders Dahnielson
//
// Contact: anders@dahnielson.com
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
// 02111-1307  USA


// FTGL
#include <FTGL/FTGLOutlineFont.h>
#include <FTGL/FTGLPolygonFont.h>
#include <FTGL/FTGLBitmapFont.h>
#include <FTGL/FTGLTextureFont.h>
#include <FTGL/FTGLPixmapFont.h>

// Boost
#include <boost/python.hpp>

// Namespaces
using namespace boost::python;


////////////////////////////////////////////////////////////////////////////////////
// Font Wrapper

template<typename base>
class FontWrapper
{
public:
	FontWrapper(const char* fontFilePath) :
		m_font(new base(fontFilePath))
	{ }

	bool Attach( const char* fontFilePath)
	{ m_font->Attach(fontFilePath); }

	void FaceSize(const int size, const int res)
	{ m_font->FaceSize(size, res); }

	void Depth(float depth)
	{ m_font->Depth(depth);	}

	void UseDisplayList(bool useList)
	{ m_font->UseDisplayList(useList); }

	float Ascender() const
	{ return m_font->Ascender(); }

	float Descender() const
	{ return m_font->Descender(); }

	float LineHeight() const
	{ return m_font->LineHeight(); }

	tuple BBox(const char* string)
	{
		float llx, lly, llz, urx, ury, urz;
		m_font->BBox(string, llx, lly, llz, urx, ury, urz);
		return make_tuple(llx, lly, llz, urx, ury, urz);
	}

	float Advance(const char* string)
	{ return m_font->Advance(string); }

	void Render(const char* string)
	{ m_font->Render(string); }

private:
	base* m_font;
};

typedef FontWrapper<FTGLOutlineFont> OutlineFontWrapper;
typedef FontWrapper<FTGLPolygonFont> PolygonFontWrapper;
typedef FontWrapper<FTGLBitmapFont> BitmapFontWrapper;
typedef FontWrapper<FTGLTextureFont> TextureFontWrapper;
typedef FontWrapper<FTGLPixmapFont> PixmapFontWrapper;

template<typename T>
void export_font(const char* name)
{
	class_<T>(name, init<const char*>())
		.add_property("ascender", &T::Ascender)
		.add_property("descender", &T::Descender)
		.add_property("line_height", &T::LineHeight)
		.def("FaceSize", &T::FaceSize)
		.def("Attach", &T::Attach)
		.def("Depth", &T::Depth)
		.def("UseDisplayList", &T::UseDisplayList)
		.def("BBox", &T::BBox)
		.def("Advance", &T::Advance)
		.def("Render", &T::Render)
		;
}

////////////////////////////////////////////////////////////////////////////////////
// FTGL Module

BOOST_PYTHON_MODULE(FTGL)
{
	export_font<OutlineFontWrapper>("OutlineFont");
	export_font<PolygonFontWrapper>("PolygonFont");
	export_font<BitmapFontWrapper>("BitmapFont");
	export_font<TextureFontWrapper>("TextureFont");
	export_font<PixmapFontWrapper>("PixmapFont");
}
