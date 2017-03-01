#include <iostream>
#include <string>

#include "defs.h"
#include "const.h"

int Config2Data(DataSet *data1)
{
	extern Configurator laserRegioniConfig;

	if (strstr(laserRegioniConfig.projectName, ".prj") == NULL)
		strcat_s(laserRegioniConfig.projectName, strlen(".prj")+1,".prj");
	
	data1->UpLeftCGrid  = 0;									//laserRegioniConfig.upLeftC;
	data1->UpLeftRGrid  = 0;									//laserRegioniConfig.upLeftR;
	data1->LoRightCGrid = laserRegioniConfig.gridWidth;			//laserRegioniConfig.lowRightC;
	data1->LoRightRGrid = laserRegioniConfig.gridHeight;		//laserRegioniConfig.lowRightR;

	data1->widthGrid    = laserRegioniConfig.gridWidth;
	data1->heightGrid   = laserRegioniConfig.gridHeight;
	data1->pelsX = data1->pelsY = laserRegioniConfig.gridUnit;  // Usa due diverse variabili per x e y ma se sono le stesse potrei unificarle

	data1->LoLeftX      = laserRegioniConfig.loLeftX;
	data1->LoLeftY      = laserRegioniConfig.loLeftY;
	data1->UpRightX     = data1->LoLeftX + (double)(data1->pelsX * data1->widthGrid);
	data1->UpRightY     = data1->LoLeftY + (double)(data1->pelsY * data1->heightGrid);

	return SUCCESS;
	
}

void printData(DataSet *data1)
{
	std::cout <<"Per ora niente"<< std::endl;
	std::cout << "cont= " << data1->cont << " dz= "<< data1->dz << std::endl;
	std::cout << "widthGrid= " << data1->widthGrid << " heightGrid= " << data1->heightGrid << std::endl;
	std::cout << "numPoints= " << data1->numPoints << std::endl;
	std::cout << "Xg= " << data1->Xg << " Yg= " << data1->Yg << std::endl;
	std::cout << "xminInput= "<< data1->xminInput << " xmaxInput= " << data1->xmaxInput << " yminInput= " << data1->yminInput << " ymaxInput= " << data1->ymaxInput << std::cout;
	std::cout << "zmin= " << data1->zmin << " zmax= " << data1->zmax << " Imax= " << data1->Imax << " Imin= " << data1->Imin << std::endl;
	std::cout << "pelsX= " << data1->pelsX << " pelsY= " << data1->pelsY << std::endl;
	std::cout << "LoLeftX= " << data1->LoLeftX << " LoLeftY= " << data1->LoLeftY << " UpRightX= " << data1->UpRightX << " UpRightY= " << data1->UpRightY << std::endl;
	std::cout << "UpLeftRGrid= " << data1->UpLeftRGrid << " UpLeftCGrid= " << data1->UpLeftCGrid << " LoRightRGrid= " << data1->LoRightRGrid << " LoRightCGrid= " << data1->LoRightCGrid << std::endl;
};

