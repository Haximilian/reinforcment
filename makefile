make:
	emcc main.cpp environment.cpp -o target/main.html -I ./include -s USE_SDL=2 -D __EMSCRIPTEN__
native:
	clang++ main.cpp environment.cpp -std=c++17 -I ./include -F /Library/Frameworks/ -framework SDL2 -o target/application