# forth2c compiler and runtime

From <http://yosefk.com/blog/c-as-an-intermediate-language.html>, with
modifications. This implements a C runtime for the Forth compiled to
C and a Forth to C compiler.

Also of note:

* The license for this set of programs is unknown. Contact the [author][] 
(and not [me][]) if you want to use this for anything serious.
* The script [forth2c][] and this system could be used as a template for
porting a [Forth][] implementation to a new CPU, such as my [bit-serial CPU][]
project. Using a small python script is much simpler than making a cross
compiler or an assembler in C.
* The generated functions could be mangled better, perhaps to have some kind
of prefix like `forth_`.

[author]: http://yosefk.com/
[me]: howe.r.j.89@gmail.com
[forth2c]: forth2c
[Forth]: https://en.wikipedia.org/wiki/Forth_(programming_language)
[bit-serial CPU]: https://github.com/howerj/bit-serial
