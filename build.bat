@echo off

cl -Zi /Fe: .\build\FruitFrog64.exe .\*.cpp /I"C:\dev\SDL2" /link /LIBPATH:C:\dev\SDL2\lib\x64 /SUBSYSTEM:WINDOWS shell32.lib SDL2.lib SDL2main.lib SDL2_image.lib SDL2_ttf.lib SDL2_mixer.lib