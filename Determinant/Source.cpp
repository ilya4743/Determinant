#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<conio.h>

//Возвращает матрицу matrix без row-ой строки и col-того столбца, результат в matrix
void MatrixWithoutRowAndCol(int **matrix, int size, int row, int col, int **matrix1) 
{
	int d = 0; //Смещение индекса строки в матрице
	int k = 0; //Смещение индекса столбца в матрице
	for (int i = 0; i < size - 1; i++) 
	{
		if (i == row) //Пропустить row-ую строку
			d = 1; //Как только встретили строку, которую надо пропустить, делаем смещение для исходной матрицы
		k = 0; //Обнулить смещение столбца
		for (int j = 0; j < size - 1; j++) 
		{
			if (j == col) //Пропустить col-ый столбец 
				k = 1; //Встретили нужный столбец, проускаем его смещением
			matrix1[i][j] = matrix[i + d][j + k];
		}
	}
}

int determinant(int **matrix, int size)//Вычисление определителя матрицы разложением по первой строке
{
	int det = 0;
	int degree = 1; 
	if (size == 1)   //Условие выхода из рекурсии
		return matrix[0][0];
	else if (size == 2)  //Условие выхода из рекурсии
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	else 
	{  //Матрица без строки и столбца
			int **matrix1 = new int*[size - 1];
			for (int i = 0; i < size - 1; i++) 
				matrix1[i] = new int[size - 1];
			//Раскладываем по 0-ой строке, цикл бежит по столбцам
			for (int j = 0; j < size; j++)
			{
				MatrixWithoutRowAndCol(matrix, size, 0, j, matrix1); //Удалить из матрицы i-ю строку и j-ый столбец
				det = det + (degree * matrix[0][j] * determinant(matrix1, size - 1));   //Рекурсивный вызов
				degree = -degree;
			}
			for (int i = 0; i < size - 1; i++) //чистка памяти
				delete[] matrix1[i];
			delete[] matrix1;
	}
	return det;
}

int main()
{
	int n, c=0;
	while (c != 2)
	{
		printf("Enter n = ");
		scanf("%d", &n);
		printf("Enter elements of matrix[%d][%d]: ", n, n);
		int **matrix = new int*[n];  //создание динамической матрицы
		for (int i = 0; i < n; i++)
			matrix[i] = new int[n];
										
		for (int i = 0; i < n; i++)   //ввод динамической матрицы  
			for (int j = 0; j < n; j++)
				scanf("%d", &matrix[i][j]);

		printf("Determinant = %d", determinant(matrix, n)); //вывод определителя
	
		for (int i = 0; i < n; i++)     // удаление динамической матрицы
			delete[]matrix[i];

		printf("\nEnter 1 to continue or enter 2 to exit: ");
		do { scanf("%d", &c); } while (c != 1 && c != 2);
		printf("\n");
	}
	return 0;
}