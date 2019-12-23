#pragma once

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