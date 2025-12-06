/*=========================================================================
 * This file is part of SwiftQt.
 * (C) 2023 Zack T Smith.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * The author may be reached at zck22 at mail dotcom.
 *=======================================================================*/

#include <stdio.h>

#include "graphics.h"

Point Point_new (Coord x, Coord y)
{
	Point point;
	point.x = x;
	point.y = y;
	return point;
}

Point Point_zero ()
{
	Point point = {0, 0};
	return point;
}

void Point_print(Point point)
{
	printf ("%ldx%ld", point.x, point.y);
}

Size Size_new (Coord width, Coord height)
{
	Size size;
	size.width = width;
	size.height = height;
	return size;
}

Size Size_zero ()
{
	Size size = {0, 0};
	return size;
}

void Size_print(Size size)
{
	printf ("%ldx%ld", size.width, size.height);
}

bool Size_equals (Size first, Size second)
{
	return first.width == second.width && first.height == second.height;
}

void Rect_print(Rect rect)
{
	printf ("(%ld,%ld %ldx%ld)", rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

Rect Rect_zero ()
{
	Rect rect = { {0, 0}, {0, 0} };
	return rect;
}

Rect Rect_new (Coord x, Coord y, Coord width, Coord height)
{
	Rect rect;
	rect.origin.x = x;
	rect.origin.y = y;
	rect.size.width = width;
	rect.size.height = height;
	return rect;
}

bool Rect_containsPoint (Rect rect, Coord x, Coord y)
{
	Coord x0 = rect.origin.x;
	Coord y0 = rect.origin.y;
	if (x < x0 || y < y0) {
		return false;
	}
	Coord xlimit = x0 + rect.size.width;
	Coord ylimit = y0 + rect.size.height;
	if (x >= xlimit || y >= ylimit) {
		return false;
	}
	return true;
}

bool Rect_equals (Rect first, Rect second)
{
	return first.size.width == second.size.width 
		&& first.size.height == second.size.height 
		&& first.origin.x == second.origin.x
		&& first.origin.y == second.origin.y;
}

RGB Color_change_brightness(RGB color, float factor)
{
	RGB red = (color & 0xff0000) >> 16; 
	RGB green = (color & 0xff00) >> 8;
	RGB blue = color & 0xff;
	float r = (float) red / 255.f;
	float g = (float) green / 255.f;
	float b = (float) blue / 255.f;
	r *= factor;
	g *= factor;
	b *= factor;
	if (r > 1.f) r = 1;
	if (g > 1.f) g = 1;
	if (b > 1.f) b = 1;
	red = 0xff & (RGB)(r * 255);
	green = 0xff & (RGB)(g * 255);
	blue = 0xff & (RGB)(b * 255);
	return (red << 16) | (green << 8) | blue;
}

RGB Color_lighten(RGB color)
{
	return Color_change_brightness(color, 1.5);
}

RGB Color_darken(RGB color)
{
	return Color_change_brightness(color, 1.0/1.25);
}

