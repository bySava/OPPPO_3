#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <limits>
#include "OPPPO_Sava.h"

WisdomContainer::~WisdomContainer() {
    for (auto wisdom : wisdoms) {
        delete wisdom;
    }
}

void WisdomContainer::add(Wisdom* wisdom) {
    wisdoms.push_back(wisdom);
}

void WisdomContainer::remove(const std::string& condition) {
    wisdoms.erase(std::remove_if(wisdoms.begin(), wisdoms.end(),
        [&](Wisdom* w) { return w->matchesCondition(condition); }), wisdoms.end());
}

void WisdomContainer::print() const {
    for (const auto& wisdom : wisdoms) {
        if (wisdom->getType() == "Aphorism") {
            auto aphorism = dynamic_cast<const Aphorism*>(wisdom);
            if (aphorism) {
                std::cout << aphorism->getType() << ": " << aphorism->content << " - Author: " << aphorism->author << std::endl;
            }
        }
        else if (wisdom->getType() == "Proverb") {
            auto proverb = dynamic_cast<const Proverb*>(wisdom);
            if (proverb) {
                std::cout << proverb->getType() << ": " << proverb->content << " - Country: " << proverb->country << std::endl;
            }
        }

    }
}


void processCommand(WisdomContainer& container, const std::string& command) {
    std::istringstream iss(command);
    std::string cmd;
    iss >> cmd;

    if (cmd == "ADD") {
        std::string type;
        std::string content;
        std::string param;

        if (!(iss >> type)) {
            std::cout << "Ошибка: Не указан тип добавляемой мудрости (Aphorism или Proverb)." << std::endl;
            return;
        }

        std::getline(iss, content);
        if (content.empty()) {
            std::cout << "Ошибка: Содержание мудрости не может быть пустым" << std::endl;
            return;
        }

        content.erase(0, content.find_first_not_of(" \t")); // Удаление пробелов в начале

        if (content.empty()) {
            std::cout << "Ошибка: Содержание мудрости не может быть пустым" << std::endl;
            return;
        }


        size_t firstSpace = content.find(' ');
        if (firstSpace == std::string::npos) {
            std::cout << "Ошибка: Нет пробела для разделения контента и параметра" << std::endl;
            return;
        }

        param = content.substr(firstSpace + 1);
        content = content.substr(0, firstSpace);


        if (type == "Aphorism") {
            if (param.empty()) {
                std::cout << "Ошибка: Не указан автор афоризма." << std::endl;
                return;
            }
            container.add(new Aphorism(content, param));
            std::cout << "Афоризм добавлен." << std::endl;
        }
        else if (type == "Proverb") {
            if (param.empty()) {
                std::cout << "Ошибка: Не указан народ пословицы." << std::endl;
                return;
            }
            container.add(new Proverb(content, param));
            std::cout << "Пословица добавлена." << std::endl;
        }
        else {
            std::cout << "Ошибка: Неизвестный тип мудрости. (Доступные типы: Aphorism или Proverb)" << std::endl;
        }
    }
    else if (cmd == "REM") {
        std::string condition;
        std::getline(iss, condition);
        if (condition.empty()) {
            std::cout << "Ошибка: Условие удаления не может быть пустым" << std::endl;
            return;
        }
        container.remove(condition);
        std::cout << "Мудрость удалена." << std::endl;
    }
    else if (cmd == "PRINT") {
        container.print();
    }
    else if (!cmd.empty()) {
        std::cout << "Ошибка: Неизвестная команда. Доступные команды: ADD, REM, PRINT." << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "");
    WisdomContainer container;
    std::string command;

    std::cout << "Добро пожаловать в программу управления мудростями!" << std::endl;
    std::cout << "Используйте следующие команды:" << std::endl;
    std::cout << "  - ADD <тип> <содержание> <параметр> - Добавляет мудрость. Тип: Aphorism или Proverb." << std::endl;
    std::cout << "  - REM <условие> - Удаляет мудрость, соответствующую условию." << std::endl;
    std::cout << "  - PRINT - Выводит все сохраненные мудрости." << std::endl;
    std::cout << "  - Для выхода из программы введите пустую строку." << std::endl;
    std::cout << "Введите команду:" << std::endl;

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, command) || command.empty()) {
            break;
        }
        processCommand(container, command);
    }

    std::cout << "Программа завершена." << std::endl;
    return 0;
}