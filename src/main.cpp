// STL includes
#include <iostream>
#include <string>


//DCMTK includes
#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmdata/dctagkey.h"
#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"

//Boost includes
#include <boost/filesystem.hpp>


using namespace std;
namespace fs = boost::filesystem;

int main(int argc, char *argv[]) { // передаем функции аргументы
	bool first_file = true; // первому файлу присваиваем true, остальным - false

	for (fs::recursive_directory_iterator it(argv[1]), end; it != end; it++) { // пробегаем циклом по всем файлам дирректории
		if (first_file) { // если первый файл, то
			//надо получить имя следующего файла
			
			DcmFileFormat fileformat;
			string name_of_file;
			it->path().filename() = name_of_file; //я хочу присвоить name_of_file имя переменной

			OFCondition status = fileformat.loadFile(name_of_file.c_str()); // проверяем, загрузился ли файл
			if (status.good()) {
				OFString SliceThickness;
				if (fileformat.getDataset()->findAndGetOFString(DCM_SliceThickness, SliceThickness).good())
				{
					cout << "Slice Thickness: " << SliceThickness << endl;
				}
				OFString ImagePosition;
				if (fileformat.getDataset()->findAndGetOFString(DCM_ImagePositionPatient, ImagePosition).good())
				{
					cout << "Image Position: " << ImagePosition << endl;
				}
				OFString ImageOrientationPatient;
				if (fileformat.getDataset()->findAndGetOFString(DCM_ImageOrientationPatient, ImageOrientationPatient).good())
				{
					cout << "Image Orientation (Patient): " << ImageOrientationPatient << endl;
				}
				OFString SliceLocation;
				if (fileformat.getDataset()->findAndGetOFString(DCM_SliceLocation, SliceLocation).good())
				{
					cout << "Slice Location: " << SliceLocation << endl;
				}
				OFString Rows;
				if (fileformat.getDataset()->findAndGetOFString(DCM_Rows, Rows).good())
				{
					cout << "Rows: " << Rows << endl;
				}
				OFString Columns;
				if (fileformat.getDataset()->findAndGetOFString(DCM_Columns, Columns).good())
				{
					cout << "Columns: " << Columns << endl;
				}
				OFString PixelSpacing;
				if (fileformat.getDataset()->findAndGetOFString(DCM_PixelSpacing, PixelSpacing).good())
				{
					cout << "Pixel Spacing: " << PixelSpacing << endl;
				}
				OFString BitsAllocated;
				if (fileformat.getDataset()->findAndGetOFString(DCM_BitsAllocated, BitsAllocated).good())
				{
					cout << "Bits Allocated: " << BitsAllocated << endl;
				}
				OFString BitsStored;
				if (fileformat.getDataset()->findAndGetOFString(DCM_BitsStored, BitsStored).good())
				{
					cout << "Bits Stored: " << BitsStored << endl;
				}
				OFString HighBit;
				if (fileformat.getDataset()->findAndGetOFString(DCM_HighBit, HighBit).good())
				{
					cout << "High Bit: " << HighBit << endl;
				}
				OFString PixelData;
				if (fileformat.getDataset()->findAndGetOFString(DCM_PixelData, PixelData).good())
				{
					cout << "Pixel Data was written" << endl;
				}
				first_file = false;
			}
		}
		else {
			cout << *it << endl; // чтоб видеть, на каком файле сейчас итератор
			DcmFileFormat fileformat;
			OFCondition status = fileformat.loadFile(argv[3]);
			if (status.good()) {
				OFString PixelData;
				if (fileformat.getDataset()->findAndGetOFString(DCM_PixelData, PixelData).good())
				{
					ofstream fout("pixel_data.raw", ios_base::binary);
					if (!fout) {
						cout << "File error";
						return 1;
					}

					cout << "Pixel Data was written" << endl;
				}
			}
			
		}

	}
}
