#include <iostream>
using namespace std;

int main(){
    string nama = "Jovan";
    string password = "031";
    string nama_login;
    string password_login;

    int percobaan = 0;
    bool ulang = true;
    int menu_pilihan;

    while(percobaan < 3){

        cout<<"====================================="<<endl;
        cout<<"=============== LOGIN ==============="<<endl;
        cout<<"====================================="<<endl;
        cout<<"Masukkan Username: ";
        cin>>nama_login;
        
        cout<<"Masukan Password: ";
        cin>>password_login;
        
        if(nama_login == nama && password_login == password){
            cout<<endl;
            cout<<"====================================="<<endl;
            cout<<"=== SELAMAT ANDA BERHASIL LOGIN!! ==="<<endl;
            cout<<"====================================="<<endl;
            cout<<endl;

            break;
        }

        else if((nama_login != nama || password_login != password) && percobaan < 2){
            cout<<"Username/Password Yang Anda Input Salah!!!"<<endl;
            cout<<"\nPercobaan Login Anda Sisa: "<<2 - percobaan<<endl;
            percobaan += 1;
        }
        
        else if(percobaan < 3){
            percobaan += 1;
            cout<<"\nPercobaan Login Anda Sisa: "<<3 - percobaan<<endl;
            cout<<"HAYOOOO KAMU SIAPA!?!?!?"<<endl;
            return 0;
        }

    }

    while(ulang){

        cout<<"==================================="<<endl;
        cout<<"||    PROGRAM KONVERSI PANJANG   ||"<<endl;
        cout<<"==================================="<<endl;
    
        cout<<"1. Meter ke Kilometer dan Centimeter"<<endl;
        cout<<"2. Kilometer ke Meter dan Centimeter"<<endl;
        cout<<"3. Centimeter ke Meter dan Kilometer"<<endl;
        cout<<"4. Keluar"<<endl;
        cout<<"Pilih menu: ";
        cin>>menu_pilihan;
    
        double nilai_panjang;
    
        switch(menu_pilihan){
            case 1:
                cout<<"Masukkan Nilai Dalam Meter: ";
                cin>>nilai_panjang;
                cout<<endl;
                cout<<"Hasil: "<<nilai_panjang / 1000<<" Kilometer dan "<<nilai_panjang * 100 <<" Centimeter"<<endl;
                cout<<endl;
                break;
    
            case 2:
                cout<<"Masukkan Nilai Dalam Kilometer: ";
                cin>>nilai_panjang;
                cout<<"Hasil: "<< nilai_panjang * 1000<<" Meter dan "<<nilai_panjang * 100000<<" Centimeter"<<endl;
                cout<<endl;
                break;
    
            case 3:
                cout<<"Masukkan nilai Dalam Centimeter: ";
                cin>>nilai_panjang;
                cout<<"Hasil: "<<nilai_panjang / 100<<" Meter dan "<<nilai_panjang / 100000<<" Kilometer"<<endl;
                cout<<endl;
                break;
                
            case 4:
                cout<<"Program Selesai."<<endl;
                ulang = false;
                break;
                
            default:
                cout<<"PILIHAN TIDAK TERSEDIA !!!."<<endl;
                ulang = false;
                break;
            
        }
    }

    return 0;
}
