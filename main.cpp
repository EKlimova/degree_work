#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>

using namespace std;

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

  if (argc == 1) {
    cout << "No file specified"; // �������� �� ������� �����
    return 1;
  }

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
  const char dicm[4] = {'D', 'I', 'C', 'M'}; //������� ������ � ����������
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

	  //cout << "Tag is (" << hex << setfill('0') << setw(4) << tag_group.num << ","
		 // << hex << setfill('0') << setw(4) << tag_element.num << ")"
		 // << "\n"; //����� �� ����� ����

	  
	  
	  


	 // ��������� Bit Alocated
	  if ((tag_group.num == 0x0028) && (tag_element.num == 0x0100)) {  // �� ����� ��� tag_number ������������ �� �������!
		  char *value = new char[2];
		  fin.read(value, 2); // ��������� �������� Bit Alocated, ��������� �� 2 ����
		  cout << "(" << hex << setfill('0') << setw(4) << tag_group.num << ","
			  << hex << setfill('0') << setw(4) << tag_element.num << ")"
			  << " "; //����� �� ����� ����
		  cout << "Bit Alocated is: " << dec << value << "\n"; // ������� �� ����� �������� Bit Alocated
		  delete[] value;
	  }

	  // ��������� Bit Stored
	  if ((tag_group.num = '0028') && (tag_element.num = '0101')) {  // �� ����� ��� tag_number ������������ �� �������!
		  char *value = new char[2];
		  fin.read(value, 2); // ��������� �������� Bit Alocated, ��������� �� 2 ����
		  reinterpret_cast<unsigned short *>(&value); // ��������� value �� ���� char  � ��� unsigned short
		  cout << "(" << hex << setfill('0') << setw(4) << tag_group.num << ","
			  << hex << setfill('0') << setw(4) << tag_element.num << ")"
			  << " "; //����� �� ����� ����
		  cout << "Bit Stored is: " << dec << value << "\n"; // ������� �� ����� Bit Alocated
		  delete[] value;
	  }

	  // ��������� Hight Bit
	  if ((tag_group.num = '0028') && (tag_element.num = '0102')) {  // �� ����� ��� tag_number ������������ �� �������!
		  char *value = new char[2];
		  fin.read(value, 2); // ��������� �������� Bit Alocated, ��������� �� 2 ����
		  reinterpret_cast<unsigned short *>(&value); // ��������� value �� ���� char  � ��� unsigned short
		  cout << "(" << hex << setfill('0') << setw(4) << tag_group.num << ","
			  << hex << setfill('0') << setw(4) << tag_element.num << ")"
			  << " "; //����� �� ����� ����
		  cout << "Hight Bit is: " << dec << value << "\n"; // ������� �� ����� Bit Alocated
		  delete[] value;
	  }





    //// �������� VR
    //char vr[3]; // ������� ������ ��� VR
    //fin.read(vr, 2); // ��������� 2 �����
    //vr[2] = '\0'; // ������ ��������� ������� �������
    //string vr_read(vr);
    //const vector<string> vrs{"OB", "OW", "OF", "SQ", "UT", "OR", "UN"};
    //value_field32 length32;
    //value_field16 length16;
    //int length;

    //for (auto s : vrs) {
    //  if (s == vr_read) { // ���� vr ������������ ��������� vrs
    //    fin.seekg(2, fin.cur); // ���������� 2 �����
    //    // ��������� Value Length
    //    fin.read(reinterpret_cast<char *>(&length32.num), 4); // ��������� 4 �����
    //    length = length32.num; // ����������� ��������� ����� ����� length
    //    break;  
    //  } else if (s == vrs.back()) { // ���� vr �� ����������� vrs
    //    fin.read(reinterpret_cast<char *>(&length16.num), 2); // ��������� 2 �����
    //    length = length16.num; // ����������� ��������� ����� ����� length
    //  }
    //}

    //char *s = new char[length + 1]; // ������� ������������ ������ ��������
    //s[length] = '\0'; // ������ ��������� ������� �������
    //fin.read(s, length); // ��������� ��������
    //string str(s);
    //cout << "Value is: " << dec << str << "\n"; // ������� �������� �� �����
    //delete[] s;                                 // ������� ������

  }
  fin.close(); // ����� �� ������
  _getch();
  return 0;
}
