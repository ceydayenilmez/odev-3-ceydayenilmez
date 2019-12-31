

#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstring>

using namespace std;

struct  StudentRecord
{
	string ogrno = "";
	char cevap[100] = {};
	float ogrnot;
};

float myround(float var)
{
	float value = (int)(var * 100 + .5);
	return (float)value / 100;
}

int main()
{
	ifstream file;
	file.open("input.txt");
	
	StudentRecord ogrlist [100];
	
	

	if (file.is_open()) {
		std::string line;
		getline(file, line); //Soru sayýsý
		int soru_sayi = std::stoi(line);

		char dogru_cevap[100] = {};

		getline(file, line); //Doðru Cevaplar

		int i;
		for (i = 0; i < soru_sayi; i++) {
			dogru_cevap[i] = line[0];
			line.erase(0, 2);
		}


		i = 0;
		int found;
		int j;
		while (getline(file, line))
		{
			found = line.find(',');
			char ono[40];
			if (found != std::string::npos) {
				std::size_t length = line.copy(ono, found, 0 );
				line.erase(0, found+1);
				ono[length] = '\0';
				ogrlist[i].ogrno = ono;
			}

			for (j = 0; j < soru_sayi-1; j++) {
				found = line.find(',');
				if (found != std::string::npos) {
					if (found == 0)
						ogrlist[i].cevap[j] = ' ';
					else
						ogrlist[i].cevap[j] = line[0];
					line.erase(0, found+1);
				}
			}
			if (line[0] == '\0')
				ogrlist[i].cevap[soru_sayi-1] = ' ';
			else
				ogrlist[i].cevap[soru_sayi - 1] = line[0];
			i++;
		}
		file.close();

		float carpan;
		float ss;
		ss = soru_sayi;
		carpan = 100 / (ss * 4);
		int ogr_sayi;
		float toplam_puan;
		ogr_sayi = 0;
		toplam_puan = 0;
		for (i = 0; i < 100; i++) {
			if (ogrlist[i].ogrno != ""){
				ogrlist[i].ogrnot = 0;
				for (j = 0; j < soru_sayi; j++) {
					if (ogrlist[i].cevap[j] != ' ')
						if (ogrlist[i].cevap[j] == dogru_cevap[j])
							ogrlist[i].ogrnot = ogrlist[i].ogrnot + 4;
						else
							ogrlist[i].ogrnot = ogrlist[i].ogrnot - 1;
				}
				ogrlist[i].ogrnot = ogrlist[i].ogrnot * carpan;
				if (ogrlist[i].ogrnot < 0)
					ogrlist[i].ogrnot = 0;
				ogr_sayi++;
				toplam_puan = toplam_puan + ogrlist[i].ogrnot;
			}
		}

		StudentRecord temp_ogrlist;
		for (i = 0; i<ogr_sayi; i++) {
			for (j = i + 1; j<ogr_sayi; j++)
			{
				if (ogrlist[i].ogrnot < ogrlist[j].ogrnot) {
					temp_ogrlist = ogrlist[i];
					ogrlist[i] = ogrlist[j];
					ogrlist[j] = temp_ogrlist;
				}
			}
		}

		float ortalama;
		float en_buyuk_not;
		float en_kucuk_not;
		float aciklik;
		float medyan;
		ortalama = toplam_puan / ogr_sayi;
		en_buyuk_not = ogrlist[0].ogrnot;
		en_kucuk_not = ogrlist[ogr_sayi-1].ogrnot;
		int orta;
		if (ogr_sayi % 2 == 0) {
			orta = (ogr_sayi) / 2;
			medyan = (ogrlist[orta].ogrnot + ogrlist[orta+1].ogrnot) / 2;
		}
		else
		{
			orta = (ogr_sayi + 1) / 2;
			medyan = ogrlist[orta].ogrnot;
		}
		aciklik = en_buyuk_not - en_kucuk_not;

		ofstream myfile;
		myfile.open("output.txt");
		for (i = 0; i < 100; i++) {
			if (ogrlist[i].ogrno != "") {
				myfile << ogrlist[i].ogrno;
				myfile << ",";
				myfile << myround(ogrlist[i].ogrnot);
				myfile << "\n";
			}
		}

		myfile << myround(en_kucuk_not);
		myfile << ",";
		myfile << myround(en_buyuk_not);
		myfile << ",";
		myfile << myround(ortalama);
		myfile << ",";
		myfile << myround(medyan);
		myfile << ",";
		myfile << myround(aciklik);
		myfile << "\n";

		myfile.close();
	}

    return 0;
}

