#include "pch.h"
#include "CppUnitTest.h"
#include "OPPPO_Sava.h"  // ���������� ����������� ������������ �����

#include <sstream>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WisdomContainerTests
{
    TEST_CLASS(WisdomContainerTest)
    {
    public:
        TEST_METHOD(TestAddAphorism)
        {
            WisdomContainer container;
            container.add(new Aphorism("����� - ��� ��, ��� ����������, ���� �� ������ ������ �����.", "���� ������"));

            std::ostringstream oss;
            std::streambuf* oldCout = std::cout.rdbuf(); // ��������� �������� ����� cout
            std::cout.rdbuf(oss.rdbuf()); // �������������� cout � oss
            container.print();
            std::cout.rdbuf(oldCout); // ��������������� �������� ����� cout

            std::string output = oss.str();
            Assert::IsTrue(output.find("����� - ��� ��, ��� ����������, ���� �� ������ ������ �����.") != std::string::npos);
            Assert::IsTrue(output.find("���� ������") != std::string::npos);
        }

        TEST_METHOD(TestAddProverb)
        {
            WisdomContainer container;
            container.add(new Proverb("�� ������ ������� �� ������ ��������.", "������� ���������"));

            std::ostringstream oss;
            std::streambuf* oldCout = std::cout.rdbuf();
            std::cout.rdbuf(oss.rdbuf());
            container.print();
            std::cout.rdbuf(oldCout);

            std::string output = oss.str();
            Assert::IsTrue(output.find("�� ������ ������� �� ������ ��������.") != std::string::npos);
            Assert::IsTrue(output.find("������� ���������") != std::string::npos);
        }

        TEST_METHOD(TestRemoveAphorism)
        {
            WisdomContainer container;
            container.add(new Aphorism("���� ������ ������, ������� �����.", "��������"));
            container.remove("���� ������ ������, ������� �����.");

            std::ostringstream oss;
            std::streambuf* oldCout = std::cout.rdbuf();
            std::cout.rdbuf(oss.rdbuf());
            container.print();
            std::cout.rdbuf(oldCout);

            std::string output = oss.str();
            Assert::IsTrue(output.find("���� ������ ������, ������� �����.") == std::string::npos);
        }

        TEST_METHOD(TestRemoveProverb)
        {
            WisdomContainer container;
            container.add(new Proverb("���� ��� ������, ���� ��� ������.", "������� ���������"));
            container.remove("���� ��� ������, ���� ��� ������.");

            std::ostringstream oss;
            std::streambuf* oldCout = std::cout.rdbuf();
            std::cout.rdbuf(oss.rdbuf());
            container.print();
            std::cout.rdbuf(oldCout);

            std::string output = oss.str();
            Assert::IsTrue(output.find("���� ��� ������, ���� ��� ������.") == std::string::npos);
        }

        TEST_METHOD(TestPrintNoWisdoms)
        {
            WisdomContainer container;

            std::ostringstream oss;
            std::streambuf* oldCout = std::cout.rdbuf();
            std::cout.rdbuf(oss.rdbuf());
            container.print();
            std::cout.rdbuf(oldCout);

            std::string output = oss.str();
            Assert::IsTrue(output.empty());
        }

        TEST_METHOD(TestRemoveNonExisting)
        {
            WisdomContainer container;
            container.add(new Proverb("���� ��� ������, ���� ��� ������.", "������� ���������"));
            container.remove("�� ������������ ��������");

            std::ostringstream oss;
            std::streambuf* oldCout = std::cout.rdbuf();
            std::cout.rdbuf(oss.rdbuf());
            container.print();
            std::cout.rdbuf(oldCout);

            std::string output = oss.str();
            Assert::IsTrue(output.find("���� ��� ������, ���� ��� ������.") != std::string::npos);
        }
    };
}