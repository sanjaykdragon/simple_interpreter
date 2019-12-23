# simple_interpreter

### description
a simple interpreter, basically a custom language


### info / credits
written in C++, using C++17 STL

credits to [code vm article](https://blog.usejournal.com/writing-a-simple-vm-in-80-lines-of-code-4fe0e949a0d9) for the inspiration, I was looking into coding something like vmprotect and found this.

### notes
jump / jump_if / copy:

all of these are a bit odd, the arguments they are assigned are actually + 1 of the argument (see void c_interpreter::execute_program()::21) because of the for loop.

add / print / sub / end_program / nop / test_eq:

none of these check their arguments

const_int:

currently only an int
