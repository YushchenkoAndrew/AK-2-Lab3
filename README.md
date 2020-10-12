# Lab3 "Flag Analyzer"

## Annotation

In "Commands" and "Examples" sections first come command name (with \$ symbol) and after that program output

## Flags

- -h, --help
- -v, --version
- -n, --num
- -l, --list

## Commands

```console
$ make                    # Compiling project
g++ -c Main.cpp           # Make Output
g++ -o Main.out Main.o
echo Compiled
Compiled
$ make clean              # Clean project
rm Main.o Main.out        # Make Output
echo Cleaned
Cleaned
```

## Examples

```console
$ ./Main.out -h
Run Command
arg: help
$ ./Main.out --help
Run Command
arg: help

$ ./Main.out -v
Run Command
arg: version
$ ./Main.out --version
Run Command
arg: version

$ ./Main.out -n 50
Run Command
arg: value = 50
$ ./Main.out --num 50
Run Command
arg: value = 50

$ ./Main.out -l 1,2,3
Run Command
arg: list: 1 2 3
$ ./Main.out --list 1,2,3
Run Command
arg: list: 1 2 3


### Some difficult examples

$ ./Main.out -hv
Run Command
arg: help
arg: version

$ ./Main.out -h -v
Run Command
arg: help
arg: version

$ ./Main.out -hvn 50
Run Command
arg: help
arg: version
arg: value = 50

$ ./Main.out -hhhhhh
Run Command
arg: help

$ ./Main.out -h -v -n 50 --help --num 8 --version --list 1,2,3 -l 1,2
Run Command
arg: help
arg: version
arg: value = 50
arg: list: 1 2 3

### Error Handler

$ ./Main.out -vhn
Run Command
arg: version
arg: help
arg: invalid option

$ ./Main.out -nlh
Run Command
arg: invalid option

$ ./Main.out -n -h
Run Command
arg: invalid option

$ ./Main.out h
Run Command
arg: Cannot Access 'h'

$ ./Main.out -n 5notNumber
Run Command
arg: invalid option
```
