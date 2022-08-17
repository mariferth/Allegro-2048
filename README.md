
## What is it?
- 2048:

2048 is a single-player sliding block puzzle game designed by Italian web developer Gabriele Cirulli. [Wikipedia](https://en.wikipedia.org/wiki/2048_(video_game))
  
 - Allegro:
 
 Allegro is a cross-platform library mainly aimed at video game and multimedia programming. It handles common, low-level tasks [...] Allegro is not a game engine: you are free to design and structure your program as you like. [Liballeg.org](https://liballeg.org/)
 
## Our version: **Allegro 2048**
A version of famous 2048 puzzle in C/C++ Using [Allegro](https://github.com/liballeg/allegro5) library. 
The main characteristic of our project is to use the data structure __STACK__ to move the cells on the board.
![game print](https://user-images.githubusercontent.com/26260636/98584258-620e0900-22a4-11eb-8cec-276e145a161f.png?w=800)

## How to run?

1. You need to install the Allegro on your machine. [Here](https://github.com/liballeg/allegro_wiki/wiki/Quickstart) is how 
2. Now you need to compile it:
  - ### If you are using Linux:
    - `g++ src/2048.cpp -o 2048 $(pkg-config allegro-5 allegro_font-5 allegro_color-5 allegro_font-5 allegro_ttf-5 allegro_dialog-5 allegro_image-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 --libs --cflags)`
  - ### If you are using Windows:
    - `g++ src/2048.cpp -o 2048.exe -lallegro -lallegro_font -lallegro_color -lallegro_font -lallegro_ttf -lallegro_dialog -lallegro_image -lallegro_primitives -lallegro_audio -lallegro_acodec`

* obviously you need have the g++ compiler.
3. Now just run the created file `./2048` on linux or `2048.exe` on windows.
4. Profit!
5. Repeat.
6. Thank you!

## Authors 
**Gabriel Utzig** – <https://github.com/Utzig26>

**Marieli Ferreira** – <https://github.com/mariferth>
