#include <iostream>
#include <string>
#include <unordered_map>
#include <cctype>
#include <stack>

using namespace std;

// H�m th?c hi?n ph�p to�n PH? �?NH (~)
bool PhuDinh(bool giaTri) {
    return !giaTri;
}

// H�m th?c hi?n ph�p to�n V� (&)
bool Va(bool a, bool b) {
    return a && b;
}

// H�m th?c hi?n ph�p to�n HO?C (|)
bool Hoac(bool a, bool b) {
    return a || b;
}

// H�m th?c hi?n ph�p to�n SAI L?CH (>)
bool SaiLech(bool a, bool b) {
    return !a || b;
}

// H�m ki?m tra t�nh h?p l? c?a bi?u th?c logic
bool KiemTraHopLe(const string& bieuThuc) {
    int ngoacMo = 0;

    // Ki?m tra t?ng k� t? trong bi?u th?c
    for (size_t i = 0; i < bieuThuc.size(); i++) {
        char kyTu = bieuThuc[i];

        // Ki?m tra d?u ngo?c
        if (kyTu == '(') {
            ngoacMo++;
        } else if (kyTu == ')') {
            if (ngoacMo == 0) return false; // C� ngo?c d�ng m� kh�ng c� ngo?c m?
            ngoacMo--;
        }

        // Ki?m tra c�c to�n t? h?p l?
        if (kyTu == '&' || kyTu == '|' || kyTu == '>' || kyTu == '~') {
            if (i == 0 || i == bieuThuc.size() - 1) {
                return false; // Kh�ng c� to�n t? ? d?u ho?c cu?i bi?u th?c
            }
            if (bieuThuc[i - 1] == '(' || bieuThuc[i + 1] == ')') {
                return false; // Kh�ng c� to�n t? li?n sau d?u ngo?c
            }
        }
    }

    // �?m b?o r?ng c�c d?u ngo?c m? v� d�ng d?u kh?p
    return ngoacMo == 0;
}

// H�m t�nh to�n gi� tr? c?a bi?u th?c logic
bool TinhGiaTriBieuThuc(const string& bieuThuc, const unordered_map<char, bool>& giaTriBien) {
    stack<bool> nganXepToanHang; // Ngan x?p luu tr? c�c gi� tr? logic
    stack<char> nganXepToanTu; // Ngan x?p luu tr? c�c to�n t? logic

    for (size_t i = 0; i < bieuThuc.size(); i++) {
        char kyTu = bieuThuc[i];

        // N?u l� bi?n (A-Z), l?y gi� tr? t? b?ng gi� tr?
        if (isalpha(kyTu)) {
            nganXepToanHang.push(giaTriBien.at(kyTu));
        }
        // N?u g?p to�n t? PH? �?NH (~), th?c hi?n ph? d?nh
        else if (kyTu == '~') {
            bool toanHang = nganXepToanHang.top();
            nganXepToanHang.pop();
            nganXepToanHang.push(PhuDinh(toanHang));
        }
        // N?u g?p to�n t? V� (&)
        else if (kyTu == '&') {
            nganXepToanTu.push(kyTu);
        }
        // N?u g?p to�n t? HO?C (|)
        else if (kyTu == '|') {
            nganXepToanTu.push(kyTu);
        }
        // N?u g?p to�n t? SAI L?CH (>)
        else if (kyTu == '>') {
            nganXepToanTu.push(kyTu);
        }
        // N?u g?p d?u ngo?c m?, d�nh d?u b?t d?u m?t nh�m
        else if (kyTu == '(') {
            nganXepToanTu.push(kyTu);
        }
        // N?u g?p d?u ngo?c d�ng, th?c hi?n t�nh to�n trong nh�m ngo?c
        else if (kyTu == ')') {
            while (nganXepToanTu.top() != '(') {
                char toanTu = nganXepToanTu.top();
                nganXepToanTu.pop();
                bool toanHangPhai = nganXepToanHang.top();
                nganXepToanHang.pop();
                bool toanHangTrai = nganXepToanHang.top();
                nganXepToanHang.pop();

                // Th?c hi?n ph�p to�n logic tuong ?ng
                if (toanTu == '&') {
                    nganXepToanHang.push(Va(toanHangTrai, toanHangPhai));
                } else if (toanTu == '|') {
                    nganXepToanHang.push(Hoac(toanHangTrai, toanHangPhai));
                } else if (toanTu == '>') {
                    nganXepToanHang.push(SaiLech(toanHangTrai, toanHangPhai));
                }
            }
            nganXepToanTu.pop(); // X�a d?u ngo?c m?
        }
    }

    // X? l� c�c ph�p to�n c�n l?i trong ngan x?p to�n t?
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

    return nganXepToanHang.top(); // Tr? v? k?t qu? cu?i c�ng
}

int main() {
    string bieuThuc;
    cout << "Nh?p bi?u th?c logic (v� d?: (A & B) > ~C): ";
    getline(cin, bieuThuc);

    // Ki?m tra t�nh h?p l? c?a bi?u th?c
    if (!KiemTraHopLe(bieuThuc)) {
        cout << "Bi?u th?c kh�ng h?p l?." << endl;
        return 1;
    }

    // Nh?p gi� tr? c?a c�c bi?n logic
    unordered_map<char, bool> giaTriBien;
    cout << "Nh?p gi� tr? cho c�c bi?n (v� d?: A: true, B: false):" << endl;

    for (size_t i = 0; i < bieuThuc.size(); i++) {
        if (isalpha(bieuThuc[i])) {
            char bien = bieuThuc[i];
            if (giaTriBien.find(bien) == giaTriBien.end()) {
                bool giaTri;
                cout << "Nh?p gi� tr? cho " << bien << " (true ho?c false): ";
                cin >> boolalpha >> giaTri;
                giaTriBien[bien] = giaTri;
            }
        }
    }

    // T�nh to�n gi� tr? c?a bi?u th?c
    bool ketQua = TinhGiaTriBieuThuc(bieuThuc, giaTriBien);
    cout << "K?t qu? c?a bi?u th?c l�: " << (ketQua ? "True" : "False") << endl;

    return 0;
}

