#ifndef SIMPLETABLE_H
#define SIMPLETABLE_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <exception>

template <typename T>
class SimpleTable
{
	private:
		class Column;
	public:
		enum Width{MANUAL, BY_AVERAGE, BY_MAX};

		// ������������
		explicit SimpleTable(const char verticalSeparator = '|', const char horizontalSeparator = '-', const char cornerSeparator = '+');

		// ���������� ������� � �����
		void appendMultipleColumns(int n, std::string * columnNames, Width width); // �������� ����� ��������� ������� � ����� �������, ������ AUTO
		void appendMultipleColumns(int n, std::string * columnNames, int * columnWidths); // �������� ����� ��������� ������� � ����� �������, ������ MANUAL
		void appendColumn(std::string columnName, Width width); // �������� ���� ������� � ����� �������, ������ AUTO
		void appendColumn(std::string columnName, int columnWidth); // �������� ���� ������� � ����� �������, ������ MANUAL

		// ���������� ������� � ������������ �����
		void insertMultileColumns(int index, int n, std::string * columnNames, Width width) throw(std::out_of_range); // �������� ��������� ������� � ������� ������� � INDEX, ������ AUTO
		void insertMultileColumns(int index, int n, std::string * columnNames, int * columnWidths) throw(std::out_of_range); // �������� ��������� ������� � ������� ������� � INDEX, ������ MANUAL
		void insertColumn(int index, std::string columnName, Width width) throw(std::out_of_range); // �������� ������� � ������� � ��������� INDEX, ������ AUTO
		void insertColumn(int index, std::string columnName, int columnWidth) throw(std::out_of_range); // �������� ������� � ������� � ��������� INDEX, ������ MANUAL

		// �����
		void showTable() const throw(std::out_of_range); // �������� ��� �������
		void showColumn(int index) const throw(std::out_of_range); // �������� ������� � �������� INDEX
		void showRow(int index) const throw(std::out_of_range); // �������� ������ � �������� INDEX

		// �������� � �������
		Column & getColumn(int index) throw (std::out_of_range);
		Column & getLastColumn();

		// �������� �������
		void deleteLastColumn(); // ������� ��������� ������� � �������
		void deleteColumn(int index)  throw(std::out_of_range); // ������� ������� � �������� INDEX

		// ��������� ��������
		int getNumberOfColumns() const;
		void setNumberOfColumns(int n);
		int getNumberOfRows() const;
		void setNumberOfRows(int n);
	private:
		int numberOfColumns; // ���������� ������� � �������
		int numberOfRows; // ���������� ����� � �������

		// �����������
		const char cornerSeparator;
		const char verticalSeparator;
		const char horizontalSeparator;

		// ����� ����� �������
		class Column
		{
		    public:
		    	// ������������
		    	Column(SimpleTable * tableReference, std::string name, Width widthFormat = Width::BY_AVERAGE);
		    	Column(SimpleTable * tableReference, std::string name, int width);

		    	// ���������� ��������� � �����
		    	void appendMultileItems(int n, T * items); // �������� ��������� ��������� � �����
		    	void appendItem(T item); // �������� ������� � ����� �������

		    	// ���������� ��������� � ������������ �����
		    	void insertMultipleItems(int index, int n, T * items); // �������� ��������� ��������� � �������, ������� � INDEX
		    	void insertItem(T item, int index) throw(std::out_of_range); // �������� ������� � ������� INDEX

		    	// �������� �������� �� �������
		    	void deleteItem(int index) throw(std::out_of_range); // ������� ������� �� ������� INDEX
		    	void deleteLastItem(); // ������� ��������� ������� �������

		    	// �����
		    	bool showItem(int index) const; // ������� ������� INDEX
		    	void show() const; // ������� ���� �������

		    	// ��������� � ���������
		    	const T & getItem(int index) throw(std::out_of_range); // �������� ������� � �������� INDEX
		    	void setItem(int index, T data) throw(std::out_of_range); // �������� � ������� INDEX �������� DATA

		    	// ��������� ������ �������
				int getWidth() const;

				// �������� ��� �������
				std::string getName() const;
				void setName(std::string name);
			private:
				std::string name; // ��� �������
				std::vector<T> items; // �������� � �������
				int width; // ������ �������
				Width widthFormat; // �� ��� ����� ������������� ������ �������
				SimpleTable * tableReference;

				// ��������� ������ �������
				void setWidth();

				void drawOneColumnLine() const;
		};

		// ������ �������
		std::vector<SimpleTable<T>::Column> columns;

		// ��������� �������������� ���������
		void drawLine() const;
		void drawTitle() const;
};

template <typename T>
SimpleTable<T>::SimpleTable(
						    const char verticalSeparator, const char horizontalSeparator, const char cornerSeparator)
						     : numberOfColumns(0), numberOfRows(0), cornerSeparator(cornerSeparator),
						    verticalSeparator(verticalSeparator), horizontalSeparator(horizontalSeparator)
{}

template <typename T>
SimpleTable<T>::Column::Column(
							   SimpleTable * tableReference, std::string name, Width widthFormat)
							    : name(name), widthFormat(widthFormat), tableReference(tableReference) { setWidth(); }

template <typename T>
SimpleTable<T>::Column::Column(
							   SimpleTable * tableReference, std::string name, int width)
							    : name(name), widthFormat(Width::MANUAL), width(width), tableReference(tableReference) { setWidth(); }

template <typename T>
void SimpleTable<T>::Column::appendItem(T item)
{
	items.push_back(item);
    setWidth();
    if(items.size() > tableReference->getNumberOfRows())
	{
		tableReference->setNumberOfRows(items.size());
	}
}

template <typename T>
void SimpleTable<T>::drawLine() const
{
	std::cout << cornerSeparator;
	for(const auto & column : columns)
	{
		std::cout << horizontalSeparator;
		for(int i = 0; i < column.getWidth(); ++i)
		{
			std::cout << horizontalSeparator;
		}
		std::cout << horizontalSeparator;
	}
	for(int i = 0; i < columns.size() - 1; ++i)
    {
        std::cout << horizontalSeparator;
    }
	std::cout << cornerSeparator << std::endl;
}

template <typename T>
void SimpleTable<T>::drawTitle() const
{
	drawLine();
	for(const auto & column : columns)
	{
		std::cout << verticalSeparator << ' ';
		if(column.getName().length() > column.getWidth()) {
			for(int i = 0; i < column.getWidth() - 1; ++i)
			{
				std::cout << column.getName()[i];
			}
			std::cout << '*' << ' ';
		}
		else
		{
			std::cout.width(column.getWidth());
            std::cout.setf(std::ios::left);
			std::cout << column.getName() << ' ';
		}
	}
	std::cout << verticalSeparator << std::endl;
	drawLine();
}

template <typename T>
typename SimpleTable<T>::Column & SimpleTable<T>::getColumn(int index) throw(std::out_of_range)
{
	if(index < 0 || index >= getNumberOfColumns()) {
	    throw std::out_of_range("index < 0 || index >= numberOfColumns");
	}
	return columns.at(index);
}

template <typename T>
typename SimpleTable<T>::Column & SimpleTable<T>::getLastColumn()
{
	return columns.at(getNumberOfColumns()-1);
}

template <typename T>
std::string SimpleTable<T>::Column::getName() const
{
	return name;
}

template <typename T>
const T & SimpleTable<T>::Column::getItem(int index) throw(std::out_of_range)
{
	if(index < 0 || index >= items.size()) {
	    throw std::out_of_range("index < 0 || index >= numberOfItems");
	}
	return items.at(index);
}

template <typename T>
void SimpleTable<T>::Column::setItem(int index, T data) throw(std::out_of_range)
{
	if(index < 0 || index >= items.size()) {
	    throw std::out_of_range("index < 0 || index >= numberOfItems");
	}
	items.at(index) = data;
    setWidth();
}

template <typename T>
int SimpleTable<T>::Column::getWidth() const
{
	return width;
}

template<typename T>
void SimpleTable<T>::Column::appendMultileItems(int n, T * items)
{
    for(int i = 0; i < n; ++i)
    {
        appendItem(items[i]);
    }
}

template <typename T>
void SimpleTable<T>::Column::insertItem(T item, int index) throw(std::out_of_range)
{
	if(index < 0 || index >= items.size()) {
	    throw std::out_of_range("index < 0 || index >= numberOfItems");
	}
    items.insert(items.begin() + index, item);
    setWidth();
    if(items.size() > tableReference->getNumberOfRows())
	{
		tableReference->setNumberOfRows(items.size());
	}
}

template <typename T>
void SimpleTable<T>::Column::insertMultipleItems(int index, int n, T * items)
{
	for(int i = 0; i < n; ++i)
	{
	    insertItem(items[i], index + i);
	}
    setWidth();
}

template <typename T>
void SimpleTable<T>::Column::deleteItem(int index) throw(std::out_of_range)
{
	if(index < 0 || index >= items.size())
	    throw std::out_of_range("index < 0 || index >= numberOfItems");
    int temp = items.size();
	items.erase(items.begin() + index);
    setWidth();
    int MAX = 0;
    for(int i = 0; i < tableReference->getNumberOfColumns(); ++i)
    {
        if (MAX < tableReference->getColumn(i).items.size())
            MAX = tableReference->getColumn(i).items.size();
    }
    if(temp > MAX)
	{
		tableReference->setNumberOfRows(items.size());
	}
}

template <typename T>
void SimpleTable<T>::Column::deleteLastItem()
{
    deleteItem(items.size() - 1);
}

template <typename T>
bool SimpleTable<T>::Column::showItem(int index) const
{
	if(index < 0 || index >= items.size())
	    return false;

	/// ������� � ������
    std::ostringstream sstream;
    sstream << items.at(index);
    std::string varString = sstream.str();

	if(varString.length() > getWidth())
	{
		for(int i = 0; i < getWidth() - 1; ++i)
		{
			std::cout << varString[i];
		}
		std::cout << '*';
	}
	else
	{
		std::cout.width(getWidth());
		std::cout.setf(std::ios::left);
		std::cout << varString;
	}
	return true;
}

template <typename T>
void SimpleTable<T>::Column::show() const
{
    drawOneColumnLine();
    std::cout << tableReference->verticalSeparator << ' ';
    std::cout.width(getWidth());
    std::cout.setf(std::ios::left);
    std::cout << getName();
    std::cout << ' ' << tableReference->verticalSeparator << std::endl;
	drawOneColumnLine();
    for(int i = 0; i < items.size(); ++i)
    {
        std::cout << tableReference->verticalSeparator << ' ';
        showItem(i);
        std::cout << ' ' << tableReference->verticalSeparator << std::endl;
    }
	drawOneColumnLine();
}

template <typename T>
void SimpleTable<T>::deleteColumn(int index) throw(std::out_of_range)
{
	if(index < 0 || index >= numberOfColumns) {
	    throw std::out_of_range("index < 0 || index >= numberOfColumns");
	}
	columns.erase(columns.begin() + index);
	numberOfColumns--;
}

template <typename T>
void SimpleTable<T>::deleteLastColumn()
{
	columns.pop_back();
	numberOfColumns--;
}

template <typename T>
void SimpleTable<T>::showColumn(int index) const throw(std::out_of_range)
{
	if(index < 0 || index >= numberOfColumns) {
	    throw std::out_of_range("index < 0 || index >= numberOfColumns");
	}
	columns.at(index).show();
}

template <typename T>
void SimpleTable<T>::showRow(int index) const throw(std::out_of_range)
{
	if(index < 0 || index >= numberOfRows) {
	    throw std::out_of_range("index < 0 || index >= numberOfRows");
	}
	for(const auto & column : columns)
	{
		std::cout << verticalSeparator << ' ';
		if(column.showItem(index))
		{
			std::cout << ' ';
		}
		else
		{
		    std::cout.width(column.getWidth());
			std::cout << ' ' << ' ';
		}
	}
	std::cout << verticalSeparator << std::endl;
}

template <typename T>
void SimpleTable<T>::showTable() const throw(std::out_of_range)
{
	drawTitle();
	for(int i = 0; i < getNumberOfRows(); ++i)
	{
		showRow(i);
	}
	drawLine();
}

template <typename T>
void SimpleTable<T>::insertColumn(int index, std::string columnName, int columnWidth) throw(std::out_of_range)
{
	if(index < 0 || index >= numberOfColumns) {
	    throw std::out_of_range("index < 0 || index >= numberOfColumns");
	}
	Column column(this, columnName, columnWidth);
	columns.insert(columns.begin() + index, column);
	numberOfColumns++;
}

template <typename T>
void SimpleTable<T>::insertColumn(int index, std::string columnName, Width width) throw(std::out_of_range)
{
	if(index < 0 || index >= numberOfColumns) {
	    throw std::out_of_range("index < 0 || index >= numberOfColumns");
	}
	Column column(this, columnName, width);
	columns.insert(columns.begin() + index, column);
	numberOfColumns++;
}

template <typename T>
void SimpleTable<T>::insertMultileColumns(int index, int n, std::string * columnNames, int * columnWidths) throw(std::out_of_range)
{
    for(int i = 0; i < n; ++i)
	{
	    insertColumn(index + i, columnNames[i], columnWidths[i]);
	}
}

template <typename T>
void SimpleTable<T>::insertMultileColumns(int index, int n, std::string * columnNames, Width width) throw(std::out_of_range)
{
	for(int i = 0; i < n; ++i)
	{
	    insertColumn(index + i, columnNames[i], width);
	}
}

template <typename T>
void SimpleTable<T>::appendColumn(std::string columnName, int columnWidth)
{
	Column column(this, columnName, columnWidth);
	columns.push_back(column);
	numberOfColumns++;
}

template <typename T>
void SimpleTable<T>::appendColumn(std::string columnName, Width width)
{
	Column column(this, columnName, width);
	columns.push_back(column);
	numberOfColumns++;
}

template <typename T>
void SimpleTable<T>::appendMultipleColumns(int n, std::string * columnNames, int * columnWidths)
{
	for(int i = 0; i < n; ++i)
	{
	    appendColumn(columnNames[i], columnWidths[i]);
	}
}

template <typename T>
void SimpleTable<T>::appendMultipleColumns(int n, std::string * columnNames, Width width)
{
	for(int i = 0; i < n; ++i)
	{
		appendColumn(columnNames[i], width);
	}
}

template <typename T>
int SimpleTable<T>::getNumberOfColumns() const
{
    return numberOfColumns;
}

template <typename T>
int SimpleTable<T>::getNumberOfRows() const
{
    return numberOfRows;
}

template <typename T>
void SimpleTable<T>::setNumberOfColumns(int n)
{
    numberOfColumns = n;
}

template <typename T>
void SimpleTable<T>::setNumberOfRows(int n)
{
    numberOfRows = n;
}

template <typename T>
void SimpleTable<T>::Column::setWidth()
{
    if(widthFormat == Width::MANUAL) {
        return;
    }
    int Max = 1, Average = 0;
    for(const auto & item : items)
    {
        /// ������� � ������
        std::ostringstream sstream;
        sstream << item;
        std::string varString = sstream.str();

        Max = (varString.length() > Max) ? varString.length() : Max;
        Average += varString.length();
    }
    Average += getName().length();
    Max = (getName().length() > Max) ? getName().length() : Max;
    Average /= items.size() + 1;
    width = (widthFormat == BY_AVERAGE) ? Average : Max;
}

template <typename T>
void SimpleTable<T>::Column::setName(std::string name)
{
    (*this).name = name;
}

template <typename T>
void SimpleTable<T>::Column::drawOneColumnLine() const
{
	std::cout << tableReference->cornerSeparator << tableReference->horizontalSeparator;
    for(int i = 0; i < getWidth(); ++i)
    {
        std::cout << tableReference->horizontalSeparator;
    }
	std::cout << tableReference->horizontalSeparator << tableReference->cornerSeparator << std::endl;
}

#endif
