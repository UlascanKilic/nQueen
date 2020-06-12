/* C/C++ program to solve N Queen Problem using 
   backtracking */

#include <stdbool.h> 
#include <time.h>
#include <windows.h>
#include <math.h>
#include <wchar.h>
#include <stdlib.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>

#define M 30

int N = 1;
double ilkArray[M][2] = {0} ,ikinciArray[M][2] = {0};

void rengim(int renk){ //renk fonksiyonum{
	HANDLE hStdout;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, renk);
}
//Bulunan çözümü yazdýran fonksiyon
void CozumYazdir(int tahta[N][N],int renk) 
{ 
	int i,j,k=0,sayac=1;

    for (i = 0; i < N; i++) { 
        for (j = 0; j < N; j++){
        	if(tahta[i][j]==1) //tahta üzerindeki 1 olan, yani üzerinde vezir olan kýsýmlarý kontrol ediyorum
        	{	if(renk>15)
				{
        			renk= renk-14;
				}	
        		rengim(renk);
        		_setmode(_fileno(stdout), _O_U16TEXT); //ASCII karakter yazdýrmak için yazý modunu deðiþtiriyorum
				wprintf(L"\x2588\x2588");    		
        	 	sayac++;    	 
			} 				
			else
			{				
				if(sayac%2==1) rengim(15); //	açýk renk
				else rengim(0); // koyu renk
				
				_setmode(_fileno(stdout), _O_U16TEXT); //ASCII karakter yazdýrmak için yazý modunu deðiþtiriyorum
					wprintf(L"\x2588\x2588");			
			 	sayac++;
			}		
				_setmode(_fileno(stdout), _O_TEXT);	  //ASCII karakter yazdýrdýktan sonra yazý modunu normale çeviriyorum
		}
		if(i%2==1){
			sayac = 1;
		}
		else{
			sayac = 0;
		}
		rengim(7);            
        printf("\n"); 
    } 
     printf("\n"); 
} 
   
/* Vezirin o an için belirlenen tahtanýn ilgili satýr ve sütununa koyulup, koyulamayacaðýný
   	kontrol eden fonksiyon. Sadece sol,sol üst diyagonal ve sol alt diyagonali kontrol ediyorum.
   	Çünkü vezirlerimi yerleþtirirken soldan saða doðru gidiyorum ve son vezire kadar sað taraf
   	her zaman boþ kalacaðý için sað taraftan bir tehdit gelmiyor. Dolayýsý ile sadece sol tarafý
   	kontrol etmem yeterli oluyor.
   	Eðer kontrol edilen karelerin birisinden 1 deðeri dönerse if koþulum saðlanmýþ oluyor ve 
   	o kontrol edilen kare için vezir tehdit edilmiþ olacaðýndan false döndürerek güvenli olmadýðýný
   	söylüyorum.
*/
bool guvenliMi(int tahta[N][N], int row, int col) 
{ 
    int i, j;  
    /* Sol satýrý kontrol ediyorum */
    for (i = 0; i < col; i++) 
        if (tahta[row][i]) 
            return false; 
  
    /* Sol üst diyagonali kontrol ediyorum*/
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) 
        if (tahta[i][j]) 
            return false; 
  
    /* Sol alt diyagonali kontrol ediyorum*/
    for (i = row, j = col; j >= 0 && i < N; i++, j--) 
        if (tahta[i][j]) 
            return false; 
  
    return true; 
} 
  
/* Problemimi çözdüðüm recursive fonksiyonum*/
bool nQueen(int tahta[N][N], int col) 
{ 
	int i;
    /* Bütün vezirlerim tahtaya yerleþtiyse true döndürüyorum */
    if (col >= N) 
        return true; 
  
    /* Seçtiðim sütunun güvenli olan satýrýna vezirimi koymak için kurduðum döngü*/
    for (i = 0; i < N; i++) { 
        /* tahta[i][col] güvenli mi diye kontrol ediyorum */
        if (guvenliMi(tahta, i, col)) { 
            /* Güvenli ise tahta[i][col] 'u 1 yaparak vezirimi oraya yerleþtiriyorum */
            tahta[i][col] = 1;          
            /* Ayný tahtanýn geri kalan sütunlarýna diðer vezirleri koymak için recursive olarak kendisini çaðýrttýrýyorum*/
            if (nQueen(tahta, col + 1)) 
                return true; 
          
            /* Eðer tahta[i][col] üzerine yerleþtirilen vezir ile
			   bir çözüme varamýyorsam ilgili veziri oradan kaldýrýyorum
			   Örn:  V * * *
			   	     * * * *
			   	     * V * *
			   	     * * * *  4x4 satranç tahtasý için 3. vezirin 3. sütuna koyulabileceði bir yer yok.
			   	     	      Bu yüzden 2. veziri oradan kaldýrýyorum.
			*/ 
            tahta[i][col] = 0; // BACKTRACK 
        } 
    }    
    /* Vezirim ilgili sütunun hiçbir satýrýna koyulamýyorsa, false döndürüyorum */ 
    return false; 
} 
  

/*	Backtrackinh kullanarak problemi çözdüðüm fonksiyon.
	Problemi çözmek için nQueen fonkisyonundan faydalanýyor.
	Vezirler yerleþtirilemez ise false döndürüyor, 
	vezirler yerleþtirilir ise true döndürüp çözümü yazdýrýyor.
*/
bool nCoz(int renk) 
{ 
    int tahta[N][N];
    int i,j;
    
    for(i=0;i<N;i++){ // Oluþturduðum tahtanýn bütün satýr ve sütunlarýna 0 deðeri atýyorum (0 - Boþ, 1 - Vezir var)
    	for(j=0;j<N;j++){
    		tahta[i][j] = 0;
		}
	}
	/* Oluþturduðum tahtanýn ilk sütunundan baþlamak üzere vezirleri koymaya baþlamasýný istiyorum
	    eðer false dönerse çözüm yok demektir.*/
    if (nQueen(tahta, 0) == false) { 
        printf("Cozum bulunamadi."); 
        return false; 
    } 
  
    CozumYazdir(tahta,renk); // Bulduðum çözümü yazdýrýyorum
    return true; 
} 
void HistogramZaman(double dizi[M][2]){	    
       int i, j,cubuk=0,renk;           	  
	              
       printf("%6s%8s%17s\n","NxN", "SURE", "GRAFIK");
       printf("___________________________________________________________\n\n");
       
       for(i=0; i <= M; i++)
       {
       		renk = i+1;
       		if(i+1>15)
       		{
       			renk = renk-14;	// Sadece 0-15 arasýnda renk deðerleri kullanabildiðim için baþa sarýyorum.
			}		
       		rengim(renk);
       		if(dizi[i][0] != 0)
			{       		
       			printf("%5.0f%10.3fs       ", dizi[i][0], dizi[i][1]);
       			if(dizi[1][0]>20)
       				cubuk = abs(dizi[i][1]*100/2);
       			else
       				cubuk = (dizi[i][1]*1000);
       				
            	for(j = 1; j<= cubuk; j++)
				{	
					_setmode(_fileno(stdout), _O_U16TEXT);
					wprintf(L"\x25A0");             	
				}
			_setmode(_fileno(stdout),  _O_TEXT);			
            printf("\n");          
			}             
       }
       rengim(7);
       printf("___________________________________________________________\n\n");         
}
void HistogramBellek(int dizi[]){
	int i, j,cubuk=0,renk;      
	printf("%5s%17s\n","N", "GRAFIK");
    printf("___________________________________________________________\n\n");
       
       for(i=0; i <= M; i++)
       {
       		renk = i+1;
       		if(i+1>15)
       		{
       			renk = renk-14;	// Sadece 0-15 arasýnda renk deðerleri kullanabildiðim için baþa sarýyorum.
			}		
       		rengim(renk);
       		
       		if(dizi[i] != 0)
			{       		
       			printf("%5d       ", dizi[i]);	
       				cubuk = dizi[i];
       				
            	for(j = 1; j<= cubuk; j++)
				{	
					_setmode(_fileno(stdout), _O_U16TEXT);
					wprintf(L"\x25A0");             	
				}
			_setmode(_fileno(stdout),  _O_TEXT);			
            printf("\n");          
			}             
       }
       rengim(7);
       printf("___________________________________________________________\n\n");       
	
}

void Iterasyon(int max, int min, int tekrar ,double dizi[M][2]){
	
	int i = 0,j=0,k=0,renk;
	int izinliRenkler[] = {1,2,3,4,5,6,9,10,11,12,13,14};
	int nDegerleri[M] = {0};
	double time_spent;
	clock_t begin,end;
	srand(time(NULL));
	
	for(i=0;i<tekrar;i++){
		renk = i+1;
		N=(rand()%(max-min)+1)+min; //Verilen max-min arasýnda rastgele bir N deðeri üretiyorum.	
		nDegerleri[i] = N;
		if(renk>15)
			renk = renk-14;		
		if(renk == 0 || renk == 7 || renk == 8 || renk == 15)
		{		
		renk = izinliRenkler[rand()%(sizeof(izinliRenkler)/sizeof(izinliRenkler[0]))];	
		}
						
		begin = clock();	
		
		rengim(renk);
		printf("%dx%d 'lik satranc tahtasi\n\n",N,N);
												
		nCoz(renk);
		
		end = clock();
		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		if(N<=19){ //Histogram için verilerimi dizime depoluyorum
		
			dizi[k][0] = N;
			dizi[k][1] = time_spent;
			k++;
		}
		else{
			dizi[j][0] = N;
			dizi[j][1] = time_spent;
			j++;
		}
		rengim(renk);
		printf("Total time = %.3f seconds\n",time_spent);
		rengim(7);
		printf("___________________________________________________________\n");
		
		printf("\n");
	}
	printf("%30s\n\n", "CALISMA ZAMANI GRAFIGI");
	HistogramZaman(dizi);
	printf("%30s\n\n", "HAFIZA KARMASIKLIGI GRAFIGI");
	HistogramBellek(nDegerleri);
	printf("\n");
	
}

int main() 
{ 	/*  N deðeri için 4-19 arasýnda birbirine yakýn ve düþük sürelerde çözülüyor.
		20-29 arasýnda ise 4-19 a göre çözüm çok daha uzun sürüyor. 
		Grafikte ekrandan taþma gibi durumlarý önlemek için
		4-19 arasýný kendi arasýnda hesaplayýp bir grafikte,
		20-29 arasýný kendi arasýnda hesaplayýp baþka bir grafikte gösteriyorum*/ 
		
	//Grafiði taþmadan görmek için cmd ekranýnýn tam ekran yapýlmasýný öneriyorum.
		
	Iterasyon(19,4,28,ilkArray); // (Max N deðeri,Min N deðeri,tekrar sayýsý,grafik için verilerin depolanacaðý dizi)
	Iterasyon(29,20,5,ikinciArray);
	printf("\n");
	
    return 0; 
} 

