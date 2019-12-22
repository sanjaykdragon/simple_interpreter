#include "c_compiler.h"

void c_compiler::execute_program()
{
	int operations_executed = 0;
	for (int current_pos = 0; current_pos < stack.size(); current_pos++)
	{
		this->current_stack_location = current_pos;
		std::optional<c_operation> previous_operation = current_pos - 1 < 0 ? c_operation{} : stack.at(current_pos - 1);
		const auto current_operation = stack.at(current_pos);
		std::optional<c_operation> next_operation = current_pos + 1 >= stack.size() ? c_operation{} : stack.at(current_pos + 1);
		auto result = execute_operation(previous_operation, current_operation, next_operation);
		operations_executed++;
		if (result == return_codes::end)
		{
			std::printf("called opcodes::end_program, ended gracefully \n");
			break;
		}
		else
			result_handler(result);
		current_pos = this->current_stack_location;
	}
	std::printf("program ended. stack operations executed: %i, total stack size: %i \n", operations_executed, stack.size());
}

return_codes c_compiler::execute_operation(maybe_operation prev_operation, c_operation current_operation, maybe_operation next_operation)
{
	if (current_operation.opcode == opcodes::end_program)
		return return_codes::end;

	const bool has_pre_operation = prev_operation.has_value();
	const bool has_next_operation = next_operation.has_value();
	const bool has_double_operations = has_pre_operation && has_next_operation;
	
	if (current_operation.opcode == opcodes::add || current_operation.opcode == opcodes::sub)
	{
		const std::string op_type = current_operation.opcode == opcodes::add ? "add" : "sub";
		if (!has_double_operations)
		{
			std::printf("called opcode %s, but missing prev / next operation \n", op_type.c_str());
			return return_codes::error;
		}

		const bool are_both_numbers = prev_operation.value().opcode == opcodes::const_int && next_operation.value().opcode == opcodes::const_int;

		if (!are_both_numbers)
		{
			std::printf("called %s, but not both operations are numbers \n", op_type.c_str());
			return return_codes::error;
		}
		
		stack.erase(stack.begin() + current_stack_location);
		stack.erase(stack.begin() + current_stack_location - 1);
		stack.erase(stack.begin() + current_stack_location - 1); //remove the 3 prev operations - const_int (n1), add, const_int (n2)

		const int prev_num = prev_operation.value().arg; //n1
		const int next_num = next_operation.value().arg; //n2
		if (current_operation.opcode == opcodes::add)
		{
			const auto operation_result = c_operation{ opcodes::const_int, prev_num + next_num }; //do the operation
			stack.insert(stack.begin() + current_stack_location - 1, operation_result); //put the result back onto the stack
		}
		else if(current_operation.opcode == opcodes::sub)
		{
			const auto operation_result = c_operation{ opcodes::const_int, prev_num - next_num }; //do the operation
			stack.insert(stack.begin() + current_stack_location - 1, operation_result); //put the result back onto the stack
		}
		const auto nop = c_operation{ opcodes::nop, 0 };
		stack.insert(stack.begin() + current_stack_location - 1, nop);
		stack.insert(stack.begin() + current_stack_location - 1, nop); //I do this so the stack keeps its original size
	}
	else if(current_operation.opcode == opcodes::print)
	{
		if(!has_pre_operation)
		{
			std::printf("called print, but didn't have a previous operation \n");
			return return_codes::error;
		}

		const auto prev_opcode = prev_operation.value().opcode;
		const bool is_printable = prev_opcode == opcodes::const_int;

		if(!is_printable)
		{
			std::printf("called print, but previous operation's opcode was not of a printable type. \n");
			return return_codes::error;
		}
		
		std::printf("print result: %i \n", prev_operation.value().arg);
	}
	else if(current_operation.opcode == opcodes::jump)
	{
		const auto new_stack_location = this->current_stack_location + current_operation.arg;
		const bool is_valid_jump = new_stack_location > 0 && new_stack_location < this->stack.size();
		if(!is_valid_jump)
		{
			std::printf("called jump into an invalid location \n");
			return return_codes::error;
		}
		this->current_stack_location = new_stack_location - 1;
	}
	else if (current_operation.opcode == opcodes::jump_if)
	{
		if (!has_pre_operation)
		{
			std::printf("called jump_if, but didn't have a previous operation \n");
			return return_codes::error;
		}

		const auto prev_opcode = prev_operation.value().opcode;
		const auto prev_opcode_val = prev_operation.value().arg;
		const bool is_bool = prev_opcode == opcodes::const_int && (prev_opcode_val == 0 || prev_opcode_val == 1);
		//0 - false, 1 - true
		if (!is_bool)
		{
			std::printf("called jump_if, but previous operation's arg was not a 0 or 1 \n");
			return return_codes::error;
		}

		//if opcode is true
		if (prev_opcode_val == 1)
		{
			const auto new_stack_location = this->current_stack_location + current_operation.arg;
			const bool is_valid_jump = new_stack_location > 0 && new_stack_location < this->stack.size();
			if (!is_valid_jump)
			{
				std::printf("called jump_if into an invalid location \n");
				return return_codes::error;
			}
			this->current_stack_location = new_stack_location - 1;
		}
	}
	return return_codes::success;
}

void c_compiler::result_handler(return_codes result)
{
	if(result == return_codes::error)
	{
		std::printf("error thrown at stack location %i, opcode at this location is %s \n", this->current_stack_location, this->stack.at(this->current_stack_location).to_string().c_str());
		return;
	}
}
