#include "pch.h"
#include "CppUnitTest.h"
#include "../testy_kodu_io/èrÛd≥o.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(ADD_TASK_TO_PROJECT_TEST_KG)
		{
			int expected = 0;
			int result;

			Project temp("nazwa");

			Account ac;
			ac.create_project(temp);

			ac.create_task("nazwa", "task", 1, "test");

			Project temp2 = ac.check_for_project("nazwa");
			
			if (temp2.check_for_task("task"))
				result = 0;
			else
				result = 1;

			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(DELETE_TASK_GG){
			int expected = 0;
			int result;
			Account ac;
			Project temp("project");
			temp.delate_task("def_task");
			if(temp.check_for_task("def_task"))
				result = 1;
			else
				result = 0;

			Assert::AreEqual(expected, result);			
		}

	};
}
