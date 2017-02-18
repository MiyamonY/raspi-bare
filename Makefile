run:
	docker run -it --rm -v $(shell pwd)/config:/home/raspi/cross/config raspi-bare /bin/bash
