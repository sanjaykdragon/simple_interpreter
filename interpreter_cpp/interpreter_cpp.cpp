#include "c_interpreter.h"

int main(int argc, char* argv[])
{
	std::printf("interpreter test \n");

	//this is not used because we are loading from file below
	const std::deque<c_operation> new_stack = {
		c_operation{opcodes::const_int, 10}, // 0
		c_operation{opcodes::add, 0}, // 1 - second arg of add doesn't matter
		c_operation{opcodes::const_int, 1337}, // 2
		c_operation{opcodes::print, 0}, // 3 - second arg of print doesn't matter

		c_operation{opcodes::const_int, 1337}, // 4
		c_operation{opcodes::sub, 0}, // 5 - second arg of sub doesn't matter
		c_operation{opcodes::const_int, 999}, // 6
		c_operation{opcodes::print, 0}, // 7 

		c_operation{opcodes::jump, 4}, // 8 - jumps to const_int - 92293313

		c_operation{opcodes::const_int, 132345976}, // 9
		c_operation{opcodes::print, 0}, // 10
		c_operation{opcodes::end_program, 0}, // 11 second arg of end doesn't matter - also anything past this point won't execute

		c_operation{opcodes::const_int, 92293313}, // 12
		c_operation{opcodes::copy, -4}, // 13 - copys the operation above into line 9

		c_operation{opcodes::const_int, 1999}, // 14
		c_operation{opcodes::test_eq, 0}, // 15 - checks if prev and next num are the same
		c_operation{opcodes::const_int, 2003}, // 16
		c_operation{opcodes::jump_if, -9}, // 17 - jumps back to the newly assigned line 9
		c_operation{opcodes::end_program, 0} // 18
	};

	//create a "new program" with a new stack
	//c_interpreter interpreter = c_interpreter(new_stack);

	c_interpreter interpreter = c_interpreter(new_stack);
	
	if (argc != 1)
	{
		if(!std::filesystem::exists(argv[1]))
		{
			std::printf("%s doesn't exist.", argv[1]);
			return 0;
		}
		interpreter = c_interpreter(argv[1]);
	}

	interpreter.execute_program();

	system("pause");
	return 0;
}