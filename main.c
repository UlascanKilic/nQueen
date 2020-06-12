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
//Bulunan çözümü yazdıran fonksiyon
void CozumYazdir(int tahta[N][N],int renk) 
{ 
	int i,j,k=0,sayac=1;

    for (i = 0; i < N; i++) { 
        for (j = 0; j < N; j++){
        	if(tahta[i][j]==1) //tahta üzerindeki 1 olan, yani üzerinde vezir olan kısımları kontrol ediyorum
        	{	if(renk>15)
				{
        			renk= renk-14;
				}	
        		rengim(renk);
        		_setmode(_fileno(stdout), _O_U16TEXT); //ASCII karakter yazdırmak için yazı modunu değiştiriyorum
				wprintf(L"\x2588\x2588");    		
        	 	sayac++;    	 
			} 				
			else
			{				
				if(sayac%2==1) rengim(15); //	açık renk
				else rengim(0); // koyu renk
				
				_setmode(_fileno(stdout), _O_U16TEXT); //ASCII karakter yazdırmak için yazı modunu değiştiriyorum
					wprintf(L"\x2588\x2588");			
			 	sayac++;
			}		
				_setmode(_fileno(stdout), _O_TEXT);	  //ASCII karakter yazdırdıktan sonra yazı modunu normale çeviriyorum
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
   
/* Vezirin o an için belirlenen tahtanın ilgili satır ve sütununa koyulup, koyulamayacağını
   	kontrol eden fonksiyon. Sadece sol,sol üst diyagonal ve sol alt diyagonali kontrol ediyorum.
   	Çünkü vezirlerimi yerleştirirken soldan sağa doğru gidiyorum ve son vezire kadar sağ taraf
   	her zaman boş kalacağı için sağ taraftan bir tehdit gelmiyor. Dolayısı ile sadece sol tarafı
   	kontrol etmem yeterli oluyor.
   	Eğer kontrol edilen karelerin birisinden 1 değeri dönerse if koşulum sağlanmış oluyor ve 
   	o kontrol edilen kare için vezir tehdit edilmiş olacağından false döndürerek güvenli olmadığını
   	söylüyorum.
*/
bool guvenliMi(int tahta[N][N], int row, int col) 
{ 
    int i, j;  
    /* Sol satırı kontrol ediyorum */
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
  
/* Problemimi çözdüğüm recursive fonksiyonum*/
bool nQueen(int tahta[N][N], int col) 
{ 
	int i;
    /* Bütün vezirlerim tahtaya yerleştiyse true döndürüyorum */
    if (col >= N) 
        return true; 
  
    /* Seçtiğim sütunun güvenli olan satırına vezirimi koymak için kurduğum döngü*/
    for (i = 0; i < N; i++) { 
        /* tahta[i][col] güvenli mi diye kontrol ediyorum */
        if (guvenliMi(tahta, i, col)) { 
            /* Güvenli ise tahta[i][col] 'u 1 yaparak vezirimi oraya yerleştiriyorum */
            tahta[i][col] = 1;          
            /* Aynı tahtanın geri kalan sütunlarına diğer vezirleri koymak için recursive olarak kendisini çağırttırıyorum*/
            if (nQueen(tahta, col + 1)) 
                return true; 
          
            /* Eğer tahta[i][col] üzerine yerleştirilen vezir ile
			   bir çözüme varamıyorsam ilgili veziri oradan kaldırıyorum
			   Örn:  V * * *
			   	     * * * *
			   	     * V * *
			   	     * * * *  4x4 satranç tahtası için 3. vezirin 3. sütuna koyulabileceği bir yer yok.
			   	     	      Bu yüzden 2. veziri oradan kaldırıyorum.
			*/ 
            tahta[i][col] = 0; // BACKTRACK 
        } 
    }    
    /* Vezirim ilgili sütunun hiçbir satırına koyulamıyorsa, false döndürüyorum */ 
    return false; 
} 
  

/*	Backtrackinh kullanarak problemi çözdüğüm fonksiyon.
	Problemi çözmek için nQueen fonkisyonundan faydalanıyor.
	Vezirler yerleştirilemez ise false döndürüyor, 
	vezirler yerleştirilir ise true döndürüp çözümü yazdırıyor.
*/
bool nCoz(int renk) 
{ 
    int tahta[N][N];
    int i,j;
    
    for(i=0;i<N;i++){ // Oluşturduğum tahtanın bütün satır ve sütunlarına 0 değeri atıyorum (0 - Boş, 1 - Vezir var)
    	for(j=0;j<N;j++){
    		tahta[i][j] = 0;
		}
	}
	/* Oluşturduğum tahtanın ilk sütunundan başlamak üzere vezirleri koymaya başlamasını istiyorum
	    eğer false dönerse çözüm yok demektir.*/
    if (nQueen(tahta, 0) == false) { 
        printf("Cozum bulunamadi."); 
        return false; 
    } 
  
    CozumYazdir(tahta,renk); // Bulduğum çözümü yazdırıyorum
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
       			renk = renk-14;	// Sadece 0-15 arasında renk değerleri kullanabildiğim için başa sarıyorum.
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
       			renk = renk-14;	// Sadece 0-15 arasında renk değerleri kullanabildiğim için başa sarıyorum.
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
		N=(rand()%(max-min)+1)+min; //Verilen max-min arasında rastgele bir N değeri üretiyorum.	
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
{ 	/*  N değeri için 4-19 arasında birbirine yakın ve düşük sürelerde çözülüyor.
		20-29 arasında ise 4-19 a göre çözüm çok daha uzun sürüyor. 
		Grafikte ekrandan taşma gibi durumları önlemek için
		4-19 arasını kendi arasında hesaplayıp bir grafikte,
		20-29 arasını kendi arasında hesaplayıp başka bir grafikte gösteriyorum*/ 
		
	//Grafiği taşmadan görmek için cmd ekranının tam ekran yapılmasını öneriyorum.
		
	Iterasyon(19,4,28,ilkArray); // (Max N değeri,Min N değeri,tekrar sayısı,grafik için verilerin depolanacağı dizi)
	Iterasyon(29,20,5,ikinciArray);
	printf("\n");
	
    return 0; 
} 

