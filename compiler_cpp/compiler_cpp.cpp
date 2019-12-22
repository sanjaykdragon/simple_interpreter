// compiler_cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "c_compiler.h"

int main()
{
	std::printf("compiler test \n");

	std::deque<c_operation> new_stack = {
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

		c_operation{opcodes::jump, -3} //jumps back to end_program
	};

	//create a "new program" with a new stack
	c_compiler cpp_compiler = c_compiler(new_stack);

	cpp_compiler.execute_program();

	system("pause");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
