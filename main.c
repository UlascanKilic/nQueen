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
//Bulunan ��z�m� yazd�ran fonksiyon
void CozumYazdir(int tahta[N][N],int renk) 
{ 
	int i,j,k=0,sayac=1;

    for (i = 0; i < N; i++) { 
        for (j = 0; j < N; j++){
        	if(tahta[i][j]==1) //tahta �zerindeki 1 olan, yani �zerinde vezir olan k�s�mlar� kontrol ediyorum
        	{	if(renk>15)
				{
        			renk= renk-14;
				}	
        		rengim(renk);
        		_setmode(_fileno(stdout), _O_U16TEXT); //ASCII karakter yazd�rmak i�in yaz� modunu de�i�tiriyorum
				wprintf(L"\x2588\x2588");    		
        	 	sayac++;    	 
			} 				
			else
			{				
				if(sayac%2==1) rengim(15); //	a��k renk
				else rengim(0); // koyu renk
				
				_setmode(_fileno(stdout), _O_U16TEXT); //ASCII karakter yazd�rmak i�in yaz� modunu de�i�tiriyorum
					wprintf(L"\x2588\x2588");			
			 	sayac++;
			}		
				_setmode(_fileno(stdout), _O_TEXT);	  //ASCII karakter yazd�rd�ktan sonra yaz� modunu normale �eviriyorum
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
   
/* Vezirin o an i�in belirlenen tahtan�n ilgili sat�r ve s�tununa koyulup, koyulamayaca��n�
   	kontrol eden fonksiyon. Sadece sol,sol �st diyagonal ve sol alt diyagonali kontrol ediyorum.
   	��nk� vezirlerimi yerle�tirirken soldan sa�a do�ru gidiyorum ve son vezire kadar sa� taraf
   	her zaman bo� kalaca�� i�in sa� taraftan bir tehdit gelmiyor. Dolay�s� ile sadece sol taraf�
   	kontrol etmem yeterli oluyor.
   	E�er kontrol edilen karelerin birisinden 1 de�eri d�nerse if ko�ulum sa�lanm�� oluyor ve 
   	o kontrol edilen kare i�in vezir tehdit edilmi� olaca��ndan false d�nd�rerek g�venli olmad���n�
   	s�yl�yorum.
*/
bool guvenliMi(int tahta[N][N], int row, int col) 
{ 
    int i, j;  
    /* Sol sat�r� kontrol ediyorum */
    for (i = 0; i < col; i++) 
        if (tahta[row][i]) 
            return false; 
  
    /* Sol �st diyagonali kontrol ediyorum*/
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) 
        if (tahta[i][j]) 
            return false; 
  
    /* Sol alt diyagonali kontrol ediyorum*/
    for (i = row, j = col; j >= 0 && i < N; i++, j--) 
        if (tahta[i][j]) 
            return false; 
  
    return true; 
} 
  
/* Problemimi ��zd���m recursive fonksiyonum*/
bool nQueen(int tahta[N][N], int col) 
{ 
	int i;
    /* B�t�n vezirlerim tahtaya yerle�tiyse true d�nd�r�yorum */
    if (col >= N) 
        return true; 
  
    /* Se�ti�im s�tunun g�venli olan sat�r�na vezirimi koymak i�in kurdu�um d�ng�*/
    for (i = 0; i < N; i++) { 
        /* tahta[i][col] g�venli mi diye kontrol ediyorum */
        if (guvenliMi(tahta, i, col)) { 
            /* G�venli ise tahta[i][col] 'u 1 yaparak vezirimi oraya yerle�tiriyorum */
            tahta[i][col] = 1;          
            /* Ayn� tahtan�n geri kalan s�tunlar�na di�er vezirleri koymak i�in recursive olarak kendisini �a��rtt�r�yorum*/
            if (nQueen(tahta, col + 1)) 
                return true; 
          
            /* E�er tahta[i][col] �zerine yerle�tirilen vezir ile
			   bir ��z�me varam�yorsam ilgili veziri oradan kald�r�yorum
			   �rn:  V * * *
			   	     * * * *
			   	     * V * *
			   	     * * * *  4x4 satran� tahtas� i�in 3. vezirin 3. s�tuna koyulabilece�i bir yer yok.
			   	     	      Bu y�zden 2. veziri oradan kald�r�yorum.
			*/ 
            tahta[i][col] = 0; // BACKTRACK 
        } 
    }    
    /* Vezirim ilgili s�tunun hi�bir sat�r�na koyulam�yorsa, false d�nd�r�yorum */ 
    return false; 
} 
  

/*	Backtrackinh kullanarak problemi ��zd���m fonksiyon.
	Problemi ��zmek i�in nQueen fonkisyonundan faydalan�yor.
	Vezirler yerle�tirilemez ise false d�nd�r�yor, 
	vezirler yerle�tirilir ise true d�nd�r�p ��z�m� yazd�r�yor.
*/
bool nCoz(int renk) 
{ 
    int tahta[N][N];
    int i,j;
    
    for(i=0;i<N;i++){ // Olu�turdu�um tahtan�n b�t�n sat�r ve s�tunlar�na 0 de�eri at�yorum (0 - Bo�, 1 - Vezir var)
    	for(j=0;j<N;j++){
    		tahta[i][j] = 0;
		}
	}
	/* Olu�turdu�um tahtan�n ilk s�tunundan ba�lamak �zere vezirleri koymaya ba�lamas�n� istiyorum
	    e�er false d�nerse ��z�m yok demektir.*/
    if (nQueen(tahta, 0) == false) { 
        printf("Cozum bulunamadi."); 
        return false; 
    } 
  
    CozumYazdir(tahta,renk); // Buldu�um ��z�m� yazd�r�yorum
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
       			renk = renk-14;	// Sadece 0-15 aras�nda renk de�erleri kullanabildi�im i�in ba�a sar�yorum.
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
       			renk = renk-14;	// Sadece 0-15 aras�nda renk de�erleri kullanabildi�im i�in ba�a sar�yorum.
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
		N=(rand()%(max-min)+1)+min; //Verilen max-min aras�nda rastgele bir N de�eri �retiyorum.	
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
		if(N<=19){ //Histogram i�in verilerimi dizime depoluyorum
		
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
{ 	/*  N de�eri i�in 4-19 aras�nda birbirine yak�n ve d���k s�relerde ��z�l�yor.
		20-29 aras�nda ise 4-19 a g�re ��z�m �ok daha uzun s�r�yor. 
		Grafikte ekrandan ta�ma gibi durumlar� �nlemek i�in
		4-19 aras�n� kendi aras�nda hesaplay�p bir grafikte,
		20-29 aras�n� kendi aras�nda hesaplay�p ba�ka bir grafikte g�steriyorum*/ 
		
	//Grafi�i ta�madan g�rmek i�in cmd ekran�n�n tam ekran yap�lmas�n� �neriyorum.
		
	Iterasyon(19,4,28,ilkArray); // (Max N de�eri,Min N de�eri,tekrar say�s�,grafik i�in verilerin depolanaca�� dizi)
	Iterasyon(29,20,5,ikinciArray);
	printf("\n");
	
    return 0; 
} 

