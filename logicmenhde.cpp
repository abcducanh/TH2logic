#include <iostream>
#include <string>
#include <unordered_map>
#include <cctype>
#include <stack>

using namespace std;

// Hàm th?c hi?n phép toán PH? Ð?NH (~)
bool PhuDinh(bool giaTri) {
    return !giaTri;
}

// Hàm th?c hi?n phép toán VÀ (&)
bool Va(bool a, bool b) {
    return a && b;
}

// Hàm th?c hi?n phép toán HO?C (|)
bool Hoac(bool a, bool b) {
    return a || b;
}

// Hàm th?c hi?n phép toán SAI L?CH (>)
bool SaiLech(bool a, bool b) {
    return !a || b;
}

// Hàm ki?m tra tính h?p l? c?a bi?u th?c logic
bool KiemTraHopLe(const string& bieuThuc) {
    int ngoacMo = 0;

    // Ki?m tra t?ng ký t? trong bi?u th?c
    for (size_t i = 0; i < bieuThuc.size(); i++) {
        char kyTu = bieuThuc[i];

        // Ki?m tra d?u ngo?c
        if (kyTu == '(') {
            ngoacMo++;
        } else if (kyTu == ')') {
            if (ngoacMo == 0) return false; // Có ngo?c dóng mà không có ngo?c m?
            ngoacMo--;
        }

        // Ki?m tra các toán t? h?p l?
        if (kyTu == '&' || kyTu == '|' || kyTu == '>' || kyTu == '~') {
            if (i == 0 || i == bieuThuc.size() - 1) {
                return false; // Không có toán t? ? d?u ho?c cu?i bi?u th?c
            }
            if (bieuThuc[i - 1] == '(' || bieuThuc[i + 1] == ')') {
                return false; // Không có toán t? li?n sau d?u ngo?c
            }
        }
    }

    // Ð?m b?o r?ng các d?u ngo?c m? và dóng d?u kh?p
    return ngoacMo == 0;
}

// Hàm tính toán giá tr? c?a bi?u th?c logic
bool TinhGiaTriBieuThuc(const string& bieuThuc, const unordered_map<char, bool>& giaTriBien) {
    stack<bool> nganXepToanHang; // Ngan x?p luu tr? các giá tr? logic
    stack<char> nganXepToanTu; // Ngan x?p luu tr? các toán t? logic

    for (size_t i = 0; i < bieuThuc.size(); i++) {
        char kyTu = bieuThuc[i];

        // N?u là bi?n (A-Z), l?y giá tr? t? b?ng giá tr?
        if (isalpha(kyTu)) {
            nganXepToanHang.push(giaTriBien.at(kyTu));
        }
        // N?u g?p toán t? PH? Ð?NH (~), th?c hi?n ph? d?nh
        else if (kyTu == '~') {
            bool toanHang = nganXepToanHang.top();
            nganXepToanHang.pop();
            nganXepToanHang.push(PhuDinh(toanHang));
        }
        // N?u g?p toán t? VÀ (&)
        else if (kyTu == '&') {
            nganXepToanTu.push(kyTu);
        }
        // N?u g?p toán t? HO?C (|)
        else if (kyTu == '|') {
            nganXepToanTu.push(kyTu);
        }
        // N?u g?p toán t? SAI L?CH (>)
        else if (kyTu == '>') {
            nganXepToanTu.push(kyTu);
        }
        // N?u g?p d?u ngo?c m?, dánh d?u b?t d?u m?t nhóm
        else if (kyTu == '(') {
            nganXepToanTu.push(kyTu);
        }
        // N?u g?p d?u ngo?c dóng, th?c hi?n tính toán trong nhóm ngo?c
        else if (kyTu == ')') {
            while (nganXepToanTu.top() != '(') {
                char toanTu = nganXepToanTu.top();
                nganXepToanTu.pop();
                bool toanHangPhai = nganXepToanHang.top();
                nganXepToanHang.pop();
                bool toanHangTrai = nganXepToanHang.top();
                nganXepToanHang.pop();

                // Th?c hi?n phép toán logic tuong ?ng
                if (toanTu == '&') {
                    nganXepToanHang.push(Va(toanHangTrai, toanHangPhai));
                } else if (toanTu == '|') {
                    nganXepToanHang.push(Hoac(toanHangTrai, toanHangPhai));
                } else if (toanTu == '>') {
                    nganXepToanHang.push(SaiLech(toanHangTrai, toanHangPhai));
                }
            }
            nganXepToanTu.pop(); // Xóa d?u ngo?c m?
        }
    }

    // X? lý các phép toán còn l?i trong ngan x?p toán t?
    while (!nganXepToanTu.empty()) {
        char toanTu = nganXepToanTu.top();
        nganXepToanTu.pop();
        bool toanHangPhai = nganXepToanHang.top();
        nganXepToanHang.pop();
        bool toanHangTrai = nganXepToanHang.top();
        nganXepToanHang.pop();

        if (toanTu == '&') {
            nganXepToanHang.push(Va(toanHangTrai, toanHangPhai));
        } else if (toanTu == '|') {
            nganXepToanHang.push(Hoac(toanHangTrai, toanHangPhai));
        } else if (toanTu == '>') {
            nganXepToanHang.push(SaiLech(toanHangTrai, toanHangPhai));
        }
    }

    return nganXepToanHang.top(); // Tr? v? k?t qu? cu?i cùng
}

int main() {
    string bieuThuc;
    cout << "Nh?p bi?u th?c logic (ví d?: (A & B) > ~C): ";
    getline(cin, bieuThuc);

    // Ki?m tra tính h?p l? c?a bi?u th?c
    if (!KiemTraHopLe(bieuThuc)) {
        cout << "Bi?u th?c không h?p l?." << endl;
        return 1;
    }

    // Nh?p giá tr? c?a các bi?n logic
    unordered_map<char, bool> giaTriBien;
    cout << "Nh?p giá tr? cho các bi?n (ví d?: A: true, B: false):" << endl;

    for (size_t i = 0; i < bieuThuc.size(); i++) {
        if (isalpha(bieuThuc[i])) {
            char bien = bieuThuc[i];
            if (giaTriBien.find(bien) == giaTriBien.end()) {
                bool giaTri;
                cout << "Nh?p giá tr? cho " << bien << " (true ho?c false): ";
                cin >> boolalpha >> giaTri;
                giaTriBien[bien] = giaTri;
            }
        }
    }

    // Tính toán giá tr? c?a bi?u th?c
    bool ketQua = TinhGiaTriBieuThuc(bieuThuc, giaTriBien);
    cout << "K?t qu? c?a bi?u th?c là: " << (ketQua ? "True" : "False") << endl;

    return 0;
}

