#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

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

		fprintf(filePointer, "%s - %s", newWordEnglish, newWordTurkish);
		fprintf(filePointer, "\n");
		fclose(filePointer);
	
	}
}

void DeleteData(int val) {

	FILE* fp;
	FILE* temp;
	errno_t err = fopen_s(&temp,"temp.txt", "w+");  //r+ modunda dosya a��ld� ��nk� ba�tan sona bak�l�p silinmek istenen kelime bulunacak ve �zerine bo�luk yaz�lacak.
	errno_t err2 = fopen_s(&fp, "Wordy.txt", "r+");
	char line[100];
	char tLine[100];
	int counter = 0, i = 0;
	if (err != 0 || err2 != 0) {
		printf("%s", "\nFile could not be opened.");
		return;
	}

	while (fgets(line, sizeof(line), fp) != NULL) {
		counter++;
		if (counter != val) {
			fprintf(temp, "%s", line);

		}

	}
	fclose(fp);
	fclose(temp);
	remove("Wordy.txt");
	rename("temp.txt", "Wordy.txt");
}

void ShowFile() {

	FILE* fp;
	int counter = 0;


	errno_t err = fopen_s(&fp, "Wordy.txt", "r"); // Okunacak dosyan�n ad�n� do�ru �ekilde belirtin
	if (err != 0) {
		printf("%s", "\nFile could not be opened.");
		return 1; // Program� hata kodu ile sonland�r
	}

	char line[100]; // Bir sat�r�n maksimum uzunlu�unu belirtin
	while (fgets(line, sizeof(line), fp) != NULL) {
		printf("%d - %s", ++counter,line);
	}
	fclose(fp);
}

void Instructions(int* userInput)
{	
	printf("\n%s", "If you want to enter a word to program press 1,\nBir kelime eklemek istiyorsaniz 1 giriniz,\n\n");
	printf("%s", "If you want to delete a word from program press 2,\nBir kelime silmek istiyorsaniz 2 giriniz,\n\n");
	printf("%s", "If you want to see all of the words press 3,\nProgramdaki tum kelimeleri gormek istiyorsaniz 3 giriniz,\n\n");
	printf("%s", "If you want to terminate the program press 4\nProgrami sonlandirmak istiyorsaniz 4 giriniz,\n\nChoice/Secim: ");
	scanf_s("%d", userInput);

}



void Execute() {
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
			printf("%s", "\nSee you again./Gorusuruz.\n");
			break;
		default:
			printf("%s", "\nInvalid Choise!/\\Hatali Secim!\n");
			userInput = 4;
			break;
		}
	}
	HideTheFile();
}