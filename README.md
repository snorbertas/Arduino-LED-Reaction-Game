# Arduino LED Reaction Game

This is my "second" Arduino project using C++. This is a slightly modified code of my first "LED Train" code (https://github.com/snorbertas/Arduino-LED-Train). The code programs the board to act as an interactive reaction game. The LEDs light up in a forward and backward pattern (bouncing) until the player taps the button. Once the button is tapped, the code checks if the yellow (center) light is ON. If yes then you procceed to play with the speed slightly increased. Otherwise the game resets. Here's a video demonstrating it: https://www.youtube.com/watch?v=oMEx-N8VWqs

The physical components used:
  - Arduino UNO board
  - 9 LED lights
  - 10 resistors (x9 220 ohm, x1 10 ohm)
  - 1 Button
  - 12 wires
  
If you want to attempt to rebuild it yourself. The default pins used in my code are as follows:
  - Digital #3: Button INPUT
  - Digital #4 to #12: LED OUTPUT

Here are two screenshots on how to build it. First one is for output only, second one is for input only, need to combine both so it works. I separated them to make it easier to illustrate it since it gets so clustered.

![Output](https://puu.sh/viR8t.png)
![Input](https://puu.sh/viRRI.png)

Big thanks to Andrew and his genius son who supplied me with the components to play around with and gave me a quick introduction on how Arduino works :)
