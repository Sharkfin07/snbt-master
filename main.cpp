/*
    SNBT Master, sebuah gim video RPG
    oleh: Mohammad Zidane Kurnianto

    Bertujuan untuk meraih nilai optimal dalam Ujian Praktik Informatika
    dan untuk belajar C++!
*/

#include <bits/stdc++.h>
#include <windows.h>
#include <ctime>
#define cls system("cls")
using namespace std;

void splashScreen()
{
    cout << R"(
  ________  _____  ___   _______  ___________      ___      ___       __        ________  ___________  _______   _______   
 /"       )(\"   \|"  \ |   _  "\("     _   ")    |"  \    /"  |     /""\      /"       )("     _   ")/"     "| /"      \  
(:   \___/ |.\\   \    |(. |_)  :))__/  \\__/      \   \  //   |    /    \    (:   \___/  )__/  \\__/(: ______)|:        | 
 \___  \   |: \.   \\  ||:     \/    \\_ /         /\\  \/.    |   /' /\  \    \___  \       \\_ /    \/    |  |_____/   ) 
  __/  \\  |.  \    \. |(|  _  \\    |.  |        |: \.        |  //  __'  \    __/  \\      |.  |    // ___)_  //      /  
 /" \   :) |    \    \ ||: |_)  :)   \:  |        |.  \    /:  | /   /  \\  \  /" \   :)     \:  |   (:      "||:  __   \  
(_______/   \___|\____\)(_______/     \__|        |___|\__/|___|(___/    \___)(_______/       \__|    \_______)|__|  \___) 
                                                                                                                           
Diciptakan oleh: Mohammad Zidane Kurnianto
Sebuah Gim Video RPG UTBK

Tekan enter untuk lanjut... )"
         << endl;

    cin.get();
    cls;
}

class Date
{
public:
    int hari, bulan, tahun;

    void simBulan(int &h, int &b, int &t)
    {
        // Menghitung bahwa Agustus memiliki 31 hari juga, jadi bulan setelah Juli kembali ke pola 30 dan 31
        int tempB;
        if (b > 7)
            tempB = b - 7;
        else
            tempB = b;

        if (tempB % 2 == 1)
        {
            if (h > 31)
            {
                h = 1;
                b++;
            }
        }
        else if (tempB % 2 == 0 && b != 2)
        {
            if (h > 30)
            {
                h = 1;
                b++;
            }
        }
        else
        {
            if (h > 28)
            {
                h = 1;
                b++;
            }
        }
        if (b > 12)
        {
            b = 1;
            t++;
        }
    }

    void simHari()
    {
        hari++;
        if (hari > 28)
            simBulan(hari, bulan, tahun);
    }

    // SNBT 2025 dilaksanakan pada tanggal 23 April 2025
    int hMin(int h, int b, int t)
    {
        if (t > 2025 or (t == 2025 and ((b == 4 and h >= 23) or b > 4)))
            return -1;

        int hMin = 0;
        while (not(t == 2025 and b == 4 and h == 23))
        {
            hMin++;
            h++;

            if (h > 28)
                simBulan(h, b, t);
        }

        return hMin;
    }
};

Date current;

class User
{
public:
    string name, kampusImpian;
    int passingGrade, hMin, uang = 100000, mood = 50;
    vector<string> jurnal;
    bool buku = false, poster = false;

    // Kemampuan Subtes SNBT
    int pu = 450, pbm = 450, pk = 375, ppu = 435, lbi = 470, lbe = 450, pm = 420;

    string moodMeter(int m)
    {
        if (m == 0)
            return "Krisis Emosional";
        else if (m > 0 && m <= 20)
            return "Sangat Stres";
        else if (m > 20 && m <= 40)
            return "Lesu";
        else if (m > 40 && m <= 60)
            return "Netral";
        else if (m > 60 && m <= 80)
            return "Bahagia";
        else if (m > 80 && m < 100)
            return "Sangat Bahagia";
        else if (m == 100)
            return "Puncak Kebahagiaan";
        else
            return "?";
    }

    void mooder(int op)
    {
        mood += op;
        if (mood < 0)
            mood = 0;
        else if (mood > 100)
            mood = 100;
    }

    void belajar(int puProg, int ppuProg, int pbmProg, int pkProg, int lbiProg, int lbeProg, int pmProg)
    {
        int boost;
        if (buku && poster)
        {
            boost = ((mood) / 10) + 12;
        }
        else if (buku)
        {
            boost = ((mood - 50) / 10) + 10;
        }
        else if (poster)
        {
            boost = ((mood - 50) / 10) + 5;
        }
        else
        {
            boost = (mood - 50) / 10;
        }

        if (puProg <= 0)
            pu += (puProg + boost);
        if (ppuProg <= 0)
            ppu += (ppuProg + boost);
        if (pbmProg <= 0)
            pbm += (pbmProg + boost);
        if (pkProg <= 0)
            pk += (pkProg + boost);
        if (lbiProg <= 0)
            lbi += (lbiProg + boost);
        if (lbeProg <= 0)
            lbe += (lbeProg + boost);
        if (pmProg <= 0)
            pm += (pmProg + boost);

        if (pu > 950)
            pu = 950;
        if (ppu > 950)
            ppu = 950;
        if (pbm > 950)
            pbm = 950;
        if (pk > 950)
            pk = 950;
        if (lbi > 950)
            lbi = 950;
        if (lbe > 950)
            lbe = 950;
        if (pm > 950)
            pm = 950;
    }

    void jurnalkan(string ent)
    {
        string date = "(" + to_string(current.hari) + '/' + to_string(current.bulan) + '/' + to_string(current.tahun) + ')';
        string entry = date + ": " + ent;
        jurnal.push_back(entry);
    }
};

User player;
bool ex = false;

string kampus[] = {
    "Universitas Indonesia",
    "Universitas Gadjah Mada",
    "Institut Teknologi Bandung",
    "Universitas Airlangga",
    "Universitas Padjajaran",
    "Institut Teknologi Sepuluh Nopember",
    "Institut Pertanian Bogor",
    "Universitas Diponegoro",
    "Universitas Sebelas Maret",
    "Universitas Brawijaya",
    "Universitas Hasanuddin",
    "Universitas Andalas",
    "Universitas Udayana",
    "Universitas Negeri Padang",
    "Universitas Riau",
    "Universitas Jambi",
    "Universitas Negeri Gorontalo",
    "Politeknik Negeri Bengkalis",
    "Universitas Bangka Belitung",
    "Universitas Papua"};

void sapaPlayer()
{
    time_t now = time(0);
    tm *localTime = localtime(&now);

    int hour = localTime->tm_hour;

    if (hour >= 5 && hour < 10)
    {
        cout << "Selamat pagi, " << player.name << "!";
    }
    else if (hour >= 10 && hour < 12)
    {
        cout << "Selamat pagi menjelang siang, " << player.name << "!";
    }
    else if (hour >= 12 && hour < 15)
    {
        cout << "Selamat siang, " << player.name << "!";
    }
    else if (hour >= 15 && hour < 16)
    {
        cout << "Selamat siang menjelang sore, " << player.name << "!";
    }
    else if (hour >= 16 && hour < 19)
    {
        cout << "Selamat sore, " << player.name << "!";
    }
    else if (hour >= 19 && hour < 23)
    {
        cout << "Selamat malam, " << player.name << "!";
    }
    else
    {
        cout << "Hari sudah sangat malam, " << player.name << ", jangan lupa untuk tidur!";
    }
    cout << endl;
}

void enterKembali()
{
    cout << endl
         << "Tekan enter untuk kembali ke menu. ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void start()
{
    cout << "Selamat datang di SNBT Master!" << endl;
    Sleep(2000);
    cls;

    for (int i = 0; i < 10; ++i)
    {
        cout << "\rSebelum bermain, silakan isi data sesuai preferensi Anda! ";
        if (i % 3 == 0)
            cout << "( ^-^ )";
        else if (i % 3 == 1)
            cout << "(^o^  )";
        else
            cout << "(  ^o^)";
        cout.flush(); // Membentuk animasi ASCII
        Sleep(200);
    }
    cls;
    cout << "Sebelum bermain, silakan isi data sesuai preferensi Anda! ( ^u^ )" << endl;
}

void pemilihan()
{
    // Input nama
    cout << "Silakan masukkan nama Anda: ";
    getline(cin, player.name);
    cout << "Oke!";
    Sleep(1000);
    cls;

    // Input date
    sapaPlayer();
    Sleep(1000);
    cout << "Sekarang silakan input tanggal mula persiapan SNBT kamu (dalam bentuk angka)! ( ^o^ )" << endl;
    cout << "Catatan: SNBT 2025 akan dilaksanakan pada tanggal 23 April 2025." << endl;

    while (true)
    {
        cout << "Hari: ";
        cin >> current.hari;
        cout << "Bulan: ";
        cin >> current.bulan;
        cout << "Tahun: ";
        cin >> current.tahun;

        player.hMin = current.hMin(current.hari, current.bulan, current.tahun);
        if (player.hMin == -1 || current.hari > 31 || current.bulan > 12)
        {
            cout << "Tanggal yang Anda input sudah melewati tanggal pelaksanaan SNBT 2025!" << endl;
            Sleep(2000);
            cls;
            sapaPlayer();
            cout << "Sekarang silakan input tanggal mula persiapan SNBT kamu (dalam bentuk angka)! ( ^o^ )" << endl;
            cout << "Catatan: SNBT 2025 akan dilaksanakan pada tanggal 23 April 2025." << endl;
            continue;
        }
        else
        {
            cout << "Jadi, Anda akan memulai persiapan pada tanggal " << current.hari << "/" << current.bulan << "/" << current.tahun << endl;
            Sleep(1000);
            cout << "SNBT 2025: H-" << player.hMin << endl;
            Sleep(2000);
            cout << "Semangat!" << endl;
            enterKembali();
            cls;
            break;
        }
    }

    // Input Kampus Impian
    while (true)
    {
        int pilihan;
        cout << "Pilih kampus impian Anda dari pilihan di bawah ini:" << endl;
        for (int i = 0; i < 20; i++)
            cout << i + 1 << ". " << kampus[i] << endl;

        cout << "Input angka kampus: ";
        cin >> pilihan;

        if (pilihan > 20 || pilihan < 1)
        {
            cout << endl;
            cout << "Pilihan tidak valid!";
            cls;
            continue;
        }
        else
        {
            cout << endl;
            player.kampusImpian = kampus[pilihan - 1];
            player.passingGrade = 760 - (12 * (pilihan - 1));
            cout << "Anda memilih: " << player.kampusImpian << "." << endl;
            Sleep(3000);
            cls;
            break;
        }
    }

    // Akhirnya main juga...
    cout << "Anda sudah mengisi semua data!" << endl;
    Sleep(1000);
    cout << "Nah, mari kita mulai perjalanan kita! ( ^-^ )" << endl;
    enterKembali();
    cls;
}

int menu()
{
    int pilihan = 0;
    sapaPlayer();
    cout << "Tanggal: " << current.hari << "/" << current.bulan << "/" << current.tahun << endl;
    cout << "Mood: " << player.moodMeter(player.mood) << endl;
    cout << "Uang: Rp" << player.uang << endl;
    cout << "Kampus Impian: " << player.kampusImpian << endl;
    cout << "SNBT 2025 H-" << player.hMin << endl
         << endl;

    cout << "Apa yang ingin Anda lakukan hari ini?" << endl;
    cout << "1. Belajar Materi SNBT (+Kemampuan)" << endl;
    cout << "2. Tryout (Rp30.000)" << endl;
    cout << "3. Riset Kampus Impian" << endl;
    cout << "4. Rekreasi (+Mood)" << endl;
    cout << "5. Pergi ke Toko" << endl;
    cout << "6. Cari Duit (+Uang)" << endl;
    cout << "7. Tidur (+Mood)" << endl;
    cout << "8. Jurnal" << endl;

    cout << "Pilih aktivitas: ";
    cin >> pilihan;
    return pilihan;
}

// ntl = Nilai Tahun Lalu
int ntl = 0;

// 1: Belajar Materi SNBT
void belajarSNBT()
{
    cls;
    int pilihan;
    sapaPlayer();
    cout << "Selamat di ruang belajarmu! Ingat bahwa mood kamu berpengaruh pada hasil belajar." << endl;
    cout << "Mood: " << player.moodMeter(player.mood) << endl;
    cout << "1. Belajar matematika (+PU, +PK, +PM)" << endl;
    cout << "2. Belajar Bahasa Indonesia (+LBI, +PBM, +PPU)" << endl;
    cout << "3. Belajar Bahasa Inggris (++LBE)" << endl;
    cout << "4. Bermain catur (+PU, +Mood)" << endl;
    cout << "5. Membaca novel (+LBI, +LBE, +Mood)" << endl;
    cout << "6. Exit" << endl;
    cout << "Mau belajar apa hari ini: ";
    cin >> pilihan;

    if (pilihan < 1 or pilihan > 5)
    {
        ex = true;
    }

    else
    {
        if (player.mood <= 0)
        {
            cout << "Anda sekarang sepertinya sedang sangat stress, istirahat yang cukup ya!" << endl;
            enterKembali();
        }
        else
        {
            string pembel;
            switch (pilihan)
            {
            case 1:
                player.belajar(10, 0, 0, 10, 0, 0, 10);
                pembel = "mempelajari materi matematika";
                break;
            case 2:
                player.belajar(0, 10, 10, 0, 10, 0, 0);
                pembel = "mempelajari materi Bahasa Indonesia";
                break;
            case 3:
                player.belajar(0, 0, 0, 0, 20, 0, 0);
                pembel = "mempelajari materi Bahasa Inggris";
                break;
            case 4:
                player.belajar(10, 0, 0, 0, 0, 0, 0);
                pembel = "melatih logika bermain catur";
                player.mooder(15);
                break;
            case 5:
                player.belajar(0, 0, 0, 0, 10, 10, 0);
                player.mooder(15);
                pembel = "membaca sebuah novel";
                break;
            }

            player.mooder(-10);
            if (player.mood > 80)
            {
                cout << "Anda belajar dengan sangat baik hari ini!" << endl;
                string j = "Anda meraih progres signifikan dalam pembelajaran SNBT dengan " + pembel + ".";
                player.jurnalkan(j);
            }
            else if (player.mood > 40)
            {
                cout << "Anda belajar dengan baik hari ini." << endl;
                string j = "Anda belajar SNBT dengan " + pembel + ".";
                player.jurnalkan(j);
            }
            else
            {
                cout << "Anda belajar dengan kurang efektik hari ini." << endl;
                string j = "Anda belajar SNBT dengan " + pembel + " secara tidak efektif karena banyak tekanan.";
                player.jurnalkan(j);
            }

            cout << endl;
            enterKembali();
        }
    }
}

// 2: Tryout
void tryout()
{
    if (player.uang < 30000)
    {
        cout << endl
             << "Uang Anda tidak cukup untuk mengikuti Tryout!" << endl;
        Sleep(3000);
        ex = true;
        cls;
    }

    else if (player.mood < 20)
    {
        cout << endl
             << "Istirahatlah! Kembali jika mood Anda sudah membaik.";
        Sleep(3000);
        ex = true;
        cls;
    }

    else
    {
        player.uang -= 30000;
        cls;

        int b = player.mood - 50, total = 0;
        cout << "Anda mulai mengerjakan Tryout..." << endl;

        int puHasil = player.pu + b + (rand() % 30);
        total += puHasil;
        Sleep(2000);
        cout << "Penalaran Umum = " << puHasil << endl;

        int ppuHasil = player.ppu + b + (rand() % 30);
        total += ppuHasil;
        Sleep(2000);
        cout << "Pengetahuan dan Pemahaman Umum = " << ppuHasil << endl;

        int pbmHasil = player.pbm + b + (rand() % 30);
        total += pbmHasil;
        Sleep(2000);
        cout << "Pemahaman Bacaan dan Menulis = " << pbmHasil << endl;

        int pkHasil = player.pk + b + (rand() % 30);
        total += pkHasil;
        Sleep(2000);
        cout << "Pengetahuan Kuantitatif = " << pkHasil << endl;

        int lbiHasil = player.lbi + b + (rand() % 30);
        total += lbiHasil;
        Sleep(2000);
        cout << "Literasi Bahasa Indonesia = " << lbiHasil << endl;

        int lbeHasil = player.lbe + b + (rand() % 30);
        total += lbeHasil;
        Sleep(2000);
        cout << "Literasi Bahasa Inggris = " << lbeHasil << endl;

        int pmHasil = player.pm + b + +(rand() % 30);
        total += pmHasil;
        Sleep(2000);
        cout << "Penalaran Matematika = " << pmHasil << endl;

        int rata2 = total / 7;
        Sleep(2000);
        cout << endl
             << "Nilai Akhir = ";
        Sleep(2000);
        cout << rata2 << endl;

        player.belajar(5, 5, 5, 5, 5, 5, 5);
        player.mooder(-35);

        enterKembali();
        string j = "Anda melaksanakan Tryout dan meraih nilai akhir " + to_string(rata2);
        player.jurnalkan(j);

        j = "PU = " + to_string(puHasil);
        player.jurnalkan(j);

        j = "PPU = " + to_string(ppuHasil);
        player.jurnalkan(j);

        j = "PBM = " + to_string(pbmHasil);
        player.jurnalkan(j);

        j = "PK = " + to_string(pkHasil);
        player.jurnalkan(j);

        j = "LBI = " + to_string(lbiHasil);
        player.jurnalkan(j);

        j = "LBE = " + to_string(lbeHasil);
        player.jurnalkan(j);

        j = "PM = " + to_string(pmHasil);
        player.jurnalkan(j);
    }
}

// 3: Riset Kampus Impian
void riset()
{
    cls;
    cout << "Anda melakukan riset pada " << player.kampusImpian << "..." << endl;
    Sleep(2000);

    if (ntl == 0)
    {
        if ((rand() % 2) == 0)
        {
            ntl = player.passingGrade - (rand() % 50);
        }
        else
        {
            ntl = player.passingGrade + (rand() % 20);
        }
    }

    player.mooder(-10);
    cout << "Pada SNBT tahun lalu, nilai minimum untuk lulus " << player.kampusImpian << " adalah: " << ntl << "." << endl;
    cout << "Ingat! Angka diatas tidak pasti sama dengan nilai minimum tahun ini." << endl;
    Sleep(3000);

    enterKembali();
    cls;

    string j = "Anda riset kampus " + player.kampusImpian + ". Nilai minimum SNBT tahun lalu adalah " + to_string(ntl) + '.';
    player.jurnalkan(j);
}

// 4: Rekreasi
void rekreasi()
{
    cls;
    int pilihan;
    cout << "Selamat datang di Ambarita Travels! Hadir untuk Membawa Anda Menjelajah Dunia." << endl;
    cout << "Uang Anda: Rp" << player.uang << endl;
    cout << "1. Paris, Perancis (Rp2.000.000)" << endl;
    cout << "2. Raja Ampat, Papua Barat (Rp560.000)" << endl;
    cout << "3. Ancol, Jakarta Barat (Rp320.000)" << endl;
    cout << "4. Danau Toba, Sumatra Utara (Rp150.000)" << endl;
    cout << "5. " << player.kampusImpian << " (Rp100.000)" << endl;
    cout << "6. Sungai Ciliwung (Rp1.000)" << endl;
    cout << "7. Exit" << endl;
    cout << "Silakan pilih destinasi yang Anda ingin: ";
    cin >> pilihan;

    if (pilihan > 6 || pilihan < 1)
        ex = true;

    else
    {
        int cost;
        string destinasi;
        switch (pilihan)
        {
        case 1:
            cost = 2000000;
            destinasi = "Paris";
            break;
        case 2:
            cost = 560000;
            destinasi = "Raja Ampat";
            break;
        case 3:
            cost = 320000;
            destinasi = "Ancol";
            break;
        case 4:
            cost = 150000;
            destinasi = "Danau Toba";
            break;
        case 5:
            cost = 100000;
            destinasi = player.kampusImpian;
            break;
        case 6:
            cost = 1000;
            destinasi = "Sungai Ciliwung (tidak ada destinasi lain kah?)";
            break;
        }

        if (player.uang >= cost)
        {
            player.uang -= cost;
            switch (pilihan)
            {
            case 1:
                player.mooder(100);
                break;
            case 2:
                player.mooder(90);
                break;
            case 3:
                player.mooder(85);
                break;
            case 4:
                player.mooder(80);
                break;
            case 5:
                player.mooder(70);
                break;
            case 6:
                player.mooder(20);
                break;
            }

            string j = "Anda pergi liburan ke " + destinasi + ".";
            player.jurnalkan(j);
        }

        else
        {
            cout << "Anda belum memiliki uang yang cukup, maaf!";
            enterKembali();
            ex = true;
        }
    }
}

// 5: Pergi ke Toko
void pkt()
{
    cls;
    int pilihan;
    cout << "Selamat datang di Toko Sitembus, segala barang kebutuhan yang Anda cari ada disini!" << endl;
    cout << "Uang Anda: Rp" << player.uang << endl;
    cout << "1. Buku \"The Queen - Bedah Tuntas SNBT 2025\": Meningkatkan efisiensi belajar SNBT (Rp250.000)" << endl;
    cout << "2. Cokelat Silver King: Meningkatkan mood (Rp. 20.000)" << endl;
    cout << "3. Poster " << player.kampusImpian << ": Meningkatkan mood dan efisiensi belajar SNBT (Rp. 100.000)" << endl;
    cout << "4. Permen Mint-X: Meningkatkan mood (Rp1.000)" << endl;
    cout << "5. Kopi PesawatUdara: Meningkatkan mood (Rp20.000)" << endl;
    cout << "6. Rokok Lemboerna Mild: Menurunkan mood (Rp16.000)" << endl;
    cout << "7. All-New Toyota Fortuner 2.8 GR Sport: Meningkatkan mood (Rp761.700.000)" << endl;
    cout << "8. Exit" << endl;
    cout << "Silakan pilih barang yang Anda inginkan: ";
    cin >> pilihan;

    if (pilihan < 1 or pilihan > 7)
    {
        ex = true;
    }

    else
    {
        int cost;
        string pembelian;
        switch (pilihan)
        {
        case 1:
            cost = 250000;
            pembelian = "Buku \"The Queen - Bedah Tuntas SNBT 2025\"";
            break;
        case 2:
            cost = 20000;
            pembelian = "Cokelat Silver King";
            break;
        case 3:
            cost = 100000;
            pembelian = "Poster " + player.kampusImpian;
            break;
        case 4:
            cost = 1000;
            pembelian = "Permen Mint-X";
            break;
        case 5:
            cost = 20000;
            pembelian = "Kopi PesawatUdara";
            break;
        case 6:
            cost = 16000;
            pembelian = "Rokok Lemboerna Mild (puas?)";
            break;
        case 7:
            cost = 761700000;
            pembelian = "All-New Toyota Fortuner 2.8 GR Sport (yang bener saja)";
            break;
        case 8:
            ex = true;
            break;
        }

        if (player.uang >= cost)
        {
            player.uang -= cost;
            switch (pilihan)
            {
            case 1:
                player.buku = true;
                break;
            case 2:
                player.mooder(15);
                break;
            case 3:
                player.mooder(10);
                player.poster = true;
                break;
            case 4:
                player.mooder(5);
                break;
            case 5:
                player.mooder(15);
                break;
            case 6:
                player.mooder(-10);
                break;
            case 7:
                player.mooder(100);
                break;
            }

            string j = "Anda membeli " + pembelian + ".";
            player.jurnalkan(j);
        }

        else
        {
            cout << "Anda belum memiliki uang yang cukup, maaf!" << endl;
            enterKembali();
            ex = true;
        }
    }
}

// 6: Cari Duit
void cduit()
{
    cls;
    int pilihan;
    cout << "Selamat datang di Agensi Cari Kerja Akmal Bersaudara, 100% menyediakan kerja untukmu 24/7!" << endl;
    cout << "Uang Anda: Rp" << player.uang << endl;
    cout << "1. Mencuci piring di Rumah Makan Sendawana, 1 hari (Rp30.000)" << endl;
    cout << "2. Mengantarkan paket untuk JLE, 2 hari (Rp70.000)" << endl;
    cout << "3. Menjadi editor majalah Bono, 3 hari (Rp120.000, +PBM, +PPU)" << endl;
    cout << "4. Manajer pabrik cokelat Silver King, 1 minggu (Rp280.000, +PU)" << endl;
    cout << "5. Bangun Rumah, 1 tahun (Rp300.000.000, +PM, +PK)" << endl;
    cout << "6. Exit" << endl;
    cout << "Silakan, mau kerja jadi apa hari ini mas: ";
    cin >> pilihan;

    if (pilihan < 1 or pilihan > 5)
    {
        ex = true;
    }

    else
    {
        int hariProses, upah, stress;
        string kerja;
        switch (pilihan)
        {
        case 1:
            hariProses = 1;
            stress = -5;
            upah = 30000;

            kerja = "mencuci piring di Rumah Makan Sendawana";
            break;
        case 2:
            hariProses = 2;
            stress = -7;
            upah = 70000;
            kerja = "mengantarkan paket untuk JLE";
            break;
        case 3:
            hariProses = 3;
            stress = -15;
            upah = 120000;
            player.belajar(0, 10, 15, 0, 0, 0, 0);
            kerja = "menjadi editor majalah Bono";
            break;
        case 4:
            hariProses = 7; // 1 minggu dianggap 7 hari
            upah = 280000;
            stress = -30;
            kerja = "manajer pabrik cokelat Silver King";
            player.belajar(35, 0, 0, 0, 0, 0, 0);
            break;
        case 5:
            hariProses = 365; // 1 tahun dianggap 365 hari
            upah = 300000000;
            stress = -100;
            kerja = "membangun rumah";
            player.belajar(0, 0, 0, 100, 0, 0, 100);
            break;
        case 6:
            ex = true; // Pilihan exit
            break;
        }

        if (player.mood < 40)
        {
            cout << "Kelihatannya kamu terlalu stress untuk melakukan pekerjaan. Istirahat dan tingkatkan mood kamu agar bisa bekerja ya!" << endl;
            enterKembali();
            ex = true;
        }
        else if (player.hMin < hariProses)
        {
            cout << "Nak, kamu akan melaksanakan SNBT " << player.hMin << " hari lagi. << endl";
            enterKembali();
            ex = true;
        }
        else
        {
            cls;
            cout << "Anda bekerja keras..." << endl;
            Sleep(2000);

            for (int i = 1; i < hariProses; i++)
            {
                current.simHari();
            }

            player.hMin -= hariProses;
            player.uang += upah;
            player.mooder(stress);
            cout << hariProses << " hari telah lewat, dan akhirnya Anda mendapatkan Rp" << upah << "!" << endl;
            enterKembali();

            string j = "Anda mencari duit dengan " + kerja + " selama " + to_string(hariProses) + " dan mendapatkan uang Rp" + to_string(upah) + ".";
            player.jurnalkan(j);
        }
    }
}

// 7: Tidur
void tidur()
{
    cls;
    int rob = rand() % 8;

    if (rob == 0)
    {
        cout << "Sepertinya ada perampok yang masuk ke rumahmu..." << endl;
        Sleep(2000);

        if (player.uang >= 20000)
        {
            int robbed = (rand() % (player.uang / 10000)) * 10000;
            cout << "Mereka merampok Rp" << robbed << "!" << endl;
            player.mooder(-20);
            player.uang -= robbed;

            string j = "Anda terkena rampok Rp" + to_string(robbed) + " selagi tidur.";
            player.jurnalkan(j);
        }
        else
        {
            cout << "Akan tetapi, kelihatannya mereka tidak jadi..." << endl;
            Sleep(2000);
            cout << "Bahkan dompet setipis punyamu itu tidak menarik bagi para perampok." << endl;
            player.mooder(10);

            string j = "Selagi tidur, perampok memasuki rumahmu... tetapi mereka tidak jadi merampok.";
            player.jurnalkan(j);
        }
        Sleep(2000);
    }
    else
    {
        cout << "Anda tidur dengan nyenyak malam ini..." << endl;
        player.mooder(20);
        Sleep(2000);

        string j = "Anda menghabiskan hari ini untuk tidur nyenyak.";
        player.jurnalkan(j);
    }
    cls;
}

// 8: Jurnal
void jurnal()
{
    cls;
    string enter;
    for (string ent : player.jurnal)
    {
        cout << ent << endl;
    }

    ex = true;
    enterKembali();
    cls;
}

// Hari H: SNBT 2025
void snbt()
{
    cls;
    cout << "Hari ini adalah hari penentu segalanya, selamat berjuang kawan!" << endl;
    enterKembali();
    cls;

    int b = player.mood - 50, total = 0;
    cout << "Anda mulai mengerjakan UTBK..." << endl;

    int puHasil = player.pu + b + (rand() % 30);
    total += puHasil;
    Sleep(2000);
    cout << "Penalaran Umum = " << puHasil << endl;

    int ppuHasil = player.ppu + b + (rand() % 30);
    total += ppuHasil;
    Sleep(2000);
    cout << "Pengetahuan dan Pemahaman Umum = " << ppuHasil << endl;

    int pbmHasil = player.pbm + b + (rand() % 30);
    total += pbmHasil;
    Sleep(2000);
    cout << "Pemahaman Bacaan dan Menulis = " << pbmHasil << endl;

    int pkHasil = player.pk + b + (rand() % 30);
    total += pkHasil;
    Sleep(2000);
    cout << "Pengetahuan Kuantitatif = " << pkHasil << endl;

    int lbiHasil = player.lbi + b + (rand() % 30);
    total += lbiHasil;
    Sleep(2000);
    cout << "Literasi Bahasa Indonesia = " << lbiHasil << endl;

    int lbeHasil = player.lbe + b + (rand() % 30);
    total += lbeHasil;
    Sleep(2000);
    cout << "Literasi Bahasa Inggris = " << lbeHasil << endl;

    int pmHasil = player.pm + b + +(rand() % 30);
    total += pmHasil;
    Sleep(2000);
    cout << "Penalaran Matematika = " << pmHasil << endl;

    int rata2 = total / 7;
    Sleep(2000);
    cout << endl
         << "Nilai Akhir = ";
    Sleep(2000);
    cout << rata2 << endl;

    cout << "Apakah ini cukup untuk lulus di " << player.kampusImpian << "?" << endl;
    cout << "Passing Grade " << player.kampusImpian << " SNBT Tahun 2025 = ";
    Sleep(3000);
    cout << player.passingGrade;
    enterKembali();

    if (rata2 >= player.passingGrade)
    {
        cls;
        cout << "Anda lulus di " << player.kampusImpian << "!" << endl;
        Sleep(2000);
        cout << "Berkat kerja keras kamu, akhirnya kamu bisa diterima di kampus impian kamu! <(^_^)>" << endl;
        enterKembali();
    }
    else
    {
        cls;
        cout << "Anda tidak lulus di " << player.kampusImpian << "." << endl;
        Sleep(2000);
        cout << "Tetap semangat belajar ya kawan, masih ada pintu lain kok! (≧︿≦)" << endl;
        enterKembali();
    }
}

int main()
{
    cls;
    splashScreen();

    // Perkenalan dan Selamat Datang
    start();

    // Opsi
    pemilihan();

    while (player.hMin > 0)
    {
        int p = menu();
        if (p >= 1 && p <= 8)
        {
            if (p == 1)
                belajarSNBT();
            if (p == 2)
                tryout();
            if (p == 3)
                riset();
            else if (p == 4)
                rekreasi();
            else if (p == 5)
                pkt();
            else if (p == 6)
                cduit();
            else if (p == 7)
                tidur();
            else if (p == 8)
                jurnal();

            if (ex)
            {
                ex = false;
                cls;
            }
            else
            {
                current.simHari();
                player.hMin--;
                cls;
            }
        }
        else
        {
            cout << "Pilihan tidak valid!";
            Sleep(1000);
            cls;
            continue;
        }
    }

    snbt();
}