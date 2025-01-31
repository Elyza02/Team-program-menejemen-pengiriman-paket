#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Paket {
    string kodePaket;
    string pengirim;
    string penerima;
    double berat;
    double biayaPengiriman;
    string status;
};

void garis(){
	cout <<"===========================================\n";
}

double hitungBiaya(double berat, double jarak) {
    const double tarifPerKg = 5000.0;
    return berat * jarak * tarifPerKg;
}

void tambahPaket(Paket daftarPaket[], int& jumlahPaket, int kapasitas) {
    if (jumlahPaket >= kapasitas) {
        cout << "Kapasitas daftar paket sudah penuh!\n";
        return;
    }

    Paket p;
    garis();
    cout << "Masukkan kode paket\t\t: ";
    cin >> p.kodePaket;
    cin.ignore();  
    cout << "Masukkan nama pengirim\t\t: ";
    getline(cin, p.pengirim);
    cout << "Masukkan nama penerima\t\t: ";
    getline(cin, p.penerima);

    cout << "Masukkan berat paket (kg)\t: ";
    cin >> p.berat;
    while (cin.fail() || p.berat <= 0) {  
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Input tidak valid! Masukkan berat paket (positif): ";
        cin >> p.berat;
    }

    double jarak;
    cout << "Masukkan jarak pengiriman (km)\t: ";
    cin >> jarak;
    while (cin.fail() || jarak <= 0) {   
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Input tidak valid! Masukkan jarak pengiriman (positif): ";
        cin >> jarak;
    }

    p.biayaPengiriman = hitungBiaya(p.berat, jarak);
    p.status = "Diproses";

    daftarPaket[jumlahPaket] = p;
    jumlahPaket++;
	
	cout<< "biaya pengiriman\t\t: " << p.biayaPengiriman << " IDR\n";
	garis();
    cout << "Paket berhasil ditambahkan!\n"; 
    
}

void tampilkanPaket(const Paket daftarPaket[], int jumlahPaket) {
    if (jumlahPaket == 0) {
        cout << "Tidak ada data paket.\n";
        return;
    }
    for (int i = 0; i < jumlahPaket; i++) {
    	garis();
        cout << "Kode\t\t: " << daftarPaket[i].kodePaket << "\n";
        cout << "Pengirim\t: " << daftarPaket[i].pengirim << "\n";
        cout << "Penerima\t: " << daftarPaket[i].penerima << "\n";
        cout << "Berat (kg)\t: " << daftarPaket[i].berat << "\n";
        cout << "Biaya (IDR)\t: " << daftarPaket[i].biayaPengiriman << "\n";
        cout << "Status\t\t: " << daftarPaket[i].status << "\n";
        garis();
    }
}

void simpanDataKeFile(const Paket daftarPaket[], int jumlahPaket, const string& DataPengirimanPaket) {
    ofstream file("DataPengirimanPaket");
    if (!file) {
        cout << "Gagal membuka file untuk menyimpan data.\n";
        return;
    }

    for (int i = 0; i < jumlahPaket; i++) {
        file << daftarPaket[i].kodePaket << ", " << daftarPaket[i].pengirim << ", "
             << daftarPaket[i].penerima << ", " << daftarPaket[i].berat << ", "
             << daftarPaket[i].biayaPengiriman << ", " << daftarPaket[i].status << "\n";
    }

    file.close();
    cout << "\nData berhasil disimpan ke file " << DataPengirimanPaket << "!\n";
    cout << "______________________________________________\n";
}

int main() {
    const int kapasitas = 100;
    Paket daftarPaket[kapasitas];
    int jumlahPaket = 0;
    int pilihan;

    do {
        cout << "\nSistem Manajemen Pengiriman Paket\n";
        cout << "1. Tambah Paket\n";
        cout << "2. Tampilkan Paket\n";
        cout << "3. Simpan Data ke File\n";
        cout << "4. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        while (cin.fail()) {   
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Pilihan tidak valid. Masukkan angka: ";
            cin >> pilihan;
        }

        switch (pilihan) {
            case 1:
                tambahPaket(daftarPaket, jumlahPaket, kapasitas);
                break;
            case 2:
                tampilkanPaket(daftarPaket, jumlahPaket);
                break;
            case 3:
                simpanDataKeFile(daftarPaket, jumlahPaket, "data_paket.txt");
                break;
            case 4:
                cout << "\nKeluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 4);

    return 0;
}


