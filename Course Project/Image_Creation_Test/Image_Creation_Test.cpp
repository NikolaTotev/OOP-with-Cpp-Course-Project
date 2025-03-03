#include "pch.h"
#include <iostream>
#include <fstream>
#include "RGB.h"
#include <vector>
#include "PROTO_Image.h"
using namespace std;

void writePixelData(ofstream& filedata, RGB pixel)
{
	for (int p = 0; p < 3; p++)
	{
		if (pixel.pixelData[p] == 0)
		{
			filedata << " ";
		}
		else
		{
			filedata << pixel.pixelData[p];
		}
	}
}


int main()
{
	const int testHeight = 512;
	const int testWidth = 512;

	string mainPath = "D:\\Documents\\Learning\\Object Oriented Programming\\Course Project\\OOP-Course-Project-S1\\saves";

	//string readFileName = "\\Test_Img.ppm";
	//string readFileName = "\\PPM_Write.ppm";
	//string readFileName = "\\Lenna_Test.ppm";
	//string readFileName = "\\Red-10x10.ppm";
	string readFileName = "\\reds.ppm";

//	string readFileName = "\\Lenna_255.ppm";
	string writeFileName = "\\PPM_Monochrome";




	Image test(mainPath + readFileName);

	Image writeImage(test.getWidth(), test.getHeight(), 255, "PPM_Copy_Test", "P6");
	string writePath = mainPath + writeFileName + ".ppm";

	ofstream file;
	file.open(writePath, ios::binary | ios::out);

	file << "P6" << endl;
	file << test.getWidth() << endl << test.getHeight() << endl;
	file << "255" << endl;
	file.close();
	int sub_index = strlen(readFileName.c_str()) - 3;
	cout << readFileName.substr(sub_index).c_str() << "  SUBSTRING"<< endl;
	/*for (int j = 0; j < 255; j++)
	{
		for (int i = 0; i < 255; i++)
		{
			RGB pixel(i % 256, j % 256, (i*j) % 256);
			writePixelData(file, pixel);
		}
	}*/
	//file.close();

	writeImage.setImageData(test.getImageData());
	//writeImage.convertToMonochrome();
	//writeImage.convertToGrayScale();
	//writeImage.rewriteRawData();
	//writeImage.writeFile(writePath);


	cout << test.getReds().at(0) << " NUMBER OF REDS AT 0"<<endl;
	cout << test.getReds().at(128) << " NUMBER OF REDS AT 128"<<endl;
	cout << test.getReds().at(208) << " NUMBER OF REDS AT 208" << endl;

	cout << test.getReds().at(255) << " NUMBER OF REDS AT 255"<<endl;

	test.generateHistogram();

	cout << test.getMagicNumber().c_str() << endl
		<< test.getWidth() << endl
		<< test.getHeight() << endl
		<< test.getColorValue() << endl
		<< test.getFileName().c_str();


	return 0;
}

