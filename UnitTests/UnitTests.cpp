#include "pch.h"
#include "CppUnitTest.h"
#include "../b_checker/b_checker.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(verify("before ( middle []) after "), true);
		}
		TEST_METHOD(TestMethod2)
		{
			Assert::AreEqual(verify("---(++++)----"), true);
		}
		TEST_METHOD(TestMethod3)
		{
			Assert::AreEqual(verify(""), true);
		}
		TEST_METHOD(TestMethod4)
		{
			Assert::AreEqual(verify(") ("), false);
		}
		TEST_METHOD(TestMethod5)
		{
			Assert::AreEqual(verify("<(   >)"), false);
		}
		TEST_METHOD(TestMethod6)
		{
			Assert::AreEqual(verify("(  [  <>  ()  ]  <>  )"), true);
		}
		TEST_METHOD(TestMethod7)
		{
			Assert::AreEqual(verify("   (      [)"), false);
		}
	};
}
