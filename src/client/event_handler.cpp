

#include "event_handler.h"


EventHandler::EventHandler(Video& vid)
{
	/* Store copy of display ptr */
	m_pDisplay = vid.getDisplay();
	
	/* Obtain atom for WM_DELETE_WINDOW */
	m_aDeleteWindow = XInternAtom(m_pDisplay, "WM_DELETE_WINDOW", False);
	
	/* Set up to use this/these atom(s) */
	XSetWMProtocols(m_pDisplay, vid.getWindow(), &m_aDeleteWindow, 1);
}

bool EventHandler::handle()
{
	XEvent e;
	unsigned int uiNumEvents;

	/* Check for events */
	if ( uiNumEvents = (unsigned)XPending(m_pDisplay) )
	{
		/* Iteratively read all events until
		counter is exhausted */
		do {
			-- uiNumEvents;
			
			/* Get next event */
			XNextEvent(m_pDisplay, &e);
			
			/* Respond */
			switch (e.type)
			{
			case KeyPress:
				{
					KeySym key;
					
					/* Translate key code into key symbol */
					XLookupString(&e.xkey, 0, 0, &key, 0);
					
					/* Respond */
					switch (key)
					{
					case XK_Escape: return false;
					
					default: break;
					}
				}
				break;
				
			case ClientMessage:
				if ((Atom)e.xclient.data.l[0] == m_aDeleteWindow)
				{
					return false;
				}
				break;
				
			default: break;
			}
		} while (uiNumEvents);
	}
	
	return true;
}


