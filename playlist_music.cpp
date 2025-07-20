#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <vector>

using namespace std;

// Struktur untuk menyimpan informasi lagu
struct Song {
    string title;
    string artist;
    string genre;
};

// Kelas untuk mengelola playlist
class Playlist {
private:
    vector<Song> songs; // Array dinamis untuk menyimpan lagu
    stack<Song> history; // Tumpukan untuk menyimpan lagu yang dihapus
    Song arraySongs[10]; // Array statis untuk latihan tambahan
    int arraySize = 0;   // Ukuran array statis

public:
    // Menambahkan lagu ke playlist (vektor)
    void addSong(const Song& song) {
        songs.push_back(song);
        cout << "Lagu '" << song.title << "' ditambahkan ke playlist." << endl;
    }

    // Menambahkan lagu ke array statis
    void addToArray(const Song& song) {
        if (arraySize < 10) {
            arraySongs[arraySize++] = song;
            cout << "Lagu '" << song.title << "' ditambahkan ke array statis." << endl;
        } else {
            cout << "Array sudah penuh." << endl;
        }
    }

    // Menampilkan isi array statis
    void displayArraySongs() {
        if (arraySize == 0) {
            cout << "Array lagu kosong." << endl;
            return;
        }

        cout << "Isi Array Statis Lagu:" << endl;
        for (int i = 0; i < arraySize; ++i) {
            cout << i << ": " << arraySongs[i].title << " - " << arraySongs[i].artist << " [" << arraySongs[i].genre << "]" << endl;
        }
    }

    // Menghapus lagu dari playlist
    void removeSong(int index) {
        if (index < 0 || index >= songs.size()) {
            cout << "Indeks tidak valid." << endl;
            return;
        }
        history.push(songs[index]);
        songs.erase(songs.begin() + index);
        cout << "Lagu dihapus dari playlist." << endl;
    }

    // Menampilkan semua lagu di playlist
    void displaySongs() {
        if (songs.empty()) {
            cout << "Playlist kosong." << endl;
            return;
        }

        cout << "Playlist:" << endl;
        for (size_t i = 0; i < songs.size(); ++i) {
            cout << i << ": " << songs[i].title << " - " << songs[i].artist << " [" << songs[i].genre << "]" << endl;
        }
    }

    // Mengembalikan lagu terakhir yang dihapus
    void restoreLastRemoved() {
        if (history.empty()) {
            cout << "Tidak ada lagu yang dihapus." << endl;
            return;
        }
        Song lastRemoved = history.top();
        history.pop();
        addSong(lastRemoved);
    }

    // Mengelompokkan lagu berdasarkan genre
    void groupByGenre() {
        map<string, vector<Song>> genreMap;
        for (const auto& song : songs) {
            genreMap[song.genre].push_back(song);
        }

        cout << "Lagu dikelompokkan berdasarkan genre:" << endl;
        for (const auto& entry : genreMap) {
            cout << entry.first << ":" << endl;
            for (const auto& song : entry.second) {
                cout << " - " << song.title << " - " << song.artist << endl;
            }
        }
    }
};

int main() {
    Playlist playlist;
    int choice;
    do {
        cout << "\nMenu:\n"
             << "1. Tambah Lagu ke Playlist\n"
             << "2. Hapus Lagu\n"
             << "3. Tampilkan Playlist\n"
             << "4. Kembalikan Lagu Terakhir yang Dihapus\n"
             << "5. Kelompokkan Lagu Berdasarkan Genre\n"
             << "6. Tambah Lagu ke Array Statis\n"
             << "7. Tampilkan Lagu di Array Statis\n"
             << "8. Keluar\n"
             << "Pilih opsi: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Song song;
                cout << "Masukkan judul lagu: ";
                cin.ignore();
                getline(cin, song.title);
                cout << "Masukkan nama artis: ";
                getline(cin, song.artist);
                cout << "Masukkan genre: ";
                getline(cin, song.genre);
                playlist.addSong(song);
                break;
            }
            case 2: {
                int index;
                cout << "Masukkan indeks lagu yang ingin dihapus: ";
                cin >> index;
                playlist.removeSong(index);
                break;
            }
            case 3:
                playlist.displaySongs();
                break;
            case 4:
                playlist.restoreLastRemoved();
                break;
            case 5:
                playlist.groupByGenre();
                break;
            case 6: {
                Song song;
                cout << "Masukkan judul lagu: ";
                cin.ignore();
                getline(cin, song.title);
                cout << "Masukkan nama artis: ";
                getline(cin, song.artist);
                cout << "Masukkan genre: ";
                getline(cin, song.genre);
                playlist.addToArray(song);
                break;
            }
            case 7:
                playlist.displayArraySongs();
                break;
            case 8:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    } while (choice != 8);

    return 0;
}
