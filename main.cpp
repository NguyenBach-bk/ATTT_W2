#include <iostream>

using namespace std;

// Hàm tạo ma trận 5x5 từ khóa
void tao_ma_tran(char ma_tran[5][5], const char* khoa) {
    bool da_su_dung[26] = { false }; // Mảng kiểm tra chữ cái đã sử dụng
    int vi_tri = 0;

    // Điền ma trận bằng khóa
    for (int i = 0; khoa[i] != '\0'; i++) {
        char ky_tu = khoa[i];
        if (ky_tu == 'J') ky_tu = 'I'; // Xem 'J' như 'I'
        int vi_tri_ky_tu = ky_tu - 'A';
        if (!da_su_dung[vi_tri_ky_tu]) {
            da_su_dung[vi_tri_ky_tu] = true;
            ma_tran[vi_tri / 5][vi_tri % 5] = ky_tu;
            vi_tri++;
        }
    }

    // Điền các chữ cái còn lại
    for (char ky_tu = 'A'; ky_tu <= 'Z'; ky_tu++) {
        if (ky_tu == 'J') continue; // Bỏ qua 'J'
        int vi_tri_ky_tu = ky_tu - 'A';
        if (!da_su_dung[vi_tri_ky_tu]) {
            ma_tran[vi_tri / 5][vi_tri % 5] = ky_tu;
            vi_tri++;
        }
    }
}

// Hàm tìm vị trí của một ký tự trong ma trận
void tim_vi_tri(char ky_tu, char ma_tran[5][5], int& hang, int& cot) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (ma_tran[i][j] == ky_tu) {
                hang = i;
                cot = j;
                return;
            }
        }
    }
}

// Hàm mã hóa văn bản bằng cách sử dụng mã Playfair 
void ma_hoa(const char* van_ban, const char* khoa) {
    char ma_tran[5][5];
    tao_ma_tran(ma_tran, khoa);

    char van_ban_chuan_bi[100]; // Độ dài tối đa văn bản
    int v_index = 0;

    // Chuẩn bị văn bản
    for (int i = 0; van_ban[i] != '\0'; i++) {
        char ky_tu = van_ban[i];
        if (ky_tu == 'J') ky_tu = 'I'; // Xem 'J' như 'I'

        van_ban_chuan_bi[v_index++] = ky_tu;

        // Thêm 'X' giữa các ký tự trùng nhau
        if (i + 1 < van_ban[i + 1] && ky_tu == van_ban[i + 1]) {
            van_ban_chuan_bi[v_index++] = 'X'; 
        }
    }
    if (v_index % 2 != 0) {
        van_ban_chuan_bi[v_index++] = 'X'; //  Chèn 'X'
    }
    van_ban_chuan_bi[v_index] = '\0';

    // Mã hóa văn bản
    char van_ban_ma[100];
    int m_index = 0;

    for (int i = 0; i < v_index; i += 2) {
        int hang1, cot1, hang2, cot2;
        tim_vi_tri(van_ban_chuan_bi[i], ma_tran, hang1, cot1);
        tim_vi_tri(van_ban_chuan_bi[i + 1], ma_tran, hang2, cot2);

        // Quy tắc mã hóa
        if (hang1 == hang2) {
            van_ban_ma[m_index++] = ma_tran[hang1][(cot1 + 1) % 5];
            van_ban_ma[m_index++] = ma_tran[hang2][(cot2 + 1) % 5];
        } else if (cot1 == cot2) {
            van_ban_ma[m_index++] = ma_tran[(hang1 + 1) % 5][cot1];
            van_ban_ma[m_index++] = ma_tran[(hang2 + 1) % 5][cot2];
        } else {
            van_ban_ma[m_index++] = ma_tran[hang1][cot2];
            van_ban_ma[m_index++] = ma_tran[hang2][cot1];
        }
    }
    van_ban_ma[m_index] = '\0';

    cout << "Van ban ma: " << van_ban_ma << endl;
}

int main() {
    char khoa[100], van_ban[100];

    cout << "Nhap khoa: ";
    cin >> khoa;
    cout << "Nhap van ban: ";
    cin >> van_ban;

    ma_hoa(van_ban, khoa);

    return 0;
}