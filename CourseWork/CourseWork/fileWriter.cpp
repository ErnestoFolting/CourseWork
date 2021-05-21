#include "fileWriter.h"

void fileWriter::outputSelf(matrix tempMatr)
{
	ofstream outFile("result.txt",ios::app);
	outFile << "����������� ����������������� �������: " << endl;
	for (int i = 0; i < tempMatr.p.size(); i++) {
		outFile << i + 1 << " : " << tempMatr.p[i] << endl;
	}
	outFile << "����� ����� �������:" << endl;
	for (int i = 0; i < tempMatr.getRows(); i++) {
		outFile << i+1 << " : " <<real(tempMatr.r.mas[i]) << endl;
	}
	for (int i = 0; i < tempMatr.vectorsX.size(); i++) {
		outFile << endl;
		outFile << i + 1 << " ������� ������: " << endl;
		for (int j = 0; j < tempMatr.rows; j++) {
			outFile << tempMatr.vectorsX[i][j][0] << endl;
		}
	}
	outFile.close();
}
void fileWriter::outputMatr(matrix tempMatr) {
	ofstream outFile("result.txt");
	outFile << "������ ������� A: " << endl;
	for (int i = 0; i < tempMatr.rows; i++) {
		for (int j = 0; j < tempMatr.rows; j++) {
			outFile << setw(9) << tempMatr.Matr[i][j];
		}
		outFile << endl;
	}
	outFile.close();
}

