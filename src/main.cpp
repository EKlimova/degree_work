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

	Float64 sliceThickness;
	Float64 x_imagePosition;
	Float64 y_imagePosition;
	Float64 z_imagePosition;
	Float64 xr_imageOrientationPatient;
	Float64 yr_imageOrientationPatient;
	Float64 zr_imageOrientationPatient;
	Float64 xc_imageOrientationPatient;
	Float64 yc_imageOrientationPatient;
	Float64 zc_imageOrientationPatient;
	Float64 sliceLocation;
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
					->findAndGetFloat64(DCM_SliceThickness, sliceThickness)
					.good()) {
					cout << "Slice Thickness: " << sliceThickness << endl;
				}
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
					->findAndGetFloat64(DCM_ImageOrientationPatient, xr_imageOrientationPatient)
					.good()) {
					cout << "Image Orientation (Patient), XR: " << xr_imageOrientationPatient
						<< endl;
				}
				if (fileformat.getDataset()
					->findAndGetFloat64(DCM_ImageOrientationPatient, yr_imageOrientationPatient, 1)
					.good()) {
					cout << "Image Orientation (Patient), YR: " << yr_imageOrientationPatient
						<< endl;
				}
				if (fileformat.getDataset()
					->findAndGetFloat64(DCM_ImageOrientationPatient, zr_imageOrientationPatient, 2)
					.good()) {
					cout << "Image Orientation (Patient), ZR: " << zr_imageOrientationPatient
						<< endl;
				}
				if (fileformat.getDataset()
					->findAndGetFloat64(DCM_ImageOrientationPatient, xc_imageOrientationPatient, 3)
					.good()) {
					cout << "Image Orientation (Patient), XC: " << xc_imageOrientationPatient
						<< endl;
				}
				if (fileformat.getDataset()
					->findAndGetFloat64(DCM_ImageOrientationPatient, yc_imageOrientationPatient, 4)
					.good()) {
					cout << "Image Orientation (Patient), YC: " << yc_imageOrientationPatient
						<< endl;
				}
				if (fileformat.getDataset()
					->findAndGetFloat64(DCM_ImageOrientationPatient, zc_imageOrientationPatient, 5)
					.good()) {
					cout << "Image Orientation (Patient), ZC: " << zc_imageOrientationPatient
						<< endl;
				}
				if (fileformat.getDataset()
					->findAndGetFloat64(DCM_SliceLocation, sliceLocation)
					.good()) {
					cout << "Slice Location: " << sliceLocation << endl;
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
				first_file = false;
			}

			cout << *it << endl; // чтоб видеть, на каком файле сейчас итератор

			if (fileformat.getDataset()
				->findAndGetUint16Array(DCM_PixelData, pixelData)
				.good()) {
				
				cout << rows*columns*bitsStored / 8 << endl;
			}
		}
	}
}
