all:
	xmake build
	cp resources build/linux/x86_64/release/resources -r
	xmake run