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

int main() { // передаем функции аргументы
	bool first_file = true; // первому файлу присваиваем true, остальным - false

	for (fs::recursive_directory_iterator it("E:/CT/hip/ct-27.08.2015/ct-27.08.2015/DICOM/PA000000/ST000000/SE000000"), end; it != end; it++) { // пробегаем циклом по всем файлам дирректории
		if (first_file) { // если первый файл, то

			DcmFileFormat fileformat;
			OFCondition status = fileformat.loadFile("E:/CT/tom.dcm");
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
			}
		}
	}
}
