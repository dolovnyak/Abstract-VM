# Abstract-VM

## MacOS - [![Build Status](https://travis-ci.com/dolovnyak/Abstract-VM.svg?branch=master)](https://travis-ci.com/dolovnyak/Abstract-VM)
###

This program provide a stack to compute simple arithmetic expressions.
-------------

Operations:
-----------
- `push v`: Pushes the value v at the top of the stack. The value v must have one of
the following form:
  - `int8(n)` : Creates an 8-bit integer with value n.
  - `int16(n)` : Creates a 16-bit integer with value n.
  - `int32(n)` : Creates a 32-bit integer with value n.
  - `float(z)` : Creates a float with value z.
  - `double(z)` : Creates a double with value z.
###
- `pop`: Unstacks the value from the top of the stack.
###
- `dump`: Displays each value of the stack.
###
- `assert v`: Asserts that the value at the top of the stack is equal to the one passed
as parameter for this instruction. If it is not the case, the program execution stop with an error. 
###
- `add`: Unstacks the first two values on the stack, adds them together and stacks the
result.
###
- `sub`: Unstacks the first two values on the stack, subtracts them, then stacks the
result.
###
- `mul`: Unstacks the first two values on the stack, multiplies them, then stacks the
result.
###
- `div`: Unstacks the first two values on the stack, divides them, then stacks the result.
###
- `mod`: Unstacks the first two values on the stack, calculates the modulus, then
stacks the result.
###
- `print`: Asserts that the value at the top of the stack is an 8-bit integer, 
then interprets it as an ASCII value and displays the corresponding character on the standard output.
###
- `exit`: Terminate the execution of the current program. If this instruction does not
appears while all others instruction has been processed, the execution must stop with an error.
###
- `;;`: pass that command to finish writing to standart output

Build and run on `MacOS`:
-------
```
cmake .
make

./abstract_vm example.txt
or
./abstract_vm
push int32(124)
push int8(12)
sub
assert int32(112)
exit
;;

(You can pass file with operations into first argument or you can write operations into standart output)

example.txt:

push int32(124)
push int8(12)
sub
assert int32(112)
exit
```

Examples:
```
./abstract_vm
push int8(33)
push int8(112)
;comment
push int8(111)
push int8(108)
push int8(112)
print
pop
print
pop
print
pop
print
pop
print
pop
exit
;;
p
l
o
p
!
```

```
example.txt:

push int32(124)
push int8(12)
push int16(5324)
push float (412.5213)
push float(.9)
push double(512.)
dump
add
add
mul
add
dump
exit

./abstract_vm example.txt
512.00
0.90
412.52
5324
12
124
-4926831.01
```
