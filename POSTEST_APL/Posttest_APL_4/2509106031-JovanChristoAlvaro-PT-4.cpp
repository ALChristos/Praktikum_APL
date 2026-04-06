#include <iostream>
#include <string>
using namespace std;

struct saham{
    string kode_shm;
    int harga_rata_rata;
    int jumlah_lot;
};

struct investor{
    string username;
    string password;
    struct saham shm[50]; 
    int banyak_saham = 0;    
    bool minta_hapus = false;    
};

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


void buat_akun(investor inv[], int &banyak_investor, string nama_fix) {
    string enter, nama, pass;
    cout<<"\n========================================================="<<endl;
    cout<<"============ PEMBUATAN AKUN CATATAN INVESTOR ==========="<<endl;
    cout<<"========================================================="<<endl;
    
    if(banyak_investor >= 100){
        cout<<"TIDAK DAPAT MEMBUAT AKUN KARENA DATA AKUN SUDAH PENUH!!!!"<<endl;
        cout<<"Tekan Enter Untuk Balik Ke Menu Awal...";
        getline(cin, enter);
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
        cout << "Username Sudah Terdaftar, Silahkan Buat Username Baru!!!!";
        cout << "\nTekan Enter Untuk Balik Ke Menu Awal...";
        getline(cin, enter);
    } 
    else{
        inv[banyak_investor].username = nama;
        cout<<"Masukan Password Anda: ";
        getline(cin, inv[banyak_investor].password);
        
        banyak_investor += 1; 
        
        cout<<"\nSelamat Akun Anda Berhasil Dibuat!!!"<<endl;
        cout<<"Tekan Enter Untuk Balik Ke Menu Awal: ";
        getline(cin, enter);
    }
}


int total_modal(saham shm[], int n){ //<---- Rekursif
    if (n <= 0){ 
        return 0;
    }

    int modal_sekarang = shm[n - 1].harga_rata_rata * (shm[n - 1].jumlah_lot * 100);
    return modal_sekarang + total_modal(shm, n - 1); //<----
}


void beli_saham(investor *user){
    string kode, enter;
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
    cout<<"Tekan Enter Untuk Kembali...";
    getline(cin, enter);
}


void porto(investor *user){
    string enter;
    cout<<"\n=================================================================================================="<<endl;
    cout<<"===================================== DAFTAR PORTFOLIO SAHAM ======================================"<<endl;
    cout<<"==================================================================================================="<<endl;
    if(user-> banyak_saham == 0){
        cout<<"Portfolio Anda Masih Kosong!"<<endl;
    } 
    else{
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
    cout<<"Tekan Enter Untuk Kembali...";
    getline(cin, enter);
}


void jual_saham(investor *user){
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
        cout<<"\n[BERHASIL] Saham "<<kode<<" berhasil Dijual Semua dan Dihapus!!!"<<endl;
    } 
    else{
        cout<<"\n[GAGAL] Saham "<<kode<<" Tidak Ditemukan Diportfolio Anda."<<endl;
    }
    cout<<"Tekan Enter Untuk Kembali...";
    getline(cin, enter);
}


void hapus_akun(investor *user){
    string enter;
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
    cout<<"Tekan Enter Untuk Kembali...";
    getline(cin, enter);
}

void ganti_pass_akun(investor *user){
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



void menu_atmin(investor inv[], int &banyak_investor){
    bool login_atmin = true; 
    char pilihan;
    string enter;
    
    while(login_atmin){
        cout<<"\n========================================================="<<endl;
        cout<<"============= SELAMAT DATANG KEMBALI ATMIN! ============="<<endl;
        cout<<"========================================================="<<endl;
        cout<<"1. Melihat Akun Investor"<<endl;
        cout<<"2. Pengajuan Hapus Akun Investor"<<endl;
        cout<<"3. Logout"<<endl;
        cout<<"\nMasukan Pilihan: ";
        cin>>pilihan;
        cin.ignore(100, '\n');
        
        switch(pilihan){
            case '1':
                cout<<"\n======================================================"<<endl;
                cout<<"============= DAFTAR INVESTOR TERDAFTAR =============="<<endl;
                cout<<"======================================================"<<endl;
                if (banyak_investor == 0) {
                    cout<<"Belum Ada Investor Yang Mendaftar."<<endl;
                } 
                else{
                    for(int i = 0; i < banyak_investor; i++){
                        cout<<i + 1<<". Username: "<<inv[i].username<<endl;
                    }
                }
                cout<<"Tekan Enter Untuk Kembali...";
                getline(cin, enter);
                break;
                
            case '2':{
                cout<<"\n======================================================"<<endl;
                cout<<"========== DAFTAR PENGAJUAN HAPUS AKUN ==============="<<endl;
                cout<<"======================================================"<<endl;

                int laporan = 0;
                for(int i = 0; i < banyak_investor; i++){
                    if(inv[i].minta_hapus == true){
                        cout<<i + 1<<". Username: "<<inv[i].username<<" Mengajukan Hapun Akun"<<endl;
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
                cout<<"Tekan Enter Untuk Kembali...";
                getline(cin, enter);
                break;
            }

            case '3':
                login_atmin = false;
                break;
            
            default:
                cout<<"Pilihan Tidak Ada!!!"<<endl;
                break;
        }
    }
}


void menu_user(investor &user){
    bool login_user = true;
    char pilihan;

    while(login_user){
        cout<<"\n========================================================="<<endl;
        cout<<"=== PORTFOLIO INVESTOR: "<<user.username<<" ==="<<endl;
        cout<<"========================================================="<<endl;
        cout<<"1. Beli Saham"<<endl;  
        cout<<"2. Lihat Portfolio Saham"<<endl;
        cout<<"3. Jual Semua Saham"<<endl;
        cout<<"4. Ajukan Penghapusan Akun"<<endl;
        cout<<"5. Ganti Password Akun"<<endl;
        cout<<"6. Logout"<<endl;
        cout<<"\nMasukan Pilihan: ";
        cin>>pilihan;
        cin.ignore(100, '\n');

        switch(pilihan){
            case '1':
                beli_saham(&user); 
                break;

            case '2':
                porto(&user);
                break;

            case '3':
                jual_saham(&user);
                break;

            case '4':
                hapus_akun(&user);
                break;

            case '5':
                ganti_pass_akun(&user);
                break;

            case '6':
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
        cout<<"1. Login" << endl;
        cout<<"2. Buat Akun" << endl;
        cout<<"3. Keluar" << endl;
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