#include <iomanip>
#include "Tests.hpp"
#include "Operand.hpp"

void Addition_Tests()
{
	std::string firstValue = "124.25235";
	std::string secondValue = "124512.25235";
	
	const IOperand* firstOp = OperandFactory::CreateOperand(OperandType::Float, firstValue);
	const IOperand* secondOp = OperandFactory::CreateOperand(OperandType::Double, secondValue);
	assert(secondOp->GetPrecision() > firstOp->GetPrecision());
	
	const IOperand* resultOp = *firstOp + *secondOp;
	assert(resultOp->GetType() == OperandType::Double);
	assert(dynamic_cast<const Operand<double>*>(resultOp)->GetValue() == std::stof(firstValue) + std::stod(secondValue));
	
	try
	{
		firstValue = "-105";
		secondValue = "81";
		
		firstOp = OperandFactory::CreateOperand(OperandType::Int8, firstValue);
		secondOp = OperandFactory::CreateOperand(OperandType::Int8, secondValue);
		
		*firstOp - *secondOp; //exception
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "out of range"));
	}
	
	firstValue = "124";
	secondValue = "124512.25235";
	
	firstOp = OperandFactory::CreateOperand(OperandType::Int8, firstValue);
	secondOp = OperandFactory::CreateOperand(OperandType::Float, secondValue);
	assert(secondOp->GetPrecision() > firstOp->GetPrecision());
	
	resultOp = *firstOp + *secondOp;
	assert(resultOp->GetType() == OperandType::Float);
	assert(dynamic_cast<const Operand<float>*>(resultOp)->GetValue() == (int8_t)std::stoi(firstValue) + std::stof(secondValue));
	
	firstValue = "124";
	secondValue = "16";
	
	firstOp = OperandFactory::CreateOperand(OperandType::Int8, firstValue);
	secondOp = OperandFactory::CreateOperand(OperandType::Int16, secondValue);
	assert(secondOp->GetPrecision() > firstOp->GetPrecision());
	
	resultOp = *firstOp + *secondOp;
	assert(resultOp->GetType() == OperandType::Int16);
	assert(dynamic_cast<const Operand<int16_t>*>(resultOp)->GetValue() == (int8_t)std::stoi(firstValue) + (int16_t)std::stoi(secondValue));
}

void Subtraction_Tests()
{
	std::string firstValue = "124.25235";
	std::string secondValue = "124512.25235";
	
	const IOperand* firstOp = OperandFactory::CreateOperand(OperandType::Float, firstValue);
	const IOperand* secondOp = OperandFactory::CreateOperand(OperandType::Double, secondValue);
	assert(secondOp->GetPrecision() > firstOp->GetPrecision());
	
	const IOperand* resultOp = *firstOp - *secondOp;
	assert(resultOp->GetType() == OperandType::Double);
	assert(dynamic_cast<const Operand<double>*>(resultOp)->GetValue() == std::stof(firstValue) - std::stod(secondValue));
	
	try
	{
		firstValue = "1051453452342134111251252353456234786745645756521251251255234.124";
		secondValue = "812352354124132152512521512131242354.76874532";
		
		firstOp = OperandFactory::CreateOperand(OperandType::Float, firstValue);
		secondOp = OperandFactory::CreateOperand(OperandType::Float, secondValue);
		std::cout << "A" << std::endl;
		
		*firstOp + *secondOp; //exception
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "out of range"));
	}
	
	firstValue = "124";
	secondValue = "124512.25235";
	
	firstOp = OperandFactory::CreateOperand(OperandType::Int8, firstValue);
	secondOp = OperandFactory::CreateOperand(OperandType::Float, secondValue);
	assert(secondOp->GetPrecision() > firstOp->GetPrecision());
	
	resultOp = *firstOp - *secondOp;
	assert(resultOp->GetType() == OperandType::Float);
	assert(dynamic_cast<const Operand<float>*>(resultOp)->GetValue() == (int8_t)std::stoi(firstValue) - std::stof(secondValue));
	
	firstValue = "124";
	secondValue = "16";
	
	firstOp = OperandFactory::CreateOperand(OperandType::Int8, firstValue);
	secondOp = OperandFactory::CreateOperand(OperandType::Int16, secondValue);
	assert(secondOp->GetPrecision() > firstOp->GetPrecision());
	
	resultOp = *firstOp - *secondOp;
	assert(resultOp->GetType() == OperandType::Int16);
	assert(dynamic_cast<const Operand<int16_t>*>(resultOp)->GetValue() == (int8_t)std::stoi(firstValue) - (int16_t)std::stoi(secondValue));
}

void Multiplication_Tests()
{
	std::string firstValue = "124.25235";
	std::string secondValue = "124512.25235";
	
	const IOperand* firstOp = OperandFactory::CreateOperand(OperandType::Float, firstValue);
	const IOperand* secondOp = OperandFactory::CreateOperand(OperandType::Double, secondValue);
	assert(secondOp->GetPrecision() > firstOp->GetPrecision());
	
	const IOperand* resultOp = *firstOp * *secondOp;
	assert(resultOp->GetType() == OperandType::Double);
	assert(dynamic_cast<const Operand<double>*>(resultOp)->GetValue() == std::stof(firstValue) * std::stod(secondValue));
	
	try
	{
		firstValue = "1125";
		secondValue = "5512";
		
		firstOp = OperandFactory::CreateOperand(OperandType::Int16, firstValue);
		secondOp = OperandFactory::CreateOperand(OperandType::Int16, secondValue);
		
		*firstOp * *secondOp; //exception
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "out of range"));
	}
	
	firstValue = "124";
	secondValue = "124512.25235";
	
	firstOp = OperandFactory::CreateOperand(OperandType::Int8, firstValue);
	secondOp = OperandFactory::CreateOperand(OperandType::Float, secondValue);
	assert(secondOp->GetPrecision() > firstOp->GetPrecision());
	
	resultOp = *firstOp * *secondOp;
	assert(resultOp->GetType() == OperandType::Float);
	assert(dynamic_cast<const Operand<float>*>(resultOp)->GetValue() == (int8_t)std::stoi(firstValue) * std::stof(secondValue));
	
	firstValue = "124";
	secondValue = "16";
	
	firstOp = OperandFactory::CreateOperand(OperandType::Int8, firstValue);
	secondOp = OperandFactory::CreateOperand(OperandType::Int16, secondValue);
	assert(secondOp->GetPrecision() > firstOp->GetPrecision());
	
	resultOp = *firstOp * *secondOp;
	assert(resultOp->GetType() == OperandType::Int16);
	assert(dynamic_cast<const Operand<int16_t>*>(resultOp)->GetValue() == (int8_t)std::stoi(firstValue) * (int16_t)std::stoi(secondValue));
}

void Division_Tests()
{
	std::string firstValue = "124.25235";
	std::string secondValue = "124512.25235";
	
	const IOperand* firstOp = OperandFactory::CreateOperand(OperandType::Float, firstValue);
	const IOperand* secondOp = OperandFactory::CreateOperand(OperandType::Double, secondValue);
	assert(secondOp->GetPrecision() > firstOp->GetPrecision());
	
	const IOperand* resultOp = *firstOp / *secondOp;
	assert(resultOp->GetType() == OperandType::Double);
	assert(dynamic_cast<const Operand<double>*>(resultOp)->GetValue() == std::stof(firstValue) / std::stod(secondValue));
	
	try
	{
		firstValue = "1214";
		secondValue = "0";
		firstOp = OperandFactory::CreateOperand(OperandType::Int16, firstValue);
		secondOp = OperandFactory::CreateOperand(OperandType::Int32, secondValue);
		assert(secondOp->GetPrecision() > firstOp->GetPrecision());
		
		resultOp = *firstOp / *secondOp;
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "Division by 0"));
	}
	
	try
	{
		firstValue = "121.2144";
		secondValue = "0";
		firstOp = OperandFactory::CreateOperand(OperandType::Float, firstValue);
		secondOp = OperandFactory::CreateOperand(OperandType::Int32, secondValue);
		
		*firstOp / *secondOp;
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "Division by 0"));
	}
	
	try
	{
		firstValue= "199999999999999999999536434353464356.2144";
		secondValue = "0.000000000000000000000124124";
		
		firstOp = OperandFactory::CreateOperand(OperandType::Float, firstValue);
		secondOp = OperandFactory::CreateOperand(OperandType::Float, secondValue);
		
		*firstOp / *secondOp; //exception
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "out of range"));
	}
	
	
	firstValue = "124";
	secondValue = "124512.25235";
	
	firstOp = OperandFactory::CreateOperand(OperandType::Int8, firstValue);
	secondOp = OperandFactory::CreateOperand(OperandType::Float, secondValue);
	assert(secondOp->GetPrecision() > firstOp->GetPrecision());
	
	resultOp = *firstOp / *secondOp;
	assert(resultOp->GetType() == OperandType::Float);
	assert(dynamic_cast<const Operand<float>*>(resultOp)->GetValue() == (int8_t)std::stoi(firstValue) / std::stof(secondValue));
	
	firstValue = "124";
	secondValue = "16";
	
	firstOp = OperandFactory::CreateOperand(OperandType::Int8, firstValue);
	secondOp = OperandFactory::CreateOperand(OperandType::Int16, secondValue);
	assert(secondOp->GetPrecision() > firstOp->GetPrecision());
	
	resultOp = *firstOp / *secondOp;
	assert(resultOp->GetType() == OperandType::Int16);
	assert(dynamic_cast<const Operand<int16_t>*>(resultOp)->GetValue() == (int8_t)std::stoi(firstValue) / (int16_t)std::stoi(secondValue));
}

void Modulo_Tests()
{
	std::string firstValue = "124.25235";
	std::string secondValue = "124512.25235";
	
	const IOperand* firstOp;
	const IOperand* secondOp;
	const IOperand* resultOp;
	
	try
	{
		firstOp = OperandFactory::CreateOperand(OperandType::Float, firstValue);
		secondOp = OperandFactory::CreateOperand(OperandType::Double, secondValue);
		assert(secondOp->GetPrecision() > firstOp->GetPrecision());
		
		resultOp = *firstOp % *secondOp;
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "doesn't correct with fractional"));
	}
	
	try
	{
		std::string firstValue = "1214";
		std::string secondValue = "0";
		firstOp = OperandFactory::CreateOperand(OperandType::Int16, firstValue);
		secondOp = OperandFactory::CreateOperand(OperandType::Int32, secondValue);
		assert(secondOp->GetPrecision() > firstOp->GetPrecision());
		
		resultOp = *firstOp % *secondOp;
		assert(false);
	}
	catch (const std::exception& e)
	{
		assert(contains(e.what(), "Mod by 0"));
	}
	
	firstValue = "124";
	secondValue = "16";
	
	firstOp = OperandFactory::CreateOperand(OperandType::Int8, firstValue);
	secondOp = OperandFactory::CreateOperand(OperandType::Int16, secondValue);
	assert(secondOp->GetPrecision() > firstOp->GetPrecision());
	
	resultOp = *firstOp % *secondOp;
	assert(resultOp->GetType() == OperandType::Int16);
	assert(dynamic_cast<const Operand<int16_t>*>(resultOp)->GetValue() == (int8_t)std::stoi(firstValue) % (int16_t)std::stoi(secondValue));
}

void Operand_Calculation_Tests()
{
	Addition_Tests();
	Print_Success("Addition_Tests -> OK");
	
	Subtraction_Tests();
	Print_Success("Subtraction_Tests -> OK");
	
	Multiplication_Tests();
	Print_Success("Multiplication_Tests -> OK");
	
	Division_Tests();
	Print_Success("Division_Tests -> OK");
	
	Modulo_Tests();
	Print_Success("Modulo_Tests -> OK");
}