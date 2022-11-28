// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц
#include <iostream>
#include "tmatrix.h"

TDynamicMatrix<double> get_matrix(int size_of_matrix)
{
	int choose;
	TDynamicMatrix<double> matrix(size_of_matrix);

	do {
		cout << "All option:\n"
			<< "1 = Random Matrix\n"
			<< "2 = Manual entry\n";
		cin >> choose;
	} while (choose < 1 || choose > 2);

	if (choose == 1)
	{
		for (int i = 0; i < size_of_matrix; i++)
			for (int j = 0; j < size_of_matrix; j++)
				matrix[i][j] = rand() % 100;
		cout << matrix;
	}
	if (choose == 2)
		cin >> matrix;
	return matrix;
}

void calculate(int size)
{
	TDynamicMatrix<double> matrix_1 = get_matrix(size);

	int choose;
	do {
		cout << "All option with Matrix:\n"
			<< "1 = + Matrix\n"
			<< "2 = * Matrix\n"
			<< "3 = - Matrix\n"
			<< "4 = * Vector\n"
			<< "5 = * Matrix and Scalar\n";
		cin >> choose;
	} while (choose < 1 || choose > 5);


	if (choose < 4)
	{
		TDynamicMatrix<double> matrix_2 = get_matrix(size);
		TDynamicMatrix<double> result;

		switch (choose)
		{
		case 1:
			result = matrix_1 + matrix_2;
			break;
		case 2:
			result = matrix_1 * matrix_2;
			break;
		case 3:
			result = matrix_1 - matrix_2;
			break;
		}
		cout << "Result :\n";
		cout << result;
	}
	else if (choose == 4)
	{
		TDynamicVector<double> vector(size);
		cout << "Input Vector:\n";
		cin >> vector;
		cout << "Result :\n";
		cout << matrix_1 * vector;
	}
	else if (choose == 5)
	{
		double num;
		cout << "Enter the number:\n";
		cin >> num;
		cout << "Result :\n";
		cout << matrix_1 * num;
	}
}

void main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Test class Matrix" << endl;

	calculate(5);

}
