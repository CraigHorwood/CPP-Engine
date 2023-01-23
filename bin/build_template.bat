set HOME_DIR=..
set INCLUDE_DIRS=-I..\ -I(GLFW include location) -I(GLEW include location) -I(lodepng.h location)
set LIB_DIRS=-L(GLFW lib location)
set LINKER_FLAGS=-lopengl32 -lglfw3 -lgdi32
set SRC_FILES=*.cpp
set EXE_NAME=CPPDemo.exe

cd %HOME_DIR%
g++ -DGLEW_STATIC -g -Wall -Wl,-subsystem,windows %INCLUDE_DIRS% %LIB_DIRS% %SRC_FILES% (glew.c location) (lodepng.cpp location) -o bin/%EXE_NAME% %LINKER_FLAGS%

pause