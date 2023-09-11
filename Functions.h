#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

void RandomManager(unsigned int* state) {
	// RANDOM NUMBER PART
	int totalWord = ShowFile(0);
	unsigned int x = *state;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	*state = x;
	x = (x) % totalWord;
	int wordIndex = x;
	// SHOWING RANDOM WORD TO USER
	FILE* fp;
	int counter = 0;
	SetConsoleTextColor(TURKUAZ);
	errno_t err = fopen_s(&fp, "Wordy.txt", "r");
	if (err != 0) {
		printf("%s", "\nFile could not be opened.");
		return; // Programý hata kodu ile sonlandýr
	}

	char line[103];
	while (counter < wordIndex) {
		fgets(line, sizeof(line), fp);
		++counter;
		//printf("%d - %s", ++counter, line);
	}
	printf("%d - %s", counter, line);
	fclose(fp);
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

	FILE* filePointer = NULL; 
	fopen_s(&filePointer, "Wordy.txt", "a+"); 
	if (filePointer == NULL) {	
		SetConsoleTextColor(RED);
		puts("\nFile could not be opened./\\Dosya acilamadi.");
	}
	else { // Dosya açýldý 
		char newWordEnglish[50];
		char newWordTurkish[50];
		printf("\n%s", "Enter the english word first and then the turkish translate of it.\n");
		SetConsoleTextColor(YELLOW);
		//scanf_s("%s %s", newWordEnglish, _countof(newWordEnglish), newWordTurkish, _countof(newWordTurkish));
		//scanf_s("%s %s", newWordEnglish, _countof(newWordEnglish), newWordTurkish, _countof(newWordTurkish));
		scanf_s(" %[^\n]s", newWordEnglish,_countof(newWordEnglish));
		scanf_s(" %[^\n]s", newWordTurkish, _countof(newWordTurkish));

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
	char line[103];
	char tLine[103];
	int counter = 0, i = 0;
	if (err != 0 || err2 != 0) {
		SetConsoleTextColor(RED);
		printf("%s", "\nFile could not be opened.\n");
		return;
	}

	while (fgets(line, sizeof(line), fp) != NULL) {
		counter++;
		if (counter != val) {
			fprintf(temp, "%s", line);
		}
	}
	SetConsoleTextColor(RED);
	printf("The line you have selected is deleted.\n");
	fclose(fp);
	fclose(temp);
	remove("Wordy.txt");
	rename("temp.txt", "Wordy.txt");
}

int ShowFile(int userInput) {

	FILE* fp;
	int counter = 0;
	SetConsoleTextColor(TURKUAZ);
	errno_t err = fopen_s(&fp, "Wordy.txt", "r"); // Okunacak dosyanýn adýný doðru þekilde belirtin
	if (err != 0) {
		printf("%s", "\nFile could not be opened.");
		return 1; // Programý hata kodu ile sonlandýr
	}

	char line[100]; // Bir satýrýn maksimum uzunluðunu belirtin
	if (3 == userInput)
	{
		while (fgets(line, sizeof(line), fp) != NULL) 
		{
			printf("%d - %s", ++counter,line);
		}
		fclose(fp);
		return 0;
	}
	else
	{
		while (fgets(line, sizeof(line), fp) != NULL) 
		{
			++counter;
		}
		fclose(fp);
		return counter;
	}
}


void Instructions(int* userInput)
{	
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
	printf("%s", "4. RandomWord");
	SetConsoleTextColor(PURPLE);
	printf("%s", "   - Rastgele Kelime\n");
	SetConsoleTextColor(GREEN);
	printf("%s", "5. Terminate");
	SetConsoleTextColor(PURPLE);
	printf("%s", "   - Sonlandir.\n");
	SetConsoleTextColor(EX_WHITE);
	printf("Choice/Secim: ");
	SetConsoleTextColor(RED);
	scanf_s("%d", userInput);
}



void Execute() {
	unsigned int seed = (unsigned int)time(NULL);
	unsigned int state = seed;

	SetConsoleTextColor(LIGHT_YELLOW);
	printf("%s\n", "WELCOME TO THE WORDY!!!");
	int userInput = 0;
	int val;
	int flag=0;
	while (5 != userInput)
	{
		if (4 == userInput) {
			flag = 1;
			Instructions(&userInput);
			switch (userInput)
			{
			case 1:
				AddWord();
				userInput = 4;
				break;
			case 2:
				SetConsoleTextColor(3);
				printf("Enter line number you want to delete:  ");
				scanf_s("%d", &val);
				DeleteData(val);
				userInput = 4;
				break;
			case 3:
				puts("");
				ShowFile(userInput);
				puts("");
				userInput = 4;
				break;
			case 4:
				//RandomManager(&state);
				userInput = 3;
				flag = 0;
				continue;
			case 5:
				SetConsoleTextColor(4);
				printf("%s", "\nSee you again./Gorusuruz.\n");
				SetConsoleTextColor(WHITE);
				break;
			default:
				SetConsoleTextColor(4);
				printf("%s", "\nInvalid Choise!/\\Hatali Secim!\n");
				SetConsoleTextColor(WHITE);
				userInput = 5;
				break;
			}
			
		}
		else if(flag!=1){
			RandomManager(&state);
			SetConsoleTextColor(BLUE);
			printf("%s", "\nEnter 4 to return main menu./ Ana menuye donmek icin 4 e basin.\n");
			SetConsoleTextColor(LIGHT_BLUE);
			scanf_s("%d", userInput);
		}
	}
	HideTheFile();
}