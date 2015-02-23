# TODO
1. Class/Object system implementation
2. Interpreter sets up base classes
2. Location encoding, better error message
5. Expression validation in parser

## Optimize later
Event Loop

JSON Library integration: Jansson
Example usage: https://groups.google.com/forum/#!topic/jansson-users/URnU-X-c2Xs

Bit pool for parser pool instead of duplicate bits

FxB\_HashMap:
better efficiency:
 * list iteration cut short when node found
 * verification or return of 1|0 for success|failure

FxB\_Array:
 * verification with return boolean on push etc


## Interpreter
Function definition objects
Class building and context/scope lookup

The way I would like to implement this is with a native register hash
any code that needs to wrap native functions should be able to do it from Fauxy
code. So, to get this passing we would just have to parse and interpret some
fauxy files.

In order to do this first attr assignment has to be possible.
Next, assigning functions to those attrs needs to happen.

## Ideas
http://www.nongnu.org/libunwind/man/libunwind(3).html for stack inspection? Used by Julia
https://github.com/JuliaLang/libmojibake utf8 management, also from Julia
