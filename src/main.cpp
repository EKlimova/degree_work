// STL includes
#include <iostream>
#include <string>

// DCMTK includes
#include "dcmtk/config/osconfig.h"
#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctagkey.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmdata/dctk.h"

// Boost includes
#include <boost/filesystem.hpp>

using namespace std;
namespace fs = boost::filesystem;

int main(int argc, char *argv[]) { // передаем функции аргументы
	bool first_file = true; // первому файлу присваиваем true, остальным - false

	OFString SliceThickness;
	OFString ImagePosition;
	OFString ImageOrientationPatient;
	OFString SliceLocation;
	Uint16 Rows;
	Uint16 Columns;
	OFString PixelSpacing;
	OFString BitsAllocated;
	Uint16 BitsStored;
	OFString HighBit;
	DcmElement* PixelData;

	
	for (fs::recursive_directory_iterator it(argv[1]), end; it != end;
	it++) { // пробегаем циклом по всем файлам дирректории
			// если первый файл, то
 //надо получить имя следующего файла

		DcmFileFormat fileformat;
		string name_of_file;
		name_of_file =
			it->path().string(); //я хочу присвоить name_of_file имя переменной

		OFCondition status = fileformat.loadFile(
			name_of_file.c_str()); // проверяем, загрузился ли файл
		if (status.good()) {
			if (first_file) {
				if (fileformat.getDataset()
					->findAndGetOFString(DCM_SliceThickness, SliceThickness)
					.good()) {
					cout << "Slice Thickness: " << SliceThickness << endl;
				}
				if (fileformat.getDataset()
					->findAndGetOFString(DCM_ImagePositionPatient, ImagePosition)
					.good()) {
					cout << "Image Position: " << ImagePosition << endl;
				}
				if (fileformat.getDataset()
					->findAndGetOFString(DCM_ImageOrientationPatient,
						ImageOrientationPatient)
					.good()) {
					cout << "Image Orientation (Patient): " << ImageOrientationPatient
						<< endl;
				}
				if (fileformat.getDataset()
					->findAndGetOFString(DCM_SliceLocation, SliceLocation)
					.good()) {
					cout << "Slice Location: " << SliceLocation << endl;
				}
				if (fileformat.getDataset()
					->findAndGetUint16(DCM_Rows, Rows)
					.good()) {
					cout << "Rows: " << Rows << endl;
				}
				if (fileformat.getDataset()
					->findAndGetUint16(DCM_Columns, Columns)
					.good()) {
					cout << "Columns: " << Columns << endl;
				}
				if (fileformat.getDataset()
					->findAndGetOFString(DCM_PixelSpacing, PixelSpacing)
					.good()) {
					cout << "Pixel Spacing: " << PixelSpacing << endl;
				}
				if (fileformat.getDataset()
					->findAndGetOFString(DCM_BitsAllocated, BitsAllocated)
					.good()) {
					cout << "Bits Allocated: " << BitsAllocated << endl;
				}
				if (fileformat.getDataset()
					->findAndGetUint16(DCM_BitsStored, BitsStored)
					.good()) {
					cout << "Bits Stored: " << BitsStored << endl;
				}
				if (fileformat.getDataset()
					->findAndGetOFString(DCM_HighBit, HighBit)
					.good()) {
					cout << "High Bit: " << HighBit << endl;
				}
				first_file = false;
			}

			cout << *it << endl; // чтоб видеть, на каком файле сейчас итератор

			if (fileformat.getDataset()
				->findAndGetElement(DCM_PixelData, PixelData)
				.good()) {
				ofstream fout("pixel_data.raw", ios_base::binary);
				if (!fout) {
					cout << "File error";
					return 1;
				}

				fout.write(reinterpret_cast<char *>(&PixelData), Rows*Columns*BitsStored / 8);
				cout << Rows*Columns*BitsStored / 8 << endl;
			}
		}
	}
}
