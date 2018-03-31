#include <iostream>
#include <string>
#include "include\SimpleTable.h"

int main(int argc, char** argv) {
    SimpleTable<std::string> table;

    std::string columnNames1[3] = {"PYPL", "CodingDojo", "IEEE Trending"};
    std::string columnNames2[2] = {"IEEE Jobs", "IEEE Open"};

    /// Добавление 3 колонок, с именами из списка, ширина устанавливается по максимаьной длине элементов
    table.appendMultipleColumns(3, columnNames1, SimpleTable<std::string>::Width::BY_MAX);
    /// Вставка во второй ИНДЕКС 2 элементов, с именами из списка, ширина устанавливается по средней длине элементов
    table.insertMultileColumns(2, 2, columnNames2, SimpleTable<std::string>::Width::BY_AVERAGE);
    /// Вставка в 1 первый ИНДЕКС элемент, длина фиксированная
    table.insertColumn(1, "Tiobe", 7);

    std::string pyplItems[20] = {"Java", "Python", "PHP", "C#", "JavaScript", "C++", "C", "Objective-C", "R", "Swift", "Matlab", "Ruby", "VBA", "Visual Basic", "Scala", "Perl", "lua", "Delphi", "Go", "Haskell"};
    /// Добавлениев колонку с индексом 0, 20 элементов из массива
    table.getColumn(0).appendMultileItems(20, pyplItems);
    /// Добавление одного элемента в колонку 1
    table.getColumn(1).appendItem("Java");
    table.getColumn(1).appendItem("C");
    table.getColumn(1).appendItem("C++");
    table.getColumn(1).appendItem("C#");
    table.getColumn(1).appendItem("Python");
    table.getColumn(1).appendItem("JavaScript");
    table.getColumn(1).appendItem("Assembly");
    /// Вставка одного элемента в колонку 1, в позицию 6
    table.getColumn(1).insertItem("PHP", 6);
    std::string halfTiobeItems[12] = {"VB.NET", "Perl", "Delphi", "Ruby", "Swift", "Objective-C", "Matlab", "Groovy", "Visual Basic", "Ruby", "Go", "PL/SQL"};
    table.getColumn(1).appendMultileItems(12, halfTiobeItems);
    /// Удалить 19 (последний) элемент из 1 колонки
    table.getColumn(1).deleteItem(19);
    /// Удалить последний элемент
    table.getColumn(1).deleteLastItem();
    table.getColumn(1).appendItem(halfTiobeItems[10]);
    table.getColumn(1).appendItem(halfTiobeItems[11]);
    /// Удалить последнюю колонку
    table.deleteLastColumn();
    table.appendColumn("IEEE Trending", 10);


    ///Заполнение остального
    std::string codingDojoItems[9] = {"SQL", "Java", "JavaScript", "C#", "Python", "C++", "PHP", "iOS", "Ruby/Rails"};
    std::string ieeeJobsItems[20] = {"C", "Java", "Python", "C++", "JavaScript", "C#", "PHP", "Ruby", "HTML", "Swift", "Assembly", "Ruby", "Scala", "Shell", "Perl", "SQL", "Objective-C", "Matlab", "Visual Basic", "Go"};
    std::string ieeeOpenItems[20] = {"C++", "Python", "C", "Java", "Swift", "JavaScript", "C#", "Ruby", "PHP", "HTML", "Go", "Scala", "Objective-C", "Shell", "Arduino", "Assembly", "Matlab", "Lua", "Perl"};
    std::string ieeeTrendingItems[20] = {"C", "C++", "Python", "Java", "Swift", "R", "JavaScript", "Ruby", "Go", "C#", "PHP", "Scala", "Arduino", "Assembly", "Shell", "Objective-C", "HTML", "Rust", "Haskell", "Visual Basic"};

    table.getColumn(2).appendMultileItems(9, codingDojoItems);
    table.getColumn(3).appendMultileItems(20, ieeeJobsItems);
    table.getColumn(4).appendMultileItems(20, ieeeOpenItems);
    table.getColumn(5).appendMultileItems(20, ieeeTrendingItems);

    /// Вывод всей таблицы
    table.showTable();

    /// Вывод колонки
    ///table.showColumn(2);
	return 0;
}
