#define private public

#include "Tests.hpp"
#include "CommandList.hpp"

void Not_Correct_Number_Of_Words_Tests()
{
	CommandList commandList;
	
	try
	{
		commandList.AddCommand("");
	}
	catch (const std::exception& exception)
	{
		assert(contains(exception.what(), "not correct number of words in command"));
	}
	
	try
	{
		commandList.AddCommand("push Int32(25) .");
	}
	catch (const std::exception& exception)
	{
		assert(contains(exception.what(), "not correct number of words in command"));
	}
	
	try
	{
		commandList.AddCommand("add push mul");
	}
	catch (const std::exception& exception)
	{
		assert(contains(exception.what(), "not correct number of words in command"));
	}
	
	try
	{
		commandList.AddCommand("add a");
	}
	catch (const std::exception& exception)
	{
		assert(contains(exception.what(), "command type is incorrect"));
	}
	
	try
	{
		commandList.AddCommand("mul add");
	}
	catch (const std::exception& exception)
	{
		assert(contains(exception.what(), "command type is incorrect"));
	}
}

void One_Word_Commands_Tests()
{
	CommandList commandList;
	
	try
	{
		commandList.AddCommand("Push");
		assert(false);
	}
	catch (const std::exception& exception)
	{
		assert(contains(exception.what(), "command type is incorrect"));
	}
	
	try
	{
		commandList.AddCommand("ad");
		assert(false);
	}
	catch (const std::exception& exception)
	{
		assert(contains(exception.what(), "command type is incorrect"));
	}
	
	try
	{
		commandList.AddCommand("pop");
		commandList.AddCommand("dump");
		commandList.AddCommand("add");
		commandList.AddCommand("sub");
		commandList.AddCommand("mul");
		commandList.AddCommand("div");
		commandList.AddCommand("mod");
		commandList.AddCommand("print");
		commandList.AddCommand("exit");
		commandList.AddCommand("add");
		
		int i = 0;
		for (CommandList::Command command : commandList._commandList)
		{
			assert(command.operandType == OperandType::Incorrect);
			assert(command.value.empty());
			switch (i)
			{
				case 0:
					assert(command.commandType == CommandList::CommandType::Pop);
					break;
				case 1:
					assert(command.commandType == CommandList::CommandType::Dump);
					break;
				case 2:
					assert(command.commandType == CommandList::CommandType::Add);
					break;
				case 3:
					assert(command.commandType == CommandList::CommandType::Sub);
					break;
				case 4:
					assert(command.commandType == CommandList::CommandType::Mul);
					break;
				case 5:
					assert(command.commandType == CommandList::CommandType::Div);
					break;
				case 6:
					assert(command.commandType == CommandList::CommandType::Modulo);
					break;
				case 7:
					assert(command.commandType == CommandList::CommandType::Print);
					break;
				case 8:
					assert(command.commandType == CommandList::CommandType::Exit);
					break;
				case 9:
					assert(command.commandType == CommandList::CommandType::Add);
					break;
				default:
					assert(false);
			}
			i++;
		}
	}
	catch (const std::exception& exception)
	{
		assert(false);
	}
}

void Two_Word_Commands_Tests()
{
	CommandList commandList;
	
	try
	{
		commandList.AddCommand("push");
	}
	catch (const std::exception& exception)
	{
		assert(contains(exception.what(), "command type is incorrect"));
	}
	
	try
	{
		commandList.AddCommand("push int8(52)");
		commandList.AddCommand("push int16(52)");
		commandList.AddCommand("push int32(-52)");
		commandList.AddCommand("push float(-52)");
		commandList.AddCommand("push double(52)");
		
		commandList.AddCommand("push int8(252)"); //it's ok that overflow not checked at this phase
		commandList.AddCommand("push int16(212552)");
		commandList.AddCommand("push int32(55311252)");
		commandList.AddCommand("push float(52.126541)");
		commandList.AddCommand("push double(52.5436545)");
		
		commandList.AddCommand("assert int8(52)");
		commandList.AddCommand("assert int16(52)");
		commandList.AddCommand("assert int32(52)");
		commandList.AddCommand("assert float(52)");
		commandList.AddCommand("assert double(52)");
		
		commandList.AddCommand("assert int8(252)"); //it's ok that overflow not checked at this phase
		commandList.AddCommand("assert int16(212552)");
		commandList.AddCommand("assert int32(55311252)");
		commandList.AddCommand("assert float(52.126541)");
		commandList.AddCommand("assert double(52.5436545)");
		
		int i = 0;
		for (CommandList::Command command : commandList._commandList)
		{
			if (i < 10)
				assert(command.commandType == CommandList::CommandType::Push);
			else
				assert(command.commandType == CommandList::CommandType::Assert);
				
			switch (i)
			{
				case 0:
					assert(command.value == "52");
					assert(command.operandType == OperandType::Int8);
					break;
				case 1:
					assert(command.value == "52");
					assert(command.operandType == OperandType::Int16);
					break;
				case 2:
					assert(command.value == "-52");
					assert(command.operandType == OperandType::Int32);
					break;
				case 3:
					assert(command.value == "-52");
					assert(command.operandType == OperandType::Float);
					break;
				case 4:
					assert(command.value == "52");
					assert(command.operandType == OperandType::Double);
					break;
					
				case 5:
					assert(command.value == "252");
					assert(command.operandType == OperandType::Int8);
					break;
				case 6:
					assert(command.value == "212552");
					assert(command.operandType == OperandType::Int16);
					break;
				case 7:
					assert(command.value == "55311252");
					assert(command.operandType == OperandType::Int32);
					break;
				case 8:
					assert(command.value == "52.126541");
					assert(command.operandType == OperandType::Float);
					break;
				case 9:
					assert(command.value == "52.5436545");
					assert(command.operandType == OperandType::Double);
					break;
					
				case 10:
					assert(command.value == "52");
					assert(command.operandType == OperandType::Int8);
					break;
				case 11:
					assert(command.value == "52");
					assert(command.operandType == OperandType::Int16);
					break;
				case 12:
					assert(command.value == "52");
					assert(command.operandType == OperandType::Int32);
					break;
				case 13:
					assert(command.value == "52");
					assert(command.operandType == OperandType::Float);
					break;
				case 14:
					assert(command.value == "52");
					assert(command.operandType == OperandType::Double);
					break;
				
				case 15:
					assert(command.value == "252");
					assert(command.operandType == OperandType::Int8);
					break;
				case 16:
					assert(command.value == "212552");
					assert(command.operandType == OperandType::Int16);
					break;
				case 17:
					assert(command.value == "55311252");
					assert(command.operandType == OperandType::Int32);
					break;
				case 18:
					assert(command.value == "52.126541");
					assert(command.operandType == OperandType::Float);
					break;
				case 19:
					assert(command.value == "52.5436545");
					assert(command.operandType == OperandType::Double);
					break;
				default:
					assert(false);
			}
			i++;
		}
	}
	catch (const std::exception& exception)
	{
		assert(false);
	}
	
	try
	{
		commandList.AddCommand("assert double(52.54365.45)");
	}
	catch (const std::exception& exception)
	{
		assert(contains(exception.what(), "few dots in number"));
	}
	
	try
	{
		commandList.AddCommand("assert double(52.54365a)");
	}
	catch (const std::exception& exception)
	{
		assert(contains(exception.what(), "value is incorrect"));
	}
	
	try
	{
		commandList.AddCommand("assert doubl(52.54365)");
	}
	catch (const std::exception& exception)
	{
		assert(contains(exception.what(), "value type is incorrect"));
	}
	
	try
	{
		commandList.AddCommand("assert int8(52.54365)");
	}
	catch (const std::exception& exception)
	{
		assert(contains(exception.what(), "value is incorrect"));
	}
	
	try
	{
		commandList.AddCommand("assert int8(525a)");
	}
	catch (const std::exception& exception)
	{
		assert(contains(exception.what(), "value is incorrect"));
	}
	
	try
	{
		commandList.AddCommand("assert int8(-525)");
		commandList.AddCommand("assert float(-525)");
		commandList.AddCommand("assert double(-525.12564)");
	}
	catch (const std::exception& exception)
	{
		assert(false);
	}
	
	try
	{
		commandList.AddCommand("assert double(-525.-12564)");
		assert(false);
	}
	catch (const std::exception& exception)
	{
		assert(contains(exception.what(), "value is incorrect"));
	}
	
	try
	{
		commandList.AddCommand("assert double(+525.12564)");
		assert(false);
	}
	catch (const std::exception& exception)
	{
		assert(contains(exception.what(), "value is incorrect"));
	}
	
	try
	{
		commandList.AddCommand("assert double(--525.12564)");
		assert(false);
	}
	catch (const std::exception& exception)
	{
		assert(contains(exception.what(), "value is incorrect"));
	}
	
	try
	{
		commandList.AddCommand("assert double(52-5.12564)");
		assert(false);
	}
	catch (const std::exception& exception)
	{
		assert(contains(exception.what(), "value is incorrect"));
	}
}

void Command_List_Tests()
{
	Not_Correct_Number_Of_Words_Tests();
	Print_Success("Not_Correct_Number_Of_Words_Tests -> OK");
	
	One_Word_Commands_Tests();
	Print_Success("One_Word_Commands_Tests -> OK");
	
	Two_Word_Commands_Tests();
	Print_Success("Two_Word_Commands_Tests -> OK");
}