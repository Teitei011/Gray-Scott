# Reaction diffusion

Reaction–diffusion systems are mathematical models which correspond to several physical phenomena: the most common is the change in space and time of the concentration of one or more chemical substances: local chemical reactions in which the substances are transformed into each other, and diffusion which causes the substances to spread out over a surface in space.


# Equation  


<img src="https://latex.codecogs.com/svg.image?\bg_white&space;\inline&space;\frac{\partial&space;A}{\partial&space;t&space;}&space;=&space;&space;D_A&space;\bigtriangledown^2&space;_A&space;-AB^2&space;&plus;&space;f(1&space;-&space;A)" title="\bg_white \inline \frac{\partial A}{\partial t } = D_A \bigtriangledown^2 _A -AB^2 + f(1 - A)" />



<img src="https://latex.codecogs.com/svg.image?\bg_white&space;\inline&space;\frac{\partial&space;B}{\partial&space;t&space;}&space;=&space;&space;D_B&space;\bigtriangledown^2&space;_B&space;-AB^2&space;&plus;&space;(k&space;&plus;&space;f)B" title="\bg_white \inline \frac{\partial B}{\partial t } = D_B \bigtriangledown^2 _B -AB^2 + (k + f)B" />


# How to compile

```
g++ -std=c++17 -Wall -Wpedantic -Wextra -O2 Gray_Scott.cpp -o GrayScott.exe

```


# How to use 

```
./GrayScott.exe  <D_a> <D_b> <Food> <Kill> <Resolution> <Iterations> <filename>
```

# Variables that you can try


# A better explanation

https://www.youtube.com/watch?v=alH3yc6tX98