 ## How to setup environment
 1) Download Visual Studio Community and Visual Studio 2022 if you don't have it
 2) Open Visual Studio Community and inside, look for "Desktop development with C++" and continue
 3) While "Desktop development with C++" is installing, go to: [SFML](https://www.sfml-dev.org/download/sfml/2.6.2/) and download "Visual C++ 17 (2022) – 64-bit" zip file
 4) Extract the SFML file in your C drive and move the "SFML-2.6.2" folder outside to the C drive
 5) You can delete the other folder that you just moved "SFML-2.6.2" out from
 6) Rename "SFML-2.6.2" to "SFML" for easier setup later on
 7) Once "Desktop development with C++" is installed, open Visual Studio 2022 and clone this repository
 8) Right-click on the project "Snake" inside the Solution Explorer and select Properties
 9) Go to the C/C++ drop-down and select General, then next to Additional Include Directories, click edit and paste this into the blank space: C:\SFML\include
10) Go to the Linker drop-down and select General, then next to Additional Library Directories, click edit and paste this into the blank space: C:\SFML\lib
11) Also in the Linker drop-down, select Input, next to Additional Dependencies, click edit and paste this into the space:
$(CoreLibraryDependencies)  
%(AdditionalDependencies)  
sfml-graphics-d.lib  
sfml-window-d.lib  
sfml-system-d.lib  
sfml-network-d.lib  
sfml-audio-d.lib  
12) Once everything has been pasted, click Apply then OK.
13) On the top menu of Visual Studio 2022, click on the Build drop-down and click Build Solution
14) Once the solution is done being built, you can run main.cpp with Local Windows Debugger
15) Enjoy your Snake game with 3 built-in difficulties
