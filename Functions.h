#include <stdio.h>
#include <stdlib.h>

void AddWord() {
	FILE* filePointer = NULL; // Dosya struct�ndan pointer olu�turuyoruz ve initialize edioruz. 
	fopen_s(&filePointer, "Wordy.txt", "a+"); // fopen fonksiyonuna bu pointer�n adresini, dosya ad�n� ve tipini yolluyoruz.
	
	if (filePointer == NULL) {	// Memoryde bo� yer olmad��� bir anda dosya a��lamayabilir. Ve pointer hata olarak NULL d�nd�r�r. Kullan�c�ya bunu s�ylemek ve baz� fonksiyonlar�n kullan�m�nda hata almamak i�in bu condition kontrol edilir.
		puts("File could not be opened./\\Dosya acilamadi.");
	}
	else { // Dosya a��ld� 
		char newWordEnglish[15];
		char newWordTurkish[15];
		printf("%s", "Enter the english word first and then the turkish translate of it.\n:");

		scanf_s("%s %s", newWordEnglish, _countof(newWordEnglish), newWordTurkish, _countof(newWordTurkish)); // scanf_s hatas�z kullan�m�


		fprintf(filePointer, "%s --> %s\n", newWordEnglish, newWordTurkish);
		fclose(filePointer);
	}
	

}

void Execute() {

	
		AddWord();
		printf("When you enter (^Z) program will be terminated.");
	
}