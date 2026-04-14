// #include <iostream>
// #include <utility>
// using namespace std;

// // Inisialisasi Array Global
// int arr[] = {29, 10, 14, 37, 13};
// int n = sizeof(arr) / sizeof(arr[0]);

// void selectionSort(int arr[], int n) {
//     // Loop luar untuk memindahkan batas sub-array yang belum urut
//     for (int i = 0; i < n - 1; i++) {
//         // Anggap elemen pertama dari bagian belum urut sebagai yang terkecil
//         int indeksMin = i;

//         // Loop dalam untuk mencari elemen terkecil di sisa array
//         for (int j = i + 1; j < n; j++) {
//             if (arr[j] < arr[indeksMin]) {
//                 indeksMin = j; // Simpan indeks elemen yang lebih kecil
//             }
//         }

//         // Tukar elemen terkecil yang ditemukan dengan elemen di posisi i
//         if (indeksMin != i) {
//             swap(arr[i], arr[indeksMin]);
//         }
//     }
// }

// void tampilkanArray(int arr[], int n) {
//     for (int i = 0; i < n; i++) {
//         cout << arr[i] << " ";
//     }
//     cout << endl;
// }

// int main() {
//     cout << "Sebelum Selection Sort: ";
//     tampilkanArray(arr, n);
//     selectionSort(arr, n);
//     cout << "Sesudah Selection Sort : ";
//     tampilkanArray(arr, n);
//     return 0;
// }


#include <iostream>
#include <vector> 
using namespace std;

// Array Global agar mudah diakses oleh semua fungsi
int arr[] = {38, 27, 43, 3, 9, 82, 10, 55};
int n = sizeof(arr) / sizeof(arr[0]);

// Fungsi untuk menggabungkan dua sub-array yang sudah terbagi
void merge(int arr[], int l, int m, int r) {
    // PERBAIKAN: Gunakan vector untuk membuat array dengan ukuran dinamis
    vector<int> temp(r - l + 1);

    int i = l;      // Indeks awal sub-array kiri
    int j = m + 1;  // Indeks awal sub-array kanan
    int k = 0;      // Indeks awal vector temp

    // Bandingkan elemen kiri dan kanan, masukkan yang terkecil ke temp
    while (i <= m && j <= r) {
        if (arr[i] < arr[j]) {
            temp[k] = arr[i];
            i++;
        } else {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }

    // Jika sub-array kiri masih ada sisa, masukkan ke temp
    while (i <= m) {
        temp[k] = arr[i];
        i++;
        k++;
    }

    // Jika sub-array kanan masih ada sisa, masukkan ke temp
    while (j <= r) {
        temp[k] = arr[j];
        j++;
        k++;
    }

    // Salin kembali data dari temp ke array asli (arr)
    for (int x = 0; x < k; x++) {
        arr[l + x] = temp[x];
    }
}

// Fungsi rekursif untuk membagi array (Divide)
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        // Cari titik tengah
        int m = l + (r - l) / 2;  // Mencegah overflow pada indeks besar

        // Bagi terus sisi kiri dan kanan
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Gabungkan kembali (Conquer & Combine)
        merge(arr, l, m, r);
    }
}

int main() {
    cout << "Sebelum sorting: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Panggil fungsi merge sort
    // n-1 sudah benar karena index array dimulai dari 0
    mergeSort(arr, 0, n - 1);

    cout << "Sesudah sorting: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}