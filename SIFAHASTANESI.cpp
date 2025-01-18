#include<iostream>
#include<locale.h>
#include<math.h>
#include<iomanip>
#include<string>
#include<cstdlib>
#include<conio.h>
#include<chrono>
#include<fstream>

using namespace std;

class hasta
{
public:
	//haasta bilgileri
	string h_adsoyad;
	int h_yas;
	int h_durum;
	int h_id;
	string h_muayeneTarihi;
	string h_ameliyatTarihi;
	string h_hastasi;
	string h_ameliyat_durumu;
	int h_ameliyatucreti;

	//çift yönlü bağlı liste yapısı için 
	hasta* h_önceki;
	hasta* h_sonraki;
	hasta* h_ilk;
	hasta* h_son;

	//fonksyonlar
	void hastaEkle(hasta*); // doktor tarafından hasta eklemek için
	void basaHASTAekleDAİRESEL(hasta*);// yine hasta eklemek için
	void hastaSil(int);// hasta silme işlemi için
	void hastabilgilistesiyazdir();//tüm hastaları yazdırmak için
	void ameliyatEkle(int, string);//hasta için ameliyat eklemek için
	void ameliyatSil(int);//ameliyat bilgisi silmek için
	int ameliyat_ucreti_hesapla(int, string);
	void ameliyatBilgiListesi();//ameliyatı olan hastaları yazdırmak için
	void hastaBilgisi(int);//aranan hastanın bilgileri yazdırmak için
	void hastaRaporuÇıktısı(int);//hasta isterse rapor oluştururuz
	void hastaBilgiYazdırDAIRESEL();//hasta girişi yapıldığında hastaları yazdırmak için
	void hastaSırala();//hastalık durumuna göre hasta sıralamak için
	void ameliyatBilgiListesiDAIRESEL();//hasta girişi yapıldığında ameliyat olacak hastaları yazdırmak için
	int hastaSay();//hasta sayısını öğrenmek için
	hasta* dugumAdresiGetir(int);//hastaları sıralarken bağlı listedeki elemanları işaretçi dizisine aktarıp yazdırmak için
	hasta(string, int, int, int, string, string);
	int ameliyatSay();


};

void hasta::basaHASTAekleDAİRESEL(hasta* yeni) {
	hasta* gec = h_ilk;
	if (h_ilk == NULL) { h_ilk = yeni; }
	else {
		h_ilk->h_önceki = yeni;
		yeni->h_sonraki = h_ilk;
		h_ilk = yeni;
		h_ilk->h_önceki = h_son;
	}
}
hasta::hasta(string a_s, int y, int d, int id, string h_h, string h_M)
{
	this->h_adsoyad = a_s;
	this->h_yas = y;
	this->h_durum = d;
	this->h_id = id;
	this->h_hastasi = h_h;
	this->h_muayeneTarihi = h_M;
	this->h_sonraki == NULL;
	this->h_önceki == NULL;

}
void hasta::hastaEkle(hasta* yeni) {
	hasta* gec = h_ilk;
	if (h_ilk == NULL) { h_ilk = yeni; }
	else if (gec->h_sonraki == NULL)
	{
		gec->h_sonraki = yeni;
		yeni->h_önceki = gec;
		yeni = h_son;
	}
	else
	{
		while (gec->h_sonraki != NULL) { gec = gec->h_sonraki; }
		gec->h_sonraki = yeni;
		yeni->h_önceki = gec;
		yeni = h_son;
	}
}
void hasta::hastaSil(int id) {
	hasta* gec = h_ilk;
	while (gec->h_id != id) { gec = gec->h_sonraki; }

	if (gec->h_önceki == NULL)
	{
		if (gec->h_sonraki == NULL) { delete gec; }
		else
		{
			hasta* temp = gec->h_sonraki;
			temp->h_önceki = NULL;
			delete gec;
			h_ilk = temp;
		}
	}
	else if (gec->h_sonraki == NULL)
	{
		hasta* temp = gec->h_önceki;
		temp->h_sonraki = NULL;
		delete gec;
		h_son = temp;
	}
	else
	{
		hasta* temp = gec->h_önceki;
		temp->h_sonraki = gec->h_sonraki;
		gec->h_sonraki->h_önceki = temp;
		delete gec;
	}
}
void hasta::hastabilgilistesiyazdir() {
	hasta* gec = h_ilk;
	cout << "+----------------------+" << endl;
	cout << "| neredeyse hazır..... |" << endl;
	cout << "+----------------------+" << endl << endl;
	cout << '+';
	for (int i = 0; i < 216; i++) { cout << '-'; }
	cout << '+' << endl;
	cout << setw(27) << left << "id :" << setw(27) << left << "ad_soyad :" << setw(27) << left << "yaşı :" << setw(27) << left << "hastalığı :" << setw(27) << left << "tehlike derecesi(10) :" << setw(27) << left << "muayene tarihi : " << setw(27) << left << "hastanın ameliyat durumu : " << setw(27) << left << "ameliyat tarihi :  " << '|' << endl;
	cout << '+';
	for (int i = 0; i < 216; i++) { cout << '-'; }
	cout << '+' << endl;
	while (gec->h_sonraki != NULL)
	{
		cout << setw(27) << left << gec->h_id << setw(27) << left << gec->h_adsoyad << setw(27) << left << gec->h_yas << setw(27) << left << gec->h_hastasi << setw(27) << left << gec->h_durum << setw(27) << left << gec->h_muayeneTarihi;
		if (gec->h_ameliyat_durumu == "EVET") { cout << setw(27) << left << gec->h_ameliyat_durumu << setw(27) << left << gec->h_ameliyatTarihi << " |" << endl; }
		else { cout << setw(27) << left << "HAYIR" << setw(27) << left << "______" << " |" << endl; }
		gec = gec->h_sonraki;
		if (gec == h_ilk) { break; }
	}
	cout << setw(27) << left << gec->h_id << setw(27) << left << gec->h_adsoyad << setw(27) << left << gec->h_yas << setw(27) << left << gec->h_hastasi << setw(27) << left << gec->h_durum << setw(27) << left << gec->h_muayeneTarihi;
	if (gec->h_ameliyat_durumu == "EVET") { cout << setw(27) << left << gec->h_ameliyat_durumu << setw(27) << left << gec->h_ameliyatTarihi << " |" << endl; }
	else { cout << setw(27) << left << "HAYIR" << setw(27) << left << "______" << " |" << endl; }
	cout << '+';
	for (int i = 0; i < 216; i++) { cout << '-'; }
	cout << '+' << endl;
	cout << "| başarıyla yazdırıldı .... |" << endl;
	cout << "+---------------------------+" << endl << endl;
}
void hasta::ameliyatEkle(int id, string tarih) {
	hasta* gec = h_ilk;
	while (gec->h_id != id) { gec = gec->h_sonraki; }

	gec->h_ameliyat_durumu = "EVET";
	gec->h_ameliyatTarihi = tarih;
}
void hasta::ameliyatSil(int id) {
	hasta* gec = h_ilk;
	while (gec->h_id != id) { gec = gec->h_sonraki; }
	gec->h_ameliyat_durumu = "HAYIR";
	gec->h_ameliyatTarihi = "------";
}
int hasta::ameliyat_ucreti_hesapla(int id, string sigorta) {
	hasta* gec = h_ilk;
	while (gec->h_id != id) { gec = gec->h_sonraki; }
	if (gec->h_ameliyat_durumu == "EVET" && gec->h_ameliyatucreti != 0) { return gec->h_ameliyatucreti; }
	if (gec->h_ameliyat_durumu == "EVET")
	{
		if (sigorta == "ssk") { gec->h_ameliyatucreti = 70000 / 10; }
		else if (sigorta == "emekli sigortası") { gec->h_ameliyatucreti = 70000 / 70; }
		else { gec->h_ameliyatucreti = 70000; }
		return gec->h_ameliyatucreti;
	}
	else { return 0; }

}
void hasta::hastaBilgisi(int id) {
	hasta* gec = h_ilk;
	while (gec->h_id != id) { gec = gec->h_sonraki; }
	cout << setw(33) << setw(17) << "+--------------+" << setw(33) << endl;
	cout << setw(33) << setw(17) << "|ŞİFA HASTANESİ|" << setw(33) << endl;
	cout << setw(33) << setw(17) << "+--------------+" << endl << endl << endl;
	cout << '+';
	for (int i = 0; i < 79; i++) { cout << '-'; }
	cout << '+' << endl;
	cout << setw(40) << left << "| BİLGİ FONKSYONU " << setw(40) << left << "BİLGİ" << "|" << endl;
	cout << setw(40) << left << "| AD_SOYAD : " << setw(40) << left << gec->h_adsoyad << "|" << endl;
	cout << setw(40) << left << "| İD : " << setw(40) << left << gec->h_id << "|" << endl;
	cout << setw(40) << left << "| YAŞ : " << setw(40) << left << gec->h_yas << "|" << endl;
	cout << setw(40) << left << "| MUAYENE TARİHİ : " << setw(40) << left << gec->h_muayeneTarihi << "|" << endl;
	cout << setw(40) << left << "| HASTALIĞI : " << setw(40) << left << gec->h_hastasi << "|" << endl;
	cout << setw(40) << left << "| HASTALIK ŞİDDETİ : " << setw(40) << left << gec->h_durum << "|" << endl;
	cout << setw(40) << left << "| AMELİYAT DURUMU :  " << setw(40) << left << gec->h_ameliyat_durumu << "|" << endl;
	cout << setw(40) << left << "| AMELİYAT TARİHİ : " << setw(40) << left << gec->h_ameliyatTarihi << "|" << endl;
	if (gec->h_ameliyat_durumu == "EVET" && gec->h_ameliyatucreti == 0)
	{
		gec->h_ameliyatucreti = (rand() % 10000) + 7000;
		cout << setw(40) << left << "| AMELİYAT ÜCRETİ : " << setw(40) << left << gec->h_ameliyatucreti << "|" << endl;
	}
	else { cout << setw(40) << left << "| AMELİYAT ÜCRETİ : " << setw(40) << left << gec->h_ameliyatucreti << "|" << endl; }
	cout << '+';
	for (int i = 0; i < 79; i++) { cout << '-'; }
	cout << '+' << endl;
}
void hasta::ameliyatBilgiListesi() {
	hasta* gec = h_ilk;
	cout << "+----------------------+" << endl;
	cout << "| neredeyse hazır..... |" << endl;
	cout << "+----------------------+" << endl << endl;
	cout << '+';
	for (int i = 0; i < 216; i++) { cout << '-'; }
	cout << '+' << endl;
	cout << setw(27) << left << "id :" << setw(27) << left << "ad_soyad :" << setw(27) << left << "yaşı :" << setw(27) << left << "hastalığı :" << setw(27) << left << "tehlike derecesi(10) :" << setw(27) << left << "muayene tarihi : " << setw(27) << left << "hastanın ameliyat durumu : " << setw(27) << left << "ameliyat tarihi :  " << " |" << endl;
	cout << '+';
	for (int i = 0; i < 216; i++) { cout << '-'; }
	cout << '+' << endl;
	while (gec->h_sonraki != NULL)
	{
		if (gec->h_ameliyat_durumu == "EVET") { cout << setw(27) << left << gec->h_id << setw(27) << left << gec->h_adsoyad << setw(27) << left << gec->h_yas << setw(27) << left << gec->h_hastasi << setw(27) << left << gec->h_durum << setw(27) << left << gec->h_muayeneTarihi << setw(27) << left << gec->h_ameliyat_durumu << setw(27) << left << gec->h_ameliyatTarihi << " |" << endl; }
		gec = gec->h_sonraki;
	}
	cout << '+';
	for (int i = 0; i < 216; i++) { cout << '-'; }
	cout << '+' << endl << endl;
	cout << "başarıyla yazdırıldı ........" << endl;
}
void hasta::hastaRaporuÇıktısı(int id) {
	hasta* gec = h_ilk;
	while (gec->h_id != id) { gec = gec->h_sonraki; }
	ofstream Rapor("rapor.txt", ios::out);
	Rapor << setw(33) << setw(17) << "+--------------+" << setw(33) << endl;
	Rapor << setw(33) << setw(17) << "|ŞİFA HASTANESİ|" << setw(33) << endl;
	Rapor << setw(33) << setw(17) << "+--------------+" << endl << endl << endl;
	Rapor << '+';
	for (int i = 0; i < 79; i++) { Rapor << '-'; }
	Rapor << '+' << endl;
	Rapor << setw(40) << left << "| BİLGİ FONKSYONU " << setw(40) << left << "BİLGİ" << "|" << endl;
	Rapor << setw(40) << left << "| AD_SOYAD : " << setw(40) << left << gec->h_adsoyad << "|" << endl;
	Rapor << setw(40) << left << "| İD : " << setw(40) << left << gec->h_id << "|" << endl;
	Rapor << setw(40) << left << "| YAŞ : " << setw(40) << left << gec->h_yas << "|" << endl;
	Rapor << setw(40) << left << "| MUAYENE TARİHİ : " << setw(40) << left << gec->h_muayeneTarihi << "|" << endl;
	Rapor << setw(40) << left << "| HASTALIĞI : " << setw(40) << left << gec->h_hastasi << "|" << endl;
	Rapor << setw(40) << left << "| HASTALIK ŞİDDETİ : " << setw(40) << left << gec->h_durum << "|" << endl;
	Rapor << setw(40) << left << "| AMELİYAT DURUMU :  " << setw(40) << left << gec->h_ameliyat_durumu << "|" << endl;
	Rapor << setw(40) << left << "| AMELİYAT TARİHİ : " << setw(40) << left << gec->h_ameliyatTarihi << "|" << endl;
	if (gec->h_ameliyat_durumu == "EVET" && gec->h_ameliyatucreti == 0)
	{
		gec->h_ameliyatucreti = (rand() % 10000) + 7000;
		Rapor << setw(40) << left << "| AMELİYAT ÜCRETİ : " << setw(40) << left << gec->h_ameliyatucreti << "|" << endl;
	}
	else { Rapor << setw(40) << left << "| AMELİYAT ÜCRETİ : " << setw(40) << left << gec->h_ameliyatucreti << "|" << endl; }


}
void hasta::hastaBilgiYazdırDAIRESEL() {
	hasta* gec = h_ilk;
	cout << "+----------------------+" << endl;
	cout << "| neredeyse hazır..... |" << endl;
	cout << "+----------------------+" << endl << endl;
	cout << '+';
	for (int i = 0; i < 216; i++) { cout << '-'; }
	cout << '+' << endl;
	cout << setw(27) << left << "id :" << setw(27) << left << "ad_soyad :" << setw(27) << left << "yaşı :" << setw(27) << left << "hastalığı :" << setw(27) << left << "tehlike derecesi(10) :" << setw(27) << left << "muayene tarihi : " << setw(27) << left << "hastanın ameliyat durumu : " << setw(27) << left << "ameliyat tarihi :    " << " |" << endl;
	cout << '+';
	for (int i = 0; i < 216; i++) { cout << '-'; }
	cout << '+' << endl;
	while (gec->h_sonraki != h_ilk)
	{
		cout << setw(27) << left << gec->h_id << setw(27) << left << gec->h_adsoyad << setw(27) << left << gec->h_yas << setw(27) << left << gec->h_hastasi << setw(27) << left << gec->h_durum << setw(27) << left << gec->h_muayeneTarihi;
		if (gec->h_ameliyat_durumu == "EVET") { cout << setw(27) << left << gec->h_ameliyat_durumu << setw(27) << left << gec->h_ameliyatTarihi << " |" << endl; }
		else { cout << setw(27) << left << "HAYIR" << setw(27) << left << "______" << " |" << endl; }
		gec = gec->h_sonraki;
	}
	cout << setw(27) << left << gec->h_id << setw(27) << left << gec->h_adsoyad << setw(27) << left << gec->h_yas << setw(27) << left << gec->h_hastasi << setw(27) << left << gec->h_durum << setw(27) << left << gec->h_muayeneTarihi;
	if (gec->h_ameliyat_durumu == "EVET") { cout << setw(27) << left << gec->h_ameliyat_durumu << setw(27) << left << gec->h_ameliyatTarihi << " |" << endl; }
	else { cout << setw(27) << left << "HAYIR" << setw(27) << left << "______" << " |" << endl; }
	cout << '+';
	for (int i = 0; i < 216; i++) { cout << '-'; }
	cout << '+' << endl;
	cout << endl << endl << "başarıyla yazdırıldı ...." << endl;

}
hasta* hasta::dugumAdresiGetir(int indis) {
	hasta* gec = h_ilk;
	for (int i = 0; i < indis; i++)
	{
		gec = gec->h_sonraki;
		if (gec == h_ilk) { return NULL; }
	}
	return gec;
}
void hasta::hastaSırala() {

	hasta* dizi[20];
	for (int i = 0; i < 20; i++) { dizi[i] = dugumAdresiGetir(i); }
	for (int i = 0; i < hastaSay() - 1; ++i) {
		for (int j = 0; j < hastaSay() - i - 1; ++j) {
			if (dizi[j]->h_durum < dizi[j + 1]->h_durum) {
				hasta* gec = dizi[j];
				dizi[j] = dizi[j + 1];
				dizi[j + 1] = gec;
			}
		}
	}
	cout << "+----------------------+" << endl;
	cout << "| neredeyse hazır..... |" << endl;
	cout << "+----------------------+" << endl << endl;
	cout << '+';
	for (int i = 0; i < 216; i++) { cout << '-'; }
	cout << '+' << endl;
	cout << setw(27) << left << "id :" << setw(27) << left << "ad_soyad :" << setw(27) << left << "yaşı :" << setw(27) << left << "hastalığı :" << setw(27) << left << "tehlike derecesi(10) :" << setw(27) << left << "muayene tarihi : " << setw(27) << left << "hastanın ameliyat durumu : " << setw(27) << left << "ameliyat tarihi :    " << " |" << endl;
	cout << '+';
	for (int i = 0; i < 216; i++) { cout << '-'; }
	cout << '+' << endl;
	for (int i = 0; i < hastaSay(); i++)
	{
		cout << setw(27) << left << dizi[i]->h_id << setw(27) << left << dizi[i]->h_adsoyad << setw(27) << left << dizi[i]->h_yas << setw(27) << left << dizi[i]->h_hastasi << setw(27) << left << dizi[i]->h_durum << setw(27) << left << dizi[i]->h_muayeneTarihi;
		if (dizi[i]->h_ameliyat_durumu == "EVET") { cout << setw(27) << left << dizi[i]->h_ameliyat_durumu << setw(27) << left << dizi[i]->h_ameliyatTarihi << " |" << endl; }
		else { cout << setw(27) << left << "HAYIR" << setw(27) << left << "______" << " |" << endl; }
	}
	cout << '+';
	for (int i = 0; i < 216; i++) { cout << '-'; }
	cout << '+' << endl;
	cout << "başarıyla yazdırıldı ...." << endl;
}
void hasta::ameliyatBilgiListesiDAIRESEL() {
	hasta* gec = h_ilk;
	cout << "+----------------------+" << endl;
	cout << "| neredeyse hazır..... |" << endl;
	cout << "+----------------------+" << endl << endl;
	cout << '+';
	for (int i = 0; i < 216; i++) { cout << '-'; }
	cout << '+' << endl;
	cout << setw(27) << left << "id :" << setw(27) << left << "ad_soyad :" << setw(27) << left << "yaşı :" << setw(27) << left << "hastalığı :" << setw(27) << left << "tehlike derecesi(10) :" << setw(27) << left << "muayene tarihi : " << setw(27) << left << "hastanın ameliyat durumu : " << setw(27) << left << "ameliyat tarihi :  " << " |" << endl;
	cout << '+';
	for (int i = 0; i < 216; i++) { cout << '-'; }
	cout << '+' << endl;
	while (gec->h_sonraki != h_ilk)
	{
		if (gec->h_ameliyat_durumu == "EVET") { cout << setw(27) << left << gec->h_id << setw(27) << left << gec->h_adsoyad << setw(27) << left << gec->h_yas << setw(27) << left << gec->h_hastasi << setw(27) << left << gec->h_durum << setw(27) << left << gec->h_muayeneTarihi << setw(27) << left << gec->h_ameliyat_durumu << setw(27) << left << gec->h_ameliyatTarihi << " |" << endl; }
		gec = gec->h_sonraki;
	}
	if (gec->h_ameliyat_durumu == "EVET") { cout << setw(27) << left << gec->h_id << setw(27) << left << gec->h_adsoyad << setw(27) << left << gec->h_yas << setw(27) << left << gec->h_hastasi << setw(27) << left << gec->h_durum << setw(27) << left << gec->h_muayeneTarihi << setw(27) << left << gec->h_ameliyat_durumu << setw(27) << left << gec->h_ameliyatTarihi << " |" << endl; }
	cout << '+';
	for (int i = 0; i < 216; i++) { cout << '-'; }
	cout << '+' << endl;
	cout << "başarıyla yazdırıldı ........" << endl;
}
int hasta::hastaSay() {
	hasta* gec = h_ilk;
	int sayac = 1;
	if (h_ilk->h_önceki == NULL)
	{while (gec->h_sonraki != NULL){gec = gec->h_sonraki;sayac++;}return sayac;}
	else
	{while (gec->h_sonraki != h_ilk){gec = gec->h_sonraki;sayac++;}return sayac;}
}
int hasta::ameliyatSay() {
	hasta* gec = h_ilk;
	int sayac = 1;
	if (h_ilk->h_önceki == NULL)
	{while (gec->h_sonraki != NULL){if (gec->h_ameliyat_durumu == "EVET"){sayac++;}gec = gec->h_sonraki;}return sayac;}
	else
	{while (gec->h_sonraki != h_ilk){if (gec->h_ameliyat_durumu == "EVET"){sayac++;}gec = gec->h_sonraki;}return sayac;}

}
class doktor
{
public:
	//doktor bilgileri
	string adsoyad;
	int sifre;
	int degerlendirmepuanı;

	//bağlı liste için
	doktor* d_önceki;
	doktor* d_sonraki;
	doktor* d_ilk;
	doktor* d_son;
	void basadoktorEkle(doktor*);
	void sonadoktorEkle(doktor*);
	void arayadoktorEkle(doktor*, string);
	void doktorSil(int);
	int doktorSay();
	void sifreDegistir(int, int);
	int degerlendirmePuanı(int);
	bool sifreKontrolu(string, int);
	int doktoruDegerlendir(string, int);
	void doktorlariYazdir();
	doktor(string, int, int);
	friend hasta;

};

doktor::doktor(string a_s, int s, int d_p)
{
	this->adsoyad = a_s;
	this->sifre = s;
	this->degerlendirmepuanı = d_p;
	d_önceki == NULL;
	d_sonraki == NULL;
}
void doktor::basadoktorEkle(doktor* yeni) {
	doktor* gec = d_ilk;
	if (d_ilk == NULL) { d_ilk = yeni; }
	else
	{
		d_ilk->d_önceki = yeni;
		yeni->d_sonraki = d_ilk;
		d_ilk = yeni;
		d_ilk->d_önceki = nullptr;
	}

}
void doktor::sonadoktorEkle(doktor* yeni) {
	doktor* gec = d_ilk;
	while (gec->d_sonraki != NULL) { gec = gec->d_sonraki; }
	gec->d_sonraki = yeni;
	yeni->d_önceki = gec;
	yeni = d_son;
}
void doktor::arayadoktorEkle(doktor* yeni, string a_s) {
	doktor* gec = d_ilk;
	if (gec->adsoyad == a_s)
	{
		gec->d_sonraki = yeni;
		yeni->d_önceki = gec;
		yeni = d_son;
	}
	while (gec->adsoyad != a_s) { gec = gec->d_sonraki; }
	doktor* gecici = gec->d_sonraki;
	gec->d_sonraki = yeni;
	yeni->d_önceki = gec;
	yeni->d_sonraki = gecici;
	gecici->d_önceki = yeni;
}
void doktor::doktorSil(int id) {
	doktor* gec = d_ilk;
	if (gec->sifre == id)
	{
		gec->d_sonraki->d_önceki == NULL;
		gec->d_sonraki = d_ilk;
		delete gec;
	}
	while (gec->sifre != id) { gec = gec->d_sonraki; }
	if (gec->d_sonraki == NULL)
	{
		gec->d_önceki->d_sonraki == NULL;
		gec->d_önceki = d_son;
		gec->d_önceki == NULL;
		delete gec;
	}
	else
	{
		gec->d_önceki->d_sonraki = gec->d_sonraki;
		gec->d_sonraki->d_önceki = gec->d_önceki;
		delete gec;
	}
}
int doktor::doktorSay() {
	doktor* gec = d_ilk;
	if (gec == NULL)
	{
		int sayac = 0;
		return sayac;
	}
	if (gec->d_önceki == NULL)
	{
		int sayac = 1;
		while (gec->d_sonraki != NULL)
		{
			gec = gec->d_sonraki;
			sayac++;
		}
		return sayac;

	}
	else
	{
		int sayac = 1;
		while (gec->d_sonraki != d_ilk)
		{
			gec = gec->d_sonraki;
			sayac++;
		}
		return sayac;
	}

}
void doktor::sifreDegistir(int eskisifre, int yenisifre) {
	doktor* gec = d_ilk;
	while (gec->sifre != eskisifre) { gec = gec->d_sonraki; }
	gec->sifre = yenisifre;
}
int doktor::degerlendirmePuanı(int sifre) {
	doktor* gec = d_ilk;
	while (gec->sifre != sifre) { gec = gec->d_sonraki; }
	return gec->degerlendirmepuanı;
}
bool doktor::sifreKontrolu(string a_s, int d_sifre) {
	doktor* gec = d_ilk;
	while (gec->adsoyad != a_s) { gec = gec->d_sonraki; }
	if (gec->sifre == d_sifre) { return true; }
	else { return false; }
}
int doktor::doktoruDegerlendir(string a_s, int puan) {
	doktor* gec = d_ilk;
	while (gec->adsoyad != a_s) { gec = gec->d_sonraki; }
	gec->degerlendirmepuanı = puan;
	return puan;
}
void doktor::doktorlariYazdir() {
	doktor* gec = d_ilk;
	cout << endl << "+---------------------+" << endl;
	cout << "| neredeyse hazır ... |" << endl;
	cout << "+---------------------+" << endl;
	cout << "+-----------------------------------------------------------------------------------------+" << endl;
	cout << setw(29) << left << "| id :" << setw(29) << left << "| ad_soyad :" << setw(32) << left << "| puanı : " << "|" << endl;
	cout << "+-----------------------------------------------------------------------------------------+" << endl;
	if (gec->d_önceki == NULL)
	{
		while (gec->d_sonraki != NULL)
		{
			cout << setw(30) << left << gec->sifre << setw(30) << left << gec->adsoyad << setw(20) << left << gec->degerlendirmepuanı << " ";
			for (int i = gec->degerlendirmepuanı; i > 0; i--) { cout << '*'; }
			cout << endl;
			gec = gec->d_sonraki;
		}
		cout << setw(30) << left << gec->sifre << setw(30) << left << gec->adsoyad << setw(20) << left << gec->degerlendirmepuanı << " ";
		for (int i = gec->degerlendirmepuanı; i > 0; i--) { cout << '*'; }
		cout << endl;
	}
	else
	{
		while (gec->d_sonraki != d_ilk)
		{
			cout << setw(30) << left << gec->sifre << setw(30) << left << gec->adsoyad << setw(20) << left << gec->degerlendirmepuanı << " ";
			for (int i = gec->degerlendirmepuanı; i > 0; i--) { cout << '*'; }
			cout << "|" << endl;
			gec = gec->d_sonraki;
		}
		cout << setw(30) << left << gec->sifre << setw(30) << left << gec->adsoyad << setw(20) << left << gec->degerlendirmepuanı << " ";
		for (int i = gec->degerlendirmepuanı; i > 0; i--) { cout << '*'; }
		cout << endl;

	}

}


int main() {

	setlocale(LC_ALL, "turkish");

	//varsayılan doktorlar tanımlaması
	doktor* d_komuta = new doktor("  ", 2323, 4);
	doktor* d1 = new doktor("Ali HIMEYDA", 123, 5);
	d_komuta->basadoktorEkle(d1);
	doktor* d2 = new doktor("Ayşe KAPLAN", 124, 4);
	d_komuta->basadoktorEkle(d2);
	doktor* d3 = new doktor("Ahmet GÜL", 125, 2);
	d_komuta->basadoktorEkle(d3);
	doktor* d4 = new doktor("Alper DUVARBAŞI", 126, 3);
	d_komuta->basadoktorEkle(d4);
	doktor* d5 = new doktor("Emrullah KAYACAN", 127, 5);
	d_komuta->basadoktorEkle(d5);
	doktor* d6 = new doktor("Ahmet Ihsan YILMAZ", 128, 1);
	d_komuta->sonadoktorEkle(d6);
	doktor* d7 = new doktor("Eyüp ÜNAL", 129, 4);
	d_komuta->sonadoktorEkle(d7);
	doktor* d8 = new doktor("Yusuf ÇIFTÇI", 120, 3);
	d_komuta->sonadoktorEkle(d8);
	doktor* d9 = new doktor("Eda DEMIR", 133, 5);
	d_komuta->sonadoktorEkle(d9);
	doktor* d10 = new doktor("Elif MANTAM", 145, 5);
	d_komuta->sonadoktorEkle(d10);

	//varsayılan hasta tanımlanması
	hasta* h_komuta = new hasta("  ", 3, 4, 5, "sad", "    ");
	hasta* h1 = new hasta("Berat KAYA", 14, 5, 324, "grip", "20.05.2024");
	h_komuta->hastaEkle(h1);
	hasta* h2 = new hasta("Ahmet YÜKSEL", 25, 8, 345, "astım", "20.05.2024");
	h_komuta->hastaEkle(h2);
	h_komuta->ameliyatEkle(345, "10.06.2024");
	h2->h_ameliyatucreti = h_komuta->ameliyat_ucreti_hesapla(345, "ssk");
	hasta* h3 = new hasta("Ali ÇAĞLAYAN", 35, 10, 534, "kanser", "22.05.2024");
	h_komuta->hastaEkle(h3);
	h_komuta->ameliyatEkle(534, "10.07.2024");
	h3->h_ameliyatucreti = h_komuta->ameliyat_ucreti_hesapla(534, "yok");
	hasta* h4 = new hasta("Kerem DEMIR", 19, 4, 978, "eklem iltihabı", "22.05.2024");
	h_komuta->hastaEkle(h4);
	hasta* h5 = new hasta("Mustafa BILEN", 15, 2, 543, "grip", "23.05.2024");
	h_komuta->hastaEkle(h5);
	hasta* h6 = new hasta("Halil ÇAPA", 23, 7, 321, "bağırsak iltihabı", "23.05.2024");
	h_komuta->hastaEkle(h6);
	h_komuta->ameliyatEkle(321, "01.06.2024");
	h6->h_ameliyatucreti = h_komuta->ameliyat_ucreti_hesapla(321, "ssk");
	hasta* h7 = new hasta("Burak KAAN", 47, 10, 974, "kalp yetmezliği", "25.05.2024");
	h_komuta->hastaEkle(h7);
	h_komuta->ameliyatEkle(974, "30.05.2024");
	h7->h_ameliyatucreti = h_komuta->ameliyat_ucreti_hesapla(974, "emekli sigortası");
	hasta* h8 = new hasta("Eyüp FIDAN", 39, 4, 123, "grip", "26.05.2024");
	h_komuta->hastaEkle(h8);
	hasta* h9 = new hasta("Mehmet CAN", 28, 3, 456, "grip", "27.05.2024");
	h_komuta->hastaEkle(h9);
	hasta* h10 = new hasta("Faruk URUN", 56, 8, 657, "grip", "29.05.2024");
	h_komuta->hastaEkle(h10);

	//gerekli veriler
	int secim;
	int sayac;
	int sifre;
	int secim1;
	int secim2;
	int secim3;
	bool deger;
	char secenek;
	string giris;
	string giris1;
	string giris2;
	doktor* d_yeni;
	hasta* h_yeni;
	//hastanede bulunan klinikler
	string klinikdizi[10] = { "Dahiliye Kliniği","Cerrahi Kliniği","Pediatri Kliniği","Kadın Hastalıkları ve Doğum Kliniği","Kardiyoloji Kliniği","Ortopedi ve Travmatoloji Kliniği","Göz Hastalıkları Kliniği","Kulak Burun Boğaz Kliniği","Dermatoloji Kliniği","Psikiyatri Kliniği" };
	cout << setw(40) << right << "+" << "----------------+" << endl;
	cout << setw(40) << right << "|" << " ŞİFA HASTANESİ |" << endl;
	cout << setw(40) << right << "+" << "----------------+" << endl;
A5:
	cout << setw(63) << right << "şifa hastanesine hoşgeldiniz " << endl;
	cout << endl << endl;
	cout << "+-----------------------------+" << endl;
	cout << "|1) doktor girişi.            |" << endl;
	cout << "+-----------------------------+" << endl;
	cout << "|2) hasta girişi.             |" << endl;
	cout << "+-----------------------------+" << endl;
	cout << "|3) hastaneye genel bakış.    |" << endl;
	cout << "+-----------------------------+" << endl;
	cout << endl << "giriş tipini seçiniz --> ";
	cin >> secim;
	cout << endl << endl;
	switch (secim)
	{
	case 1:
		//eğer hasta girişinden sonra tekrar doktor girişi yapılırsa çift yönlü bağlı listeyi daireselden düze 
		if (d_komuta->d_ilk->d_önceki != NULL)
		{
			//doktor nesnelerini çift yönlü bağlı liste yapısına aktarma kısmı
			{
				doktor* gec = d_komuta->d_ilk;
				while (gec->d_sonraki != d_komuta->d_ilk) { gec = gec->d_sonraki; }
				gec->d_sonraki = NULL;
				d_komuta->d_ilk->d_önceki = NULL;
			}
			//hasta nesnelerini çift yönlü bağlı liste yapısına aktarma kısmı
			{
				hasta* gec = h_komuta->h_ilk;
				while (gec->h_sonraki != h_komuta->h_ilk) { gec = gec->h_sonraki; }
				gec->h_sonraki = NULL;
				h_komuta->h_ilk->h_önceki = NULL;
			}
		}

		cout << "hesabınız var mı ? (e/h)";
		cin >> secenek;
		if (secenek == 'e')
		{
			cout << "ad ve soyadınızı giriniz --> ";
			cin.ignore();
			getline(cin, giris);
			cout << endl;
			cout << "+-------------------------------------------+" << endl;
			cout << "|hoş geldiniz sayın " << giris << "             |" << endl;
			cout << "+-------------------------------------------+" << endl;
		A2:
			cout << "sifrenizi giriniz --> ";
			cin >> sifre;
			deger = d_komuta->sifreKontrolu(giris, sifre);
			if (deger == false)//şifre yanlış ise 5 deneme şansı sunulacak
			{
				int i = 0;
				while (i != 5)
				{
					cout << "şifre yanlış" << endl;
					cout << "tekrar deneyiniz --> ";
					cin >> sifre;
					deger = d_komuta->sifreKontrolu(giris, sifre);
					if (deger == true) { goto A1; }
					i++;
				}
				cout << "+-------------------------------------+" << endl;
				cout << "| deneme hakkınız dolmuştur           |" << endl;
				cout << "| 60 saniye sonra tekrar deneyiniz... |" << endl;
				cout << "+-------------------------------------+" << endl;
				chrono::seconds sure(60);
				auto baslangic = chrono::steady_clock::now();
				while (chrono::steady_clock::now() - baslangic < sure) {
					// Boş döngü
				}
				cout << "60 dakika bitti!" << endl;
				goto A2;
			}
		A1:
			cout << endl << endl;
			cout << "+-----------------------------------------+" << endl;
			cout << "|1) hasta ekle                            |" << endl;
			cout << "+-----------------------------------------+" << endl;
			cout << "|2) hasta sil                             |" << endl;
			cout << "+-----------------------------------------+" << endl;
			cout << "|3) ameliyat ekle                         |" << endl;
			cout << "+-----------------------------------------+" << endl;
			cout << "|4) ameliyat sil                          |" << endl;
			cout << "+-----------------------------------------+" << endl;
			cout << "|5) hasta detay listesi yazdır            |" << endl;
			cout << "+-----------------------------------------+" << endl;
			cout << "|6) ameliyat detay listesi yazdır         |" << endl;
			cout << "+-----------------------------------------+" << endl;
			cout << "|7) hastanın ameliyat ücretini hesapla    |" << endl;
			cout << "+-----------------------------------------+" << endl;
			cout << "|8) hastaya ait bilgi listesi yazdır      |" << endl;
			cout << "+-----------------------------------------+" << endl;
			cout << "|9) hasta için rapor dosyası oluştur      |" << endl;
			cout << "+-----------------------------------------+" << endl;
			cout << "|10) hesap işlemleri                      |" << endl;
			cout << "+-----------------------------------------+" << endl;
			cout << "|11) ana menuye dön                       |" << endl;
			cout << "+-----------------------------------------+" << endl;
			cout << "|12) çıkış                                |" << endl;
			cout << "+-----------------------------------------+" << endl;
			cout << endl << endl;
			cout << "gerçekleştirmek istediğiniz işlemin numarasını giriniz --> ";
			cin >> secim;
			switch (secim)
			{

			case 1:
				cout << endl << endl << "hastanın ad_soyadını giriniz --> ";
				cin.ignore();
				getline(cin, giris);
				cout << endl << "hastanın yaşını giriniz --> ";
				cin >> secim;
				cout << endl << "hastanın hastalık şiddetinin 10'luk değerini giriniz --> ";
				cin >> secim1;
				cout << endl << "hastanın İD'ini giriniz --> ";
				cin >> secim2;
				cout << endl << "hastanın hastalık türünü giriniz --> ";
				cin.ignore();
				getline(cin, giris1);
				cout << endl << "muayene tarihi giriniz --> ";
				cin >> giris2;
				h_yeni = new hasta(giris, secim, secim1, secim2, giris1, giris2);
				h_komuta->hastaEkle(h_yeni);
				cout << endl << "+---------------------+" << endl;
				cout << "|başarıyla eklendi ...|" << endl;
				cout << "+---------------------+" << endl;
				cout << endl << "başka bir işlem yapmak istiyormusunuz ? (e/h) ";
				cin >> secenek;
				if (secenek == 'e')
				{
					goto A1;
				}
				else
				{
					cout << endl << "+-----------------------------+" << endl;
					cout << "| yine bekleriz          ^_^  |" << endl;
					cout << "+-----------------------------+" << endl;
					break;
				}
			case 2:
				cout << "silinecek hastanın İD'ini giriniz --> ";
				cin >> secim;
				h_komuta->hastaSil(secim);
				cout << endl << "+---------------------+" << endl;
				cout << "|başarıyla silindi ...|" << endl;
				cout << "+---------------------+" << endl;
				cout << endl << "başka bir işlem yapmak istiyormusunuz ? (e/h) ";
				cin >> secenek;
				if (secenek == 'e')
				{
					goto A1;
				}
				else
				{
					cout << endl << "+-----------------------------+" << endl;
					cout << "| yine bekleriz          ^_^  |" << endl;
					cout << "+-----------------------------+" << endl;
					break;
				}
			case 3:

				cout << "kendisine ameliyat bilgisi eklemek istediğiniz hastanın İD'ini giriniz --> ";
				cin >> secim;
				cout << "ameliyat tarihini giriniz --> ";
				cin >> giris;
				h_komuta->ameliyatEkle(secim, giris);
				cout << endl << "+---------------------+" << endl;
				cout << "|başarıyla eklend' ...|" << endl;
				cout << "+---------------------+" << endl;
				cout << endl;
				cout << "+------------------------------------------------+" << endl;
				cout << "| Ameliyatın ücretini hesaplamak ister misiniz ? |" << endl;
				cout << "+------------------------------------------------+" << endl;
				cout << endl;
				cout << "+---------------------+" << endl;
				cout << "|e) hesapla           |" << endl;
				cout << "+---------------------+" << endl;
				cout << "|h) sonra             |" << endl;
				cout << "+---------------------+" << endl;
				cin >> secenek;
				if (secenek == 'e')
				{
					cout << endl << "hastanın sigorta tipini giriniz --> ";
					cin.ignore();
					getline(cin, giris);

					secim1 = h_komuta->ameliyat_ucreti_hesapla(secim, giris);
					cout << "+------------------------------------------+" << endl;
					cout << "| ameliyatın ücreti " << secim1 << "TL'dir |" << endl;
					cout << "+------------------------------------------+" << endl;
				}
				cout << endl << "başka bir işlem yapmak istiyormusunuz ? (e/h) ";
				cin >> secenek;
				if (secenek == 'e')
				{
					goto A1;
				}
				else
				{
					cout << endl << "+-----------------------------+" << endl;
					cout << "| yine bekleriz          ^_^  |" << endl;
					cout << "+-----------------------------+" << endl;
					break;
				}
			case 4:
				cout << "kendisinin ameliyat bilgisini silmek istediğiniz hastanın İD'ini giriniz --> ";
				cin >> secim;
				h_komuta->ameliyatSil(secim);
				cout << endl << "+---------------------+" << endl;
				cout << "|başarıyla silindi ...|" << endl;
				cout << "+---------------------+" << endl;
				cout << endl << "başka bir işlem yapmak istiyormusunuz ? (e/h) ";
				cin >> secenek;
				if (secenek == 'e')
				{
					goto A1;
				}
				else
				{
					cout << endl << "+-----------------------------+" << endl;
					cout << "| yine bekleriz          ^_^  |" << endl;
					cout << "+-----------------------------+" << endl;
					break;
				}
			case 5:
				cout << endl << endl;
				cout << endl << "+---------------------+" << endl;
				cout << "|yazdırılıyor ...     |" << endl;
				cout << "+---------------------+" << endl << endl;
				h_komuta->hastabilgilistesiyazdir();
				cout << endl << "başka bir işlem yapmak istiyormusunuz ? (e/h) ";
				cin >> secenek;
				if (secenek == 'e')
				{
					goto A1;
				}
				else
				{
					cout << endl << "+-----------------------------+" << endl;
					cout << "| yine bekleriz          ^_^  |" << endl;
					cout << "+-----------------------------+" << endl;
					break;
				}
			case 6:
				cout << endl << endl;
				cout << endl << "+---------------------+" << endl;
				cout << "|yazdırılıyor ...     |" << endl;
				cout << "+---------------------+" << endl << endl;
				h_komuta->ameliyatBilgiListesi();
				cout << endl << "başka bir işlem yapmak istiyormusunuz ? (e/h) ";
				cin >> secenek;
				if (secenek == 'e')
				{
					goto A1;
				}
				else
				{
					cout << endl << "+-----------------------------+" << endl;
					cout << "| yine bekleriz          ^_^  |" << endl;
					cout << "+-----------------------------+" << endl;
					break;
				}
			case 7:
				cout << "hastanın İD'ini giriniz --> ";
				cin >> secim;
				cout << "hastanın sigorta tipini giriniz --> ";
				cin.ignore();
				getline(cin, giris);
				secim3 = h_komuta->ameliyat_ucreti_hesapla(secim, giris);
				if (secim3 == 0)
				{
					cout << "+----------------------------------------------------------------------------------+" << endl;
					cout << "| hastanın kaydında ameliyat bilgisi bulunmadığından ücret " << secim3 << "'dır ...|" << endl << endl;
					cout << "+----------------------------------------------------------------------------------+" << endl;
				}
				else
				{
					cout << "+---------------------------------------------------------+" << endl;
					cout << "| hastanın ameliyat ücreti --> " << secim3 << " TL'dir ...|" << endl << endl;
					cout << "+---------------------------------------------------------+" << endl;
				}

				cout << endl << "başka bir işlem yapmak istiyormusunuz ? (e/h) ";
				cin >> secenek;
				if (secenek == 'e')
				{
					goto A1;
				}
				else
				{
					cout << endl << "+-----------------------------+" << endl;
					cout << "| yine bekleriz          ^_^  |" << endl;
					cout << "+-----------------------------+" << endl;
					break;
				}
			case 8:
				cout << "bilgilerini yazdırmak istediğiniz hastanın İD'ini giriniz --> ";
				cin >> secim;
				cout << endl << "+---------------------+" << endl;
				cout << "|yazdırılıyor ...     |" << endl;
				cout << "+---------------------+" << endl;
				h_komuta->hastaBilgisi(secim);
				cout << endl << endl;
				cout << endl << "başka bir işlem yapmak istiyormusunuz ? (e/h) ";
				cin >> secenek;
				if (secenek == 'e')
				{
					goto A1;
				}
				else
				{
					cout << endl << "+-----------------------------+" << endl;
					cout << "| yine bekleriz          ^_^  |" << endl;
					cout << "+-----------------------------+" << endl;
					break;
				}
			case 9:
				cout << "rapor dosyasını yazdırmak istediğiniz hastanın İD'ini giriniz --> ";
				cin >> secim;
				cout << endl << "+---------------------+" << endl;
				cout << "|yazdırılıyor ...     |" << endl;
				cout << "+---------------------+" << endl;
				h_komuta->hastaRaporuÇıktısı(secim);
				cout << "+----------------------------------------------------------------------------------+" << endl;
				cout << "|dosya hazır , konumu --> (Ali HİMEYDA VERİ YAPILARI DERSİ 1.OTOMASYON DOSYASI)    |" << endl << endl;
				cout << "+----------------------------------------------------------------------------------+" << endl;
				cout << endl << "başka bir işlem yapmak istiyormusunuz ? (e/h) ";
				cin >> secenek;
				if (secenek == 'e')
				{
					goto A1;
				}
				else
				{
					cout << endl << "+-----------------------------+" << endl;
					cout << "| yine bekleriz          ^_^  |" << endl;
					cout << "+-----------------------------+" << endl;
					break;
				}
			case 10:
				cout << endl << endl;
				cout << "+---------------------------+" << endl;
				cout << "|a) şifre değiştir          |" << endl;
				cout << "+---------------------------+" << endl;
				cout << "|b) son değerlendirme puanı |" << endl;
				cout << "+---------------------------+" << endl;
				cout << "|c) hesabımı sil            |" << endl;
				cout << "+---------------------------+" << endl << endl;
				cout << "secim yapınız --> ";
				cin >> secenek;
				if (secenek == 'a')
				{
					cout << "yeni şifrenizi giriniz -->";
					cin >> secim;
					d_komuta->sifreDegistir(sifre, secim);
					cout << endl << "+--------------------------+" << endl;
					cout << "|başarıyla değiştirildi ...|" << endl;
					cout << "+--------------------------+" << endl;
					cout << endl << "başka bir işlem yapmak istiyormusunuz ? (e/h) ";
					cin >> secenek;
					if (secenek == 'e')
					{
						goto A1;
					}
					else
					{
						cout << endl << "+-----------------------------+" << endl;
						cout << "| yine bekleriz          ^_^  |" << endl;
						cout << "+-----------------------------+" << endl;
						break;
					}
				}
				else if (secenek == 'b')
				{
					int puan = d_komuta->degerlendirmePuanı(sifre);
					cout << "+----------------------------------------------------------------------------------+" << endl;
					cout << "| son değerlendirme puanı --> " << puan << " ";
					for (int i = puan; i > 0; i--) { cout << '*'; }
					cout << "                               |" << endl;
					cout << endl;
					cout << endl << "başka bir işlem yapmak istiyormusunuz ? (e/h) ";
					cin >> secenek;
					if (secenek == 'e')
					{
						goto A1;
					}
					else
					{
						cout << endl << "+-----------------------------+" << endl;
						cout << "| yine bekleriz          ^_^  |" << endl;
						cout << "+-----------------------------+" << endl;
						break;
					}
				}
				else if (secenek == 'c')
				{
					cout << "hesabınız silinmek üzere , devam etmek ister misiniz !? (e/h) ";
					cin >> secenek;
					cout << endl;
					if (secenek == 'e')
					{
						d_komuta->doktorSil(sifre);
						goto A5;
					}
					else
					{
						cout << endl << "başka bir işlem yapmak istiyormusunuz ? (e/h) ";
						cin >> secenek;
						if (secenek == 'e')
						{
							goto A1;
						}
						else
						{
							cout << endl << "+-----------------------------+" << endl;
							cout << "| yine bekleriz          ^_^  |" << endl;
							cout << "+-----------------------------+" << endl;
							break;
						}
					}

				}
				break;
			case 11:
				goto A5;
				break;
			case 12:
				cout << endl << "+-----------------------------+" << endl;
				cout << "| yine bekleriz          ^_^  |" << endl;
				cout << "+-----------------------------+" << endl;
				break;

			default:
				cout << endl << "yanlış secim ..." << endl << endl;
				break;
			}

		}
		else
		{
			cout << "yeni bir kayıt yapalım mı (e/h) ..." << endl;
			cin >> secenek;
			if (secenek == 'h') { goto A5; }
			cout << endl << "ad_soyadınızı giriniz --> ";
			cin.ignore();
			getline(cin, giris);
			cout << endl << "sifre giriniz --> ";
			cin >> sifre;
			cout << endl << "aynı şifreyi tekrar giriniz --> ";
			cin >> secim1;
			while (sifre != secim1)
			{
				cout << "+------------------------------------------+" << endl;
				cout << "| şifreler örtüşmüyor ...                  |" << endl;
				cout << "+------------------------------------------+" << endl;
				cout << endl << "sifre giriniz --> ";
				cin >> sifre;
				cout << endl << "aynı şifreyi tekrar giriniz --> ";
				cin >> secim1;
			}
			d_yeni = new doktor(giris, sifre, 5);
			d_komuta->basadoktorEkle(d_yeni);
			cout << endl << "+---------------------+" << endl;
			cout << "|başarıyla eklendi ...|" << endl;
			cout << "+---------------------+" << endl;
			cout << endl << endl << "giriş yapılsın mı ? (e/h) ";
			cin >> secenek;
			if (secenek == 'e') { goto A1; }
			else { goto A5; }
		}
		break;
	case 2:
		if (d_komuta->d_ilk->d_önceki == NULL)
		{
			//doktor nesnelerini çift yönlü dairesel bağlı liste yapısına aktarma kısmı
			{
				doktor* gec = d_komuta->d_ilk;
				while (gec->d_sonraki != NULL)
				{
					gec = gec->d_sonraki;
				}
				d_komuta->d_ilk->d_önceki = gec;
				gec->d_sonraki = d_komuta->d_ilk;

			}
			//hasta nesnelerini çift yönlü dairesel bağlı liste yapısına aktarma kısmı
			{
				hasta* gec = h_komuta->h_ilk;
				while (gec->h_sonraki != NULL)
				{
					gec = gec->h_sonraki;
				}
				gec->h_sonraki = h_komuta->h_ilk;
				h_komuta->h_ilk->h_önceki = gec;

			}

		}
		cout << endl << endl << "+----------------------------------------------------------------------------------+" << endl;
		cout << "|                  ŞİFA HASTANESİ KONTROL SİSTEMİNE HOŞ GELDİNİZ                   |" << endl;
		cout << "+----------------------------------------------------------------------------------+" << endl << endl << endl;
	A0:
		cout << "+--------------------------------------------+" << endl;
		cout << "|1) hastane doktorlarını yazdır              |" << endl;
		cout << "+--------------------------------------------+" << endl;
		cout << "|2) hastaları yazdır                         |" << endl;
		cout << "+--------------------------------------------+" << endl;
		cout << "|3) hastaları öncelik açısından sırala       |" << endl;
		cout << "+--------------------------------------------+" << endl;
		cout << "|4) ameliyat hastalarını yazdır              |" << endl;
		cout << "+--------------------------------------------+" << endl;
		cout << "|5) doktor değerlendir                       |" << endl;
		cout << "+--------------------------------------------+" << endl;
		cout << "|6) ana menüye dön                           |" << endl;
		cout << "+--------------------------------------------+" << endl;
		cout << "|7) çıkış                                    |" << endl;
		cout << "+--------------------------------------------+" << endl;
		cout << endl;
		cout << "gerçekleştirmek istediğiniz işlemin numarasını seçiniz --> ";
		cin >> secim;
		switch (secim)
		{
		case 1:
			d_komuta->doktorlariYazdir();
			cout << endl << endl;
			cout << endl << "başka bir işlem yapmak istiyormusunuz ? (e/h) ";
			cin >> secenek;
			if (secenek == 'e')
			{
				goto A0;
			}
			else
			{
				cout << endl << "+-----------------------------+" << endl;
				cout << "| yine bekleriz          ^_^  |" << endl;
				cout << "+-----------------------------+" << endl;
				break;
			}
		case 2:

			h_komuta->hastaBilgiYazdırDAIRESEL();
			cout << endl << "başka bir işlem yapmak istiyormusunuz ? (e/h) ";
			cin >> secenek;
			if (secenek == 'e')
			{
				goto A0;
			}
			else
			{
				cout << endl << "+-----------------------------+" << endl;
				cout << "| yine bekleriz          ^_^  |" << endl;
				cout << "+-----------------------------+" << endl;
				break;
			}
		case 3:
			h_komuta->hastaSırala();
			cout << endl << "başka bir işlem yapmak istiyormusunuz ? (e/h) ";
			cin >> secenek;
			if (secenek == 'e')
			{
				goto A0;
			}
			else
			{
				cout << endl << "+-----------------------------+" << endl;
				cout << "| yine bekleriz          ^_^  |" << endl;
				cout << "+-----------------------------+" << endl;
				break;
			}
		case 4:
			h_komuta->ameliyatBilgiListesiDAIRESEL();
			cout << endl << "başka bir işlem yapmak istiyormusunuz ? (e/h) ";
			cin >> secenek;
			if (secenek == 'e')
			{
				goto A0;
			}
			else
			{
				cout << endl << "+-----------------------------+" << endl;
				cout << "| yine bekleriz          ^_^  |" << endl;
				cout << "+-----------------------------+" << endl;
				break;
			}
		case 5:
			cout << "doktorun ad_soyadını yazınız --> ";
			cin.ignore();
			getline(cin, giris);
			cout << endl << "puanı giriniz --> 5/";
			cin >> secim;
			d_komuta->doktoruDegerlendir(giris, secim);
			cout << endl << "+---------------------+" << endl;
			cout << "|puanınız eklendi  ...|" << endl;
			cout << "+---------------------+" << endl;
			cout << endl << "başka bir işlem yapmak istiyormusunuz ? (e/h) ";
			cin >> secenek;
			if (secenek == 'e')
			{
				goto A0;
			}
			else
			{
				cout << endl << "+-----------------------------+" << endl;
				cout << "| yine bekleriz          ^_^  |" << endl;
				cout << "+-----------------------------+" << endl;
				break;
			}
		case 6:
			goto A5;
		case 7:
			cout << endl << "+-----------------------------+" << endl;
			cout << "| yine bekleriz          ^_^  |" << endl;
			cout << "+-----------------------------+" << endl;
			break;

		default:
			cout << "+----------------------------------------------------------------------------------+" << endl;
			cout << "| yanlış seçim    !!!                                                              |" << endl;
			cout << "+----------------------------------------------------------------------------------+" << endl;
			cout << endl << endl;
			goto A5;

		}
		break;
	case 3:

		cout << endl << endl << endl << endl;
		cout << "+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
		cout << "|                                                                              ŞİFA HASTANESİ                                                                                      |" << endl;
		cout << "+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
		cout << endl << endl << endl << endl;
		cout << "+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
		cout << "| " << setw(176) << left << "Hastane Genel Bakışı :" << " |" << endl << "|" << setw(179) << right << "|" << endl;
		cout << "| " << setw(176) << left << "Şifa Hastanesi, İSTANBUL ÜMRANİYE ilçesi konumunda," << " |" << endl;
		cout << "| " << setw(176) << left << "şehrin sağlık ihtiyaçlarını karşılamak amacıyla modern tıbbi hizmetler sunan öncü bir sağlık kuruluşudur." << " |" << endl;
		cout << "| " << setw(176) << left << "(12.05.2020) tarihinde faaliyete geçen hastanemiz," << " |" << endl;
		cout << "| " << setw(176) << left << "o günden bu yana hastalarına kaliteli ve güvenilir sağlık hizmetleri sunma misyonunu sürdürmektedir." << " |" << endl << "|" << setw(179) << right << "|" << endl;
		cout << "| " << setw(176) << left << "Misyon ve Vizyon :" << " |" << endl << "|" << setw(179) << right << "|" << endl;
		cout << "| " << setw(176) << left << "Misyonumuz, toplumun sağlık ihtiyaçlarını karşılamak," << " |" << endl;
		cout << "| " << setw(176) << left << "hastalarımıza en yüksek kalitede tedavi ve bakımı sunmak," << " |" << endl;
		cout << "| " << setw(176) << left << "aynı zamanda tıbbi araştırmaları teşvik etmek ve toplum sağlığını iyileştirmek üzerine odaklanmıştır." << " |" << endl;
		cout << "| " << setw(176) << left << "Vizyonumuz ise sürekli yenilik ve gelişme ile hastalarımızın yaşam kalitesini artırmak ve onlara sağlıklı bir gelecek sağlamaktır." << " |" << endl << "|" << setw(179) << right << "|" << endl;
		cout << "| " << setw(176) << left << "Altyapı ve Teknoloji :" << " |" << endl << "|" << setw(179) << right << "|" << endl;
		cout << "| " << setw(176) << left << "Hastanemiz, çağdaş tıbbi teknolojiyi kullanarak teşhis," << " |" << endl;
		cout << "| " << setw(176) << left << "tedavi ve bakım süreçlerini optimize etmektedir." << " |" << endl;
		cout << "| " << setw(176) << left << "Son teknolojiye sahip medikal cihazlar, laboratuvarlar ve görüntüleme merkezleriyle donatılmış olan hastanemizde," << " |" << endl;
		cout << "| " << setw(176) << left << "uzman hekimlerimiz ve deneyimli sağlık personelimiz," << " |" << endl;
		cout << "| " << setw(176) << left << "hastalarımıza en iyi hizmeti sunmak için sürekli olarak eğitim almaktadır." << " |" << endl << "|" << setw(179) << right << "|" << endl;
		cout << "| " << setw(176) << left << "Hizmetlerimiz :" << " |" << endl << "|" << setw(179) << right << "|" << endl;
		cout << "| " << setw(176) << left << "Hastanemizde geniş bir tıbbi hizmet yelpazesi sunulmaktadır." << " |" << endl;
		cout << "| " << setw(176) << left << "Acil servisimiz 7 / 24 hizmet verirken," << " |" << endl;
		cout << "| " << setw(176) << left << "polikliniklerimizde çeşitli branşlarda uzman doktorlarımız hastalarımıza muayene ve tedavi hizmetleri sunmaktadır." << " |" << endl;
		cout << "| " << setw(176) << left << "Ameliyathanelerimizde cerrahi müdahaleler titizlikle gerçekleştirilirken," << " |" << endl;
		cout << "| " << setw(176) << left << "yoğun bakım ünitelerimiz de kritik durumdaki hastalarımıza özenle bakım sağlamaktadır." << " |" << endl;
		cout << "| " << setw(176) << left << "Ayrıca, rehabilite ve fizyoterapi merkezimiz ile psikolojik danışmanlık hizmetlerimiz de hastalarımızın tam ve hızlı bir iyileşme süreci geçirmelerini desteklemektedir." << " |" << endl << "|" << setw(179) << right << "|" << endl;
		cout << "| " << setw(176) << left << "Hastane Personeli :" << " |" << endl << "|" << setw(179) << right << "|" << endl;
		cout << "| " << setw(176) << left << "Hastanemizin en büyük değeri olan personelimiz, alanlarında uzman, deneyimli ve hasta memnuniyeti odaklıdır." << " |" << endl;
		cout << "| " << setw(176) << left << "Doktorlarımız, hemşirelerimiz, teknisyenlerimiz ve diğer sağlık personelimiz," << " |" << endl;
		cout << "| " << setw(176) << left << "hastalarımıza sıcak ve şefkatli bir ortamda hizmet sunarak onların güvenlerini kazanmayı hedeflemektedir." << " |" << endl << "|" << setw(179) << right << "|" << endl;
		cout << "| " << setw(176) << left << "Toplumsal Katkılar :" << " |" << endl << "|" << setw(179) << right << "|" << endl;
		cout << "| " << setw(176) << left << "Hastane olarak sadece hastalarımıza değil," << " |" << endl;
		cout << "| " << setw(176) << left << "aynı zamanda toplumumuza da fayda sağlamayı amaçlıyoruz." << " |" << endl;
		cout << "| " << setw(176) << left << "Sağlık eğitim programları, bilinçlendirme kampanyaları ve toplum sağlığını destekleyici etkinlikler düzenleyerek," << " |" << endl;
		cout << "| " << setw(176) << left << "toplumun sağlık bilincini artırmaya ve sağlıklı bir yaşam tarzını teşvik etmeye çalışıyoruz." << " |" << endl << "|" << setw(179) << right << "|" << endl;
		cout << "| " << setw(176) << left << "Şifa Hastanesi olarak, kalite standartlarından ödün vermeden," << " |" << endl;
		cout << "| " << setw(176) << left << "her zaman hastalarımızın yanında olmayı ve onların sağlığına kattığımız değeri artırmayı hedefliyoruz." << " |" << endl;
		cout << "+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl << endl;

		cout << "+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
		cout << "|                                                                              KLİNİKLERİMİZ                                                                                       |" << endl;
		cout << "+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
		cout << "|                                                                                                                                                                                  |" << endl;
		for (int i = 0; i < 10; i++) { cout << "| " << setw(177) << left << klinikdizi[i] << "|" << endl; }
		cout << "+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
		cout << endl;
		cout << "+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
		cout << "|                                                                              DOKTORLARIMIZ                                                                                       |" << endl;
		cout << "+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
		d_komuta->doktorlariYazdir();
		cout << endl << endl;
		cout << "+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
		cout << "|                                                                                 GENEL                                                                                            |" << endl;
		cout << "+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
		cout << endl << "kayıtta bulunan hasta sayımız :";
		sayac = h_komuta->hastaSay();
		cout << sayac << "'dir" << endl << endl;
		cout << "doktor sayımız :";
		sayac = d_komuta->doktorSay();
		cout << sayac << "'dir" << endl << endl;
		cout << "kayıtta bulunan ameliyat sayısı :";
		sayac = h_komuta->ameliyatSay();
		cout << sayac << "'dir" << endl << endl;
		cout << "ameliyattan kazandırdığımız ücretler :  1200455 TL 'dir" << endl << endl;

		cout << "+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
		cout << "|                                                                              İLETİŞİM                                                                                            |" << endl;
		cout << "+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
		cout << "| Facebook: facebook.com / shifahastanesi                                                                                                                                          |" << endl;
		cout << "| Instagram: instagram.com / shifahastanesi                                                                                                                                        |" << endl;
		cout << "| Twitter : twitter.com / shifahastanesi                                                                                                                                           |" << endl;
		cout << "| LinkedIn : linkedin.com / company / shifahastanesi                                                                                                                               |" << endl;
		cout << "| YouTube : youtube.com / c / shifahastanesi                                                                                                                                       |" << endl;
		cout << "| Pinterest : pinterest.com / shifahastanesi                                                                                                                                       |" << endl;
		cout << "| TikTok : tiktok.com / @shifahastanesi                                                                                                                                            |" << endl;
		cout << "| Snapchat : snapchat.com / add / shifahastanesi                                                                                                                                   |" << endl;
		cout << "| WhatsApp : +905551234567                                                                                                                                                         | " << endl;
		cout << "| E - posta : info@shifahastanesi.com                                                                                                                                              |" << endl;
		cout << "+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
		cout << "|                                                      2023 YILINDA ŞİFA HASTANESİ : YILLIK PERFORMANS RAPORU                                                                      |" << endl;
		cout << "+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
		cout << "| ŞİFA Hastanesi, 2023 yılında sunduğu sağlık hizmetleriyle öne çıktı.İşte rastgele seçilen sayılarla yapılan bir yıllık değerlendirme :                                           |" << endl;
		cout << "| Ameliyatlar:                                                                                                                                                                     |" << endl;
		cout << "| 2023 yılında ŞİFA Hastanesi, çeşitli cerrahi müdahaleler gerçekleştirerek toplamda 527 ameliyat gerçekleştirdi.Bu ameliyatların dağılımı şu şekildedir :                         |" << endl;
		cout << "| Kalp Cerrahisi : Hastanemiz, 134 kalp cerrahisi gerçekleştirdi.                                                                                                                  |" << endl;
		cout << "| Beyin Cerrahisi : ŞİFA Hastanesi, 182 beyin cerrahisi operasyonunu başarıyla tamamladı.                                                                                          |" << endl;
		cout << "| Ortopedik Cerrahi : Kas - iskelet sistemi rahatsızlıklarının tedavisinde lider olan hastanemiz, 211 ortopedik cerrahi müdahale gerçekleştirdi.                                   |" << endl;
		cout << "| Muayeneler :                                                                                                                                                                     |" << endl;
		cout << "| 2023 yılında ŞİFA Hastanesi, toplamda 3254 muayene gerçekleştirdi.Bu muayeneler arasında öne çıkanlar :                                                                          |" << endl;
		cout << "| Dahiliye Muayeneleri : Genel sağlık durumu ve kronik hastalıkların takibi için yapılan 1050 muayene.                                                                             |" << endl;
		cout << "| Cerrahi Muayeneler : Ameliyat öncesi değerlendirme ve cerrahi tedavi planlaması için yapılan 1183 muayene.                                                                       |" << endl;
		cout << "| Pediatrik Muayeneler : Çocuk sağlığına odaklanan hastanemiz, 1021 pediatrik muayene gerçekleştirdi.                                                                              |" << endl;
		cout << "| Hasta Sayısı ve Memnuniyeti :                                                                                                                                                    |" << endl;
		cout << "| ŞİFA Hastanesi, yüksek hasta sayısına rağmen etkili bir şekilde hizmet verdi ve hastaların memnuniyetini ön planda tuttu.                                                        |" << endl;
		cout << "| Hastaların % 89'u sağlık hizmetlerinden memnun kaldıklarını belirtirken, %94'ü de tekrar hastanemize başvuracaklarını ifade etti.                                                |" << endl;
		cout << "| Sonuç :                                                                                                                                                                          |" << endl;
		cout << "| ŞİFA Hastanesi, 2023 yılında sunduğu sağlık hizmetleri ile toplumun ihtiyaçlarını karşılamaya devam etti.Hem ameliyatlar hem de muayenelerde yüksek kalitede hizmet sunarak,     |" << endl;
		cout << "| hastaların sağlığını korumaya ve iyileştirmeye odaklandı.Gelecek yıllarda da aynı başarıyı sürdürmeyi ve sağlık alanında öncü bir kurum olmayı hedefliyoruz.                     |" << endl;
		cout << "+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl << endl;

		cout << endl << "başka bir işlem yapmak istiyormusunuz ? (e/h) ";
		cin >> secenek;
		if (secenek == 'e')
		{
			goto A5;
		}
		else
		{
			cout << endl << "+-----------------------------+" << endl;
			cout << "| yine bekleriz          ^_^  |" << endl;
			cout << "+-----------------------------+" << endl;
			break;
		}
	default:
		cout << endl << "+---------------------+" << endl;
		cout << "| yanlş seçim ...     |" << endl;
		cout << "+---------------------+" << endl << endl;
		goto A5;

	}
	system("pause");
	return 0;

}






