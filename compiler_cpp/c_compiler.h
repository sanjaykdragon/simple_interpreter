#pragma once
#include <deque>
#include <iostream>
#include <string>
#include <optional>


enum class opcodes
{
	end_program,
	print,
	const_int,
	const_string,
	add,
	sub
};

enum class return_codes
{
	success,
	error,
	end
};

class c_operation
{
public:
	opcodes opcode;
	int arg;
	std::string to_string() const
	{
		return "opcode: " + opcode_to_str() + " arg: " + std::to_string(arg);
	}
private:
	std::string opcode_to_str() const
	{
		//bad code
		switch(opcode)
		{
		case opcodes::end_program:
			return "end program";
			break;
		case opcodes::print:
			return "print";
			break;
		case opcodes::const_int:
			return "const int";
			break;
		case opcodes::const_string:
			return "const string";
			break;
		case opcodes::add:
			return "add";
			break;
		case opcodes::sub:
			return "sub";
			break;
		default:
			return "unknown opcode";
			break;
		}
	}
};

class c_compiler
{
public:
	c_compiler(std::deque<c_operation> new_stack)
	{
		stack = new_stack;
	}

	void set_stack(std::deque<c_operation> new_stack)
	{
		stack = new_stack;
	}
	void execute_program();
private:
	
	using maybe_operation = std::optional<c_operation>;
	return_codes execute_operation(maybe_operation prev_operation, c_operation current_operation, maybe_operation next_operation);
	void result_handler(return_codes result);
	int current_stack_location;
	
	std::deque<c_operation> stack;
};