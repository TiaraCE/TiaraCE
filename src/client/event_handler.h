

#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "video.h"

class EventHandler
{
public:
	
	EventHandler(Video&);

	bool handle();
	
protected:
	Display * m_pDisplay;
	Atom m_aDeleteWindow;
};

#endif /* EVENT_HANDLER_H */
