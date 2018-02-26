

#include "event_handler.h"


/* Entry point */
int main(int argc, char ** argv)
{
	Video video;
	double d = 0.0;
	
	/* Initialise video */
	if (!video.initialise(0)) return 0;
	
	/* Initialise event handler */
	EventHandler eh(video);
	
	/* Enter program loop */
	for (;;)
	{
		/* Handle system events (input) */
		if (!eh.handle()) break;
		
		/* Render video (output) */
		video.render(d);
		d += 0.1;
	}
	
	/* Exit point */
	return 0;
}


