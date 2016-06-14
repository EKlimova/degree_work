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
	bool second_file = true;

	Float64 x_imagePosition;
	Float64 y_imagePosition;
	Float64 z_imagePosition;
	Float64 xx_imageOrientationPatient;
	Float64 xy_imageOrientationPatient;
	Float64 xz_imageOrientationPatient;
	Float64 yx_imageOrientationPatient;
	Float64 yy_imageOrientationPatient;
	Float64 yz_imageOrientationPatient;
	Float64 sliceLocation;
	Float64 sliceLocation1;
	Float64 sliceLocation2;
	Uint16 rows;
	Uint16 columns;
	Float64 x_pixelSpacing;
	Float64 y_pixelSpacing;
	Uint16 bitsAllocated;
	Uint16 bitsStored;
	Uint16 highBit;
	const Uint16 * pixelData;

	
	for (fs::recursive_directory_iterator it(argv[1]), end; it != end;
	it++) { // пробегаем циклом по всем файлам дирректории
			// если первый файл, то

		DcmFileFormat fileformat;
		string name_of_file;
		name_of_file =
			it->path().string(); //я хочу присвоить name_of_file имя переменной

		OFCondition status = fileformat.loadFile(
			name_of_file.c_str()); // проверяем, загрузился ли файл
		if (status.good()) {
			if (first_file) {
				if (fileformat.getDataset()
					->findAndGetFloat64(DCM_ImagePositionPatient, x_imagePosition)
					.good()) {
					cout << "Image Position, X: " << x_imagePosition << endl;
				}
				if (fileformat.getDataset()
					->findAndGetFloat64(DCM_ImagePositionPatient, y_imagePosition, 1)
					.good()) {
					cout << "Image Position, Y: " << y_imagePosition << endl;
				}
				if (fileformat.getDataset()
					->findAndGetFloat64(DCM_ImagePositionPatient, z_imagePosition, 2)
					.good()) {
					cout << "Image Position, Z: " << z_imagePosition << endl;
				}
				if (fileformat.getDataset()
					->findAndGetFloat64(DCM_ImageOrientationPatient, xx_imageOrientationPatient)
					.good()) {
					cout << "Image Orientation (Patient), Xx: " << xx_imageOrientationPatient
						<< endl;
				}
				if (fileformat.getDataset()
					->findAndGetFloat64(DCM_ImageOrientationPatient, xy_imageOrientationPatient, 1)
					.good()) {
					cout << "Image Orientation (Patient), Xy: " << xy_imageOrientationPatient
						<< endl;
				}
				if (fileformat.getDataset()
					->findAndGetFloat64(DCM_ImageOrientationPatient, xz_imageOrientationPatient, 2)
					.good()) {
					cout << "Image Orientation (Patient), Xz: " << xz_imageOrientationPatient
						<< endl;
				}
				if (fileformat.getDataset()
					->findAndGetFloat64(DCM_ImageOrientationPatient, yx_imageOrientationPatient, 3)
					.good()) {
					cout << "Image Orientation (Patient), Yx: " << yx_imageOrientationPatient
						<< endl;
				}
				if (fileformat.getDataset()
					->findAndGetFloat64(DCM_ImageOrientationPatient, yy_imageOrientationPatient, 4)
					.good()) {
					cout << "Image Orientation (Patient), Yy: " << yy_imageOrientationPatient
						<< endl;
				}
				if (fileformat.getDataset()
					->findAndGetFloat64(DCM_ImageOrientationPatient, yz_imageOrientationPatient, 5)
					.good()) {
					cout << "Image Orientation (Patient), Yz: " << yz_imageOrientationPatient
						<< endl;
				}
				if (fileformat.getDataset()
					->findAndGetFloat64(DCM_SliceLocation, sliceLocation1)
					.good()) {
					cout << "Slice Location from the first image: " << sliceLocation1 << endl;
				}
				if (fileformat.getDataset()
					->findAndGetUint16(DCM_Rows, rows)
					.good()) {
					cout << "Rows: " << rows << endl;
				}
				if (fileformat.getDataset()
					->findAndGetUint16(DCM_Columns, columns)
					.good()) {
					cout << "Columns: " << columns << endl;
				}
				if (fileformat.getDataset()
					->findAndGetFloat64(DCM_PixelSpacing, x_pixelSpacing)
					.good()) {
					cout << "Pixel Spacing, X: " << x_pixelSpacing << endl;
				}
				if (fileformat.getDataset()
					->findAndGetFloat64(DCM_PixelSpacing, y_pixelSpacing, 1)
					.good()) {
					cout << "Pixel Spacing, Y: " << y_pixelSpacing << endl;
				}
				if (fileformat.getDataset()
					->findAndGetUint16(DCM_BitsAllocated, bitsAllocated)
					.good()) {
					cout << "Bits Allocated: " << bitsAllocated << endl;
				}
				if (fileformat.getDataset()
					->findAndGetUint16(DCM_BitsStored, bitsStored)
					.good()) {
					cout << "Bits Stored: " << bitsStored << endl;
				}
				if (fileformat.getDataset()
					->findAndGetUint16(DCM_HighBit, highBit)
					.good()) {
					cout << "High Bit: " << highBit << endl;
				}
			}
			

			cout << *it << endl; // чтоб видеть, на каком файле сейчас итератор

			if (fileformat.getDataset()
				->findAndGetUint16Array(DCM_PixelData, pixelData)
				.good()) {
				
				cout << rows*columns*bitsStored / 8 << endl;
			}
		}
		if (!first_file && second_file) {
			if (fileformat.getDataset()
				->findAndGetFloat64(DCM_SliceLocation, sliceLocation2)
				.good()) {
				cout << "Slice Location from the second image: " << sliceLocation2 << endl;
				sliceLocation = sliceLocation2 - sliceLocation1;
				cout << "Real Slice Location: " << sliceLocation << endl;
			}
			second_file = false;
		}

		first_file = false;
	}
}
