// STL includes
#include <iostream>
#include <string>


//DCMTK includes
#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"

int main()
{
	DcmFileFormat fileformat;
	OFCondition status = fileformat.loadFile("E:/CT/tom.dcm");
	if (status.good())
	{
		OFString patientsName;
		if (fileformat.getDataset()->findAndGetOFString(DCM_PatientName, patientsName).good())
		{
			std::cout << "Patient's Name: " << patientsName << std::endl;
		}
		else
			std::cerr << "Error: cannot access Patient's Name!" << std::endl;
	}
	else
		std::cerr << "Error: cannot read DICOM file (" << status.text() << ")" << std::endl;
	return 0;
}