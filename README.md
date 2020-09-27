# Assembler

## Universidade de Brasília (UnB) - Software Básico

<br/>
To compile:

```sh
g++ montador.cpp -o montador
```

To run:
```
./montador
```

<br/>

## After:

To preprocess only, generating a `.pre` file:
```
./montador -p assemble_program.asm
```

To preprocess only, generating a `.obj`:
```
./montador -o preprocess_file.pre
```