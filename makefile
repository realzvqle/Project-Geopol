all:
	xmake build
	cp raylib.dll build\linux\x64\release\raylib.dll 
	cp resources build\linux\x64\release\resources -r
	xmake run