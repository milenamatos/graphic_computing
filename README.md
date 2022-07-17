# Computação Gtáfica (graphic computing)

Códigos pessoais utilizados na disciplina de Computação Gráfica na UNIFESP.

- Instalação: 

sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev

- Uso: 

gcc circulo.c -o circulo.out -L/usr/X11R6/lib/ -lGL -lGLU -lglut -lm && ./circulo.out
