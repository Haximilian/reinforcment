make:
	emcc main.cpp -o target/main.html -s USE_SDL=2 -D __EMSCRIPTEN__
native:
	clang++ main.cpp -std=c++17 -I/Library/Frameworks/SDL2.framework/Headers -F /Library/Frameworks/ -framework SDL2 -o target/application