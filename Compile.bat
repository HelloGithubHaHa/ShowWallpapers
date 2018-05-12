@echo off
gcc -DBUILD_DLL --shared -o KeyboardHook.dll KeyboardHook.c -Wl,--out-implib,libKeyboardHook.a
windres Wallpaper.rc Wallpaper.o
gcc -O2 -o Wallpaper.exe Wallpaper.c Wallpaper.o -L. -lKeyboardHook
del Wallpaper.o
pause