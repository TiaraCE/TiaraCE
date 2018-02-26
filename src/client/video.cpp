

#include "video.h"


Video::~Video()
{
	shutdown();
}

bool Video::initialise(Display * pDisplay)
{
	int iDefScr;
	int iBlack, iWhite;
	Window root;
	Screen * pScreen;
	
	GLint majorGLX = 0, minorGLX = 0;
	GLint glAttribs[] =
	{
		GLX_RGBA,
		GLX_DOUBLEBUFFER,
		GLX_DEPTH_SIZE,     24,
		GLX_STENCIL_SIZE,   8,
		GLX_RED_SIZE,       8,
		GLX_GREEN_SIZE,     8,
		GLX_BLUE_SIZE,      8,
		GLX_SAMPLE_BUFFERS, 0,
		GLX_SAMPLES,        0,
		None
	};
	
	XSetWindowAttributes wAttribs;
	
	/* If no default parameter */
	if (!pDisplay)
	{
		/* Establish connection to default display server */
		m_pDisplay = XOpenDisplay(0);
		if (!m_pDisplay) return false;
	}
	else m_pDisplay = pDisplay;
	
	/* Obtain default screen number */
	iDefScr = DefaultScreen(m_pDisplay);
	
	/* Obtain monochrome colour values */
	iBlack = BlackPixel(m_pDisplay, iDefScr);
	iWhite = WhitePixel(m_pDisplay, iDefScr);
	
	/* Obtain root window */
	root = XRootWindow(m_pDisplay, iDefScr);
	
	/* Prepare OpenGL by querying info */
	glXQueryVersion(m_pDisplay, &majorGLX, &minorGLX);
	if (majorGLX <= 1 && minorGLX < 2)
	{
		/* Invoke shutdown and return */
		shutdown();
		return false;
	}
	
	/* Find a visual format which matches our preferences */
	m_pVisual = glXChooseVisual(m_pDisplay, iDefScr, glAttribs);
	if (!m_pVisual)
	{
		/* Invoke shutdown and return */
		shutdown();
		return false;
	}
	
	/* Create a colormap */
	m_colourMap = XCreateColormap(m_pDisplay, root, m_pVisual -> visual, AllocNone);
	if (!m_colourMap)
	{
		/* Invoke shutdown and return */
		shutdown();
		return false;
	}
	
	/* Create a window */
	wAttribs.border_pixel		= iBlack;
	wAttribs.background_pixel	= iWhite;
	wAttribs.override_redirect	= true;
	wAttribs.colormap			= m_colourMap;
	wAttribs.event_mask			= EVENT_MASK;
	
	m_window = XCreateWindow(m_pDisplay, root,
		0, 0, 800, 600, 0,
		m_pVisual -> depth,
		InputOutput,
		m_pVisual -> visual,
		CWBackPixel | CWColormap | CWBorderPixel | CWEventMask,
		&wAttribs);
	if (!m_window)
	{
		/* Invoke shutdown and return */
		shutdown();
		return false;
	}
	
	/* Create a GL context */
	m_GLC = glXCreateContext(m_pDisplay, m_pVisual, 0, GL_TRUE);
	glXMakeCurrent(m_pDisplay, m_window, m_GLC);
	
	/* Map the window so that it displays */
	XClearWindow(m_pDisplay, m_window);
	XMapWindow(m_pDisplay, m_window);
	XFlush(m_pDisplay);
	
	/* With that done, wait now for the window to
	map */
	for(;;)
	{
		XEvent e;
		
		/* Poll for an event */
		XNextEvent(m_pDisplay, &e);
		
		/* Map notification? */
		if (e.type == MapNotify)
			break;
		
		/* Prevent "busy wait" by relinquishing time slice */
		sleep(0);
	}
	
	/* All good - return */
	return true;
}

void Video::shutdown()
{
	if (m_pDisplay)
	{
		if (m_GLC)			glXDestroyContext(m_pDisplay, m_GLC);
		if (m_colourMap)	XFreeColormap(m_pDisplay, m_colourMap);
		if (m_pVisual)		XFree(m_pVisual);
		if (m_window)		XDestroyWindow(m_pDisplay, m_window);
		
		XCloseDisplay(m_pDisplay);
	}
	
	*this = Video{};
}

Display * Video::getDisplay() const
{
	return m_pDisplay;
}

Window Video::getWindow() const
{
	return m_window;
}

XVisualInfo * Video::getVisual() const
{
	return m_pVisual;
}

Colormap Video::getColormap() const
{
	return m_colourMap;
}

GLXContext Video::getContext() const
{
	return m_GLC;
}

void Video::render(double rDelta)
{
	/* Set clear colour */
	glClearColor(0.5f, 0.2f, 0.7f, 1.0f);
	
	/* Generate request to clear screen */
	glClear(GL_COLOR_BUFFER_BIT);
	
	/* Generate a Z-axis rotation matrix
	for transforming the input primitives.
	Input parameter 'rDelta' specifies how
	much rotation is applied */
	glRotated(1.0, 0.0, 0.0, rDelta);

	/* Prepare GL for receiving primitives */
	glBegin(GL_TRIANGLES);
		/* For each vertex, define its:
			- color (float red, float green, float blue)
			- absolute position (float x, float y, float z)*/
		glColor3f(  1.0f,  0.0f, 0.0f);
		glVertex3f( 0.0f, -0.5f, 0.0f);
		
		/* Another vertex, same format */
		glColor3f(  0.0f,  1.0f, 0.0f);
		glVertex3f(-0.5f,  0.5f, 0.0f);
		
		/* Last vertex */
		glColor3f(  0.0f,  0.0f, 1.0f);
		glVertex3f( 0.5f,  0.5f, 0.0f);
	glEnd();

	/* Send the back buffer, with the
	freshly drawn image, to the
	video display */
	glXSwapBuffers(m_pDisplay, m_window);
}



