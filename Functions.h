#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#define BLUE 1
#define GREEN 2
#define LIGHT_BLUE 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHT_GREEN 10
#define TURKUAZ 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define EX_WHITE 15

void SetConsoleTextColor(int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void HideTheFile() {
	const char* filePath = "Wordy.txt";
	HANDLE fileHandle = CreateFileA(filePath, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	if (fileHandle == INVALID_HANDLE_VALUE) {
		perror("CreateFile failed");
		return 1;
	}

	FILE_BASIC_INFO fileInfo;
	GetFileInformationByHandleEx(fileHandle, FileBasicInfo, &fileInfo, sizeof(fileInfo));

	fileInfo.FileAttributes |= FILE_ATTRIBUTE_HIDDEN;

	if (!SetFileInformationByHandle(fileHandle, FileBasicInfo, &fileInfo, sizeof(fileInfo))) {
		perror("SetFileInformationByHandle failed");
		CloseHandle(fileHandle);
		return 1;
	}

	CloseHandle(fileHandle);

	//printf("File hidden successfully.\n");
}

void AddWord() {

	FILE* filePointer = NULL; // Dosya structýndan pointer oluþturuyoruz ve initialize edioruz. 
	fopen_s(&filePointer, "Wordy.txt", "a+"); // fopen fonksiyonuna bu pointerýn adresini, dosya adýný ve tipini yolluyoruz.
	if (filePointer == NULL) {	// Memoryde boþ yer olmadýðý bir anda dosya açýlamayabilir. Ve pointer hata olarak NULL döndürür. Kullanýcýya bunu söylemek ve bazý fonksiyonlarýn kullanýmýnda hata almamak için bu condition kontrol edilir.
		SetConsoleTextColor(RED);
		puts("\nFile could not be opened./\\Dosya acilamadi.");
	}
	else { // Dosya açýldý 
		char newWordEnglish[15];
		char newWordTurkish[15];
		printf("\n%s", "Enter the english word first and then the turkish translate of it.\n");
		SetConsoleTextColor(YELLOW);
		scanf_s("%s %s", newWordEnglish, _countof(newWordEnglish), newWordTurkish, _countof(newWordTurkish)); // scanf_s hatasýz kullanýmý

		fprintf(filePointer, "%s - %s", newWordEnglish, newWordTurkish);
		fprintf(filePointer, "\n");
		fclose(filePointer);
	
	}
}

void DeleteData(int val) {

	FILE* fp;
	FILE* temp;
	errno_t err = fopen_s(&temp,"temp.txt", "w+");  //r+ modunda dosya açýldý çünkü baþtan sona bakýlýp silinmek istenen kelime bulunacak ve üzerine boþluk yazýlacak.
	errno_t err2 = fopen_s(&fp, "Wordy.txt", "r+");
	char line[100];
	char tLine[100];
	int counter = 0, i = 0;
	if (err != 0 || err2 != 0) {
		SetConsoleTextColor(RED);
		printf("%s", "\nFile could not be opened.");
		return;
	}

	while (fgets(line, sizeof(line), fp) != NULL) {
		counter++;
		if (counter != val) {
			fprintf(temp, "%s", line);

		}

	}
	SetConsoleTextColor(7);
	SetConsoleTextColor(RED);
	printf("The line you have selected is deleted.\n");
	fclose(fp);
	fclose(temp);
	remove("Wordy.txt");
	rename("temp.txt", "Wordy.txt");
}

void ShowFile() {

	FILE* fp;
	int counter = 0;
	SetConsoleTextColor(TURKUAZ);
	errno_t err = fopen_s(&fp, "Wordy.txt", "r"); // Okunacak dosyanýn adýný doðru þekilde belirtin
	if (err != 0) {
		printf("%s", "\nFile could not be opened.");
		return 1; // Programý hata kodu ile sonlandýr
	}

	char line[100]; // Bir satýrýn maksimum uzunluðunu belirtin
	while (fgets(line, sizeof(line), fp) != NULL) {
		printf("%d - %s", ++counter,line);
	}
	fclose(fp);
}


void Instructions(int* userInput)
{	
	//SetConsoleTextColor(2);
	//printf("%s", "If you want to enter a word to program press 1,\n");
	//printf("%s", "Bir kelime eklemek istiyorsaniz 1 giriniz,\n\n");
	//printf("%s", "If you want to delete a word from program press 2,\n");
	//printf("%s", "Bir kelime silmek istiyorsaniz 2 giriniz, \n\n");
	//printf("%s", "If you want to see all of the words press 3,\n");
	//printf("%s", "Programdaki tum kelimeleri gormek istiyorsaniz 3 giriniz,\n\n");
	//printf("%s", "If you want to terminate the program press 4\n");
	//printf("%s", "Programi sonlandirmak istiyorsaniz 4 giriniz, \n\n");
	//SetConsoleTextColor(7);
	//printf("Choice/Secim: ");
	//scanf_s("%d", userInput);


	SetConsoleTextColor(GREEN);
	printf("%s", "1. Add word");
	SetConsoleTextColor(PURPLE);
	printf("%s", "    - Kelime ekle\n");
	SetConsoleTextColor(GREEN);
	printf("%s", "2. Delete word");
	SetConsoleTextColor(PURPLE);
	printf("%s", " - Kelime sil\n");
	SetConsoleTextColor(GREEN);
	printf("%s", "3. All words");
	SetConsoleTextColor(PURPLE);
	printf("%s", "   - Tum kelimeler\n");
	SetConsoleTextColor(GREEN);
	printf("%s", "4. Terminate");
	SetConsoleTextColor(PURPLE);
	printf("%s", "   - Sonlandir.\n");
	SetConsoleTextColor(EX_WHITE);
	printf("Choice/Secim: ");
	SetConsoleTextColor(RED);
	scanf_s("%d", userInput);
}



void Execute() {

	SetConsoleTextColor(LIGHT_YELLOW);
	printf("%s\n", "WELCOME TO THE WORDY!!!");
	int userInput = 0;
	char word[15];
	int val;
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
			SetConsoleTextColor(3);
			printf("Enter line number you want to delete:  ");
			scanf_s("%d", &val);
			DeleteData(val);
			userInput = 0;
			break;
		case 3:
			puts("");
			ShowFile();
			puts("");
			userInput = 0;
			break;
		case 4:
			SetConsoleTextColor(4);
			printf("%s", "\nSee you again./Gorusuruz.\n");
			SetConsoleTextColor(WHITE);
			break;
		default:
			SetConsoleTextColor(4);
			printf("%s", "\nInvalid Choise!/\\Hatali Secim!\n");
			SetConsoleTextColor(WHITE);
			userInput = 4;
			break;
		}
	}
	HideTheFile();
}