
#include "ffplay.h"

const char source_name[] = "rtsp://192.168.1.11:554/user=admin&password=admin&channel=1&stream=0.sdp";


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
