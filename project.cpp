#include <bits/stdc++.h>
using namespace std;


struct Mahasiswa {
    string nim;
    string nama;
    string prodi;
    Mahasiswa *next;
    Mahasiswa(string _nim, string _nama, string _prodi)
        : nim(_nim), nama(_nama), prodi(_prodi), next(nullptr) {}
};

struct BSTNode {
    string nim;
    string nama;
    BSTNode *left, *right;
    BSTNode(string _nim, string _nama)
        : nim(_nim), nama(_nama), left(nullptr), right(nullptr) {}
};


Mahasiswa *head = nullptr;             // Linked List
BSTNode *root = nullptr;               // BST
unordered_map<string, vector<string>> graph; // Graph hubungan

// Linked list

void tambahMahasiswaLL(string nim, string nama, string prodi) {
    Mahasiswa *m = new Mahasiswa(nim, nama, prodi);

    if (!head) {
        head = m;
        return;
    }
    Mahasiswa *cur = head;
    while (cur->next) cur = cur->next;
    cur->next = m;
}

bool hapusMahasiswaLL(string nim) {
    if (!head) return false;

    if (head->nim == nim) {
        Mahasiswa *del = head;
        head = head->next;
        delete del;
        return true;
    }

    Mahasiswa *cur = head;
    while (cur->next && cur->next->nim != nim)
        cur = cur->next;

    if (!cur->next) return false;

    Mahasiswa *del = cur->next;
    cur->next = cur->next->next;
    delete del;
    return true;
}

void editMahasiswaLL(string nim, string namaBaru, string prodiBaru) {
    Mahasiswa *cur = head;
    while (cur) {
        if (cur->nim == nim) {
            cur->nama = namaBaru;
            cur->prodi = prodiBaru;
            return;
        }
        cur = cur->next;
    }
}

// BST

BSTNode* insertBST(BSTNode *node, string nim, string nama) {
    if (!node) return new BSTNode(nim, nama);
    if (nim < node->nim) node->left = insertBST(node->left, nim, nama);
    else if (nim > node->nim) node->right = insertBST(node->right, nim, nama);
    return node;
}

BSTNode* searchBST(BSTNode *node, string nim) {
    if (!node) return nullptr;
    if (node->nim == nim) return node;
    if (nim < node->nim) return searchBST(node->left, nim);
    else return searchBST(node->right, nim);
}

void inorder(BSTNode *node) {
    if (!node) return;
    inorder(node->left);
    cout << node->nim << " - " << node->nama << "\n";
    inorder(node->right);
}

void preorder(BSTNode *node) {
    if (!node) return;
    cout << node->nim << " - " << node->nama << "\n";
    preorder(node->left);
    preorder(node->right);
}

void postorder(BSTNode *node) {
    if (!node) return;
    postorder(node->left);
    postorder(node->right);
    cout << node->nim << " - " << node->nama << "\n";
}

// Graph

void tambahTeman(string a, string b) {
    graph[a].push_back(b);
    graph[b].push_back(a);
}

bool cekTerhubung(string a, string b) {
    unordered_set<string> visited;
    queue<string> q;

    q.push(a);
    visited.insert(a);

    while (!q.empty()) {
        string now = q.front();
        q.pop();

        if (now == b) return true;

        for (string next : graph[now]) {
            if (!visited.count(next)) {
                visited.insert(next);
                q.push(next);
            }
        }
    }
    return false;
}

// Menu
void tampilkanSemua() {
    cout << "\n==== DATA MAHASISWA ====\n";
    Mahasiswa *cur = head;
    while (cur) {
        cout << cur->nim << " | " << cur->nama << " | " << cur->prodi << "\n";
        cur = cur->next;
    }
    if (!head) cout << "(Kosong)\n";
}

void menu() {
    cout << "\n===== SISTEM INFORMASI MAHASISWA =====\n";
    cout << "1. Tambah Mahasiswa\n";
    cout << "2. Hapus Mahasiswa\n";
    cout << "3. Edit Mahasiswa\n";
    cout << "4. Cari Mahasiswa x\n";
    cout << "5. BST Traversal\n";
    cout << "6. Tambah Pertemanan \n";
    cout << "7. Cek Apakah Terhubung \n";
    cout << "8. Tampilkan Semua Mahasiswa\n";
    cout << "0. Keluar\n";
    cout << "Pilih: ";
}

int main() {
    while (true) {
        menu();
        int pilih;
        cin >> pilih;
        cin.ignore();

        if (pilih == 0) break;

        if (pilih == 1) {
            string nim, nama, prodi;
            cout << "NIM: "; getline(cin, nim);
            cout << "Nama: "; getline(cin, nama);
            cout << "Prodi: "; getline(cin, prodi);
            tambahMahasiswaLL(nim, nama, prodi);
            root = insertBST(root, nim, nama);
        }

        else if (pilih == 2) {
            string nim;
            cout << "NIM yang dihapus: ";
            getline(cin, nim);
            hapusMahasiswaLL(nim);
        }

        else if (pilih == 3) {
            string nim, nama, prodi;
            cout << "NIM: "; getline(cin, nim);
            cout << "Nama baru: "; getline(cin, nama);
            cout << "Prodi baru: "; getline(cin, prodi);
            editMahasiswaLL(nim, nama, prodi);
        }

        else if (pilih == 4) {
            string nim;
            cout << "Cari NIM: "; getline(cin, nim);
            BSTNode *res = searchBST(root, nim);
            if (res)
                cout << "Ditemukan: " << res->nim << " - " << res->nama << "\n";
            else
                cout << "Tidak ditemukan\n";
        }

        else if (pilih == 5) {
            cout << "\nInorder:\n"; inorder(root);
            cout << "\nPreorder:\n"; preorder(root);
            cout << "\nPostorder:\n"; postorder(root);
        }

        else if (pilih == 6) {
            string a, b;
            cout << "NIM 1: "; getline(cin, a);
            cout << "NIM 2: "; getline(cin, b);
            tambahTeman(a, b);
        }

        else if (pilih == 7) {
            string a, b;
            cout << "Cek dari NIM: "; getline(cin, a);
            cout << "ke NIM: "; getline(cin, b);
            if (cekTerhubung(a, b)) cout << "Mereka terhubung!\n";
            else cout << "Tidak terhubung.\n";
        }

        else if (pilih == 8) {
            tampilkanSemua();
        }

        else {
            cout << "Pilihan salah!\n";
        }
    }
}
