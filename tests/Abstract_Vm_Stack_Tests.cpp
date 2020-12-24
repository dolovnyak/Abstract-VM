#include "Tests.hpp"
#include "OperandFactory.hpp"
#include "AbstractVmStack.hpp"

void Push_Pop_Assert_Print_Tests()
{
	AbstractVmStack vmStack;
	
	try
	{
		vmStack.Dump();
		vmStack.Pop();
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "pop when stack is empty"));
	}
	
	try
	{
		vmStack.Push(OperandType::Int8, "52");
		vmStack.Push(OperandType::Int16, "5532");
		vmStack.Push(OperandType::Int32, "5261664");
		vmStack.Push(OperandType::Float, "5261664.5312");
		vmStack.Push(OperandType::Double, "953245261664.462341132433");
		
		vmStack.Assert(OperandType::Double, "953245261664.462341132433");
		vmStack.Pop();
		vmStack.Assert(OperandType::Float, "5261664.5312");
		vmStack.Pop();
		vmStack.Assert(OperandType::Int32, "5261664");
		vmStack.Pop();
		vmStack.Assert(OperandType::Int16, "5532");
		vmStack.Pop();
		vmStack.Assert(OperandType::Int8, "52");
		vmStack.Pop();
		vmStack.Assert(OperandType::Int8, "8");
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "assert instruction when stack is empty"));
	}
	
	try
	{
		vmStack.Push(OperandType::Int8, "52");
		vmStack.Assert(OperandType::Double, "52.0");
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "assert instruction is not true"));
	}
	
	try
	{
		vmStack.Push(OperandType::Int8, "52"); //different types aren't equal
		vmStack.Assert(OperandType::Int16, "52");
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "assert instruction is not true"));
	}
	
	try
	{
		vmStack.Push(OperandType::Int8, "52");
		vmStack.Assert(OperandType::Int8, "53");
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "assert instruction is not true"));
	}
	
	try
	{
		vmStack.Push(OperandType::Int16, "52");
		vmStack.Print();
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "try to print non 8-bit integer"));
	}
}

void Add_Sub_Mul_Div_Mod_Tests()
{
	AbstractVmStack vmStack;
	
	std::string v1 = "-52";
	std::string v2 = "-1256";
	std::string v3 = "-345664";
	std::string v4 = "-5464.5312";
	std::string v5 = "-9786541664.46234113432433";
	
	vmStack.Push(OperandType::Int8, v1);
	vmStack.Push(OperandType::Int16, v2);
	vmStack.Push(OperandType::Int32, v3);
	vmStack.Push(OperandType::Float, v4);
	vmStack.Push(OperandType::Double, v5);
	try
	{
		vmStack.Add();
		vmStack.Assert(OperandType::Double, to_string_precision(std::stod(v5) + std::stof(v4)));
		vmStack.Add();
		vmStack.Assert(OperandType::Double, to_string_precision(std::stod(v5) + std::stof(v4) + std::stoi(v3)));
		vmStack.Add();
		vmStack.Assert(OperandType::Double, to_string_precision(std::stod(v5) + std::stof(v4) + std::stoi(v3) + std::stoi(v2)));
		vmStack.Add();
		vmStack.Assert(OperandType::Double, to_string_precision(std::stod(v5) + std::stof(v4) + std::stoi(v3) + std::stoi(v2) + std::stoi(v1)));
		vmStack.Add();
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "stack is composed of strictly less that two values when an arithmetic instruction is executed"));
		vmStack.Pop();
	}
	
	vmStack.Push(OperandType::Int8, v1);
	vmStack.Push(OperandType::Int16, v2);
	vmStack.Push(OperandType::Int32, v3);
	vmStack.Push(OperandType::Float, v4);
	vmStack.Push(OperandType::Double, v5);
	try
	{
		vmStack.Sub();
		vmStack.Assert(OperandType::Double, to_string_precision(std::stod(v5) - std::stof(v4)));
		vmStack.Sub();
		vmStack.Assert(OperandType::Double, to_string_precision(std::stod(v5) - std::stof(v4) - std::stoi(v3)));
		vmStack.Sub();
		vmStack.Assert(OperandType::Double, to_string_precision(std::stod(v5) - std::stof(v4) - std::stoi(v3) - std::stoi(v2)));
		vmStack.Sub();
		vmStack.Assert(OperandType::Double, to_string_precision(std::stod(v5) - std::stof(v4) - std::stoi(v3) - std::stoi(v2) - std::stoi(v1)));
		vmStack.Sub();
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "stack is composed of strictly less that two values when an arithmetic instruction is executed"));
		vmStack.Pop();
	}
	
	vmStack.Push(OperandType::Int8, v1);
	vmStack.Push(OperandType::Int16, v2);
	vmStack.Push(OperandType::Int32, v3);
	vmStack.Push(OperandType::Float, v4);
	vmStack.Push(OperandType::Double, v5);
	try
	{
		vmStack.Mul();
		vmStack.Assert(OperandType::Double, to_string_precision(std::stod(v5) * std::stof(v4)));
		vmStack.Mul();
		vmStack.Assert(OperandType::Double, to_string_precision(std::stod(v5) * std::stof(v4) * std::stoi(v3)));
		vmStack.Mul();
		vmStack.Assert(OperandType::Double, to_string_precision(std::stod(v5) * std::stof(v4) * std::stoi(v3) * std::stoi(v2)));
		vmStack.Mul();
		vmStack.Assert(OperandType::Double, to_string_precision(std::stod(v5) * std::stof(v4) * std::stoi(v3) * std::stoi(v2) * std::stoi(v1)));
		vmStack.Mul();
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "stack is composed of strictly less that two values when an arithmetic instruction is executed"));
		vmStack.Pop();
	}
	
	vmStack.Push(OperandType::Int8, v1);
	vmStack.Push(OperandType::Int16, v2);
	vmStack.Push(OperandType::Int32, v3);
	vmStack.Push(OperandType::Float, v4);
	vmStack.Push(OperandType::Double, v5);
	try
	{
		vmStack.Div();
		vmStack.Assert(OperandType::Double, to_string_precision(std::stod(v5) / std::stof(v4)));
		vmStack.Div();
		vmStack.Assert(OperandType::Double, to_string_precision(std::stod(v5) / std::stof(v4) / std::stoi(v3)));
		vmStack.Div();
		vmStack.Assert(OperandType::Double, to_string_precision(std::stod(v5) / std::stof(v4) / std::stoi(v3) / std::stoi(v2)));
		vmStack.Div();
		vmStack.Assert(OperandType::Double, to_string_precision(std::stod(v5) / std::stof(v4) / std::stoi(v3) / std::stoi(v2) / std::stoi(v1)));
		vmStack.Div();
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "stack is composed of strictly less that two values when an arithmetic instruction is executed"));
		vmStack.Pop();
	}
	
	vmStack.Push(OperandType::Int8, v1);
	vmStack.Push(OperandType::Int16, v2);
	vmStack.Push(OperandType::Int32, v3);
	vmStack.Push(OperandType::Float, v4);
	vmStack.Push(OperandType::Double, v5);
	try
	{
		vmStack.Mod();
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "mod doesn't correct with fractional values"));
		vmStack.Pop();
	}
	try
	{
		vmStack.Mod();
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "mod doesn't correct with fractional values"));
		vmStack.Pop();
	}
	try
	{
		vmStack.Mod();
		vmStack.Assert(OperandType::Int32, std::to_string(std::stoi(v3) % std::stoi(v2)));
		vmStack.Mod();
		vmStack.Assert(OperandType::Int32, std::to_string(std::stoi(v3) % std::stoi(v2) % std::stoi(v1)));
		vmStack.Mod();
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "stack is composed of strictly less that two values when an arithmetic instruction is executed"));
		vmStack.Pop();
	}
	
	try
	{
		vmStack.Pop();
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "pop when stack is empty"));
	}
}

void Abstract_Vm_Stack_Tests()
{
	Push_Pop_Assert_Print_Tests();
	Print_Success("Push_Pop_Assert_Print_Tests -> OK");
	
	Add_Sub_Mul_Div_Mod_Tests();
	Print_Success("Add_Sub_Mul_Div_Mod_Tests -> OK");
}