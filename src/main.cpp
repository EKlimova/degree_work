#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <boost/filesystem.hpp>
#include <iostream>



using namespace std;
namespace fs = boost::filesystem;


union tag_number { // ��������� ���� ��������
  unsigned char ch[2];
  unsigned short num;
};

union value_field16 { // ��������� ����� �� 2 �����
  unsigned char ch[2];
  unsigned short num;
};
union value_field32 { // ��������� ����� �� 4 �����
  unsigned char ch[4];
  unsigned int num;
};

int main(int argc, char *argv[]) {


	for (fs::recursive_directory_iterator it("E:/CT/ct-27.08.2015/ct-27.08.2015/DICOM/PA000000/ST000000/SE000000"), end; it != end; ++it) { // ��������� ������ �� ���� ������ � �����
		if (it->path().extension() == ".dcm") { // �������� ������ ����� � ����������� dcm
			if (it->path().filename() == "IM000000.dcm") { // �������� ������ ����

				ifstream fin(
					argv[1],
					ios_base::in |
					ios_base::binary); //������� ������ � ����������� ��� � ������

				if (!fin) {
					cout << "File error"; //������� ��������� �� ������, ���� ���� �� ��������
					return 1;
				}
				// �������� ��������� DICM
				fin.seekg(128);                            //��������� �� 129 ����
				char ch;
				const char dicm[4] = { 'D', 'I', 'C', 'M' }; //������� ������ � ����������
				for (int i = 0; i < 4; i++) {
					fin >> ch;								 // �������� ��������� 4 ��������
					if (ch != dicm[i]) {					// � ���������� �� � ����������
						cout << "Signature error";			// ������� ��������� �� ������, ���� ���������
						return 2;								// �� ������� � ������� �� �����
					}
				}
				while (!fin.eof()) {
					char byte;
					fin.read(&byte, 1); // ��������� 1 ����
					if (fin.eof()) // ���� ��������� ����� �����
						break; // ����� �� �����
					else
						fin.seekg(-1, fin.cur); // ����� ������������ �� 1 ���� �����

					// ��������� ��� ������
					// ��������� Group Number
					tag_number tag_group;
					fin.read(reinterpret_cast<char *>(&tag_group.num), sizeof(tag_number)); // ��������� 2 �����

					// ��������� Element Number
					tag_number tag_element;
					fin.read(reinterpret_cast<char *>(&tag_element.num), sizeof(tag_number)); // ��������� 2 �����

					if ((tag_group.num == 0x0018) && (tag_element.num == 0x0050)) { // ������� Slice Thickness

						cout << "(" << hex << setfill('0') << setw(4) << tag_group.num << ","
							<< hex << setfill('0') << setw(4) << tag_element.num << ")"; //����� �� ����� ����

						fin.seekg(2, fin.cur); // ���������� 2 �����
						value_field16 length16;
						int length;
						fin.read(reinterpret_cast<char *>(&length16.num), 2); // ��������� 2 ����� - �����
						length = length16.num; // ����������� ��������� ����� ����� length

						char *s = new char[length + 1]; // ������� ������������ ������ ��������
						s[length] = '\0'; // ������ ��������� ������� �������
						fin.read(s, length); // ��������� ��������
						string str(s);
						cout << " Slice Thickness: " << dec << str << "\n"; // ������� ���, �������� � �������� �������� ������ �� �����
						delete[] s;                                 // ������� ������

					}



					if ((tag_group.num == 0x0020) && (tag_element.num == 0x0030)) { // ������� Image Position

						cout << "(" << hex << setfill('0') << setw(4) << tag_group.num << ","
							<< hex << setfill('0') << setw(4) << tag_element.num << ")"; //����� �� ����� ����

						fin.seekg(2, fin.cur); // ���������� 2 �����
						value_field16 length16;
						int length;
						fin.read(reinterpret_cast<char *>(&length16.num), 2); // ��������� 2 ����� - �����
						length = length16.num; // ����������� ��������� ����� ����� length

						char *s = new char[length + 1]; // ������� ������������ ������ ��������
						s[length] = '\0'; // ������ ��������� ������� �������
						fin.read(s, length); // ��������� ��������
						string str(s);
						cout << " Image Position: " << dec << str << "\n"; // ������� ���, �������� � �������� �������� ������ �� �����
						delete[] s;                                 // ������� ������

					}



					if ((tag_group.num == 0x0020) && (tag_element.num == 0x0035)) { // ������� Image Orientation

						cout << "(" << hex << setfill('0') << setw(4) << tag_group.num << ","
							<< hex << setfill('0') << setw(4) << tag_element.num << ")"; //����� �� ����� ����


						fin.seekg(2, fin.cur); // ���������� 2 �����
						value_field16 length16;
						int length;
						fin.read(reinterpret_cast<char *>(&length16.num), 2); // ��������� 2 ����� - �����
						length = length16.num; // ����������� ��������� ����� ����� length

						char *s = new char[length + 1]; // ������� ������������ ������ ��������
						s[length] = '\0'; // ������ ��������� ������� �������
						fin.read(s, length); // ��������� ��������
						string str(s);
						cout << " Image Orientation: " << dec << str << "\n"; // ������� ���, �������� � �������� �������� ������ �� �����
						delete[] s;                                 // ������� ������

					}


					if ((tag_group.num == 0x0020) && (tag_element.num == 0x1041)) { // ������� Slice Location

						cout << "(" << hex << setfill('0') << setw(4) << tag_group.num << ","
							<< hex << setfill('0') << setw(4) << tag_element.num << ")"; //����� �� ����� ����

						fin.seekg(2, fin.cur); // ���������� 2 �����
						value_field16 length16;
						int length;
						fin.read(reinterpret_cast<char *>(&length16.num), 2); // ��������� 2 ����� - �����
						length = length16.num; // ����������� ��������� ����� ����� length

						char *s = new char[length + 1]; // ������� ������������ ������ ��������
						s[length] = '\0'; // ������ ��������� ������� �������
						fin.read(s, length); // ��������� ��������
						string str(s);
						cout << " Slice Location: " << dec << str << "\n"; // ������� ���, �������� � �������� �������� ������ �� �����
						delete[] s;                                 // ������� ������

					}


					if ((tag_group.num == 0x0028) && (tag_element.num == 0x0010)) { // ������� Rows

						cout << "(" << hex << setfill('0') << setw(4) << tag_group.num << ","
							<< hex << setfill('0') << setw(4) << tag_element.num << ")"; //����� �� ����� ����

						fin.seekg(2, fin.cur); // ���������� 2 �����
						value_field16 length16;
						int length;
						fin.read(reinterpret_cast<char *>(&length16.num), 2); // ��������� 2 ����� - �����
						length = length16.num; // ����������� ��������� ����� ����� length

						char *s = new char[length + 1]; // ������� ������������ ������ ��������
						s[length] = '\0'; // ������ ��������� ������� �������
						fin.read(s, length); // ��������� ��������
						string str(s);
						cout << " Rows: " << dec << str << "\n"; // ������� ���, �������� � �������� �������� ������ �� �����
						delete[] s;                                 // ������� ������

					}


					if ((tag_group.num == 0x0028) && (tag_element.num == 0x0011)) { // ������� Columns

						cout << "(" << hex << setfill('0') << setw(4) << tag_group.num << ","
							<< hex << setfill('0') << setw(4) << tag_element.num << ")"; //����� �� ����� ����

						fin.seekg(2, fin.cur); // ���������� 2 �����
						value_field16 length16;
						int length;
						fin.read(reinterpret_cast<char *>(&length16.num), 2); // ��������� 2 ����� - �����
						length = length16.num; // ����������� ��������� ����� ����� length

						char *s = new char[length + 1]; // ������� ������������ ������ ��������
						s[length] = '\0'; // ������ ��������� ������� �������
						fin.read(s, length); // ��������� ��������
						string str(s);
						cout << " Columns: " << dec << str << "\n"; // ������� ���, �������� � �������� �������� ������ �� �����
						delete[] s;                                 // ������� ������

					}


					if ((tag_group.num == 0x0028) && (tag_element.num == 0x0030)) { // ������� Pixel Spacing

						cout << "(" << hex << setfill('0') << setw(4) << tag_group.num << ","
							<< hex << setfill('0') << setw(4) << tag_element.num << ")"; //����� �� ����� ����

						fin.seekg(2, fin.cur); // ���������� 2 �����
						value_field16 length16;
						int length;
						fin.read(reinterpret_cast<char *>(&length16.num), 2); // ��������� 2 ����� - �����
						length = length16.num; // ����������� ��������� ����� ����� length

						char *s = new char[length + 1]; // ������� ������������ ������ ��������
						s[length] = '\0'; // ������ ��������� ������� �������
						fin.read(s, length); // ��������� ��������
						string str(s);
						cout << " Pixel Spacing: " << dec << str << "\n"; // ������� ���, �������� � �������� �������� ������ �� �����
						delete[] s;                                 // ������� ������

					}


					if ((tag_group.num == 0x0028) && (tag_element.num == 0x0100)) { // ������� Bits Allocated

						cout << "(" << hex << setfill('0') << setw(4) << tag_group.num << ","
							<< hex << setfill('0') << setw(4) << tag_element.num << ")"; //����� �� ����� ����

						fin.seekg(2, fin.cur); // ���������� 2 �����
						value_field16 length16;
						int length;
						fin.read(reinterpret_cast<char *>(&length16.num), 2); // ��������� 2 ����� - �����
						length = length16.num; // ����������� ��������� ����� ����� length

						char *s = new char[length + 1]; // ������� ������������ ������ ��������
						s[length] = '\0'; // ������ ��������� ������� �������
						fin.read(s, length); // ��������� ��������
						string str(s);
						cout << " Bits Allocated: " << dec << str << "\n"; // ������� ���, �������� � �������� �������� ������ �� �����
						delete[] s;                                 // ������� ������

					}


					if ((tag_group.num == 0x0028) && (tag_element.num == 0x0101)) { // ������� Bits Stored

						cout << "(" << hex << setfill('0') << setw(4) << tag_group.num << ","
							<< hex << setfill('0') << setw(4) << tag_element.num << ")"; //����� �� ����� ����

						fin.seekg(2, fin.cur); // ���������� 2 �����
						value_field16 length16;
						int length;
						fin.read(reinterpret_cast<char *>(&length16.num), 2); // ��������� 2 ����� - �����
						length = length16.num; // ����������� ��������� ����� ����� length

						char *s = new char[length + 1]; // ������� ������������ ������ ��������
						s[length] = '\0'; // ������ ��������� ������� �������
						fin.read(s, length); // ��������� ��������
						string str(s);
						cout << " Bits Stored: " << dec << str << "\n"; // ������� ���, �������� � �������� �������� ������ �� �����
						delete[] s;                                 // ������� ������

					}


					if ((tag_group.num == 0x0028) && (tag_element.num == 0x0102)) { // ������� Hight Bit

						cout << "(" << hex << setfill('0') << setw(4) << tag_group.num << ","
							<< hex << setfill('0') << setw(4) << tag_element.num << ")"; //����� �� ����� ����

						fin.seekg(2, fin.cur); // ���������� 2 �����
						value_field16 length16;
						int length;
						fin.read(reinterpret_cast<char *>(&length16.num), 2); // ��������� 2 ����� - �����
						length = length16.num; // ����������� ��������� ����� ����� length

						char *s = new char[length + 1]; // ������� ������������ ������ ��������
						s[length] = '\0'; // ������ ��������� ������� �������
						fin.read(s, length); // ��������� ��������
						string str(s);
						cout << " Hight Bit: " << dec << str << "\n"; // ������� ���, �������� � �������� �������� ������ �� �����
						delete[] s;                                 // ������� ������

					}

					//��������� Pixel Data
					if ((tag_group.num == 0x7FE0) && (tag_element.num == 0x0010)) {
						fin.seekg(-524288, fin.cur);										//���������� vr � ����������������� ����
						ofstream fout("pixel_data.raw", ios_base::binary);								//������� ������ � ���� ��� ������
						if (!fout) {
							cout << "File error";										//������� ��������� �� ������, ���� ���� �� ��������
							return 1;
						}
						short pixel_data[511][511]; // ������ ��������� ������ �������� 512 �� 512
						short pixel; // ������ ���� �������, ������� ������� � ���� 2 �����
						for (int i = 0; i < 512; i++) {
							for (int j = 0; j < 512; j++) {
								fin.read(reinterpret_cast<char *>(&pixel), 2); //��������� 2 ����� �� ���������� � pixel
								fout.write(reinterpret_cast<char *>(&pixel), 2); // ���������� 2 ����� �� pixel � ��������� ��������
							}
						}
						fout.close();//��������� ����
					}
				}
				fin.close(); // ����� �� ������
				_getch();
				return 0;
			}
			else {
				ifstream fin(
					argv[1],
					ios_base::in |
					ios_base::binary); //������� ������ � ����������� ��� � ������

				if (!fin) {
					cout << "File error"; //������� ��������� �� ������, ���� ���� �� ��������
					return 1;
				}
				// �������� ��������� DICM
				fin.seekg(128);                            //��������� �� 129 ����
				char ch;
				const char dicm[4] = { 'D', 'I', 'C', 'M' }; //������� ������ � ����������
				for (int i = 0; i < 4; i++) {
					fin >> ch;								 // �������� ��������� 4 ��������
					if (ch != dicm[i]) {					// � ���������� �� � ����������
						cout << "Signature error";			// ������� ��������� �� ������, ���� ���������
						return 2;								// �� ������� � ������� �� �����
					}
				}
				while (!fin.eof()) {
					char byte;
					fin.read(&byte, 1); // ��������� 1 ����
					if (fin.eof()) // ���� ��������� ����� �����
						break; // ����� �� �����
					else
						fin.seekg(-1, fin.cur); // ����� ������������ �� 1 ���� �����

												// ��������� ��� ������
												// ��������� Group Number
					tag_number tag_group;
					fin.read(reinterpret_cast<char *>(&tag_group.num), sizeof(tag_number)); // ��������� 2 �����

																							// ��������� Element Number
					tag_number tag_element;
					fin.read(reinterpret_cast<char *>(&tag_element.num), sizeof(tag_number)); // ��������� 2 �����
				//��������� Pixel Data
				if ((tag_group.num == 0x7FE0) && (tag_element.num == 0x0010)) {
					fin.seekg(-524288, fin.cur);										//���������� vr � ����������������� ����
					ofstream fout("pixel_data.raw", ios_base::binary);								//������� ������ � ���� ��� ������
					if (!fout) {
						cout << "File error";										//������� ��������� �� ������, ���� ���� �� ��������
						return 1;
					}
					short pixel_data[511][511]; // ������ ��������� ������ �������� 512 �� 512
					short pixel; // ������ ���� �������, ������� ������� � ���� 2 �����
					for (int i = 0; i < 512; i++) {
						for (int j = 0; j < 512; j++) {
							fin.read(reinterpret_cast<char *>(&pixel), 2); //��������� 2 ����� �� ���������� � pixel
							fout.write(reinterpret_cast<char *>(&pixel), 2); // ���������� 2 ����� �� pixel � ��������� ��������
						}
					}
					fout.close();//��������� ����
				}
			}
			fin.close(); // ����� �� ������
			_getch();
			return 0;


			}
		}
	}
}
