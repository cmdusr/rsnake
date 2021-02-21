#include "win_renderer_gdi.hpp"

Windows::GDIRenderer::GDIRenderer(Internal& in_internal) : Submodule{in_internal}
{
}

void Windows::GDIRenderer::init()
{
}

void Windows::GDIRenderer::cleanup()
{
}

void Windows::GDIRenderer::handle_paint_msg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT paint_struct;
	BeginPaint(hWnd, &paint_struct);

	// Do Stuff here

	EndPaint(hWnd, &paint_struct);
}

void Windows::GDIRenderer::draw_quad(const Quad& quad, const Colour& colour)
{
	HPEN new_hPen = CreatePen(PS_NULL, 1, RGB(0, 0, 0));
	HPEN old_hPen = (HPEN)SelectObject(hDC, new_hPen);

	HBRUSH new_hBrush = CreateSolidBrush(RGB(colour.r, colour.g, colour.b));
	HBRUSH old_hBrush = (HBRUSH)SelectObject(hDC, new_hBrush);

	RECT rect = quad_to_rect(quad);
	Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);

	SelectObject(hDC, old_hPen);
	SelectObject(hDC, old_hBrush);
	
	DeleteObject(new_hPen);
	DeleteObject(new_hBrush);
}

void Windows::GDIRenderer::begin_rendering(HWND hWnd)
{
	hDC = GetDC(hWnd);
}

void Windows::GDIRenderer::end_rendering(HWND hWnd)
{
	ReleaseDC(hWnd, hDC);
	hDC = 0;
}
