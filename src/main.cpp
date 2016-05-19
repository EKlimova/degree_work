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

	bool first_file = true;

	for (fs::recursive_directory_iterator it(argv[1]), end; it != end; ++it) { // пробегаем циклом по всем файлам в папке
		if (first_file) { //если мы считываем первый файл

			ifstream fin(
				argv[2],
				ios_base::in |
				ios_base::binary); //создаем объект и ассоциируем его с файлом

			if (!fin) {
				cout << "File error"; //выводим сообщение об ошибке, если файл не открылся
				return 1;
			}
			// проверка сигнатуры DICM
			fin.seekg(128);                            //переходим на 129 байт
			char ch;
			const char dicm[4] = { 'D', 'I', 'C', 'M' }; //создаем массив с сигнатурой
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

				if ((tag_group.num == 0x0018) && (tag_element.num == 0x0050)) { // находим Slice Thickness

					cout << "(" << hex << setfill('0') << setw(4) << tag_group.num << ","
						<< hex << setfill('0') << setw(4) << tag_element.num << ")"; //вывод на экран тега

					fin.seekg(2, fin.cur); // пропускаем 2 байта
					value_field16 length16;
					int length;
					fin.read(reinterpret_cast<char *>(&length16.num), 2); // считываем 2 байта - длина
					length = length16.num; // присваиваем считанные байты длине length

					char *s = new char[length + 1]; // создаем динамический массив значений
					s[length] = '\0'; // задаем последний элемент массива
					fin.read(s, length); // считываем значение
					string str(s);
					cout << " Slice Thickness: " << dec << str << "\n"; // выводим тег, название и значение элемента данных на экран
					delete[] s;                                 // удаляем массив

				}



				if ((tag_group.num == 0x0020) && (tag_element.num == 0x0030)) { // находим Image Position

					cout << "(" << hex << setfill('0') << setw(4) << tag_group.num << ","
						<< hex << setfill('0') << setw(4) << tag_element.num << ")"; //вывод на экран тега

					fin.seekg(2, fin.cur); // пропускаем 2 байта
					value_field16 length16;
					int length;
					fin.read(reinterpret_cast<char *>(&length16.num), 2); // считываем 2 байта - длина
					length = length16.num; // присваиваем считанные байты длине length

					char *s = new char[length + 1]; // создаем динамический массив значений
					s[length] = '\0'; // задаем последний элемент массива
					fin.read(s, length); // считываем значение
					string str(s);
					cout << " Image Position: " << dec << str << "\n"; // выводим тег, название и значение элемента данных на экран
					delete[] s;                                 // удаляем массив

				}



				if ((tag_group.num == 0x0020) && (tag_element.num == 0x0035)) { // находим Image Orientation

					cout << "(" << hex << setfill('0') << setw(4) << tag_group.num << ","
						<< hex << setfill('0') << setw(4) << tag_element.num << ")"; //вывод на экран тега


					fin.seekg(2, fin.cur); // пропускаем 2 байта
					value_field16 length16;
					int length;
					fin.read(reinterpret_cast<char *>(&length16.num), 2); // считываем 2 байта - длина
					length = length16.num; // присваиваем считанные байты длине length

					char *s = new char[length + 1]; // создаем динамический массив значений
					s[length] = '\0'; // задаем последний элемент массива
					fin.read(s, length); // считываем значение
					string str(s);
					cout << " Image Orientation: " << dec << str << "\n"; // выводим тег, название и значение элемента данных на экран
					delete[] s;                                 // удаляем массив

				}


				if ((tag_group.num == 0x0020) && (tag_element.num == 0x1041)) { // находим Slice Location

					cout << "(" << hex << setfill('0') << setw(4) << tag_group.num << ","
						<< hex << setfill('0') << setw(4) << tag_element.num << ")"; //вывод на экран тега

					fin.seekg(2, fin.cur); // пропускаем 2 байта
					value_field16 length16;
					int length;
					fin.read(reinterpret_cast<char *>(&length16.num), 2); // считываем 2 байта - длина
					length = length16.num; // присваиваем считанные байты длине length

					char *s = new char[length + 1]; // создаем динамический массив значений
					s[length] = '\0'; // задаем последний элемент массива
					fin.read(s, length); // считываем значение
					string str(s);
					cout << " Slice Location: " << dec << str << "\n"; // выводим тег, название и значение элемента данных на экран
					delete[] s;                                 // удаляем массив

				}


				if ((tag_group.num == 0x0028) && (tag_element.num == 0x0010)) { // находим Rows

					cout << "(" << hex << setfill('0') << setw(4) << tag_group.num << ","
						<< hex << setfill('0') << setw(4) << tag_element.num << ")"; //вывод на экран тега

					fin.seekg(2, fin.cur); // пропускаем 2 байта
					value_field16 length16;
					int length;
					fin.read(reinterpret_cast<char *>(&length16.num), 2); // считываем 2 байта - длина
					length = length16.num; // присваиваем считанные байты длине length

					char *s = new char[length + 1]; // создаем динамический массив значений
					s[length] = '\0'; // задаем последний элемент массива
					fin.read(s, length); // считываем значение
					string str(s);
					cout << " Rows: " << dec << str << "\n"; // выводим тег, название и значение элемента данных на экран
					delete[] s;                                 // удаляем массив

				}


				if ((tag_group.num == 0x0028) && (tag_element.num == 0x0011)) { // находим Columns

					cout << "(" << hex << setfill('0') << setw(4) << tag_group.num << ","
						<< hex << setfill('0') << setw(4) << tag_element.num << ")"; //вывод на экран тега

					fin.seekg(2, fin.cur); // пропускаем 2 байта
					value_field16 length16;
					int length;
					fin.read(reinterpret_cast<char *>(&length16.num), 2); // считываем 2 байта - длина
					length = length16.num; // присваиваем считанные байты длине length

					char *s = new char[length + 1]; // создаем динамический массив значений
					s[length] = '\0'; // задаем последний элемент массива
					fin.read(s, length); // считываем значение
					string str(s);
					cout << " Columns: " << dec << str << "\n"; // выводим тег, название и значение элемента данных на экран
					delete[] s;                                 // удаляем массив

				}


				if ((tag_group.num == 0x0028) && (tag_element.num == 0x0030)) { // находим Pixel Spacing

					cout << "(" << hex << setfill('0') << setw(4) << tag_group.num << ","
						<< hex << setfill('0') << setw(4) << tag_element.num << ")"; //вывод на экран тега

					fin.seekg(2, fin.cur); // пропускаем 2 байта
					value_field16 length16;
					int length;
					fin.read(reinterpret_cast<char *>(&length16.num), 2); // считываем 2 байта - длина
					length = length16.num; // присваиваем считанные байты длине length

					char *s = new char[length + 1]; // создаем динамический массив значений
					s[length] = '\0'; // задаем последний элемент массива
					fin.read(s, length); // считываем значение
					string str(s);
					cout << " Pixel Spacing: " << dec << str << "\n"; // выводим тег, название и значение элемента данных на экран
					delete[] s;                                 // удаляем массив

				}


				if ((tag_group.num == 0x0028) && (tag_element.num == 0x0100)) { // находим Bits Allocated

					cout << "(" << hex << setfill('0') << setw(4) << tag_group.num << ","
						<< hex << setfill('0') << setw(4) << tag_element.num << ")"; //вывод на экран тега

					fin.seekg(2, fin.cur); // пропускаем 2 байта
					value_field16 length16;
					int length;
					fin.read(reinterpret_cast<char *>(&length16.num), 2); // считываем 2 байта - длина
					length = length16.num; // присваиваем считанные байты длине length

					char *s = new char[length + 1]; // создаем динамический массив значений
					s[length] = '\0'; // задаем последний элемент массива
					fin.read(s, length); // считываем значение
					string str(s);
					cout << " Bits Allocated: " << dec << str << "\n"; // выводим тег, название и значение элемента данных на экран
					delete[] s;                                 // удаляем массив

				}


				if ((tag_group.num == 0x0028) && (tag_element.num == 0x0101)) { // находим Bits Stored

					cout << "(" << hex << setfill('0') << setw(4) << tag_group.num << ","
						<< hex << setfill('0') << setw(4) << tag_element.num << ")"; //вывод на экран тега

					fin.seekg(2, fin.cur); // пропускаем 2 байта
					value_field16 length16;
					int length;
					fin.read(reinterpret_cast<char *>(&length16.num), 2); // считываем 2 байта - длина
					length = length16.num; // присваиваем считанные байты длине length

					char *s = new char[length + 1]; // создаем динамический массив значений
					s[length] = '\0'; // задаем последний элемент массива
					fin.read(s, length); // считываем значение
					string str(s);
					cout << " Bits Stored: " << dec << str << "\n"; // выводим тег, название и значение элемента данных на экран
					delete[] s;                                 // удаляем массив

				}


				if ((tag_group.num == 0x0028) && (tag_element.num == 0x0102)) { // находим Hight Bit

					cout << "(" << hex << setfill('0') << setw(4) << tag_group.num << ","
						<< hex << setfill('0') << setw(4) << tag_element.num << ")"; //вывод на экран тега

					fin.seekg(2, fin.cur); // пропускаем 2 байта
					value_field16 length16;
					int length;
					fin.read(reinterpret_cast<char *>(&length16.num), 2); // считываем 2 байта - длина
					length = length16.num; // присваиваем считанные байты длине length

					char *s = new char[length + 1]; // создаем динамический массив значений
					s[length] = '\0'; // задаем последний элемент массива
					fin.read(s, length); // считываем значение
					string str(s);
					cout << " Hight Bit: " << dec << str << "\n"; // выводим тег, название и значение элемента данных на экран
					delete[] s;                                 // удаляем массив

				}

				//считываем Pixel Data
				if ((tag_group.num == 0x7FE0) && (tag_element.num == 0x0010)) {
					ofstream fout("pixel_data.raw", ios_base::binary);								//создаем объект и файл для записи
					if (!fout) {
						cout << "File error";										//выводим сообщение об ошибке, если файл не открылся
						return 1;
					}
					fin.seekg(4, fin.cur); // пропускаем 4 байта
					value_field32 length32;
					int length;
					fin.read(reinterpret_cast<char *>(&length32.num), 4); // считываем 4 байта - длина
					length = length32.num; // присваиваем считанные байты длине length

					char *s = new char[length]; // создаем динамический массив значений
					fin.read(s, length); // считываем значение
					fout.write(s, length); //записываем значение в созданный файл
					delete[] s; // удаляем массив

					fout.close();//закрываем файл
				}
			}
			fin.close(); // выход из потока
			first_file = false;
		}
		else {
			ifstream fin(
				argv[2],
				ios_base::in |
				ios_base::binary); //создаем объект и ассоциируем его с файлом

			if (!fin) {
				cout << "File error"; //выводим сообщение об ошибке, если файл не открылся
				return 1;
			}
			// проверка сигнатуры DICM
			fin.seekg(128);                            //переходим на 129 байт
			char ch;
			const char dicm[4] = { 'D', 'I', 'C', 'M' }; //создаем массив с сигнатурой
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
			//считываем Pixel Data
			if ((tag_group.num == 0x7FE0) && (tag_element.num == 0x0010)) {
				ofstream fout("pixel_data.raw", ios_base::binary);								//создаем объект и файл для записи
				if (!fout) {
					cout << "File error";										//выводим сообщение об ошибке, если файл не открылся
					return 1;
				}
				fin.seekg(4, fin.cur); // пропускаем 4 байта
				value_field32 length32;
				int length;
				fin.read(reinterpret_cast<char *>(&length32.num), 4); // считываем 4 байта - длина
				length = length32.num; // присваиваем считанные байты длине length

				char *s = new char[length]; // создаем динамический массив значений
				fin.read(s, length); // считываем значение
				fout.write(s, length); //записываем значение в созданный файл
				delete[] s; // удаляем массив

				fout.close();//закрываем файл
			}
		}
		fin.close(); // выход из потока
		
		}


		_getch();
		return 0;
	}
}