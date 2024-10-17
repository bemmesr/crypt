# Crypt
A library of functions which both encode and decode various ciphers from
"The Code Book" by Simon Singh.
## Restrictions
To make this project possible and for my own sanity, there are some
restrictions on the scope of this project:
1. Each symbol in any cipher is assumed to take at most one char of space. This
may change in future as I would very much __like__ to generalize this project
to the max, however, I would also like to get at least some functionality done.
## Testing
Run 'make tests', this will compile all the test files found in test/ with the
appropriate sources in src/. Once this is done, a file named "run\_tests.sh"
will appear in the root project directory. The script prints nothing if all
tests are ok.
## Building
Just run 'make'. There are no dependencies besides gcc and the standard C
libraries. Should you use a different compiler, it will probably still work as
long as you override $(CC). The final library is written to bin/crypt.a.
## Using
To use crypt.a in your own projects, you'll want to compile your project with
'gcc -static yourfile.c crypt.a -o yourfile'. You'll also want to make the
contents of include/ available to your compiler. The specification for each
function can be found in its header file. I've tried to keep everything as
simple as possible, so everything should be fairly self explanatory. If you
need to know how a specific type of encryption works, you'll have to look it
up. I've tried to name each file based on its encryption type's most popular
name, so this shouldn't be hard to do.
