#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <locale.h>

void AddWord() {

	FILE* filePointer = NULL; // Dosya structýndan pointer oluþturuyoruz ve initialize edioruz. 
	fopen_s(&filePointer, "Wordy.txt", "a+"); // fopen fonksiyonuna bu pointerýn adresini, dosya adýný ve tipini yolluyoruz.
	
	if (filePointer == NULL) {	// Memoryde boþ yer olmadýðý bir anda dosya açýlamayabilir. Ve pointer hata olarak NULL döndürür. Kullanýcýya bunu söylemek ve bazý fonksiyonlarýn kullanýmýnda hata almamak için bu condition kontrol edilir.
		puts("\nFile could not be opened./\\Dosya acilamadi.");
	}
	else { // Dosya açýldý 
		char newWordEnglish[15];
		char newWordTurkish[15];
		printf("\n%s", "Enter the english word first and then the turkish translate of it.\n");
		scanf_s("%s %s", newWordEnglish, _countof(newWordEnglish), newWordTurkish, _countof(newWordTurkish)); // scanf_s hatasýz kullanýmý
		

		// BUNUNLA ÝLGÝLENMEM GEREKLÝ ! 
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

	FILE* fp;  //r+ modunda dosya açýldý çünkü baþtan sona bakýlýp silinmek istenen kelime bulunacak ve üzerine boþluk yazýlacak.
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
			pos = ftell(fp) - strlen(word); // silinecek kelimeden sonraki konum bilgisi ** pos- kelime boyutu yapýlarak kelimenin silineceði konum bulunabilir.
			//printf("%ld", pos);
			fseek(fp, pos, SEEK_SET); //imleci dosyanýn baþýndan pos kadar ilerletir.
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


	errno_t err = fopen_s(&fp, "Wordy.txt", "r"); // Okunacak dosyanýn adýný doðru þekilde belirtin
	if (err != 0) {
		printf("%s", "\nFile could not be opened.");
		return 1; // Programý hata kodu ile sonlandýr
	}

	char line[100]; // Bir satýrýn maksimum uzunluðunu belirtin
	while (fgets(line, sizeof(line), fp) != NULL) {
		printf("%s", line);
	}
	fclose(fp);
}

void Instructions(int* userInput)
{	
//	setlocale(LC_ALL, ".utf8");
	printf("\n%s", "If you want to enter a word to program press 1,\nBir kelime eklemek istiyorsanýz 1 giriniz,\n\n");
	printf("%s", "If you want to delete a word from program press 2,\nBir kelime silmek istiyorsanýz 2 giriniz,\n\n");
	printf("%s", "If you want to see all of the words press 3,\nProgramdaki tüm kelimeleri görmek istiyorsanýz 3 giriniz,\n\n");
	printf("%s", "If you want to terminate the program press 4\nProgramý sonlandýrmak istiyorsanýz 4 giriniz,\n\nChoice/Seçim: ");
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