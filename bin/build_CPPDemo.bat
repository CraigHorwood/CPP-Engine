set HOME_DIR=..
set INCLUDE_DIRS=-I..\ -IC:\Libraries\GLFW3\include -IC:\Libraries\glew-2.1.0\include -IC:\Libraries\lodepng
set LIB_DIRS=-LC:\Libraries\GLFW3\lib-mingw
set LINKER_FLAGS=-lopengl32 -lglfw3 -lgdi32
set SRC_FILES=Main.cpp Game.cpp Shader.cpp Texture.cpp Mesh.cpp Player.cpp Matrix.cpp BinaryStream.cpp
set EXE_NAME=CPPDemo.exe

cd %HOME_DIR%
g++ -DGLEW_STATIC -g -Wall -Wl,-subsystem,windows %INCLUDE_DIRS% %LIB_DIRS% %SRC_FILES% C:/Libraries/glew-2.1.0/glew.c C:/Libraries/lodepng/lodepng.cpp -o bin/%EXE_NAME% %LINKER_FLAGS%

pause