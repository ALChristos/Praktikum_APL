#include <iostream>
#include <stdexcept> // Wajib untuk lempar-tangkap error

using namespace std;

int main() {
    int umur;
    
    cout << "Masukkan umur kamu: ";
    cin >> umur;

    // 1. TRY: Kita coba jalankan blok kode ini
    try {
        if (umur < 0) {
            // 2. THROW: Kalau umurnya minus, kita lemparkan error!
            throw runtime_error("Mustahil, umur tidak boleh angka minus!");
        }
          // Baris ini hanya jalan kalau TIDAK ADA error yang dilempar
        cout << "Wah, umur kamu " << umur << " tahun ya." << endl;

    } 
    // 3. CATCH: Jaring untuk menangkap lemparan error dari dalam "try"
    catch (const exception& e) {
        cout << "[DITANGKAP] Pesan Error: " << e.what() << endl;
    }

  
    return 0;
}