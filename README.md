# Quick Screenshot
A small tool for instantly displaying screenshots you make, potentially useful in gaming.

# Usage
- Open the program.
- Type in the shortcut you would like to use. (It cannot include print screen because of a bug in qt/the library I use)
- Select which screen you want to screenshot, and which screen you want to display it on. Optionally check if they're correct with the `Preview Monitors` button.
- Use the shortcut you entered.

# Building
I used **QT Creator** (version 5.0.2) with **QT6** (6.2.1) and **MinGW 8.1.0 64bit** to make, and compile this. Steps:
- Download the mentioned software using the Qt Maintenance Tool.
- Open the project in Qt creator, add the MinGW 8.1.0 64bit kit.
- You can build either the release or the debug version, the only difference being is that the debug version has a console when the program is ran, and the other one does not. (Though there aren't many debug messages, so it's probably best to use the release build)
- Run MinGW's `windeployqt.exe` on the exe for it to work on everyone's computer.

# Known bugs
- The hotkey cannot include print screen because of a bug in qt/the library I use. (as mentioned above)
- Doesn't work for games yet (that's basically what I made it for lol)

I'm gonna try a different library in hopes of fixing both of these issues.
