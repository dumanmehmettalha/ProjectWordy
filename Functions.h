#include <stdio.h>
#include <stdlib.h>

void AddWord() {
	FILE* filePointer = NULL; // Dosya structýndan pointer oluþturuyoruz ve initialize edioruz. 
	fopen_s(&filePointer, "Wordy.txt", "a+"); // fopen fonksiyonuna bu pointerýn adresini, dosya adýný ve tipini yolluyoruz.
	
	if (filePointer == NULL) {	// Memoryde boþ yer olmadýðý bir anda dosya açýlamayabilir. Ve pointer hata olarak NULL döndürür. Kullanýcýya bunu söylemek ve bazý fonksiyonlarýn kullanýmýnda hata almamak için bu condition kontrol edilir.
		puts("File could not be opened./\\Dosya acilamadi.");
	}
	else { // Dosya açýldý 
		char newWordEnglish[15];
		char newWordTurkish[15];
		printf("%s", "Enter the english word first and then the turkish translate of it.\n:");

		scanf_s("%s %s", newWordEnglish, _countof(newWordEnglish), newWordTurkish, _countof(newWordTurkish)); // scanf_s hatasýz kullanýmý


		fprintf(filePointer, "%s --> %s\n", newWordEnglish, newWordTurkish);
		fclose(filePointer);
	}
	

}

void Execute() {

	
		AddWord();
		printf("When you enter (^Z) program will be terminated.");
	
}