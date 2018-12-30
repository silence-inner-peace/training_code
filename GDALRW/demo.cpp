#include <iostream>
#include <gdal_priv.h>
#include "GDALRead.h"
#include "GDALWrite.h"
using namespace std;

int main(int argc, char *argv[])
{
	if (argc<3)
	{
		cout<<"please input I/O filename. exit."<<endl;
		return -1;
	}

	//register
	GDALAllRegister();
	//OGRRegisterAll();
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");

	//test_data
	CGDALRead* pread = new CGDALRead;
	
	//Assume we load a image, the data type is unsigned short (UINT16)
	if (!pread->loadFrom(argv[1]))
	{
		cout<<"load error!"<<endl;
	}
	
	cout<<"load success!"<<endl;

	int cols = pread->cols();
	int rows = pread->rows();
	double geoTransform[6];
	double* pgeo = pread->geotransform();
	for (int kk=0; kk<6; kk++)
	{
		geoTransform[kk] = pgeo[kk];
	}

	char projref[2048];
	strcpy(projref, pread->projectionRef());

	//
	cout<<"samples = "<<pread->cols()<<endl;
	cout<<"lines = "<<pread->rows()<<endl;
	cout<<pread->bandnum()<<endl;
	cout<<pread->datalength()<<endl;
	cout<<pread->projectionRef()<<endl;

	//We load all data from image into pdata.
	unsigned short* pdata = new unsigned short[pread->rows()*pread->cols()];

	int i, j, k;

	//this model is thread-safety
//#pragma omp parallel for private(j), num_threads(omp_get_max_threads())
	for (i=0; i<pread->rows(); i++)
	{
		for (j=0; j<pread->cols(); j++)
		{
			//Here should change the pread->read() point into destination data type. Here just is unsigned char. 
			pdata[0*pread->rows()*pread->cols()+i*pread->cols()+j] = *(unsigned short*)pread->read(i, j, 0);
		}
	}

	cout<<"read success!"<<endl;

	pread->close();	//release memory
	delete pread; //release memory

	
	//*****************write a new image*****************
	CGDALWrite pwrite;
	bool brlt = pwrite.init(argv[2], rows, cols, 1, geoTransform, projref, GDT_Float32, 0);
	if (!brlt)
	{
		cout<<"write init error!"<<endl;
		return -2;
	}

	float _val = 0;

//#pragma omp parallel for private(j, k, _val), num_threads(omp_get_max_threads())
	for (i=0; i<pwrite.rows(); i++)
	{
		for (j=0; j<pwrite.cols(); j++)
		{
			for (k=0; k<1; k++)
			{
				 _val = (float)pdata[k*pwrite.rows()*pwrite.cols()+i*pwrite.cols()+j]/2.0;
				 pwrite.write(i, j, k, &_val);
			}
		}
	}

	cout<<"write success!"<<endl;

	pwrite.close(); //flush the data into file, and release memory

	delete []pdata; //release memory

	return 0;
}