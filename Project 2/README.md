# Project 2 - Code Generation

The primary focus of this project is on generating assembly. I have written code that will produces RISC-V code

In this project I completed a compiler for a C like language. A compiler consists of many steps, parsing input files, enforcing operator precedence, validating typing, etc. However this project is only concerned with outputting code.

This project is NOT about building a compiler, instead it is about using a compiler to gain a better of understanding of the relationship between C code and the assembly created to implement it. Opted to use a compiler because most of the assembly produced is not written directly by people therefore this exposed me to the idea of automating assembly generation.

Goals of the project:

  1. How to produce various C operations in RISC-V
  2. How the instructions selected relate to type details
  3. That higher level produces can be automated
