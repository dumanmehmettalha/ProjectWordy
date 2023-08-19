#include <stdio.h>
#include <string.h>

void deleteData(char word[15]) {
	FILE* fp = fopen("deneme.txt", "r+"); //r+ modunda dosya a��ld� ��nk� ba�tan sona bak�l�p silinmek istenen kelime bulunacak ve �zerine bo�luk yaz�lacak.
	char temp[15];
	long int pos;
	char space[15] = { ' ' };// bu k�s�mda silinecek kelime say�s� kadar bo�luk i�eren bir string olu�turulacak.

	while (!feof(fp)) {
		fscanf(fp, "%s", temp);
		printf("temp: %s", temp); // kontrol noktas� :D
		if (strcmp(temp, word) == 0) {
			pos = ftell(fp) - strlen(word); // silinecek kelimeden sonraki konum bilgisi ** pos- kelime boyutu yap�larak kelimenin silinece�i konum bulunabilir.
			printf("%ld", pos);
			fseek(fp, pos, SEEK_SET); //imleci dosyan�n ba��ndan pos kadar ilerletir.
			fputs(space, fp); // imlecin oldu�u noktadan itibaren space ad�ndaki stringi o konumdaki kelimenin �zerine bas�yor ve silme i�lemi tamamlan�yor.
			break;
		}
	}

	fclose(fp); // Dosya kapat�l�yor.
}

int main() {
	char word[15];
	printf("Enter a word you want to delete:  ");
	scanf("%s", word);
	deleteData(word);
}