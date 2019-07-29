set HOME_DIR=(directory to export to, should contain glew32.dll)
set INCLUDE_DIRS=-I(location of engine header files) -I(location of GLFW header files) -I(location of GLEW header files)
set LIB_DIRS=-L(location of GLFW libraries) -L(location of GLEW libraries)
set LINKER_FLAGS=-lopengl32 -lglew32 -lglfw3 -lgdi32
set SRC_FILES=Main.cpp Game.cpp Shader.cpp Texture.cpp Mesh.cpp Player.cpp Matrix.cpp BinaryStream.cpp
set EXE_NAME=CPPDemo.exe

cd %HOME_DIR%
g++ -g -Wall %INCLUDE_DIRS% %LIB_DIRS% %SRC_FILES% -o %EXE_NAME% %LINKER_FLAGS%

pause