# console-snake
This is a port of the classic arcade game Snake that runs inside of windows terminal. 

### Prerequisites/Notes
You need to be running this inside of windows command prompt because this takes advantage of windows system commands to change the background color of the text so that colored "pixels" can be printed to the screen. 
The frame rate of the game is limited by the printing speed of the terminal along with commands to change the color of the background. Thus, at times, the frames will mix together. This happens especially if the worm is close to the right side and is vertical. I have optimized the printing as much as possible so there is nothing else that I can do to solve this.

### Installing
You can simply clone this project and run the snake.exe file or if you want to compile it yourself, use the following command for mingw or its equivalent for your compiler
```
g++ -std=c++17 game.cpp main.cpp -o snake.exe -I./
```
This will recompile the snake.exe file.

### To Improve
I could try to write a timer so that the program can detect when the frames are going to take longer to print and then have those frames last for longer so that the frames don't bleed together.
