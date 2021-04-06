#include <iostream>
#include <random>
#include <ctime>

using namespace std;

extern "C" {

	const int size = 5;
	int tempSize = size;

	int newArray[size];

	int array[size][size];
};

int main()
{
	srand(time(0));	

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			array[i][j] = 0 + rand() % 10;
		}
	}

	__asm
	(
	R"(
		.intel_syntax noprefix
		;//{
		mov esi, 0				;// этот регистр будет хранить адрес элементов одномерного массива	
		mov ecx, 0				;// этот регистр будет указывать адрес элементов двумерного массива
		mov dl, 0				;// этот регистр будет считать количество пройденных строк

			StartNewLine:
		mov dh, 0				;// этот регистр считает количество пройденных элементов массива
		mov ebx, 0	            ;// сюда будем класть макс элемент

			Main:
		mov eax, array[ecx]	    ;// здесь будет лежать текущий (проверяемый) элемент	
		cmp eax, ebx
		jg MaxElement

		jmp Incrementing

			MaxElement:
		mov ebx, eax

			Incrementing:
		add ecx, 4
		add dh, 1

			CheckEndLine:
		cmp dh, BYTE PTR tempSize
		jl Main

		mov newArray[esi], ebx
		add esi, 4

			CheckEndArray:
		add dl, 1
		cmp dl, BYTE PTR tempSize
		jl StartNewLine
	;//}
	.att_syntax
	)"
	);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << array[i][j] << " ";
		}
		cout << endl;
	}

	cout << "_________" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << newArray[i] << " ";
	}
	cout << endl;

	return 0;
}
