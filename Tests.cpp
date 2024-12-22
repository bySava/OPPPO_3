#include "pch.h"
#include "CppUnitTest.h"
#include "OPPPO_Sava.h"  // Подключите необходимые заголовочные файлы

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
            container.add(new Aphorism("Жизнь - это то, что происходит, пока мы строим другие планы.", "Джон Леннон"));

            std::ostringstream oss;
            std::streambuf* oldCout = std::cout.rdbuf(); // Сохраняем исходный буфер cout
            std::cout.rdbuf(oss.rdbuf()); // Перенаправляем cout в oss
            container.print();
            std::cout.rdbuf(oldCout); // Восстанавливаем исходный буфер cout

            std::string output = oss.str();
            Assert::IsTrue(output.find("Жизнь - это то, что происходит, пока мы строим другие планы.") != std::string::npos);
            Assert::IsTrue(output.find("Джон Леннон") != std::string::npos);
        }

        TEST_METHOD(TestAddProverb)
        {
            WisdomContainer container;
            container.add(new Proverb("На пустой желудок не бывает мудрости.", "Русская пословица"));

            std::ostringstream oss;
            std::streambuf* oldCout = std::cout.rdbuf();
            std::cout.rdbuf(oss.rdbuf());
            container.print();
            std::cout.rdbuf(oldCout);

            std::string output = oss.str();
            Assert::IsTrue(output.find("На пустой желудок не бывает мудрости.") != std::string::npos);
            Assert::IsTrue(output.find("Русская пословица") != std::string::npos);
        }

        TEST_METHOD(TestRemoveAphorism)
        {
            WisdomContainer container;
            container.add(new Aphorism("Пока солнце светит, надежда живет.", "Анонимус"));
            container.remove("Пока солнце светит, надежда живет.");

            std::ostringstream oss;
            std::streambuf* oldCout = std::cout.rdbuf();
            std::cout.rdbuf(oss.rdbuf());
            container.print();
            std::cout.rdbuf(oldCout);

            std::string output = oss.str();
            Assert::IsTrue(output.find("Пока солнце светит, надежда живет.") == std::string::npos);
        }

        TEST_METHOD(TestRemoveProverb)
        {
            WisdomContainer container;
            container.add(new Proverb("Семь раз отмерь, один раз отрежь.", "Русская пословица"));
            container.remove("Семь раз отмерь, один раз отрежь.");

            std::ostringstream oss;
            std::streambuf* oldCout = std::cout.rdbuf();
            std::cout.rdbuf(oss.rdbuf());
            container.print();
            std::cout.rdbuf(oldCout);

            std::string output = oss.str();
            Assert::IsTrue(output.find("Семь раз отмерь, один раз отрежь.") == std::string::npos);
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
            container.add(new Proverb("Семь раз отмерь, один раз отрежь.", "Русская пословица"));
            container.remove("Не существующая мудрость");

            std::ostringstream oss;
            std::streambuf* oldCout = std::cout.rdbuf();
            std::cout.rdbuf(oss.rdbuf());
            container.print();
            std::cout.rdbuf(oldCout);

            std::string output = oss.str();
            Assert::IsTrue(output.find("Семь раз отмерь, один раз отрежь.") != std::string::npos);
        }
    };
}