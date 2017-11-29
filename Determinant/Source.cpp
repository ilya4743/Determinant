#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<conio.h>

//���������� ������� matrix ��� row-�� ������ � col-���� �������, ��������� � matrix
void MatrixWithoutRowAndCol(int **matrix, int size, int row, int col, int **matrix1) 
{
	int d = 0; //�������� ������� ������ � �������
	int k = 0; //�������� ������� ������� � �������
	for (int i = 0; i < size - 1; i++) 
	{
		if (i == row) //���������� row-�� ������
			d = 1; //��� ������ ��������� ������, ������� ���� ����������, ������ �������� ��� �������� �������
		k = 0; //�������� �������� �������
		for (int j = 0; j < size - 1; j++) 
		{
			if (j == col) //���������� col-�� ������� 
				k = 1; //��������� ������ �������, ��������� ��� ���������
			matrix1[i][j] = matrix[i + d][j + k];
		}
	}
}

int determinant(int **matrix, int size)//���������� ������������ ������� ����������� �� ������ ������
{
	int det = 0;
	int degree = 1; 
	if (size == 1)   //������� ������ �� ��������
		return matrix[0][0];
	else if (size == 2)  //������� ������ �� ��������
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	else 
	{  //������� ��� ������ � �������
			int **matrix1 = new int*[size - 1];
			for (int i = 0; i < size - 1; i++) 
				matrix1[i] = new int[size - 1];
			//������������ �� 0-�� ������, ���� ����� �� ��������
			for (int j = 0; j < size; j++)
			{
				MatrixWithoutRowAndCol(matrix, size, 0, j, matrix1); //������� �� ������� i-� ������ � j-�� �������
				det = det + (degree * matrix[0][j] * determinant(matrix1, size - 1));   //����������� �����
				degree = -degree;
			}
			for (int i = 0; i < size - 1; i++) //������ ������
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
		int **matrix = new int*[n];  //�������� ������������ �������
		for (int i = 0; i < n; i++)
			matrix[i] = new int[n];
										
		for (int i = 0; i < n; i++)   //���� ������������ �������  
			for (int j = 0; j < n; j++)
				scanf("%d", &matrix[i][j]);

		printf("Determinant = %d", determinant(matrix, n)); //����� ������������
	
		for (int i = 0; i < n; i++)     // �������� ������������ �������
			delete[]matrix[i];

		printf("\nEnter 1 to continue or enter 2 to exit: ");
		do { scanf("%d", &c); } while (c != 1 && c != 2);
		printf("\n");
	}
	return 0;
}