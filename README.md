# LAPRES SISOP MODUL 5

**Penjelasan soal 2**

Tugas pada modul ini adalah membuat sebuah Shell / Command Interpreter interaktif sederhana pada Sistem Operasi 16-bit berbasis teks (CLI). Sistem operasi ini harus mampu menerima input perintah dari pengguna, memproses logika string, mengubah warna teks sistem berdasarkan tema musim (VGA Memory Manipulation), melakukan perhitungan matematika dasar (add, sub, fac), serta mencetak dekorasi visual berupa segitiga karakter.

Proses pengerjaan dan eksekusi sistem operasi ini dibagi menjadi 4 tahapan utama:

- Tahap Penulisan Kode (Source Code): Mengimplementasikan logika pemrosesan string dan perintah CLI di dalam file bahasa C standar yaitu kernel.c.
- Tahap Kompilasi (Docker Build): Menggunakan script ./build.sh untuk menjalankan compiler bcc (Bruce's C Compiler) untuk mengompilasi kernel C, dan nasm untuk mengompilasi bootloader.asm ke dalam bentuk biner 16-bit (kernel.bin dan bootloader.bin).
- Tahap Pembuatan Image (Disk Image): Menggabungkan file biner tersebut ke dalam file replika disket virtual berukuran 1.44 MB bernama floppy.img menggunakan perintah low-level dd. bootloader.bin diletakkan tepat pada Sektor 0 (Master Boot Record).
- Tahap Emulasi (QEMU): Menjalankan sistem operasi menggunakan emulator QEMU (qemu-system-i386 -fda floppy.img) sehingga BIOS virtual membaca bootloader di Sektor 0, memuat kernel ke RAM virtual, dan mengeksekusi shell.

**Penjelasan Kode Kernel.c**
```c
else if (startsWith(cmd, "season ")) {
    if (strcmp(cmd + 7, "winter"))      color = 0x09; // Biru
    else if (strcmp(cmd + 7, "spring")) color = 0x0A; // Hijau Terang
    else if (strcmp(cmd + 7, "summer")) color = 0x0E; // Kuning
    else if (strcmp(cmd + 7, "fall"))   color = 0x06; // Oranye
    else if (strcmp(cmd + 7, "radiant")) color = 0x0D; // Pink
    
    printString(cmd + 7);
    printString(" mode");
    newline();
}
```
Fungsi ini mengambil argumen setelah teks "season ". Nilai dari variabel global color akan diubah ke kode Hex warna teks VGA yang sesuai. Setiap pemanggilan fungsi cetak teks berikutnya otomatis menggunakan warna baru ini.
```c
else if (startsWith(cmd, "triangle ")) {
    if (cmd[9] != '\0' && cmd[9] != ' ' && cmd[9] != '\r' && cmd[9] != '\n') {
        int n = atoi(cmd + 9);
        int r, c;
        if (n > 0 && n <= 15) { 
            for (r = 1; r <= n; r++) {
                for (c = 1; c <= r; c++) {
                    printString("X");
                }
                newline();
            }
        } else {
            printString("Input must be between 1 and 15");
            newline();
        }
    }
}
```

Menggunakan perulangan bersandar (nested loop) untuk mencetak baris (r) dan kolom (c) karakter 'X'. Diberikan validasi cmd[9] untuk mencegah jalannya fungsi triangle secara tidak sengaja akibat membaca karakter sampah atau string kosong saat sistem pertama kali dinyalakan.

```c
else if (strcmp(cmd, "clear")) xungsi ini mengembalikan nilai variabel color ke bentuk asal (0x0A), lalu memanggil clearScreen() untuk mengulangi seluruh alamat memori video VGA (0xB800) dan mengisinya dengan karakter kosong atau spasi (' ') agar layar kembali bersih.
    color = 0x0A; // Kembalikan warna default ke hijau
    clearScreen();
}
```

**Kendala**
Kendala: Emulator Bochs tidak dapat dijalankan langsung di lingkungan praktikum (terjadi eror panic / tidak bisa membaca konfigurasi display), sehingga proses simulasi sistem operasi terhambat.
Solusi: Praktikan mengalihkan emulator dari Bochs ke QEMU (qemu-system-i386). QEMU terbukti lebih stabil dan memiliki kompatibilitas yang jauh lebih baik dalam melakukan emulasi arsitektur x86 16-bit, terutama saat dijalankan di dalam mesin virtual (VM Kali Linux) di atas perangkat keras modern. File floppy.img tetap bisa dieksekusi dengan lancar menggunakan parameter -fda.

  
