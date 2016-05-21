#include <glut.h>
#include <gl.h>
#include <glu.h>
#include <glaux.h>
#include <fstream>

unsigned int MyTextureObject[2];												// ╦егн©К
AUX_RGBImageRec *pTextureImage[2];

AUX_RGBImageRec * LoadBMP(char *szFilename){
	FILE * pFile = NULL;
	if (!szFilename){
		return NULL;
	}
	pFile = fopen(szFilename, "r");
	if (pFile){
		fclose(pFile);
		return auxDIBImageLoad(szFilename);
	}
	return NULL;
}

int LoadGLTextures(){
	int Status = FALSE;
	memset(pTextureImage, 0, sizeof(void *) * 2);

	if ((pTextureImage[0] = LoadBMP("../data/texture1.bmp")) && (pTextureImage[1] = LoadBMP("../data/nabi.bmp"))){
		Status = TRUE;
		glGenTextures(2, &MyTextureObject[0]);
		for (int i = 0; i<2; i++){
			glBindTexture(GL_TEXTURE_2D, MyTextureObject[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, pTextureImage[i]->sizeX, pTextureImage[i]->sizeY,
				0, GL_RGB, GL_UNSIGNED_BYTE, pTextureImage[i]->data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}
	for (int i = 0; i<2; i++){
		if (pTextureImage[i]){
			if (pTextureImage[i]->data){
				free(pTextureImage[i]->data);
			}
			free(pTextureImage[i]);
		}
	}
	glEnable(GL_TEXTURE_2D);
	return Status;
}