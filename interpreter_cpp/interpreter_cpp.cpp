#include "c_interpreter.h"

int main()
{
	std::printf("interpreter test \n");

	const std::deque<c_operation> new_stack = {
		c_operation{opcodes::const_int, 10},
		c_operation{opcodes::add, 0}, //second arg of add doesn't matter
		c_operation{opcodes::const_int, 1337},
		c_operation{opcodes::print, 0}, //second arg of print doesn't matter

		c_operation{opcodes::const_int, 1337},
		c_operation{opcodes::sub, 0}, //second arg of sub doesn't matter
		c_operation{opcodes::const_int, 42069},
		c_operation{opcodes::print, 0},

		c_operation{opcodes::jump, 2}, //jumps to const_int - 132345976

		c_operation{opcodes::end_program, 0}, //second arg of end doesn't matter - also anything past this point won't execute
		c_operation{opcodes::const_int, 132345976},
		c_operation{opcodes::print, 0},

		c_operation{opcodes::const_int, 1},
		c_operation{opcodes::jump_if, -4} //jumps back to end_program
	};

	//create a "new program" with a new stack
	//c_interpreter interpreter = c_interpreter(new_stack);
	c_interpreter interpreter = c_interpreter("example_script.sk_script");

	interpreter.execute_program();

	system("pause");
}