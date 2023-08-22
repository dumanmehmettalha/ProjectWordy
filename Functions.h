#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <locale.h>

void AddWord() {

	FILE* filePointer = NULL; // Dosya struct�ndan pointer olu�turuyoruz ve initialize edioruz. 
	fopen_s(&filePointer, "Wordy.txt", "a+"); // fopen fonksiyonuna bu pointer�n adresini, dosya ad�n� ve tipini yolluyoruz.
	
	if (filePointer == NULL) {	// Memoryde bo� yer olmad��� bir anda dosya a��lamayabilir. Ve pointer hata olarak NULL d�nd�r�r. Kullan�c�ya bunu s�ylemek ve baz� fonksiyonlar�n kullan�m�nda hata almamak i�in bu condition kontrol edilir.
		puts("\nFile could not be opened./\\Dosya acilamadi.");
	}
	else { // Dosya a��ld� 
		char newWordEnglish[15];
		char newWordTurkish[15];
		printf("\n%s", "Enter the english word first and then the turkish translate of it.\n");
		scanf_s("%s %s", newWordEnglish, _countof(newWordEnglish), newWordTurkish, _countof(newWordTurkish)); // scanf_s hatas�z kullan�m�
		

		// BUNUNLA �LG�LENMEM GEREKL� ! 
		/*gets_s(newWordEnglish, sizeof(newWordEnglish));

		int c = 0;
		while ((c = getchar()) != "\n" && c != EOF) { break; }

		printf("Turkish Word:");
		gets_s(newWordTurkish, 15);
		
		c = 0;
		while ((c = getchar()) != "\n" && c != EOF) { break; }*/

		fprintf(filePointer, "%s-%s", newWordEnglish, newWordTurkish);
		fprintf(filePointer, "\n");
		fclose(filePointer);
	}
}

void DeleteData(char word[15]) {

	FILE* fp;  //r+ modunda dosya a��ld� ��nk� ba�tan sona bak�l�p silinmek istenen kelime bulunacak ve �zerine bo�luk yaz�lacak.
	char temp[15];
	long int pos;
	errno_t err = fopen_s(&fp, "Wordy.txt", "r+");
	if (err != 0) {
		printf("%s", "\nFile could not be opened.");
		return;
	}

	while (!feof(fp)) {
		fscanf_s(fp, "%s", temp, sizeof(temp));
		// printf("temp: %s", temp);
		if (strcmp(temp, word) == 0) {
			pos = ftell(fp) - strlen(word); // silinecek kelimeden sonraki konum bilgisi ** pos- kelime boyutu yap�larak kelimenin silinece�i konum bulunabilir.
			//printf("%ld", pos);
			fseek(fp, pos, SEEK_SET); //imleci dosyan�n ba��ndan pos kadar ilerletir.
			fprintf(fp, "%*s", strlen(temp), "");
			printf_s("\nThe word you have entered have just deleted.\n");
			break;
		}
	}
	if (strcmp(temp, word) != 0) 
	{
		printf_s("\nThe word you have entered is not in the text file.\n");
	}

	fclose(fp);
}

void ShowFile() {

	FILE* fp;


	errno_t err = fopen_s(&fp, "Wordy.txt", "r"); // Okunacak dosyan�n ad�n� do�ru �ekilde belirtin
	if (err != 0) {
		printf("%s", "\nFile could not be opened.");
		return 1; // Program� hata kodu ile sonland�r
	}

	char line[100]; // Bir sat�r�n maksimum uzunlu�unu belirtin
	while (fgets(line, sizeof(line), fp) != NULL) {
		printf("%s", line);
	}
	fclose(fp);
}

void Instructions(int* userInput)
{	
//	setlocale(LC_ALL, ".utf8");
	printf("\n%s", "If you want to enter a word to program press 1,\nBir kelime eklemek istiyorsan�z 1 giriniz,\n\n");
	printf("%s", "If you want to delete a word from program press 2,\nBir kelime silmek istiyorsan�z 2 giriniz,\n\n");
	printf("%s", "If you want to see all of the words press 3,\nProgramdaki t�m kelimeleri g�rmek istiyorsan�z 3 giriniz,\n\n");
	printf("%s", "If you want to terminate the program press 4\nProgram� sonland�rmak istiyorsan�z 4 giriniz,\n\nChoice/Se�im: ");
	scanf_s("%d", userInput);
}



void Execute() {
	int userInput = 0;
	char word[15];
	while (4 != userInput)
	{
		Instructions(&userInput);
		switch (userInput)
		{
		case 1:
			AddWord();
			userInput = 0;
			break;
		case 2:
			printf("%s", "\nEnter a word you want to delete:  ");
			scanf_s("%s", word, sizeof(word));
			DeleteData(word);
			userInput = 0;
			break;
		case 3:
			puts("");
			ShowFile();
			puts("");
			userInput = 0;
			break;
		case 4:
			printf("%s", "\nSee you again./Gorusuruz.\n");
			break;
		default:
			printf("%s", "\nInvalid Choise!/\\Hatali Secim!\n");
			userInput = 4;
			break;
		}
	}
}