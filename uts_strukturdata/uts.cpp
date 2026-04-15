#include <iostream>
#include <string> // gunanya untuk data judul dan penyanyi
#include <vector> //bikin rak khusus cetakan lagu ( pengganti array seng lebih canggih )
#include <deque> //mengganti queue agar bisa mengingintip antrean di tengah tengah 
#include <stack> //bikin tumpukan buat fitur back
using namespace std;

//cetakan dasar (kalau ingin nambahkan variabel lainnya)
struct lagu {
    string judul;
    string artis;
};

// bagian linkedlist
struct riwayatlagu {
    lagu datalagu; //buat nyimpen lagu
    riwayatlagu* next;
};

    riwayatlagu* headriwayat = nullptr;

void lihatsemua() {
    cout << "\n Riwayat Pemutaran Lagu: \n";
    riwayatlagu* polisi = headriwayat;
    if (polisi == nullptr){
        cout << "Belum ada lagu yang diputar kocak \n";
    }
    // sebelum polisi sampai ujung nullptr maka lakukan ini
    while (polisi != nullptr)
    {
        cout << "->" << polisi->datalagu.judul << "-" << polisi->datalagu.artis << "\n";
        polisi = polisi->next;
    }
    
};

vector<lagu> kumpulanlagu;
void tambahlagu(){
    lagu lagubarucuy; //

    cout << "\n TAMBAHKAN LAGU BARU \n";
    cout << " Masukan Judul Lagu:";
    cin >> ws;
    getline(cin, lagubarucuy.judul); // menyimpan ketikan user ke dalam judul;
    cout << " Masukan Nama Artis: ";
    getline(cin, lagubarucuy.artis); // menyimpan ketikan user ke dalam artis

    kumpulanlagu.push_back(lagubarucuy); // memasukkan lagu ke paling belakang/terakhir
    cout << "anjay lagunya udah berhasil dimasukan ke playlist\n";
}

deque<lagu> antrianlagu;
void nambahkeantrian() {
    //jika playlistnya masih kosong nanti di batalin
    if (kumpulanlagu.empty()) {
        cout << "playlist lagi kosong nih! tambahin lagu dong di menu 1. \n";
        return; //langsung keluar dari fungsi ini
    }

    cout << "\n DAFTAR LAGU DI PLAYLIST\n";
    // buat nampilin semua isi kumpukan lagu
    for (int i = 0; i < kumpulanlagu.size (); i++) {
        cout << i << ". " << kumpulanlagu[i].judul << "-" << kumpulanlagu[i].artis << "\n";
    }

    int pilihan;
    cout << "Pilih lagunya cintaku buat dimasukin ke playlist: ";

    // agar ngga looping
    if (!(cin >> pilihan)) {
        // jika si user ngetik huruf maka akan masuk kesini
        cout << "masukin angka nomornya bro bukan huruf";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    // mengecek apakah nomornya masuk akal yang di ketik oleh user
    if (pilihan >= 0 && pilihan < kumpulanlagu.size()) {
        // mengambil lagui yang sesuai pilihan user, dorong ke antrian paling akhir
        antrianlagu.push_back(kumpulanlagu[pilihan]);
        cout << "yeyy lagu berhasil masuk antrian! \n";
    }
    else {
        cout << "nomornya gaada di daftar bosku!";
    };
}

stack <lagu> stacklagusebelumnya; // bikin tumpukan buat fitur back
void putarlagu(){
    // mengecek apakah ada yang di putar di antrian
    if (antrianlagu.empty()){
        cout << "antrian lagi kosong broku, tambahin lagu dulu! \n";
        return;
    }

    // mengambil dari queue
    // ngecek apa lagui yang paling atas
    lagu lagusekarang = antrianlagu.front();
    // hapus lagunya dari antrian karna udh di putar (dequeue)
    antrianlagu.pop_front();

    cout << "sekarang lagi muter: " << lagusekarang.judul << "-" << lagusekarang.artis << "\n";
    // masukin ke stack
    // dorong lagu ke tumpukan paling atas agar bisa di back
    stacklagusebelumnya.push(lagusekarang);

    // masukin ke linkedlist
    riwayatlagu* nodebaru = new riwayatlagu(); //bikin playlist
    nodebaru->datalagu = lagusekarang; // isi nuatan lagu
    nodebaru->next = headriwayat; // kaitkan ke rangkaian lama
    headriwayat = nodebaru; // jadikan kepala baru
}

void putarsebelumnya () {
    // mengecek apakah ada lagu yang udh pernah di putar
    if (stacklagusebelumnya.size() <=1) {
        cout << "belum ada history lagu nih sayang, gabisa di back";
        return;
    }

        //  ngebuang dari tumpukan biar kalo di back dia mundur ke lagu sebelumnya
    stacklagusebelumnya.pop();
    
    // mengintip tumpukan paling atas
    lagu lagumundur = stacklagusebelumnya.top();

    cout << "Mundur ke lagu: " << lagumundur.judul << " - " << lagumundur.artis << "\n";
}

int main() {
    int pilihanMenu;

    // do-while: Lakukan perulangan menu ini selama pilihannya bukan 0
    do {
        cout << "\n🎧 === PEMUTAR MUSIK KELAS BERAT === 🎧\n";
        cout << "1. Tambah Lagu ke Playlist\n";
        cout << "2. Tambah Lagu ke Antrean\n";
        cout << "3. Putar Lagu \n";
        cout << "4. Putar Lagu Sebelumnya \n";
        cout << "5. Lihat Riwayat \n";
        cout << "0. Keluar\n";
        cout << "Pilih menu cuy: ";
        // jika user ngetik huruf
        if (!(cin >> pilihanMenu)) {
            cout << "Masukin angka kocak bukan huruf, udah di enakin juga \n ";
            cin.clear(); // untuk mereset errornya
            cin.ignore(1000, '\n'); // membuang sisa huruf
            pilihanMenu = -1; // set angka agar program tidak keluar
            continue; // kembali ngulang menu
        }

        // switch-case untuk mengarahkan pilihan user ke fungsi yang tepat
        switch (pilihanMenu) {
            case 1:
                tambahlagu();
                break;
            case 2:
                nambahkeantrian();
                break;
            case 3:
                putarlagu();
                break;
            case 4:
                putarsebelumnya();
                break;
            case 5:
                lihatsemua();
                break;
            case 0:
                cout << "alhamdulillah program selesai, waktunya bobo\n";
                break;
            default:
                cout << "Pilihan nggak ada di menu, kocak!\n";
        }
    } while (pilihanMenu != 0);

    return 0; // Tanda program selesai dengan aman
}