#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// Lớp Phim để quản lý thông tin phim
class Phim {
protected:
    string tenPhim;
    string theLoai;
    int thoiLuong;
public:
    Phim(string t = "", string g = "", int d = 0) : tenPhim(t), theLoai(g), thoiLuong(d) {}
    virtual void hienThi() {
        cout << "Tên phim: " << tenPhim << ", Thể loại: " << theLoai << ", Thời lượng: " << thoiLuong << " phút" << endl;
    }
    string getTenPhim() { return tenPhim; }
    string getTheLoai() { return theLoai; }
    string toString() {
        stringstream ss;
        ss << tenPhim << "|" << theLoai << "|" << thoiLuong;
        return ss.str();
    }
};

// Lớp PhimHanhDong kế thừa từ Phim
class PhimHanhDong : public Phim {
public:
    PhimHanhDong(string t, int d) : Phim(t, "Hành động", d) {}
    void hienThi() override {
        cout << "Phim Hành Động - ";
        Phim::hienThi();
    }
};

// Lớp PhimHaiHuoc kế thừa từ Phim
class PhimHaiHuoc : public Phim {
public:
    PhimHaiHuoc(string t, int d) : Phim(t, "Hài hước", d) {}
    void hienThi() override {
        cout << "Phim Hài Hước - ";
        Phim::hienThi();
    }
};

// Lớp Nguoi để quản lý thông tin người
class Nguoi {
protected:
    string hoTen;
    string soDienThoai;
public:
    Nguoi(string n = "", string p = "") : hoTen(n), soDienThoai(p) {}
    virtual void hienThi() {
        cout << "Họ tên: " << hoTen << ", SĐT: " << soDienThoai << endl;
    }
};

// Lớp KhachHang kế thừa từ Nguoi
class KhachHang : public Nguoi {
public:
    KhachHang(string n, string p) : Nguoi(n, p) {}
    void hienThi() override {
        cout << "Khách Hàng - ";
        Nguoi::hienThi();
    }
    string toString() {
        stringstream ss;
        ss << hoTen << "|" << soDienThoai;
        return ss.str();
    }
};

// Lớp SuatChieu để quản lý thông tin suất chiếu
class SuatChieu {
    Phim* phim;
    string gioChieu;
    int soGheTrong;
    vector<KhachHang> danhSachKhachDatVe;
public:
    SuatChieu(Phim* m, string t, int seats) : phim(m), gioChieu(t), soGheTrong(seats) {}
    Phim* getPhim() { return phim; }
    string getGioChieu() { return gioChieu; }
    int getSoGheTrong() { return soGheTrong; }
    void datVe(KhachHang khachHang) {
        if (soGheTrong > 0) {
            soGheTrong--;
            danhSachKhachDatVe.push_back(khachHang);
            cout << "Đặt vé thành công cho phim " << phim->getTenPhim() << " lúc " << gioChieu << endl;
        } else {
            cout << "Không còn ghế trống cho suất chiếu này!" << endl;
        }
    }
    void hienThi() {
        cout << "Suất chiếu: " << gioChieu << ", Ghế trống: " << soGheTrong << endl;
        phim->hienThi();
    }
};

// Lớp QuanLyRap để quản lý toàn bộ hệ thống
class QuanLyRap {
    vector<Phim*> danhSachPhim;
    vector<SuatChieu> danhSachSuatChieu;
public:
    void themPhim(Phim* phim) {
        danhSachPhim.push_back(phim);
    }
    
    void xoaPhim(string tenPhim) {
        for (auto it = danhSachPhim.begin(); it != danhSachPhim.end(); ++it) {
            if ((*it)->getTenPhim() == tenPhim) {
                delete *it;
                danhSachPhim.erase(it);
                cout << "Xóa phim thành công." << endl;
                return;
            }
        }
        cout << "Không tìm thấy phim." << endl;
    }
    
    void themSuatChieu(SuatChieu suatChieu) {
        danhSachSuatChieu.push_back(suatChieu);
    }
    
    void hienThiDanhSachPhim() {
        cout << "Danh sách phim:" << endl;
        for (auto phim : danhSachPhim) {
            phim->hienThi();
        }
    }
    
    void hienThiDanhSachSuatChieu() {
        cout << "Danh sách suất chiếu:" << endl;
        for (auto& suatChieu : danhSachSuatChieu) {
            suatChieu.hienThi();
        }
    }
    
    void datVeChoSuatChieu(int index, KhachHang khachHang) {
        if (index >= 0 && index < danhSachSuatChieu.size()) {
            danhSachSuatChieu[index].datVe(khachHang);
        } else {
            cout << "Mã suất chiếu không hợp lệ!" << endl;
        }
    }

    vector<Phim*>& getDanhSachPhim() {
        return danhSachPhim;
    }
    
    void luuDanhSachPhim(const string& filename) {
        ofstream file(filename);
        if (!file) {
            cout << "Không thể mở file để ghi!" << endl;
            return;
        }
        for (auto phim : danhSachPhim) {
            file << phim->toString() << endl;
        }
        file.close();
        cout << "Lưu danh sách phim thành công." << endl;
    }
    
    void docDanhSachPhim(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Không thể mở file để đọc!" << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string tenPhim, theLoai;
            int thoiLuong;
            getline(ss, tenPhim, '|');
            getline(ss, theLoai, '|');
            ss >> thoiLuong;
            if (theLoai == "Hành động") {
                themPhim(new PhimHanhDong(tenPhim, thoiLuong));
            } else if (theLoai == "Hài hước") {
                themPhim(new PhimHaiHuoc(tenPhim, thoiLuong));
            }
        }
        file.close();
        cout << "Đọc danh sách phim thành công." << endl;
    }
    
    ~QuanLyRap() {
        for (auto phim : danhSachPhim) {
            delete phim;
        }
    }
};

int main() {
    QuanLyRap rap;
    rap.docDanhSachPhim("danhSachPhim.txt");
    int luaChon;

    do {
        cout << "\nHệ Thống Quản Lý Rạp Chiếu Phim\n";
        cout << "1. Thêm Phim\n";
        cout << "2. Xóa Phim\n";
        cout << "3. Hiển Thị Danh Sách Phim\n";
        cout << "4. Thêm Suất Chiếu\n";
        cout << "5. Hiển Thị Danh Sách Suất Chiếu\n";
        cout << "6. Đặt Vé\n";
        cout << "7. Lưu Danh Sách Phim\n";
        cout << "8. Thoát\n";
        cout << "Nhập lựa chọn của bạn: ";
        cin >> luaChon;

        switch (luaChon) {
            case 1: {
                string tenPhim, theLoai;
                int thoiLuong;
                cout << "Nhập tên phim: ";
                cin.ignore();
                getline(cin, tenPhim);
                cout << "Nhập thể loại (Hành động/Hài hước): ";
                getline(cin, theLoai);
                cout << "Nhập thời lượng (phút): ";
                cin >> thoiLuong;
                if (theLoai == "Hành động") {
                    rap.themPhim(new PhimHanhDong(tenPhim, thoiLuong));
                } else if (theLoai == "Hài hước") {
                    rap.themPhim(new PhimHaiHuoc(tenPhim, thoiLuong));
                } else {
                    cout << "Thể loại không hợp lệ." << endl;
                }
                break;
            }
            case 2: {
                string tenPhim;
                cout << "Nhập tên phim cần xóa: ";
                cin.ignore();
                getline(cin, tenPhim);
                rap.xoaPhim(tenPhim);
                break;
            }
            case 3:
                rap.hienThiDanhSachPhim();
                break;
            case 4: {
                int chiSoPhim;
                string gioChieu;
                int soGhe;
                rap.hienThiDanhSachPhim();
                cout << "Chọn chỉ số phim cho suất chiếu: ";
                cin >> chiSoPhim;
                if (chiSoPhim < 0 || chiSoPhim >= rap.getDanhSachPhim().size()) {
                    cout << "Chỉ số phim không hợp lệ!" << endl;
                    break;
                }
                cout << "Nhập giờ chiếu (HH:MM): ";
                cin >> gioChieu;
                cout << "Nhập số ghế trống: ";
                cin >> soGhe;
                rap.themSuatChieu(SuatChieu(rap.getDanhSachPhim()[chiSoPhim], gioChieu, soGhe));
                break;
            }
            case 5:
                rap.hienThiDanhSachSuatChieu();
                break;
            case 6: {
                int chiSoSuatChieu;
                string tenKhachHang, soDienThoai;
                rap.hienThiDanhSachSuatChieu();
                cout << "Chọn chỉ số suất chiếu để đặt vé: ";
                cin >> chiSoSuatChieu;
                cout << "Nhập tên khách hàng: ";
                cin.ignore();
                getline(cin, tenKhachHang);
                cout << "Nhập số điện thoại khách hàng: ";
                getline(cin, soDienThoai);
                rap.datVeChoSuatChieu(chiSoSuatChieu, KhachHang(tenKhachHang, soDienThoai));
                break;
            }
            case 7:
                rap.luuDanhSachPhim("danhSachPhim.txt");
                break;
            case 8:
                cout << "Thoát chương trình.\n";
                break;
            default:
                cout << "Lựa chọn không hợp lệ, vui lòng thử lại.\n";
        }
    } while (luaChon != 8);

    return 0;
}
