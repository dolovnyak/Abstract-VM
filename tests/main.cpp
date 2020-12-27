#include "Tests.hpp"

int main()
{
	std::cout << "Operand_Factory_Tests:" << std::endl;
	Operand_Factory_Tests();
	std::cout << std::endl;
	
	std::cout << "Operand_Calculation_Tests:" << std::endl;
	Operand_Calculation_Tests();
	std::cout << std::endl;
	
	std::cout << "Abstract_Vm_Stack_Tests:" << std::endl;
	Abstract_Vm_Stack_Tests();
	std::cout << std::endl;
	
	std::cout << "Command_List_Tests:" << std::endl;
	Command_List_Tests();
	std::cout << std::endl;
	
	return 0;
}
