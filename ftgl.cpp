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
#include <FTGL/FTGLExtrdFont.h>
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
	{ 
		if (m_font->Error() != 0)
			throw std::invalid_argument("Invalid argument");
	}

	bool Attach( const char* fontFilePath)
	{ return m_font->Attach(fontFilePath); }

	bool CharMap(FT_Encoding encoding)
	{ return m_font->CharMap(encoding); }

	bool FaceSize(const unsigned int size, const unsigned int res)
	{ return m_font->FaceSize(size, res); }

	bool FaceSize1(const unsigned int size)
	{ return m_font->FaceSize(size); }

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
typedef FontWrapper<FTGLExtrdFont> ExtrdFontWrapper;
typedef FontWrapper<FTGLBitmapFont> BitmapFontWrapper;
typedef FontWrapper<FTGLTextureFont> TextureFontWrapper;
typedef FontWrapper<FTGLPixmapFont> PixmapFontWrapper;

template<typename T>
void export_font(const char* name)
{
	class_<T>(name, init<const char*>())
		.add_property("ascender", &T::Ascender, "The global ascender height for the face.")
		.add_property("descender", &T::Descender, "The global descender height for the face.")
		.add_property("line_height", &T::LineHeight, "The line spacing for the font.")
		.def("FaceSize", &T::FaceSize, "Set the char size for the current face.")
		.def("FaceSize", &T::FaceSize1)
		.def("Attach", &T::Attach, "Attach auxilliary file to font e.g font metrics.")
		.def("CharMap", &T::CharMap, "Set the character map for the face.")
		.def("Depth", &T::Depth, "Set the extrusion distance for the font.")
		.def("UseDisplayList", &T::UseDisplayList, "Enable or disable the use of Display Lists inside FTGL.")
		.def("BBox", &T::BBox, "Get the bounding box for a string.")
		.def("Advance", &T::Advance, " Get the advance width for a string.")
		.def("Render", &T::Render, "Render a string of characters.")
		;
}

////////////////////////////////////////////////////////////////////////////////////
// FTGL Module

BOOST_PYTHON_MODULE(FTGL)
{
	enum_<FT_Encoding>("encoding")
		.value("ft_encoding_none", FT_ENCODING_NONE)
		.value("ft_encoding_unicode", FT_ENCODING_UNICODE)
		.value("ft_encoding_symbol", FT_ENCODING_MS_SYMBOL)
		.value("ft_encoding_latin_1", FT_ENCODING_ADOBE_LATIN_1)
		.value("ft_encoding_latin_2", FT_ENCODING_OLD_LATIN_2)
		.value("ft_encoding_sjis", FT_ENCODING_SJIS)
		.value("ft_encoding_gb2312", FT_ENCODING_GB2312)
		.value("ft_encoding_big5", FT_ENCODING_BIG5)
		.value("ft_encoding_wansung", FT_ENCODING_WANSUNG)
		.value("ft_encoding_johab", FT_ENCODING_JOHAB)
		.value("ft_encoding_adobe_standard", FT_ENCODING_ADOBE_STANDARD)
		.value("ft_encoding_adobe_expert",  FT_ENCODING_ADOBE_EXPERT)
		.value("ft_encoding_adobe_custom", FT_ENCODING_ADOBE_CUSTOM )
		.value("ft_encoding_apple_roman", FT_ENCODING_APPLE_ROMAN)
		;
	export_font<OutlineFontWrapper>("OutlineFont");
	export_font<PolygonFontWrapper>("PolygonFont");
	export_font<ExtrdFontWrapper>("ExtrdFont");
	export_font<BitmapFontWrapper>("BitmapFont");
	export_font<TextureFontWrapper>("TextureFont");
	export_font<PixmapFontWrapper>("PixmapFont");
}
