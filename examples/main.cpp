
#include "ffplay.h"

const char source_name[] = "rtsp://192.168.1.11:554/user=admin&password=admin&channel=1&stream=0.sdp";

void event_loop(VideoState *cur_stream);

int main(int argc, char* argv[])
{
	initialize();

	VideoState *is = stream_open(source_name, NULL);
	if (!is) {
		fprintf(stderr, "Failed to initialize VideoState!\n");
		//do_exit(NULL);
	}

	event_loop(is);

	/* never returns */

	return 0;
}


static void refresh_loop_wait_event(VideoState *is, SDL_Event *event) {
	double remaining_time = 0.0;
	SDL_PumpEvents();
	while (!SDL_PeepEvents(event, 1, SDL_GETEVENT, SDL_ALLEVENTS)) {
		if (remaining_time > 0.0)
			av_usleep((int64_t)(remaining_time * 1000000.0));
		remaining_time = REFRESH_RATE;
		if (is->show_mode != SHOW_MODE_NONE && (!is->paused || is->force_refresh))
			video_refresh(is, &remaining_time);
		SDL_PumpEvents();
	}
}

/* handle an event sent by the GUI */
void event_loop(VideoState *cur_stream)
{
	SDL_Event event_SDL;
	double incr, pos, frac;

	for (;;) {
		double x;
		refresh_loop_wait_event(cur_stream, &event_SDL);
		switch (event_SDL.type) {

		case SDL_VIDEOEXPOSE:
			cur_stream->force_refresh = 1;
			break;

		case SDL_QUIT:
		case FF_QUIT_EVENT:
			do_exit(cur_stream);
			break;

		case FF_ALLOC_EVENT:
			alloc_picture((VideoState *)event_SDL.user.data1);
			break;

		default:
			break;
		}
	}
}