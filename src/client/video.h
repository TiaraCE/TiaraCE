

#ifndef VIDEO_H
#define VIDEO_H

#include "main.h"

#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>

#define EVENT_MASK (StructureNotifyMask | KeyPressMask | KeyReleaseMask |\
					PointerMotionMask | ButtonPressMask | ButtonReleaseMask |\
					EnterWindowMask | LeaveWindowMask | ExposureMask)

#define MAKE_OGL_VERSION(hi, lo) (uint32_t)((hi<<16)|(lo&0xFFFF))

class Video
{
public:
	~Video();

	bool			initialise(Display *);
	void			shutdown();

	Display *		getDisplay()	const;
	Window			getWindow()		const;
	XVisualInfo *	getVisual()		const;
	Colormap		getColormap()	const;
	GLXContext		getContext()	const;
	
	void			render(double rDelta);
	
protected:

	Display * m_pDisplay;
	Window m_window;
	XVisualInfo * m_pVisual;
	Colormap m_colourMap;
	GLXContext m_GLC;
};


#endif /* VIDEO_H */
