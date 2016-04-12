#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>

using namespace std;

union tag_number { // структура тега элемента
  unsigned char ch[2];
  unsigned short num;
};

union value_field16 { // структура длины на 2 байта
  unsigned char ch[2];
  unsigned short num;
};
union value_field32 { // структура длины на 4 байта
  unsigned char ch[4];
  unsigned int num;
};

int main(int argc, char *argv[]) {

  if (argc == 1) {
    cout << "No file specified"; // проверка на задание файла
    return 1;
  }

  ifstream fin(
      argv[1],
      ios_base::in |
          ios_base::binary); //создаем объект и ассоциируем его с файлом

  if (!fin) { 
    cout << "File error"; //выводим сообщение об ошибке, если файл не открылся
    return 1;
  }

  // проверка сигнатуры DICM
  fin.seekg(128);                            //переходим на 129 байт
  char ch;                                   
  const char dicm[4] = {'D', 'I', 'C', 'M'}; //создаем массив с сигнатурой
  for (int i = 0; i < 4; i++) {
    fin >> ch;								 // побайтно считываем 4 элемента
    if (ch != dicm[i]) {					// и сравниваем их с сигнатурой
      cout << "Signature error";			// выводим сообщение об ошибке, если сигнатура
      return 2;								// не совпала с данными из файла
    }
  }

  while (!fin.eof()) {
	  char byte;
	  fin.read(&byte, 1); // считывает 1 байт
	  if (fin.eof()) // если достигнут конец файла
		  break; // выход из цикла
	  else
		  fin.seekg(-1, fin.cur); // иначе возвращаемся на 1 байт назад

		// считываем тег группы

		// считываем Group Number
	  tag_number tag_group;
	  fin.read(reinterpret_cast<char *>(&tag_group.num), sizeof(tag_number)); // считываем 2 байта

	  // считываем Element Number
	  tag_number tag_element;
	  fin.read(reinterpret_cast<char *>(&tag_element.num), sizeof(tag_number)); // считываем 2 байта

	  value_field32 length32;
	  //считываем Pixel Data
	  if ((tag_group.num == 0x7FE0) && (tag_element.num == 0x0010)) {
		  fin.seekg(4, fin.cur);										//пропускаем vr и зарезервированное поле
		  fin.read(reinterpret_cast<char *>(&length32.num), 4);			//считали значение длины
		  ofstream fout("pixel_data.raw");								//создаем объект и файл для записи
		  if (!fout) {
			  cout << "File error";										//выводим сообщение об ошибке, если файл не открылся
			  return 1;
		  }
		  char *pixel_data = new char[length32.num + 1];
		  pixel_data[length32.num] = '\0';
		  fin.read(pixel_data, length32.num);
		  fout.write(pixel_data, length32.num);
		  delete[] pixel_data;
		  
		  fout.close();												//закрываем файл
	  }


	  cout << "Tag is (" << hex << setfill('0') << setw(4) << tag_group.num << ","
		  << hex << setfill('0') << setw(4) << tag_element.num << ")"
		  << "\n"; //вывод на экран тега

    // проверка VR
    char vr[3]; // создаем массив для VR
    fin.read(vr, 2); // считываем 2 байта
    vr[2] = '\0'; // задаем последний элемент массива
    string vr_read(vr);
    const vector<string> vrs{"OB", "OW", "OF", "SQ", "UT", "OR", "UN"};
    value_field16 length16;
    int length;

    for (auto s : vrs) {
      if (s == vr_read) { // если vr принадлежить множеству vrs
        fin.seekg(2, fin.cur); // пропускаем 2 байта
        // считываем Value Length
        fin.read(reinterpret_cast<char *>(&length32.num), 4); // считываем 4 байта
        length = length32.num; // присваиваем считанные байты длине length
        break;  
      } else if (s == vrs.back()) { // если vr не принадлежит vrs
        fin.read(reinterpret_cast<char *>(&length16.num), 2); // считываем 2 байта
        length = length16.num; // присваиваем считанные байты длине length
      }
    }

    char *s = new char[length + 1]; // создаем динамический массив значений
    s[length] = '\0'; // задаем последний элемент массива
    fin.read(s, length); // считываем значение
    string str(s);
    cout << "Value is: " << dec << str << "\n"; // выводим значение на экран
    delete[] s;                                 // удаляем массив

  }
  fin.close(); // выход из потока
  _getch();
  return 0;
}
