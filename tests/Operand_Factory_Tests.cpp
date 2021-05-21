#include "Tests.hpp"
#include "Operand.hpp"

void Int8_Tests()
{
	try
	{
		const IOperand* correctInt8 = OperandFactory::CreateOperand(OperandType::Int8, "127");
		assert(correctInt8->GetType() == OperandType::Int8);
		assert(correctInt8->ToString() == "127");
		assert(dynamic_cast<const Operand<int8_t>*>(correctInt8)->GetValue() == 127);

		const IOperand* notCorrectInt8 = OperandFactory::CreateOperand(OperandType::Int8, "128");
		(void)notCorrectInt8;
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "operand overflow"));
	}

	try
	{
		const IOperand* correctInt8 = OperandFactory::CreateOperand(OperandType::Int8, "-128");
		assert(correctInt8->GetType() == OperandType::Int8);
		assert(correctInt8->ToString() == "-128");
		assert(dynamic_cast<const Operand<int8_t>*>(correctInt8)->GetValue() == -128);

		const IOperand* notCorrectInt8 = OperandFactory::CreateOperand(OperandType::Int8, "-129");
		(void)notCorrectInt8;
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "operand underflow"));
	}
}

void Int16_Tests()
{
	try
	{
		const IOperand* correctInt16 = OperandFactory::CreateOperand(OperandType::Int16, "32767");
		assert(correctInt16->GetType() == OperandType::Int16);
		assert(correctInt16->ToString() == "32767");
		assert(dynamic_cast<const Operand<int16_t>*>(correctInt16)->GetValue() == 32767);

		const IOperand* notCorrectInt16 = OperandFactory::CreateOperand(OperandType::Int16, "32768");
		(void)notCorrectInt16;
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "operand overflow"));
	}
	
	try
	{
		const IOperand* correctInt16 = OperandFactory::CreateOperand(OperandType::Int16, "-32768");
		assert(correctInt16->GetType() == OperandType::Int16);
		assert(correctInt16->ToString() == "-32768");
		assert(dynamic_cast<const Operand<int16_t>*>(correctInt16)->GetValue() == -32768);
		
		const IOperand* notCorrectInt16 = OperandFactory::CreateOperand(OperandType::Int16, "-32769");
		(void)notCorrectInt16;
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "operand underflow"));
	}
}

void Int32_Tests()
{
	try
	{
		const IOperand* correctInt32 = OperandFactory::CreateOperand(OperandType::Int32, "2147483647");
		assert(correctInt32->GetType() == OperandType::Int32);
		assert(correctInt32->ToString() == "2147483647");
		assert(dynamic_cast<const Operand<int32_t>*>(correctInt32)->GetValue() == 2147483647);

		const IOperand* notCorrectInt32 = OperandFactory::CreateOperand(OperandType::Int32, "2147483648");
		(void)notCorrectInt32;
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "operand overflow"));
	}

	try
	{
		const IOperand* correctInt32 = OperandFactory::CreateOperand(OperandType::Int32, "-2147483648");
		assert(correctInt32->GetType() == OperandType::Int32);
		assert(correctInt32->ToString() == "-2147483648");
		assert(dynamic_cast<const Operand<int>*>(correctInt32)->GetValue() == -2147483648);
		
		const IOperand* notCorrectInt32 = OperandFactory::CreateOperand(OperandType::Int32, "-2147483649");
		(void)notCorrectInt32;
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "operand underflow"));
	}
}

void Float_Tests()
{
	try
	{
		const IOperand* correctFloat = OperandFactory::CreateOperand(OperandType::Float, "124.25235");
		assert(correctFloat->GetType() == OperandType::Float);
		assert(correctFloat->ToString() == to_string_precision(std::stof("124.25235"), 2));
		assert(dynamic_cast<const Operand<float>*>(correctFloat)->GetValue() == std::stof("124.25235"));
		
		const IOperand* notCorrectFloat = OperandFactory::CreateOperand(OperandType::Float,"21124235345555555547483648235235235235423");
		(void)notCorrectFloat;
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "operand overflow"));
	}
}

void Double_Tests()
{
	try
	{
		const IOperand* correctDouble = OperandFactory::CreateOperand(OperandType::Double, "124.25235");
		assert(correctDouble->GetType() == OperandType::Double);
		assert(correctDouble->ToString() == to_string_precision(std::stod("124.25235"), 2));
		assert(dynamic_cast<const Operand<double>*>(correctDouble)->GetValue() == std::stod("124.25235"));
		
		const IOperand* notCorrectDouble = OperandFactory::CreateOperand(OperandType::Double,"2111325555555555555555555553215345234523452345234523215555555555555555555532153452345234523452345232155555555555555555555321534523452345234523452321555555555555555555553215345234523452345234523215555555555555555555532153452345234523452345232155555555555555555555321534523452345234523452321555555555555555555553215345234523452345234523215555555555555555555532153452345234523452345232155555555555555555555321534523452345234523452321555555555555555555553215345234523452345234523215555555555555555555555532153452345234523452345232153452345234523452345234523451235215345234523452345234523452345123521534523452345234523452345234512352153452345234523452345234523451235452345123564576575675463524145678654325674324235345555555547483648235235235235423");
		(void)notCorrectDouble;
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "operand overflow"));
	}
}

void Operand_Factory_Tests()
{
	Int8_Tests();
	Print_Success("Int8_Tests -> OK");
	
	Int16_Tests();
	Print_Success("Int16_Tests -> OK");
	
	Int32_Tests();
	Print_Success("Int32_Tests -> OK");
	
	Float_Tests();
	Print_Success("Float_Tests -> OK");
	
	Double_Tests();
	Print_Success("Double_Tests -> OK");
}
