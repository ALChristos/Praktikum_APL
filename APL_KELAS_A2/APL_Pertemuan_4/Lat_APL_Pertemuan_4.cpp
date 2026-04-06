// // #include <iostream>
// // #include <string>

// // using namespace std;

// // int main(){
// //     string rumahucup = "Ucup";
// //     cout<< &rumahucup << endl;
// // }

// // passByValue.cpp
// # include <iostream>
// using namespace std;
// struct Address{
// string kota;
// string provinsi;
// string negara;
// };
// int main(){
// // deklarasi variabel dengan struct
// Address address1, address2;
// // mengisi value address1
// address1.kota = "Samarinda";
// address1.provinsi = "Kalimantan Timur";
// address1.negara = "Indonesia";
// // mengcopy value address1 ke address2
// address2 = address1;
// // mengganti property kota dari samarinda ke ikn
// address2.kota = "ikn";
// // value address1
// cout << address1.kota << endl;
// // value address2
// cout << address2.kota;
// return 0;
// }

// buatPtr.cpp
#include <iostream>
using namespace std;
int main () {
string var = "Aku Variabel";
string *varPtr = &var;
cout << "Hasil dari varPtr: " << varPtr << endl;
cout << "Hasil dari *varPtr: " << *varPtr <<endl;
cout << endl << "Kesimpulannya varPtr isi nya alamatnya var" <<endl;
cout << "*varPtr hasilnya value dari var" <<endl;
cout << "Jika masih bingung bisa amati output berikut" <<endl;
cout << endl;
cout << "Hasil/value dari var " << var <<endl;
cout << "Hasil/value dari alamat var (&var) " << &var <<endl;
cout << "Hasil/value dari varPtr " << varPtr <<endl;
cout << "Hasil/value dari *varPtr " << var <<endl;
return 0;
}