// // // // // #include <iostream>
// // // // // using namespace std;

// // // // // int main(){
// // // // //     cout<<"Halo DUnia"<<endl<<"ABC";
// // // // // // }


// // // // // #include <iostream>
// // // // // #include <string>
// // // // // using namespace std;

// // // // // int main() {
// // // // //     string Nama;

// // // // //     cout << "Masukkan Nama lengkap: ";
// // // // //     getline(cin, Nama);

// // // // //     cout << "Halo, " << Nama;

// // // // //     return 0;
// // // // // }


// // // // #include <iostream>
// // // // using namespace std;
// // // // int main() {
// // // //     bool hujan = false;
// // // //     string pesan = hujan ? "Bawa payung" : "Tidak perlu payung";
// // // //     cout << pesan;
// // // // }


// // // #include <iostream>
// // // using namespace std;

// // // int main() {
// // //     int age = 18;

// // //     if (age < 13) {
// // //         cout << "Anak";
// // //     }
// // //     else if (age >= 13 && age <= 18) {
// // //         cout << "Remaja";
// // //     }
// // //     else {
// // //         cout << "Dewasa";
// // //     }

// // //     return 0;
// // // }



// // #include <iostream>
// // using namespace std;
// // int main() {
// // int nilai;
// // cout << " = Konversi Nilai Akademik =\n";
// // cout << "Masukkan nilai akhir (0-100): ";
// // cin >> nilai;
// // if (nilai < 0 | nilai > 100) {
// // cout << "Error: Nilai harus 0-100.\n";
// // return 1;
// // }
// // switch (nilai / 10) {
// // case 10:
// // cout << "Predikat: A (Sangat Baik)\n";
// // break;
// // case 9:
// // cout << "Predikat: A (Sangat Baik)\n";
// // break;
// // case 8:
// // cout << "Predikat: B (Baik)\n";
// // break;
// // case 7:
// // cout << "Predikat: C (Cukup)\n";
// // break;
// // case 6:
// // cout << "Predikat: D (Kurang)\n";
// // break;
// // default:
// // cout << "Predikat: E (Gagal)\n";
// // break;

// // }
// // return 0;
// // }

// #include <iostream>
// using namespace std;
// int main() {
// int arr[] = {1, 2, 3, 88, 5};
// for (int x : arr) {
// cout << x << endl;
// }
// return 0;
// }