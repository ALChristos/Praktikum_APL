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
};

int main(){
    struct investor inv[100];
    string nama_fix = "Jovan";
    string pass_fix = "031";
    int coba = 0;
    int banyak_investor = 0;
    char pilihan;
    string enter;
    string nama;
    string pass;

    while(true){
        cout<<"\n========================================================"<<endl;
        cout<<"=============== APLIKASI CATATAN INVESTOR ==============="<<endl;
        cout<<"========================================================="<<endl;
        cout<<"1. Login"<<endl;
        cout<<"2. Buat Akun"<<endl;
        cout<<"3. Keluar"<<endl;
        cout<<"========================================================="<<endl;
        cout<<"========================================================="<<endl;
        cout<<"\nMasukan Pilihan: ";
        cin>>pilihan;
        cin.ignore(100, '\n');
        
        switch(pilihan){
            case '1':{
                int percobaan = 0;
                bool ulang = true;

                while(percobaan < 3 && ulang == true){
                    int index_login = -1;
                    cout<<"Masukan Username Anda: ";
                    getline(cin, nama);
                    cout<<"Masukan Password Anda: ";
                    getline(cin, pass);

                    for(int i = 0; i < banyak_investor; i++){
                        if(nama == inv[i].username && pass == inv[i].password){
                            index_login = i; 
                            break;
                        }
                    }
                    
                    if(nama == nama_fix && pass == pass_fix){
                        bool login_atmin = true; 
                        while(login_atmin){
                            cout<<endl;
                            cout<<"========================================================="<<endl;
                            cout<<"============= SELAMAT DATANG KEMBALI ATMIN! ============="<<endl;
                            cout<<"========================================================="<<endl;
                            cout<<"1. Melihat Akun Investor"<<endl;
                            cout<<"2. Logout"<<endl;
                            cout<<"\nMasukan Pilihan: ";
                            cin>>pilihan;
                            cin.ignore(100, '\n');
    
                            switch(pilihan){
                            case '1':
                                cout<<"\n============= DAFTAR INVESTOR TERDAFTAR ============="<<endl;
                                if(banyak_investor == 0){
                                    cout<<"Belum Ada Investor Yang Mendaftar."<<endl;
                                } 
                                else{
                                    for(int i = 0; i < banyak_investor; i++){
                                        cout << i+1 << ". Username: " << inv[i].username << endl;
                                    }
                                }
                                cout << "Tekan Enter Untuk Kembali...";
                                getline(cin, enter);
                                break;

                            case '2':
                                login_atmin = false;
                                ulang = false;
                                break;

                            default:
                                cout<<"Pilihan Tidak Ada!!!"<<endl;
                                break;
                        }
                        
                    }

                }
                   
                    else if(index_login >= 0 && pass == inv[index_login].password){
                        bool login_user = true;
                        while(login_user){
                            cout<<endl;
                            cout<<"========================================================="<<endl;
                            cout<<"=== PORTFOLIO INVESTOR: "<<inv[index_login].username<<" ==="<<endl;
                            cout<<"========================================================="<<endl;
                            cout<<"1. Beli Saham"<<endl;  //<-------INI CREATE SEKALIAN UPDATE, JADI OTOMATIS UPDATE (INI TANDA PRIBADI DAN BUKAN AI!!!!!)
                            cout<<"2. Lihat Portfolio Saham"<<endl;
                            cout<<"3. Jual Semua Saham"<<endl;
                            cout<<"4. Logout"<<endl;
                            cout<<"\nMasukan Pilihan: ";
                            cin>>pilihan;
                            cin.ignore(100, '\n');

                            switch(pilihan){
                                case '1': {
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
                                    for(int i = 0; i < inv[index_login].banyak_saham; i++){
                                        if(inv[index_login].shm[i].kode_shm == kode) {
                                            index_saham = i; 
                                            break;
                                        }
                                    }

                                    if(index_saham != -1){
                                        int lot_lama = inv[index_login].shm[index_saham].jumlah_lot;
                                        int harga_lama = inv[index_login].shm[index_saham].harga_rata_rata;
                                        
                                        int total_modal_lama = lot_lama * harga_lama;
                                        int total_modal_baru = lot * harga;
                                        int total_lot = lot_lama + lot;
                                        
                                        inv[index_login].shm[index_saham].harga_rata_rata = (total_modal_lama + total_modal_baru) / total_lot;
                                        inv[index_login].shm[index_saham].jumlah_lot = total_lot;
                                        
                                        cout<<"\n[BERHASIL] Anda Berhasil Menambah Rata-rata Saham "<<kode<<"!"<< endl;
                                    } 
                                    else{

                                        int saham_baru = inv[index_login].banyak_saham;
                                        inv[index_login].shm[saham_baru].kode_shm = kode;
                                        inv[index_login].shm[saham_baru].harga_rata_rata = harga;
                                        inv[index_login].shm[saham_baru].jumlah_lot = lot;
                                        inv[index_login].banyak_saham += 1; 
                                        
                                        cout<<"\n[BERHASIL] Saham "<<kode<<" Berhasil Ditambahkan Ke Portfolio!"<<endl;
                                    }
                                    cout<<"Tekan Enter Untuk Kembali...";
                                    getline(cin, enter);
                                    break;
                                }

                                case '2':{ 
                                    cout<<"\n============= DAFTAR PORTFOLIO SAHAM =============="<<endl;
                                    if(inv[index_login].banyak_saham == 0){
                                        cout<<"Portfolio Anda Masih Kosong!"<<endl;
                                    } 
                                    else{
                                        int modal_total = 0;
                                        for(int i = 0; i < inv[index_login].banyak_saham; i++){
                                            string kode = inv[index_login].shm[i].kode_shm;
                                            int harga = inv[index_login].shm[i].harga_rata_rata;
                                            int lot = inv[index_login].shm[i].jumlah_lot;
                                            int modal = harga * (lot * 100); 
                                            
                                            cout<<i+1<<". "<<kode<<" | Lot: "<<lot<<" | Harga Rata-rata: Rp"<<harga<<" | Total Modal: Rp"<<modal<<endl;
                                            modal_total += modal;
                                        }
                                        cout<<"---------------------------------------"<<endl;
                                        cout<<"TOTAL SEMUA MODAL: Rp"<<modal_total<<endl;
                                    }
                                    cout<<"Tekan Enter Untuk Kembali...";
                                    getline(cin, enter);
                                    break;
                                }

                                case '3':{ 
                                    string kode;
                                    cout << "Masukan Kode Emiten yang ingin dijual SEMUA: ";
                                    getline(cin, kode);
                                    
                                    int index_saham = -1;
                                    for(int i = 0; i < inv[index_login].banyak_saham; i++){
                                        if(inv[index_login].shm[i].kode_shm == kode) {
                                            index_saham = i;
                                            break;
                                        }
                                    }
                                    
                                    if(index_saham != -1){
                                        for(int i = index_saham; i < inv[index_login].banyak_saham - 1; i++) {
                                            inv[index_login].shm[i] = inv[index_login].shm[i+1];
                                        }
                                        inv[index_login].banyak_saham -= 1; 
                                        cout<<"\n[BERHASIL] Saham "<<kode<<" berhasil Dijual Semua dan Dihapus!!!"<<endl;
                                    } 
                                    else{
                                        cout<<"\n[GAGAL] Saham "<<kode<<" Tidak Ditemukan Diportfolio Anda."<<endl;
                                    }
                                    cout<<"Tekan Enter Untuk Kembali...";
                                    getline(cin, enter);
                                    break;
                                }

                                case '4':
                                    login_user = false;
                                    ulang = false;
                                    break;

                                default:
                                cout<<"Pilihan Tidak Ada!!!"<<endl;
                                break;
                        }
                    }
                }

                else if((index_login >= 0 && pass != inv[index_login].password) || (nama == nama_fix && pass != pass_fix)){
                    percobaan += 1;
                    cout<<"PASSWORD SALAH!!!"<<endl;
                    cout<<"\nSilahkan Tekan Enter Untuk Menginput Ulang"<<"(Sisa Percobaan: "<<3 - percobaan<<") :";
                    getline(cin, enter);
                }
    
                else{
                    cout<<"AKUN BELUM TERDAFTAR!!!!"<<endl;
                    cout<<"Tekan Enter Untuk Balik Ke Menu Awal dan Membuat Akun";
                    getline(cin, enter);
                    break;
                }

            }

            if (percobaan == 3) {
                ulang = true;
                cout << "\nANDA TELAH GAGAL 3X. KEMBALI KE MENU AWAL!!!!!" << endl;
                cout << "Tekan Enter Untuk Kembali Ke Menu Awal: ";
                getline(cin, enter);
            }
            break;
        }
        
        case '2':{
            
            cout<<"========================================================="<<endl;
            cout<<"============ PEMBUATAN AKUN CATATAN INVESRTOR ==========="<<endl;
            cout<<"========================================================="<<endl;
    
           if (banyak_investor >= 100) {
                    cout<<"Mohon Maaf, Memori Pendaftaran Sudah Penuh"<<endl;
                    cout<<"Tekan Enter Untuk Balik Ke Menu Awal...";
                    getline(cin, enter);
                    break;
                }

                cout<<"Masukan Username Anda: ";
                getline(cin, nama);

                bool nama_kembar = false;
                if(nama == nama_fix) {
                    nama_kembar = true;
                } 
                else {
                    for(int i = 0; i < banyak_investor; i++) {
                        if(nama == inv[i].username) {
                            nama_kembar = true;
                            break;
                        }
                    }
                }

                if(nama_kembar){
                    cout<<"Username Sudah Terdaftar, Silahkan Buat Username Baru!!!!";
                    cout<<"\nTekan Enter Untuk Balik Ke Menu Awal...";
                    getline(cin, enter);
                } 
                else {
                    inv[banyak_investor].username = nama;
                    cout<<"Masukan Password Anda: ";
                    getline(cin, inv[banyak_investor].password);
                    
                    banyak_investor += 1; 
                    
                    cout<<"\nSelamat Akun Anda Berhasil Dibuat!!!"<<endl;
                    cout<<"Tekan Enter Untuk Balik Ke Menu Awal: ";
                    getline(cin, enter);
                }
                break;
            }
            
            case '3':
                cout<<"\nTerima Telah Menggunakan Aplikasi Kami :)"<<endl;
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



    


            

           



