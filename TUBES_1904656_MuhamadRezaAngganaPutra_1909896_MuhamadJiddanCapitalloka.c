#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include<math.h>
#define maxsize 100

//variable global yang digunakan hampir disetiap prosedur/fungsi
int pilihan;
int i=0;
int j=0;
int k=0;
int jumlah = 0;
char cekuser[10];
char cekpass[9];
int total_pph[maxsize];
int total_ppn[maxsize];
int total_pbb[maxsize];
int total[maxsize];
int check[maxsize];
int count = 0;

typedef struct{ //variable bentukan untuk menyimpan akun user pajak
	char username[maxsize];
	char password[9];
}akun;

typedef struct{ //variable bentukan untuk menyimpan data pajak pajak
	int pph[maxsize];
	int ppn[maxsize];
	int pbb[maxsize];
}pajak;

typedef struct{ //variable bentukan untuk menyimpan total pajak yang akan digunakan pada prosedur write file
	int pph;
	int ppn;
	int pbb;
}total_pajak;

total_pajak Pajak[maxsize];

void judul(){ //(M.Reza Anggana.P)
	printf("===============================================\n");
	printf("=              Selamat Datang di              =\n");
	printf("=            Aplikasi Hitung Pajak            =\n");
	printf("=        created by: M.Reza & M.Jiddan        =\n");
	printf("===============================================\n");
}

void buatAkun(int * no_account, akun *account){ //(M.Reza Anggana.P)
	int cek = 0; //variabel lokal pengecekan keberadaan username 
	char nama[maxsize];
	char pass[maxsize];
	printf("====================SIGN UP===================\n");
	printf("Username:"); scanf("%s", &nama);
	printf("Password:"); scanf("%s", &pass);
	printf("\n");
	for (i=0; i<jumlah; i++){ 
		if ((strcmp(nama, account[i].username) == 0) && (cek != 1)){
			cek = 1;
		}
	}
	if (cek != 1){ //jika username tidak ditemukan
		*no_account = jumlah;
		strcpy(account[*no_account].username, nama);
		strcpy(account[*no_account].password, pass);
		printf("Akun terdaftar!\n");
		jumlah = jumlah + 1;
	}else{
		printf("Akun sudah ada!\n");
	}
	printf("===============================================\n");
}

int sign_in(int * no_account, akun *account){ //(M.Reza Anggana.P)
	int cek = 0; //variabel lokal pengecekan keberadaan username
	printf("=====================LOGIN=====================\n");
	printf("Username:"); scanf("%s", &cekuser);
	printf("Password:"); scanf("%s", &cekpass);
	printf("===============================================\n");
	for (i=0; i<jumlah; i++){ //sequential searching untuk menemukan username dan password yang sesuai
		if ((strcmp(cekuser,account[i].username) == 0) && (strcmp(cekpass,account[i].password) == 0) && (cek != 1)){
			printf("\n");
			printf("BERHASIL LOGIN !\n");
			cek = 1;
			*no_account = i;
			printf("\n");
		}
	}
	if (cek != 1){ //jika setelah pencarian tidak ditemukan username dengan password yang tepat
		printf("\n");
		printf("Username dan atau Password Salah!\n");
	}
	system("pause");
	system("cls");
	return cek;
}

//presedure fungsi untuk  PPH
void PPH(int * no_account, pajak *tax, int *no_pph){ //(M.Jiddan C)
	int ptkp;
	int penghasilan;
	printf("======= PPH =======\n");//tampilah menu PPH
	printf("[1] Bujangan/single/jomblo\n");
	printf("[2] Sudah menikah\n");
	printf("[3] Berkeluarga\n");
	printf("Masukan Pilihan : ");scanf("%d", &pilihan);
	printf("===================\n");
	printf("Penghasilan Per Bulan: Rp. ");scanf("%d", &penghasilan);
	printf("\n");
	printf("======= INFORMASI PENGHASILAN =======\n");
	printf("Penghasilan Per bulan : Rp. %d\n",penghasilan);
	penghasilan = penghasilan * 12;
	printf("Penghasilan Per Tahun : Rp. %d\n",penghasilan);
	printf("=====================================\n");
	if(pilihan == 1){
		ptkp = 54000000;
	} else if(pilihan == 2){
		ptkp = 54000000 + 4500000;
	} else if(pilihan == 3){
		ptkp = 54000000+(4500000*2);
	}else{
		printf("Pilihan Salah");
	}
	penghasilan = penghasilan - ptkp;//Rumus menghitung penghasilan PPH
	if ((penghasilan <= 50000000) && (penghasilan > 0)){
		tax[*no_account].pph[*no_pph] = penghasilan * 5 / 100;
	}else if((penghasilan > 50000000) && (penghasilan < 250000000)){
		tax[*no_account].pph[*no_pph] = penghasilan * 15 / 100;
	}else if((penghasilan > 250000000) && (penghasilan < 500000000)){
		tax[*no_account].pph[*no_pph] = penghasilan * 25 / 100;
	}else if(penghasilan >= 500000000){
		tax[*no_account].pph[*no_pph] = penghasilan * 50 / 100;
	}
	printf("Penghasilan Murni : Rp.%d\n",penghasilan);
	if (tax[*no_account].pph[*no_pph] <= 0){ //jika hasil kurang dari atau sama dengan nol, tidak terkena pajak
		tax[*no_account].pph[*no_pph] = 0;
	}
	printf("PPH : Rp%d\n\n", tax[*no_account].pph[*no_pph]);
	*no_pph = *no_pph + 1;
	system("PAUSE");
	system("CLS");
}
//Presedure fungsi untuk PPnBM
void PPnBM(int * no_account, pajak *tax, int *no_ppn){//(M.Jiddan C)
	printf("======= PPnMb =======\n");//Tampilan Menu
	printf("[1] Peralatan Rumah Tangga\n");
	printf("[2] Barang Impor\n");
	printf("[3] Transportasi\n");
	printf("[4] Batu Akik\n");
	printf("Masukan Pilihan : ");scanf("%d",&pilihan);
	printf("===================\n");
	if(pilihan==1){//Rumus menghitung PPnBM
		tax[*no_account].ppn[*no_ppn] = peralatan();	
	}else if(pilihan==2){
		tax[*no_account].ppn[*no_ppn] = impor();
	}else if(pilihan==3){
		tax[*no_account].ppn[*no_ppn] = transportasi();		
	}else if(pilihan==4){
		tax[*no_account].ppn[*no_ppn] = batu();		
	}else{
		printf("Pilihan Salah");
	}
	if(tax[*no_account].ppn[*no_ppn] <= 0){ //jika hasil kurang dari atau sama dengan nol, tidak terkena pajak
		tax[*no_account].ppn[*no_ppn] = 0;
	}
	printf("PPN :Rp.%d \n", tax[*no_account].ppn[*no_ppn]);
	*no_ppn = *no_ppn + 1;	
	system("PAUSE");
	system("CLS");
}
//Fungsi peralatan,impor,dan kendaraan 
int peralatan(){//(M.Jiddan C)
	int hasil;
	printf("====== Peralatan rumah tangga =====\n");
	int kulkas = 3000000;
	int televisi = 2500000;
	int kipas = 200000;
	int ppnmb;
	printf("[1] Kulkas\n");//Tampilan menu
	printf("[2] Televisi\n");
	printf("[3] Kipas\n");
	printf("Masukan Pilihan : ");scanf("%d",&pilihan);
	if(pilihan == 1){
		ppnmb = kulkas * 10/100;//Rumus menghitung ppnmb peralatan 
		hasil = (kulkas-ppnmb) * 10 / 100;//rumus menghitung total pajak ppbm
	}else if(pilihan == 2){
		ppnmb = televisi * 10 /100;
		hasil = (televisi - ppnmb) * 10 / 100;
	}else if(pilihan == 3){
		ppnmb = kipas * 10 / 100;
		hasil = (kipas-ppnmb) * 10 / 100;
	}else{
		printf("Pilihan Salah");
	}
	printf("\n");
	return hasil;
}

int impor(){//(M.Jiddan C)
	int hasil;
	int ppnmb;
	printf("====== Barang Impor =====\n");
	int perhiasan = 300000;
	int sayuran = 2500000;
	int obat = 20000;
	printf("[1] Perhiasan\n");
	printf("[2] Sayuran\n");
	printf("[3] Obat Obatan terlarang\n");
	printf("Masukan Pilihan : ");scanf("%d",&pilihan);
	if(pilihan == 1){
		ppnmb = perhiasan * 20 / 100;//Rumus menghitung ppnmb Impor
		hasil = (perhiasan - ppnmb) * 10 / 100;
	}else if(pilihan == 2){
		ppnmb = sayuran * 20 / 100;
		hasil = (sayuran - ppnmb) * 10 / 100;
	}else if(pilihan == 3){
		ppnmb = obat * 10 / 100;
		hasil = (obat - ppnmb) * 10 / 100;
	}else{
		printf("Pilihan Salah");
	}
	printf("\n");
	return hasil;
}

int transportasi(){//(M.Jiddan C)
	int hasil;
	int ppnmb;
	printf("====== Trasportasi =====\n");
	int mobil = 300000;
	int motor = 2500000;
	int bus = 20000;
	printf("[1] mobil\n");
	printf("[2] motor\n");
	printf("[3] bus\n");
	printf("Masukan Pilihan : ");scanf("%d",&pilihan);
	if(pilihan == 1){
		ppnmb = mobil * 25 / 100;//Rumus menghitung ppnmb Transportasi
		hasil = (mobil - ppnmb) * 10 / 100;
	}else if(pilihan == 2){
		ppnmb = motor * 25 / 100;
		hasil = (motor - ppnmb) * 10 / 100;	
	}else if(pilihan == 3){
		ppnmb = bus * 25 / 100;
		hasil = (bus - ppnmb) * 10 / 100;
	}else{
		printf("Pilihan Salah");
	}
	printf("\n");
	return hasil;
}

int batu(){//(M.Jiddan C)
	int hasil;
	int ppnmb;
	printf("====== Batu Perhiasan =====\n");
	int diamond = 300000;
	int gold = 2500000;
	int platinum = 200000;
	printf("[1] Diamond\n");
	printf("[2] Gold\n");
	printf("[3] Platinum\n");
	printf("Masukan Pilihan : ");scanf("%d",&pilihan);
	if(pilihan == 1){
		ppnmb = diamond * 40 / 100;//Rumus menghitung ppnmb batu
		hasil = (diamond - ppnmb) * 10 /100;	
	}else if(pilihan == 2){
		ppnmb = gold * 40 / 100;
		hasil = (gold - ppnmb ) * 10 / 100;
	}else if(pilihan == 3){
		ppnmb = platinum * 40 / 100;
		hasil = (platinum - ppnmb) * 10 / 100;	
	}else{
		printf("Pilihan Salah");
	}
	printf("\n");
	return hasil;
}
//presedure fungsi PBB
void PBB(int * no_account, pajak * tax, int *no_pbb){ //(M.Jiddan C)
	int bangunan;
	int tanah;
	int njop;
	int njkp;
	printf("Masukan Luas Bangunan : ");scanf("%d",&bangunan);	
	printf("Masukan Luas tanah : ");scanf("%d",&tanah);
	njop = (bangunan * 500000) + (tanah * 1000000);//rumus menghitung njop
	njkp = njop * 20 / 100;//rumus menghitung njkp
	tax[*no_account].pbb[*no_pbb] = njkp * 5 / 1000;//rumus menghitung pajak PBB
	printf("PBB : Rp.%d\n",tax[*no_account].pbb[*no_pbb]);
	if(tax[*no_account].pbb[*no_pbb] <= 0){ //jika hasil kurang dari atau sama dengan nol, tidak terkena pajak
		tax[*no_account].pbb[*no_pbb] = 0;
	}
	*no_pbb = *no_pbb + 1;
	system("PAUSE");
	system("CLS");
}

void tanggungan(akun *account, int check, int *no_account, pajak *tax, int *no_pph, int *no_ppn, int *no_pbb){ //(M.Reza Anggana.P)
	printf("======= TANGGUNGAN PAJAK =======\n");
	if(check == 0){ //jika terjadi penambahan tanggungan pajak
		//hitung masing-masing total pajak
		for(i=0;i<*no_pph;i++){	
			total_pph[*no_account] = total_pph[*no_account] + tax[*no_account].pph[i];
		}
		for(i=0;i<*no_ppn;i++){
			total_ppn[*no_account] = total_ppn[*no_account] + tax[*no_account].ppn[i];
		}
		for(i=0;i<*no_pbb;i++){
			total_pbb[*no_account] = total_pbb[*no_account] + tax[*no_account].pbb[i];
		}
	}
	printf("Total PPH : Rp.%d\n", total_pph[*no_account]);
	printf("\n");
	printf("Total PPN : Rp.%d\n", total_ppn[*no_account]);
	printf("\n");
	printf("Total PBB : Rp.%d\n", total_pbb[*no_account]);
	printf("\n");
	total[*no_account] = total_pph[*no_account] + total_ppn[*no_account] + total_pbb[*no_account];
	printf("Total : Rp.%d\n", total[*no_account]);
	printf("\n");
	//menu file
	printf("Arsipkan?\n");
	printf("[1] Ya\n");
	printf("[2] Tidak\n");
	printf("Pilihan:"); scanf("%d",&pilihan);
	if (pilihan == 1){ //jika ingin dibuat file
		writeFile(&*no_account, total_pph[*no_account], total_ppn[*no_account], total_pbb[*no_account]);
		readFile();
	}else if(pilihan ==2){ //jika tidak ingin dibuat file
		printf("Data Belum Diarsipkan\n");
	}
	printf("================================\n");
	system("PAUSE");
	system("CLS");
}

void bayar(int *no_account, pajak *tax, int *no_pph, int *no_ppn, int *no_pbb){ //(M.Reza Anggana.P)
	int bayar;
	printf("======= BAYAR PAJAK =======\n");
	printf("[1] Penghasilan (PPH)\n");
	printf("[2] Barang mewah(PPbBM)\n");
	printf("[3] Bumi dan Bangunan(PBB)\n");
	printf("[0] EXIT\n");
	printf("Masukan pilihan : ");scanf("%d",&pilihan);
	printf("Nominal Pembayaran : "); scanf("%d", &bayar);
	switch(pilihan){
		case 1:
			*no_pph = 0; //mereset no pph menjadi nol agar ketika perhitungan total pph, pph sebelum dibayar tidak terhitung kembali
			total_pph[*no_account] = total_pph[*no_account] - bayar;
			if (total_pph[*no_account] < 0){ //jika membayar lebih dari tunggakan pajak yang dimiliki
				printf("Kembalian Rp.%d\n", abs(total_pph[*no_account]));
				total_pph[*no_account] = 0;
			}
			printf("Tanggungan PPH sekarang : Rp.%d\n", total_pph[*no_account]);
			break;
		case 2:
			*no_ppn = 0; //mereset no ppn menjadi nol agar ketika perhitungan total ppn, ppn sebelum dibayar tidak terhitung kembali
			total_ppn[*no_account] = total_ppn[*no_account] - bayar;
			if (total_ppn[*no_account] < 0){ //jika membayar lebih dari tunggakan pajak yang dimiliki
				printf("Kembalian Rp.%d\n", abs(total_ppn[*no_account]));
				total_ppn[*no_account] = 0;
			}
			printf("Tanggungan PPN sekarang : Rp.%d\n", total_ppn[*no_account]);
			break;
		case 3:
			*no_pbb = 0; //mereset no pbb menjadi nol agar ketika perhitungan total pbb, pbb sebelum dibayar tidak terhitung kembali
			total_pbb[*no_account] = total_pbb[*no_account] - bayar;
			if (total_pbb[*no_account] < 0){ //jika membayar lebih dari tunggakan pajak yang dimiliki
				printf("Kembalian Rp.%d\n", abs(total_pbb[*no_account]));
				total_pbb[*no_account] = 0;
			}
			printf("Tanggungan PBB sekarang : Rp.%d\n", total_pbb[*no_account]);
			break;
	}
	system("PAUSE");
	system("CLS");
}

void writeFile(int *no_account, int total_pph, int total_ppn, int total_pbb){ //(M.Reza Anggana.P)
	FILE *pajak;
	system("md temp");
	//memasukan nilai hasil perhitungan total pajak pada varibel bentukan
	Pajak[*no_account].pph = total_pph;
	Pajak[*no_account].ppn = total_ppn;
	Pajak[*no_account].pbb = total_pbb;																															
	pajak = fopen("temp\\dataPajak.txt","w+"); //membuat file 'dataPajak' untuk data total pajak
	for(i = 0; i <= jumlah; i++){																	
		fprintf(pajak, "%d;%d;%d\n", Pajak[i].pph, Pajak[i].ppn, Pajak[i].pbb);
	}							
	fclose(pajak);	
	pajak = fopen("temp\\jml.txt","w+"); //membuat file 'jml' untuk jumlah user pajak
	fprintf(pajak,"%d",jumlah);
	fclose(pajak);									
}

void readFile(){ //(M.Reza Anggana.P)
	int pph[maxsize];
	int ppn[maxsize];
	int pbb[maxsize];
	i = 0;
	FILE *pajak;
	pajak = fopen("temp\\dataPajak.txt", "a+"); 
	//membaca file 'dataPajak'
	while(fscanf(pajak, "%d; %d; %d\n", &pph[i], &ppn[i], &pbb[i]) != EOF){			
		i++;
	}
	fclose(pajak);
	pajak = fopen("temp\\jml.txt","a+"); 
	//membaca file 'jml'
	fscanf(pajak,"%d",&count);
	fclose(pajak);
	//tampilkan
	printf("================ARSIP=============\n");
	for(i=0; i< count; i++){
		printf("PPH: %d, PPN:%d, PBB:%d \n", pph[i], ppn[i], pbb[i]);
	}
	printf("==================================\n");				
	printf("\n");	
}


int main(){ //(M.Reza Anggana.P)
	akun account[maxsize];
	pajak tax[maxsize];
	int ulang = 0;
	int proses;
	int no_account;
	int no_pph;
	int no_ppn;
	int no_pbb;
	while (ulang == 0){
		judul();
		printf("[1] Buat Akun\n");
		printf("[2] LOGIN\n");
		printf("[0] EXIT\n");
		printf("\n");
		printf("PILIH:"); scanf ("%d", &pilihan);
		switch(pilihan){
			case 1:
				printf("\n");
				buatAkun(&no_account, &account);
				system("pause");
				system("cls");
				break;
			case 2:
				printf("\n");
				proses = sign_in(&no_account, &account);
				int ulang2 = 0;
				if (proses == 1){
					while (ulang2 == 0){
						printf("Hai %s Selamat Datang di Aplikasi Hitung Pajak\n",cekuser);
						printf("\n");
						printf("============ HITUNG PAJAK ==========\n");
						printf("[1] Penghasilan (PPH)\n");
						printf("[2] Barang mewah(PPbBM)\n");
						printf("[3] Bumi dan Bangunan(PBB)\n");	
						printf("[4] Tanggungan Pajak\n");
						printf("[5] Bayar Pajak\n");
						printf("[0] EXIT\n");
						printf("==================\n");
						printf("Masukan pilihan : ");scanf("%d",&pilihan);
						switch (pilihan){
							case 0:
								ulang2 ++;
								system("PAUSE");
								system("CLS");
								break;
							case 1:
								PPH(&no_account, &tax, &no_pph);
								check[no_account] = 0;
								break;
							case 2:	
								PPnBM(&no_account, &tax, &no_ppn);
								check[no_account] = 0;
								break;
							case 3:
								PBB(&no_account, &tax, &no_pbb);
								check[no_account] = 0;
								break;
							case 4:
								tanggungan(&account, check[no_account], &no_account, &tax, &no_pph, &no_ppn, &no_pbb);
								check[no_account] = 1;
								break;
							case 5:
								check[no_account] = 1;
								bayar(&no_account, &tax, &no_pph, &no_ppn, &no_pbb);
								break;
							default:
								printf("Pilihan Salah!");
								system("PAUSE");
								system("CLS");	
								break;
						}
					}
				}else{
					break;
				}
				break;
			case 0:
				ulang ++;
				break;
		}			
	}
}
