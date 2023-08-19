#include <stdio.h>
#include <string.h>

void deleteData(char word[15]) {
	FILE* fp = fopen("deneme.txt", "r+"); //r+ modunda dosya açýldý çünkü baþtan sona bakýlýp silinmek istenen kelime bulunacak ve üzerine boþluk yazýlacak.
	char temp[15];
	long int pos;
	char space[15] = { ' ' };// bu kýsýmda silinecek kelime sayýsý kadar boþluk içeren bir string oluþturulacak.

	while (!feof(fp)) {
		fscanf(fp, "%s", temp);
		printf("temp: %s", temp); // kontrol noktasý :D
		if (strcmp(temp, word) == 0) {
			pos = ftell(fp) - strlen(word); // silinecek kelimeden sonraki konum bilgisi ** pos- kelime boyutu yapýlarak kelimenin silineceði konum bulunabilir.
			printf("%ld", pos);
			fseek(fp, pos, SEEK_SET); //imleci dosyanýn baþýndan pos kadar ilerletir.
			fputs(space, fp); // imlecin olduðu noktadan itibaren space adýndaki stringi o konumdaki kelimenin üzerine basýyor ve silme iþlemi tamamlanýyor.
			break;
		}
	}

	fclose(fp); // Dosya kapatýlýyor.
}

int main() {
	char word[15];
	printf("Enter a word you want to delete:  ");
	scanf("%s", word);
	deleteData(word);
}