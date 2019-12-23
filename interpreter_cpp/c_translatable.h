#pragma once
#include <vector>
#include <string>
#include <array>
#include "ec_opcodes.h"

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