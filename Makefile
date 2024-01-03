#OBJS specifies which files to compile as part of the project
OBJS = Game.cpp Level.cpp Object.cpp Player.cpp TextureManager.cpp ScoreSystem.cpp main.cpp

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IC:\mingw64-w32\SDL2\include

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LC:\mingw64-w32\SDL2\lib

#COMPILER_FLAGS specifies the addtional compilation options we're using
#-static-libgcc -static-libstdc++
#-Wunsafe-loop-optimizations -Weffc++ -pedantic
COMPILER_FLAGS = -g -Wall -static-libstdc++ -static-libgcc

#LINKER_FLAGS specifies the libraries we're linking against -lSDL2_ttf -lSDL2_mixer
#-static -lpthread
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = FruitFrogWin32.exe

#This is the target that compiles our executable
#Ex: g++ LoadFromFile.cpp -IC:\mingw64\include\SDL2 -LC:\mingw64\lib -g -Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o LoadFromFileMingw32.exe
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)