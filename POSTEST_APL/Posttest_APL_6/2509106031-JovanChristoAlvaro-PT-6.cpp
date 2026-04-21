#include <iostream>
#include <string>
using namespace std;

struct saham {
    string kode_shm;
    int harga_rata_rata;
    int jumlah_lot;
};

struct investor {
    string username;
    string password;
    struct saham shm[50]; 
    int banyak_saham = 0;    
    bool minta_hapus = false;    
};

void sort_investor_asc(investor inv[], int banyak_investor){ //<--- Bubble Sort Ascending Untuk Mengurutkan Data Investor Berdasarkan Ururtan Nama (:))
    for(int i = 0; i < banyak_investor - 1; i++) {
        for(int j = 0; j < banyak_investor - i - 1; j++) {
            if(inv[j].username > inv[j+1].username) {
                investor temp = inv[j];
                inv[j] = inv[j+1];
                inv[j+1] = temp;
            }
        }
    }
}

void sort_emiten_asc(saham shm[], int banyak_saham){ //<--- Selection Sort Untuk Mengurutkan Data Emiten Saham Berdasarkan Nama
    for(int i = 0; i < banyak_saham - 1; i++) {
        int data_terkecil = i;

        for(int j = i + 1; j < banyak_saham; j++){
            if(shm[j].kode_shm < shm[data_terkecil].kode_shm){
                data_terkecil = j;
            }
        }

        if(data_terkecil != i){
            saham temp = shm[i];
            shm[i] = shm[data_terkecil];
            shm[data_terkecil] = temp;
        }
    }
}

void sort_lot_desc(saham shm[], int banyak_saham){ //<-- Insertion Sort Untuk Mengurutkan Data Banyak Lot Saham Yang Dimiliki Secara Descending
    for(int i = 1; i < banyak_saham; i++){
        saham data_sekarang = shm[i];
        int j = i - 1;

        while(j >= 0 && shm[j].jumlah_lot < data_sekarang.jumlah_lot){
            shm[j + 1] = shm[j];
            j = j - 1;
        }
        shm[j + 1] = data_sekarang;
    }
}

void sort_lot_asc(saham shm[], int banyak_saham){ //<-- Insertion Sort Tapi Ini Ascending, Karena nanti di search pakai interpolation.
                                                  // (Kalau pakai yang data Desc, rumus Interpolationnya berubah)
    for(int i = 1; i < banyak_saham; i++){
        saham data_sekarang = shm[i];
        int j = i - 1;

        while(j >= 0 && shm[j].jumlah_lot > data_sekarang.jumlah_lot){
            shm[j + 1] = shm[j];
            j = j - 1;
        }
        shm[j + 1] = data_sekarang;
    }
}

int linear_search_investor(investor inv[], int banyak_investor, string target){ //<-- Linear Search Untuk Mecari data investor tertentu 
    for(int i = 0; i < banyak_investor; i++){
        if(inv[i].username == target) {
            return i;
        }
    }
    return -1;
}

int binary_search_emiten(saham shm_temp[], int kiri, int kanan, string target){ //<-- Binary search untuk mencari emiten saham tertentu
    while (kiri <= kanan){
        int tengah = kiri + (kanan - kiri) / 2;
        
        if(shm_temp[tengah].kode_shm == target){
            return tengah;
        } 
        else if (shm_temp[tengah].kode_shm < target){
            kiri = tengah + 1;
        }
        else{
            kanan = tengah - 1;
        } 
    }
    return -1;
}

int interpolation_search_lot(saham arr[], int low, int high, int target){ //<-- Interpolation Search untuk mencari saham berdasarkan jumlah lot nya
    while (low <= high && target >= arr[low].jumlah_lot && target <= arr[high].jumlah_lot){
        if (low == high){
            if (arr[low].jumlah_lot == target){
                return low;
            } 
            return -1;
        }

        int pos = low + (((double)(high - low) / (arr[high].jumlah_lot - arr[low].jumlah_lot)) * (target - arr[low].jumlah_lot));

        if(arr[pos].jumlah_lot == target){
            return pos;
        }
        else if(arr[pos].jumlah_lot < target){
            low = pos + 1;
        } 
        else{
            high = pos - 1;
        }
    }
    return -1;
}

bool cek_login(string input_user, string input_pass, string fix_user, string fix_pass){
    return (input_user == fix_user && input_pass == fix_pass);
}

int cek_login(string input_user, string input_pass, investor inv[], int banyak_investor){
    for(int i = 0; i < banyak_investor; i++){
        if(input_user == inv[i].username && input_pass == inv[i].password){
            return i;
        }
    }
    return -1;
}

void buat_akun(investor inv[], int &banyak_investor, string nama_fix){
    string nama, pass;
    cout<<"\n========================================================="<<endl;
    cout<<"============ PEMBUATAN AKUN CATATAN INVESTOR ==========="<<endl;
    cout<<"========================================================="<<endl;
    
    if(banyak_investor >= 100){
        cout<<"TIDAK DAPAT MEMBUAT AKUN KARENA DATA AKUN SUDAH PENUH!!!!"<<endl;
        cout<<"Tekan Enter Untuk Balik Ke Menu Awal...";
        system("pause");
        return;
    }
    
    cout<<"Masukan Username Anda: ";
    getline(cin, nama);
    
    bool nama_kembar = false;
    
    if(nama == nama_fix){
        nama_kembar = true;
    } 
    else{
        for(int i = 0; i < banyak_investor; i++){
            if(nama == inv[i].username){
                nama_kembar = true;
                break;
            }
        }
    }
    
    if(nama_kembar){
        cout<<"Username Sudah Terdaftar, Silahkan Buat Username Baru!!!!";
        cout<<"\nTekan Enter Untuk Balik Ke Menu Awal...";
        system("pause");
    } 
    else{
        inv[banyak_investor].username = nama;
        cout<<"Masukan Password Anda: ";
        getline(cin, inv[banyak_investor].password);
        
        banyak_investor += 1; 
        
        cout<<"\nSelamat Akun Anda Berhasil Dibuat!!!"<<endl;
        system("pause");
    }
}

void hapus_akun(investor *user) {
    if(user -> minta_hapus == true){
        cout<<"\n[INFO] Anda Sudah Mengajukan Penghapusan Akun!!!"<<endl;
        cout<<"Silahkan Tunggu Persetujuan Dari Admin :)"<<endl;
    }
    else{
        char konfirmasi;

        cout<<"Apakah Anda Yakin Ingin Mengajukan Penghapusan Akun???(Y/N): ";
        cin>>konfirmasi;
        cin.ignore(100, '\n');
                    
        if(konfirmasi == 'Y' || konfirmasi == 'y'){
            user -> minta_hapus = true; 
            cout<<"\n[BERHASIL] Pengajuan Hapus Akun Telah Dikirim Ke Admin!!!"<<endl;
        } 
        else if(konfirmasi == 'N' || konfirmasi == 'n'){
            cout<<"\n[BATAL] Pengajuan Dibatalkan."<<endl;
        }
        else{
            cout<<"\nPilihan Hanya Berupa (Y/N) Tidak Bisa Yang Lain!!!!!"<<endl;
        }
    }
    
    system("pause");
}

int total_modal(saham shm[], int n){ 
    if (n <= 0) { 
        return 0;
    }
    int modal_sekarang = shm[n - 1].harga_rata_rata * (shm[n - 1].jumlah_lot * 100);
    return modal_sekarang + total_modal(shm, n - 1); 
}

void beli_saham(investor *user) {
    string kode;
    int harga, lot;
    cout<<"Masukan Kode Emiten (Misal: BBCA): ";
    getline(cin, kode);
    cout<<"Masukan Harga Beli per Lembar: ";
    cin>>harga;
    cout<<"Masukan Jumlah Lot: ";
    cin>>lot;
    cin.ignore(100, '\n');

    int index_saham = -1;
    for(int i = 0; i < user -> banyak_saham; i++){
        if(user -> shm[i].kode_shm == kode){
            index_saham = i; 
            break;
        }
    }

    if(index_saham != -1){ 
        int lot_lama = user -> shm[index_saham].jumlah_lot;
        int harga_lama = user -> shm[index_saham].harga_rata_rata;
        
        int total_modal_lama = lot_lama * harga_lama;
        int total_modal_baru = lot * harga;
        int total_lot = lot_lama + lot;
        
        user -> shm[index_saham].harga_rata_rata = (total_modal_lama + total_modal_baru) / total_lot;
        user -> shm[index_saham].jumlah_lot = total_lot;
        
        cout<<"\n[BERHASIL] Anda Berhasil Menambah Rata-rata Harga Saham "<<kode<<"!"<<endl;
    } 
    else{ 
        int saham_baru = user -> banyak_saham;
        user -> shm[saham_baru].kode_shm = kode;
        user -> shm[saham_baru].harga_rata_rata = harga;
        user -> shm[saham_baru].jumlah_lot = lot;
        user -> banyak_saham += 1; 
        
        cout<<"\n[BERHASIL] Saham "<<kode<<" Berhasil Ditambahkan Ke Portfolio!"<<endl;
    }

   system("pause");
}

void porto(investor *user) {
    cout<<"\n=================================================================================================="<<endl;
    cout<<"===================================== DAFTAR PORTFOLIO SAHAM ======================================"<<endl;
    cout<<"==================================================================================================="<<endl;
    if(user-> banyak_saham == 0){
        cout<<"Portfolio Anda Masih Kosong!"<<endl;
    } 
    else{
        int opsi_sort;
        cout<<"\n=====Tampilan Portfolio ====="<<endl;
        cout<<"1. Default (Sesuai Urutan Beli)"<<endl;
        cout<<"2. Sorting Ascending (Berdasarkan Nama Emiten)"<<endl;
        cout<<"3. Sorting Descending (Berdasarkan Jumlah Lot)"<<endl;
        cout<<"Pilih Opsi Tampilan: ";
        cin>>opsi_sort;
        cout<<"\n";

        if(opsi_sort == 1){
            for(int i = 0; i < user-> banyak_saham; i++){
            string kode = user -> shm[i].kode_shm;
            int harga = user -> shm[i].harga_rata_rata;
            int lot = user -> shm[i].jumlah_lot;
            int modal = harga * (lot * 100); 
            
            cout<< i + 1<<". "<<kode<<" | Lot: "<<lot<<" | Harga Rata-rata: Rp"<<harga<<" | Total Modal: Rp"<<modal<<endl;
        }
        cout<<"---------------------------------------------------------------------------------------------------"<<endl;
        
        int modal_total = total_modal(user -> shm, user -> banyak_saham);
        cout<<"TOTAL SEMUA MODAL: Rp"<<modal_total<<endl;
        }
        else if(opsi_sort == 2){
            sort_emiten_asc(user->shm, user->banyak_saham);

            for(int i = 0; i < user-> banyak_saham; i++){
            string kode = user -> shm[i].kode_shm;
            int harga = user -> shm[i].harga_rata_rata;
            int lot = user -> shm[i].jumlah_lot;
            int modal = harga * (lot * 100); 
            
            cout<< i + 1<<". "<<kode<<" | Lot: "<<lot<<" | Harga Rata-rata: Rp"<<harga<<" | Total Modal: Rp"<<modal<<endl;
            }
            cout<<"---------------------------------------------------------------------------------------------------"<<endl;
            
            int modal_total = total_modal(user -> shm, user -> banyak_saham);
            cout<<"TOTAL SEMUA MODAL: Rp"<<modal_total<<endl;
        } 
        else if(opsi_sort == 3){
            sort_lot_desc(user->shm, user->banyak_saham);

            for(int i = 0; i < user-> banyak_saham; i++){
            string kode = user -> shm[i].kode_shm;
            int harga = user -> shm[i].harga_rata_rata;
            int lot = user -> shm[i].jumlah_lot;
            int modal = harga * (lot * 100); 
            
            cout<< i + 1<<". "<<kode<<" | Lot: "<<lot<<" | Harga Rata-rata: Rp"<<harga<<" | Total Modal: Rp"<<modal<<endl;
            }
            cout<<"---------------------------------------------------------------------------------------------------"<<endl;
            
            int modal_total = total_modal(user -> shm, user -> banyak_saham);
            cout<<"TOTAL SEMUA MODAL: Rp"<<modal_total<<endl;
        }
        else{
            cout<<"=== Pilihan Tidak Ada!!! ==="<<endl;
        }
        
    }
   
    system("pause");
}

void jual_saham(investor *user) {
   string kode, enter;
    cout<<"Masukan Kode Emiten yang ingin dijual SEMUA: ";
    getline(cin, kode);
    
    int index_saham = -1;
    for(int i = 0; i < user -> banyak_saham; i++){
        if (user -> shm[i].kode_shm == kode) {
            index_saham = i;
            break;
        }
    }
    
    if (index_saham != -1){
        for(int i = index_saham; i < user -> banyak_saham - 1; i++){
            user -> shm[i] = user -> shm[i + 1];
        }
        user -> banyak_saham -= 1; 
        cout<<"\n[BERHASIL] Saham "<<kode<<" Berhasil Dijual Semua dan Dihapus!!!"<<endl;
    } 
    else{
        cout<<"\n[GAGAL] Saham "<<kode<<" Tidak Ditemukan Diportfolio Anda."<<endl;
    }
    cout<<"Tekan Enter Untuk Kembali...";
    getline(cin, enter);
}

void ganti_pass_akun(investor *user) {
    string konfirmasi, pass_baru, enter;

    cout<<"Masukan Password Anda Yang Lama: ";
    cin>>konfirmasi;

    if(konfirmasi == user -> password){
        cout<<"Masukan Password Anda Yang Baru: ";
        cin>>pass_baru;

        if(pass_baru == user -> password){
            cout<<"Password Itu Sudah Anda Gunakan !!!"<<endl;
            system("pause");
        }
        else{
            user -> password = pass_baru;
            cout<<"\n==== Password Anda Berhasil Diganti!!! ===="<<endl;
            system("pause");
        }
    }
    else{
        cout<<"\n==== Password Yang Anda Masukan Tidak Sesuai Dengan Password Anda!!! ===="<<endl;
        cout<<"==================== GANTI PASSWORD DIBATALKAN !!!!! ===================="<<endl;
        system("pause");
    }
}

void menu_atmin(investor inv[], int &banyak_investor) {
    bool login_atmin = true; 
    char pilihan; 
    string enter;
    
    while(login_atmin) {
        cout<<"\n========================================================="<<endl;
        cout<<"============= SELAMAT DATANG KEMBALI ATMIN! ============="<<endl;
        cout<<"========================================================="<<endl;
        cout<<"1. Melihat Akun Investor"<<endl;
        cout<<"2. Cari Akun Investor"<<endl; 
        cout<<"3. Pengajuan Hapus Akun Investor"<<endl;
        cout<<"4. Logout"<<endl;
        cout<<"\nMasukan Pilihan: ";
        cin>>pilihan; cin.ignore(100, '\n');
        
        switch(pilihan) {
            case '1':
                cout<<"\n======================================================"<<endl;
                cout<<"============= DAFTAR INVESTOR TERDAFTAR =============="<<endl;
                cout<<"======================================================"<<endl;

                if (banyak_investor == 0){
                    cout<<"Belum Ada Investor!!!"<<endl;
                } 
                else{
                    sort_investor_asc(inv, banyak_investor);
                    for(int i = 0; i < banyak_investor; i++){
                        cout<<i + 1<<". "<<inv[i].username<<endl;
                    } 
                }
                
                system("pause");
                break;
                
            case '2':{
                if (banyak_investor == 0){
                    cout<<"Belum Ada Investor Yang Terdaftar!"<<endl;
                } 
                else{
                    string target;

                    cout<<"Masukkan Username Investor Yang Dicari: ";
                    getline(cin, target);
                    
                    int hasil = linear_search_investor(inv, banyak_investor, target);
                    
                    if (hasil != -1) {
                        cout<<"\n[DITEMUKAN] Detail Investor:"<<endl;
                        cout<<"Username      : "<<inv[hasil].username<<endl;
                        cout<<"Total Emiten  : "<<inv[hasil].banyak_saham<<" Saham"<<endl;
                        cout<<"Status Hapus  : "<<(inv[hasil].minta_hapus ? "Ya" : "Tidak")<<endl;
                    } 
                    else{
                        cout<<"\n[TIDAK DITEMUKAN] Investor Dengan Username:"<<target<<" ,Tidak Terdaftar!!!"<<endl;
                    }
                }

                system("pause");
                break;
            }
                
            case '3':{
                cout<<"\n======================================================"<<endl;
                cout<<"========== DAFTAR PENGAJUAN HAPUS AKUN ==============="<<endl;
                cout<<"======================================================"<<endl;

                int laporan = 0;
                for(int i = 0; i < banyak_investor; i++){
                    if(inv[i].minta_hapus == true){
                        cout<<i + 1<<". Username: "<<inv[i].username<<" Mengajukan Hapus Akun"<<endl;
                        laporan++;
                    }
                }

                if(laporan == 0){
                    cout<<"Belum Ada Pengajuan Hapus Akun Dari Investor "<<endl;
                }
                else if(laporan > 0){
                    int pilihan_hapus;
                    cout<<"\nMasukan Nomor Akun Yang Ingin Dihapus (Ketik 0 Untuk Batal): ";
                    cin>>pilihan_hapus;
                    cin.ignore(100, '\n');

                    if(pilihan_hapus > 0 && pilihan_hapus <= banyak_investor){
                        int idx_investor = pilihan_hapus - 1;
                        
                        if(inv[idx_investor].minta_hapus == true){
                            string nama_dihapus = inv[idx_investor].username;

                            for(int i = idx_investor; i < banyak_investor - 1; i++){
                                inv[i] = inv[i + 1]; 
                            }
                            banyak_investor -= 1; 
                            cout<<"\n[BERHASIL] Akun "<<nama_dihapus<<"  Berhasil Dihapus!!!"<<endl;
                        } 
                        else{
                            cout<<"\n[GAGAL] Akun Tersebut Tidak Mengajukan Penghapusan Akun!!!"<<endl;
                        }
                    } 
                    else if (pilihan_hapus != 0){
                        cout << "\n[GAGAL] Nomor tidak valid!" << endl;
                    }
                }

                system("pause");
                break;
            }

            case '4':
                login_atmin = false;
                break;
            
            default: cout<<"Pilihan Tidak Ada!!!"<<endl; break;
        }
    }
}

void menu_user(investor &user) {
    bool login_user = true;
    char pilihan;

    while(login_user) {
        cout<<"\n========================================================="<<endl;
        cout<<"=== PORTFOLIO INVESTOR: "<<user.username<<" ==="<<endl;
        cout<<"========================================================="<<endl;
        cout<<"1. Beli Saham"<<endl;  
        cout<<"2. Lihat Portfolio Saham"<<endl;
        cout<<"3. Cari Saham Berdasarkan Nama Saham"<<endl;   
        cout<<"4. Cari Saham Berdasarkan Jumlah Lot"<<endl; 
        cout<<"5. Jual Semua Saham"<<endl;
        cout<<"6. Ajukan Penghapusan Akun"<<endl;
        cout<<"7. Ganti Password Akun"<<endl;
        cout<<"8. Logout"<<endl;
        cout<<"\nMasukan Pilihan: ";
        cin>>pilihan; cin.ignore(100, '\n');

        switch(pilihan) {
            case '1': beli_saham(&user); 
            break;

            case '2': porto(&user); 
            break;
            
            case '3':{ 
                string target;

                if(user.banyak_saham == 0){
                    cout<<"Portfolio Kosong!!!"<<endl; 
                    system("pause"); 
                    break;
                }
                saham* shm_temp = new saham[user.banyak_saham];

                for(int i = 0; i < user.banyak_saham; i++){
                    shm_temp[i] = user.shm[i];
                } 
                
                sort_emiten_asc(shm_temp, user.banyak_saham);

                cout<<"Masukkan Kode Emiten Yang Dicari: ";
                getline(cin, target);

                int hasil = binary_search_emiten(shm_temp, 0, user.banyak_saham - 1, target);

                if(hasil != -1){
                    cout<<"\n[KETEMU] "<<target<<" | Lot: "<<shm_temp[hasil].jumlah_lot<<" | Harga: Rp"<<shm_temp[hasil].harga_rata_rata<<endl;
                } 
                else{
                    cout<<"\n[GAGAL] Saham tidak ada!!!"<<endl;
                } 

                delete[] shm_temp; 
                system("pause"); 
                break;
            }

            case '4':{ 
                int target_lot;

                if(user.banyak_saham == 0){
                    cout<<"Portfolio Kosong!!"<<endl; 
                    system("pause");
                    break;
                }
                saham* shm_temp = new saham[user.banyak_saham];

                for(int i = 0; i < user.banyak_saham; i++){
                    shm_temp[i] = user.shm[i];
                } 
                
                sort_lot_asc(shm_temp, user.banyak_saham);

                cout<<"Masukkan Target JUMLAH LOT Yang Dicari: ";
                cin>>target_lot; 
                cin.ignore(100, '\n');

                int hasil = interpolation_search_lot(shm_temp, 0, user.banyak_saham - 1, target_lot);

                if(hasil != -1){
                    cout<<"\n[KETEMU] Ada saham dengan "<<target_lot<<" Lot, Yaitu Saham: "<<shm_temp[hasil].kode_shm<<endl;
                } 
                else{
                    cout<<"\n[GAGAL] Anda Tidak Memiliki Saham Dengan Jumlah Lot:"<<target_lot<<" Lot"<<endl;
                }

                delete[] shm_temp; 
                system("pause");
                break;
            }

            case '5': 
                jual_saham(&user); 
                break;

            case '6': 
                hapus_akun(&user); 
                break;

            case '7': 
                ganti_pass_akun(&user); 
                break;

            case '8': 
                login_user = false; 
                break;

            default: 
                cout<<"Pilihan Tidak Ada!!!"<<endl; 
                break;
        }
    }
}

int main(){
    struct investor inv[100];
    string nama_fix = "Jovan";
    string pass_fix = "031";
    int banyak_investor = 0;
    char pilihan;
    string enter, nama, pass;

    while(true){
        cout<<"\n========================================================="<<endl;
        cout<<"=============== APLIKASI CATATAN INVESTOR ==============="<<endl;
        cout<<"========================================================="<<endl;
        cout<<"1. Login"<<endl;
        cout<<"2. Buat Akun"<<endl;
        cout<<"3. Keluar"<<endl;
        cout<<"=========================================================" << endl;
        cout<<"\nMasukan Pilihan: ";
        cin>> pilihan;
        cin.ignore(100, '\n');
        
        switch(pilihan){
            case '1':{
                int percobaan = 0;
                bool berhasil_login = false;

                while(percobaan < 3 && !berhasil_login){
                    cout<<"Masukan Username Anda: ";
                    getline(cin, nama);
                    cout<<"Masukan Password Anda: ";
                    getline(cin, pass);

                    if(cek_login(nama, pass, nama_fix, pass_fix)){
                        berhasil_login = true;
                        menu_atmin(inv, banyak_investor);
                    } 
                    else{
                        int index_login = cek_login(nama, pass, inv, banyak_investor);
                        if(index_login >= 0){
                            berhasil_login = true;
                            menu_user(inv[index_login]);
                        } 
                        else{
                            bool akun_terdaftar = false;
                            for(int i = 0; i < banyak_investor; i++){
                                if(inv[i].username == nama){
                                    akun_terdaftar = true;
                                    break;
                                }
                            }

                            if(nama == nama_fix || akun_terdaftar){
                                percobaan += 1;
                                cout<<"\nPASSWORD SALAH!!!"<<endl;
                                if(percobaan < 3){
                                    cout<<"Silahkan Tekan Enter Untuk Menginput Ulang (Sisa Percobaan: "<<3 - percobaan<<") :";
                                    getline(cin, enter);
                                }
                            } 
                            else{
                                cout<<"\nAKUN BELUM TERDAFTAR!!!!"<<endl;
                                cout<<"Tekan Enter Untuk Balik Ke Menu Awal dan Membuat Akun";
                                getline(cin, enter);
                                break; 
                            }
                        }
                    }
                }

                if(percobaan == 3){
                    cout<<"\nANDA TELAH GAGAL 3X. KEMBALI KE MENU AWAL!!!!!"<<endl;
                    cout<<"Tekan Enter Untuk Kembali Ke Menu Awal: ";
                    getline(cin, enter);
                }
                break;
            }
            
            case '2':
                buat_akun(inv, banyak_investor, nama_fix);
                break;
            
            case '3':
                cout<<"\nTerima Kasih Telah Menggunakan Aplikasi Kami :)"<<endl;
                return 0;
                
            default:
                cout<<"Pilihan Tidak Ada!!!"<<endl;
                cout<<"Tekan Enter Untuk Balik Ke Menu Awal: ";
                getline(cin, enter);
                break;
        }
    }
    return 0;
}