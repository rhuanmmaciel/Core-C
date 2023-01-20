# Jogo Core

Como rodá-lo no Linux:

Com a biblioteca Allegro 5 e o gcc instalados no computador, deve-se entrar pelo terminal na pasta em que o jogo está e executar o seguinte comando: gcc t.c $(pkg-config allegro-5 allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_primitives-5 --libs --cflags) -lm -o game. Isso irá criar um executável com o nome de "game". Agora basta executar: ./game.
