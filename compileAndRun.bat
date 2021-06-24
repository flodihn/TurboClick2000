g++ -c -o main.o main.cpp -D FREEGLUT_STATIC -I"C:\Program Files\mingw-w64\x86_64-8.1.0-win32-seh-rt_v6-rev0\freeglut\include"
g++ -o main.exe main.o -L"C:\Program Files\mingw-w64\x86_64-8.1.0-win32-seh-rt_v6-rev0\freeglut\lib\x64" -lfreeglut_static -lopengl32 -lglu32 -lwinmm -lgdi32 -Wl,--subsystem,windows
main.exe