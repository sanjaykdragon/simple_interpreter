#pragma once
#include <deque>
#include <string>
#include <optional>
#include <utility>
#include <filesystem>
#include <fstream>


enum class opcodes
{
	end_program,
	print,
	const_int,
	add,
	sub,
	jump,
	jump_if,
	nop
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
		case opcodes::add:
			return "add";
			break;
		case opcodes::sub:
			return "sub";
			break;
		case opcodes::jump:
			return "jump";
			break;
		case opcodes::jump_if:
			return "jump_if";
			break;
		default:
			return "unknown opcode";
			break;
		}
	}
};

class c_interpreter
{
public:
	explicit c_interpreter(std::deque<c_operation> new_stack);

	explicit c_interpreter(std::string filename);

	void set_stack(std::deque<c_operation> new_stack)
	{
		stack = std::move(new_stack);
	}
	void execute_program();
private:
	std::deque<c_operation> read_file(std::string filename);
	c_operation interpret_string(std::string str) const;
	opcodes get_opcode_from_str(std::string str) const;
	
	using maybe_operation = std::optional<c_operation>;
	return_codes execute_operation(maybe_operation prev_operation, c_operation current_operation, maybe_operation next_operation);
	void result_handler(return_codes result);
	int current_stack_location;
	
	std::deque<c_operation> stack;
};