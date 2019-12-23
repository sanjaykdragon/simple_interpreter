#pragma once
#include <deque>
#include <string>
#include <optional>
#include <utility>
#include <filesystem>
#include "c_translatable.h"
#include "c_operation.h"

enum class return_codes
{
	success,
	error,
	end
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

	void stack_remove(const size_t pos)
	{
		this->stack.erase(stack.begin() + pos);
	}

	void stack_add(const size_t pos, const c_operation& op)
	{
		this->stack.insert(stack.begin() + pos, op);
	}
	
	std::deque<c_operation> stack;
};