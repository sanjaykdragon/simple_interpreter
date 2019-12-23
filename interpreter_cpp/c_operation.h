#pragma once
#include <string>
#include "c_translatable.h"

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