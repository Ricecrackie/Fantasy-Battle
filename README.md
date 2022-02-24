# Fantasy-Battle
The goal of this project is to implement a game with turn-based battle system, which is a system that has been adopted by various popular video games.
---Application required for Game Setup----
Qt 5.15.1 (MinGW 8.1.0 32-bit)
Qt Creator

----------Qt Environment Setup-----------
1. Download the installer at this website: https://www.qt.io/download-qt-installer
2. Login to your account (You might need to register one if you do not have an account) and choose the install directory.
3. Choose the following components:
 
In Qt->Qt 5.15.1,
MinGW 8.1.0 32-bit (For Windows) OR
macOS (For Mac OS)

In Developer and Designer Tools,
-Qt Creator 5.0.3 CDB Debugger Support
-Debugging Tools for Windows
-Qt Creator 5.0.3 Debug Symbols
-Qt Creator 5.0.3 Plugin Development
-Qt Design Studio 2.2.2-community
-MinGW 8.1.0 32-bit (For Windows)
-CMake 3.21.1
-Ninja 1.10.2
---------How to compile the game----------
1. Open Qt Creator. Go to File->Open File or Project...

2. Select FantasyBattle.pro

3. If a window "No Valid Settings Found" shows up, press Ok, select Desktop Qt 5.15.1 and press "Configure Project".

4. Click on "Projects" on the left toolbar. In General, browse a directory for build directory.

5. Go to the left toolbar. Above the run button, select Release mode and run the project.

6. Open the build directory. Open the release folder and you will see FantasyBattle.exe.

7. Open Qt 5.15.1 MinGW, enter "cd (the directory of FantasyBattle.exe)"
For example: cd C:\Users\FantasyBattle\build\release

8. Enter "windeployqt FantasyBattle.exe"

9. After the process is done, the game is compiled and you can start the game by opening FantasyBattle.exe.
------------------------------------------
