#include <iostream>
// Gabriel Augusto Ribeiro Gomes              32134762
// Paulo Henrique Braga Cechinel              32151128
// Ricardo Gabriel Marques dos Santos Ruiz    31234908
//#define TEST_MODE

void printSolution(double* array, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << "X" << i + 1 << " : " << array[i] << std::endl;
	}
}
void printMatrix(double** matrix, int lines, int columns)
{
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void elimination(double** matrix, int lines, int columns)
{
	int c;
	for (int i = 0; i < lines - 1; i++)
	{
		// Pivotamento
		for (int k = i + 1; k < lines; k++)
		{
			// Se o elemento da diagonal for menor que os termos dele, fazer a troca de linhas, colunas ou ambas
			if (matrix[i][i] < matrix[k][i])
			{
				for (int j = 0; j < columns; j++)
				{
					double temp = matrix[i][j];
					matrix[i][j] = matrix[k][j];
					matrix[k][j] = temp;
				}
			}
		}
		// Eliminação de Gauss
		for (int k = i + 1; k < lines; k++)
		{
			double term = matrix[k][i] / matrix[i][i];
			for (int j = 0; j < columns; j++)
			{
				matrix[k][j] = matrix[k][j] - term * matrix[i][j];
			}
		}
	}
}
void appendBintoMatrix(double** matrix, double* b, int lines, int columns)
{
	for (int i = 0; i < lines; i++)
	{
		matrix[i][columns] = b[i];
	}
}

void mockMatrix(double** matrix)
{
	matrix[0][0] = 1;
	matrix[0][1] = -1;
	matrix[0][2] = 2;
	matrix[0][3] = -1;

	matrix[1][0] = 2;
	matrix[1][1] = -2;
	matrix[1][2] = 3;
	matrix[1][3] = -3;

	matrix[2][0] = 1;
	matrix[2][1] = 1;
	matrix[2][2] = 1;
	matrix[2][3] = 0;

	matrix[3][0] = 1;
	matrix[3][1] = -1;
	matrix[3][2] = 4;
	matrix[3][3] = 3;
}
void mockB(double* b)
{
	b[0] = -8;
	b[1] = -20;
	b[2] = -2;
	b[3] = 4;
}
void fillMatrix(double** matrix, int lines, int columns)
{
	for (int i = 0; i < lines; i++)
	{
		std::cout << "Digite a linha " << i + 1 << " da matriz: " << std::endl;
		std::cin.clear();
		for (int j = 0; j < columns; j++)
		{
			double value;
			std::cin >> value;
			matrix[i][j] = value;
		}
	}
}
void fillB(double* b, int lines)
{
	std::cout << "Digite os valores de B: " << std::endl;
	for (int i = 0; i < lines; i++)
	{
		std::cin.clear();
		double value;
		std::cin >> value;
		b[i] = value;
	}
}

// Back Substitution : https://www.youtube.com/watch?v=9udkLTr0sgA
void solveTriangularSystem(double** matrix, int matrixOrder, double* outputArray)
{

	// Devemos começar pela última equação (i = N-1 - ultimo elemento)
	for (int i = matrixOrder - 1; i >= 0; i--)
	{
		// Ax = b
		outputArray[i] = matrix[i][matrixOrder];

		// J = i+1 (sistema triangular)
		for (int j = i + 1; j < matrixOrder; j++)
		{
			outputArray[i] -= matrix[i][j] * outputArray[j];
		}
		outputArray[i] = outputArray[i] / matrix[i][i];
	}
}
int main()
{
	int lines;
	int columns;
#ifndef TEST_MODE
	std::cout << "Digite a ordem da matrix: ";
	std::cin >> lines;
	columns = lines;
#else
	lines = 4;
	columns = 4;
#endif
	// Create the matrix and B with given values
	double** matrix = new double* [lines];
	for (int i = 0; i < lines; i++)
	{
		matrix[i] = new double[columns + 1];
	}
	double* b = new double[lines];
#ifndef TEST_MODE
	fillMatrix(matrix, lines, columns);
	fillB(b, lines);
#else
	mockMatrix(matrix);
	mockB(b);
#endif
	appendBintoMatrix(matrix, b, lines, columns);
	elimination(matrix, lines, columns + 1);
	std::cout << "Sistema triangular: " << std::endl;
	printMatrix(matrix, lines, columns + 1);
	double* output = new double[lines];
	solveTriangularSystem(matrix, lines, output);
	std::cout << std::endl << "Solucao: " << std::endl;
	printSolution(output, lines);
}