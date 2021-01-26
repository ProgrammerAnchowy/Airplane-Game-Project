/************************************************************************************************************
**						SAKARYA �N�VERS�TES�
**				B�LG�SAYAR VE B�L���M B�L�MLER� FAK�LTES�
**					B�LG�SAYAR M�HEND�SL��� B�L�M�
**					 PROGRAMLAMAYA G�R��� DERS�
**
**                           PROJE �DEV�
**
**					��RENC� ADI......: Davud Samed Tombul
**					��RENC� NUMARASI.: B171210007
**					DERS GRUBU.......: 1D
*************************************************************************************************************/

#include<iostream>//Temel komutlar�(cout vs) kullanabilmemizi sa�layan k�t�phane.
#include<Windows.h>//Kurs�r�n yerini de�i�tirmek ve kurs�r� gizlemek i�in yazaca��m�z komutlar� bu k�t�phane sayesinde kullanabiliyoruz.
#include<time.h>//Rand() komutunu s�f�rlay�p yeni de�er atamak i�in gerekli k�t�phane.

using namespace std;

//Kontoller = W: Yukar�, S: A�a��, K: Ate�

//Y�nler
enum YON
{
	YON_SOL = 1,
	YON_SAG = 2,
	YON_YUKARI = 3,
	YON_ASAGI = 4
};

//U�a��n koordinat, y�n ve karakterini i�eren yap�.
struct ucakHucre
{
	int		x;
	int		y;
	YON		yon;
	char	karakter;
};

//Merminin koordinat ve karakterini i�eren yap�.
struct atesYapi
{
	int		x;
	int		y;
	char	karakter;
};

//D��man biriminin koordinatlar�n�,y�n�n� ve karakterini i�eren yap�.
struct dusmanHucre
{
int		x;
int		y;
YON		yon;
char	karakter;
};

const int	genislik = 110;//Sahnenin toplam geni�li�i
const int	yukseklik = 20;//Sahnenin y�ksekli�i


const char	ucakKarakteri = 219;

const char dusmanKarakteri = 176;

const char	atesKarakteri = 254;

const int dusmanSayisi = 50;

const int	govdeUzunlugu = 5;

const int  atesSayisi = 1000;

char	sahne[genislik][yukseklik];

char    tuslar[256];

int		a = 0, e = 0;


ucakHucre	ucakGovdesi[govdeUzunlugu];

atesYapi    atesBirimi[atesSayisi];

dusmanHucre dusman[dusmanSayisi];

//Klavyede bast���m�z tu�u okuyan ve kaydeden fonksiyon.
void klavyeOku(char tuslar[])//*
{
	for (int x = 0; x < 256; x++)
		tuslar[x] = (char)(GetAsyncKeyState(x) >> 8);
}

//Kurs�r�n yerini belirleyen fonksiyon.
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Program�n �al��mas� esnas�nda kus�r� gizleyerek daha iyi bir g�r�nt� olu�mas�n� sa�layan fonksiyon.
void kursoruGizle()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}

//T�m sahneyi �izen fonksiyon.
void sahneyiCiz()
{
	for (int y = 0; y < yukseklik; y++)
	{
		for (int x = 0; x < genislik; x++)
		{
			cout << sahne[x][y];
		}
		cout << endl;
	}
}

//Sahneyi temizleyen fonksiyon.
void sahneyiTemizle()
{
	for (int y = 0; y < yukseklik; y++)
	{
		for (int x = 0; x < genislik; x++)
		{
			sahne[x][y] = ' ';
		}
	}
}

//Oyunu oynad���m�z s�n�rlar�n olu�mas�n� sa�layan fonksiyon.
void sinirlariOlustur()
{
	for (int x = 0; x < genislik-30; x++)
	{
		sahne[x][0] = 219;
		sahne[x][yukseklik - 1] = 219;
	}
	for (int y = 0; y < yukseklik; y++)
	{
		sahne[0][y] = 219;
		sahne[genislik-30 - 1][y] = 219;
	}
}

//U�a��m�z�n koordinatlar�n� ve karakterini olu�turan fonksiyon.
void ucakOlustur()
{

	ucakGovdesi[0].x = 1;
	ucakGovdesi[0].y = 9;
	ucakGovdesi[0].karakter = ucakKarakteri;


	ucakGovdesi[1].x = 2;
	ucakGovdesi[1].y = 10;
	ucakGovdesi[1].karakter = ucakKarakteri;


	ucakGovdesi[2].x = 3;
	ucakGovdesi[2].y = 11;
	ucakGovdesi[2].karakter = ucakKarakteri;


	ucakGovdesi[3].x = 2;
	ucakGovdesi[3].y = 12;
	ucakGovdesi[3].karakter = ucakKarakteri;


	ucakGovdesi[4].x = 1;
	ucakGovdesi[4].y = 13;
	ucakGovdesi[4].karakter = ucakKarakteri;
}

//U�a��n hareket etmesini sa�layan fonksiyon.
void ucagiHareketEttir()
{
	for (int t = 0; t < 5; t++)
	{
		switch (ucakGovdesi[t].yon)
		{
		case YON_ASAGI:
			ucakGovdesi[t].y++;
			break;
		case YON_YUKARI:
			ucakGovdesi[t].y--;
			break;
		}
	}
}

//U�ak karakterlerinin sahneye �izilmesini sa�layan fonksiyon.
void ucagiSahneyeYerlestir()
{
	for (int i = 0; i < 5; i++)
	{
		int x = ucakGovdesi[i].x;
		int y = ucakGovdesi[i].y;

		sahne[x][y] = ucakGovdesi[i].karakter;
	}
}

//Mermimizin u�a��n ortadaki karakterinin bir birim �n�nde olu�mas�n� sa�layan fonksiyon.
void atesBirimiOlustur()
{
	atesBirimi[a].x = ucakGovdesi[2].x+1;
	atesBirimi[a].y = ucakGovdesi[2].y;
	atesBirimi[a].karakter = atesKarakteri;

	//Ate� say�s� 1000 e geldi�inde ate� s�f�rlan�r ve ba�a d�ner.
	if (a == 1000)
		a = 0;
		a++;
}

//Sahneye yerle�tirilen ate�in sahnenin sa� taraf�na do�ru ilerlemesini sa�layan fonksiyon.
void atesiHareketEttir()
{
	for (int t = 0; t < a; t++)
	{
		atesBirimi[t].x++;
	}
}

//Ate�in sahnede g�z�kmesini sa�layan fonksiyon. 
void atesiSahneyeYerlestir()
{
	for (int i = 0; i < a; i++)
	{
		int x = atesBirimi[i].x;
		int y = atesBirimi[i].y;

		//Ate� �izdi�imiz s�n�rlar� a�t���nda yani x koordinat� 79 u ge�ti�inde sahneye �izimi engellenir. B�ylece s�n�rlar� a�an ate� g�z�kmez.
		if(x<79)
		sahne[x][y] = atesBirimi[i].karakter;
	}
}

//KlavyeOku fonksiyonuna kaydedilen verileri taray�p klavyeden bas�lan tu�lar W,S ve K oldu�unda �e�itli i�lemler yapan fonksiyon.
void klavyeKontrol()
{
	klavyeOku(tuslar);

	if (tuslar['W'] != 0 && ucakGovdesi[0].y != 1)//Yukar� hareket
	{

		for (int a = 0; a < 5; a++)
		{
			ucakGovdesi[a].y = ucakGovdesi[a].y--;
		}
	}

	if (tuslar['S'] != 0 && ucakGovdesi[4].y != 18)//A�a�� hareket
	{
		for (int a = 0; a < 5; a++)
		{
			ucakGovdesi[a].y = ucakGovdesi[a].y++;
		}

	}

	if (tuslar['K'] != 0)//Ate�
	{
		atesBirimiOlustur();
	}
}

//D��man biriminin koordinat�n� ve y�n�n� i�erisinde bar�nd�ran fonksiyon.
void dusmaniOlustur()
{
dusman[e].x = 76;
dusman[e].y = rand()%14+5;
dusman[e].yon = YON_SOL;

//D��man say�s� 1000 e gelene kadar artt�r�l�r.
if (e < 10000)
	e++;
}

//D��man biriminin hareketini sa�layan fonksiyon.
void dusmaniHareketEttir()
{
	
	for (int t = 0; t < e; t++)
	{
		//D��man�m�z �izdi�imiz s�n�rlar i�erisinde ise x ekseninde sola do�ru hareket eder. S�n�rlar d��ar�s�ndaki d��manlar hareket etmez.
		if (dusman[t].x<80)
			dusman[t].x--;
	}
}

//S�n�rlar i�erisindeki d��manlar�n sahnede g�z�kmesini sa�layan fonksiyon.
void dusmaniSahneyeYerlestir()

{
	for (int i = 0; i < e; i++)
	{
		int x = dusman[i].x;
		int y = dusman[i].y;
	
		if (x > 0 && x<100) 
		{

		sahne[x][y] = dusmanKarakteri;
		sahne[x][y-1] = dusmanKarakteri;
		sahne[x][y-2] = dusmanKarakteri;

		sahne[x+1][y] = dusmanKarakteri;
		sahne[x+2][y] = dusmanKarakteri;
		sahne[x+2][y-1] = dusmanKarakteri;
		sahne[x+2][y-2] = dusmanKarakteri;
		sahne[x+1][y-2] = dusmanKarakteri;
		}
	}
}

//Mermi d��mana �arpt���nda mermi ve d��man�n �izdi�imiz alan�n d���nda bir bo�lu�a g�nderilmesini yani ekrandan kaybolmas�n� sa�layan fonksiyon.
void carpismaKontrol()
{
	for (int i = 0; i < a; i++)
	{
		for (int t = 0; t < e; t++)
		{
			if (dusman[t].x == atesBirimi[i].x && dusman[t].y == atesBirimi[i].y || dusman[t].x == atesBirimi[i].x && dusman[t].y-1 == atesBirimi[i].y|| dusman[t].x == atesBirimi[i].x && dusman[t].y-2 == atesBirimi[i].y)
			{
				dusman[t].x = 100;
				atesBirimi[i].x = 120;
			}
		}
	}
}


int main()
{
	//Rand() komutunun program�n bir sonraki �al��t�r�lmas�nda farkl� de�er almas�n� sa�l�yor.
	srand(time(NULL));

	kursoruGizle();

	ucakOlustur();

	//D��man�n belirli aral�klarla gelmesini sa�lamak i�in bir tamsay� de�eri olu�turdum. Bu de�er 15 in katlar� oldu�unda d��man olu�turuluyor
	int sayi = 0;
	
	//While d�ng�s�n�n s�rekli �al��mas�n� istedi�imizden dolay� i�ine true yazd�k. D�ng� her ba�a d�nd���nde t�m fonksiyonlar teker teker �al��t�r�l�r.
	while (true)
	{

		sahneyiTemizle();
		
		sinirlariOlustur();

		klavyeKontrol();

		ucagiHareketEttir();

		ucagiSahneyeYerlestir();
		
		atesiHareketEttir();
		
		carpismaKontrol();

		atesiSahneyeYerlestir();
		
		//Sayi 15 ve 15'in katlar� oldu�unda d��man olu�tur fonksiyonu �al��t�r�l�r.
		if(sayi%15==0)
		dusmaniOlustur();

		dusmaniHareketEttir();

		dusmaniSahneyeYerlestir();

		carpismaKontrol();
		
		gotoxy(0, 0);

		sahneyiCiz();

		sayi++;
	}

}