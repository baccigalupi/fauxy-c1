# TODO
1. Class/Object system implementation
2. Interpreter sets up base classes and objectss
2. Location encoding, better error message
5. Expression validation in parser

## Cleanup
Interpreter takes capacity options and directly passes on to Pool. Should be an array of ints

## Optimize later
Event Loop

JSON Library integration

Long decimals
FxB_String concat, push and add validation for inspect

Literal/Constant pool instead of duplicate bits

FxB_HashMap:
better efficiency:
 * list iteration not cut short when node found
verification or return of 1|0 for success|failure 

FxB_Array:
verification with return boolean on push etc



## Interpreter
Function objects
Class building and context/scope lookup
