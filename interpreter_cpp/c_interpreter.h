#pragma once
#include <deque>
#include <string>
#include <optional>
#include <utility>
#include <filesystem>
#include <array>

enum class opcodes
{
	end_program,
	print,
	const_int,
	add,
	sub,
	jump,
	jump_if,
	nop,
	copy,
	test_eq
};

enum class return_codes
{
	success,
	error,
	end
};


class c_operation_translate
{
public:
	c_operation_translate(std::vector<std::string> tn, const opcodes op_type, std::string op_txt_n)
	{
		text_names = std::move(tn);
		opcode_type = op_type;
		operation_text_name = std::move(op_txt_n);
	}
	std::vector<std::string> text_names;
	opcodes opcode_type;
	std::string operation_text_name;
};

//this is basically a list of - opcodes keywords, the opcodes they translate to, and the printable name
const static std::array<c_operation_translate, 10> translatable_operations =
{
	c_operation_translate({"add", "+"}, opcodes::add, "add"),
	c_operation_translate({"sub", "-"}, opcodes::sub, "sub"),
	c_operation_translate({"end", "end_program", "exit"}, opcodes::end_program, "end_program"),
	c_operation_translate({"print"}, opcodes::print, "print"),
	c_operation_translate({"i", "int", "integer", "iconst"}, opcodes::const_int, "const_int"),
	c_operation_translate({"jump", "jmp"}, opcodes::jump, "jump"),
	c_operation_translate({"jump_if", "jmp_if"}, opcodes::jump_if, "jump_if"),
	c_operation_translate({"nop"}, opcodes::nop, "nop"),
	c_operation_translate({"copy"}, opcodes::copy, "copy"),
	c_operation_translate({"test_eq", "=="}, opcodes::test_eq, "test_eq")
};

class c_operation
{
public:
	opcodes opcode;
	int arg;
	std::string opcode_text_name;
	std::string to_string()
	{
		return "opcode: " + opcode_to_str() + " arg: " + std::to_string(arg);
	}
private:
	[[nodiscard]] std::string opcode_to_str()
	{
		if (opcode_text_name.empty())
		{
			for (const auto& translate : translatable_operations)
			{
				if (translate.opcode_type == opcode)
				{
					opcode_text_name = translate.operation_text_name;
					return translate.operation_text_name;
				}
			}
			return "unknown opcode";
		}
		return opcode_text_name;
	}
};

class c_interpreter
{
public:
	explicit c_interpreter(std::deque<c_operation> new_stack);

	explicit c_interpreter(const std::string& filename);

	void set_stack(std::deque<c_operation> new_stack)
	{
		stack = std::move(new_stack);
	}
	void execute_program();
	void print_stack();
private:
	[[nodiscard]] std::deque<c_operation> read_file(const std::string& filename) const;
	[[nodiscard]] c_operation interpret_string(std::string str) const;
	[[nodiscard]] opcodes get_opcode_from_str(const std::string& str) const;
	
	using maybe_operation = std::optional<c_operation>;

	maybe_operation get_prev_operation()
	{
		const auto pos = this->current_stack_location;
		return pos - 1 < 0 ? c_operation{} : stack.at(pos - 1);
	}
	maybe_operation get_next_operation()
	{
		const auto pos = this->current_stack_location;
		return pos + 1 >= stack.size() ? c_operation{} : stack.at(pos + 1);
	}
	
	return_codes execute_operation(const c_operation& current_operation);
	void result_handler(return_codes result);
	int current_stack_location;

	void stack_remove(size_t pos)
	{
		this->stack.erase(stack.begin() + pos);
	}

	void stack_add(size_t pos, const c_operation& op)
	{
		this->stack.insert(stack.begin() + pos, op);
	}
	
	std::deque<c_operation> stack;
};