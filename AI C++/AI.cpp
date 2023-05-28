#include <iostream>
#include <math.h>
#include <fstream>
#include <conio.h>
#define PI 3.14
using namespace std;
	//tinh toan cho duong tinh
//Tinh trung binh
float meanDT(float a[], int n, bool k[]){
	float sum=0;
	int count=0;
	for(int i=0; i<n; i++){
		if (k[i]==1) {
			sum += a[i];
			count++;
		}
	}
	return sum/count;
}
//Tinh do lech chuan
float standardDeviationDT(float a[], int n, bool k[]){
	float x=0;
	float avg = meanDT(a,n,k);
	int count=0;
	for(int i=0;i<n;i++){
		if(k[i]==1){
			x += pow((a[i] - avg),2);
			count++;
		}
	}
	return sqrt(x/(count-1));
}
	//tinh toan cho am tinh
//Tinh trung binh
float meanAT(float a[], int n, bool k[]){
	float sum=0;
	int count=0;
	for(int i=0; i<n; i++){
		if (k[i]==0) {
			sum += a[i];
			count++;
		}
	}
	return sum/count;
}
//Tinh do lech chuan
float standardDeviationAT(float a[], int n, bool k[]){
	float x=0;
	float avg = meanAT(a,n,k);
	int count=0;
	for(int i=0;i<n;i++){
		if(k[i]==0){
			x += pow((a[i] - avg),2);
			count++;
		}
	}
	return sqrt(x/(count-1));
}


//---------Tinh xac suat cua tung bien theo phan phoi Gausian-------
float calculateProb(float x, float mean, float standardDeviation){
	return exp(-pow((x-mean),2)/(2*standardDeviation))/(sqrt(x*PI*pow(standardDeviation,2)));
}
int main(){
			//DOC DU LIEU TU FILE
	ifstream ifs;
	ifs.open("covid.txt");
	int n;
	char k;
	ifs>>n;
	float tuoi[n];
	float nhipTho[n];
	float mach[n];
	float nhietDoCoThe[n];
	float chiSoSpO2[n];
	bool macBenh[n];
	for(int i=0;i<n;i++){
		ifs>>tuoi[i]>>k>>nhipTho[i]>>k>>mach[i]>>k>>nhietDoCoThe[i]>>k>>chiSoSpO2[i]>>k>>macBenh[i]>>k;
	}
	ifs.close();
			//QUA TRINH TRAINING
	//Dem so nguoi am tinh va duong tinh
	float countDuongTinh=0;
	for(int i=0;i<n;i++){
		if(macBenh[i]==true) countDuongTinh++;
	}
	float countAmTinh=n-countDuongTinh;
	
	//Tinh xac suat theo bang cua nguoi am tinh va duong tinh
	double pDuongTinh = countDuongTinh/n;
	double pAmTinh = countAmTinh/n;
	//Tinh toan thong so cua nguoi duong tinh
	double meanTuoiDuongTinh = meanDT(tuoi,n,macBenh);
	double standardDeviationTuoiDuongTinh = standardDeviationDT(tuoi,n,macBenh);
	
	double meanNhipThoDuongTinh = meanDT(nhipTho,n,macBenh);
	double standardDeviationNhipThoDuongTinh = standardDeviationDT(nhipTho,n,macBenh);
	
	double meanNhietDoCoTheDuongTinh = meanDT(nhietDoCoThe,n,macBenh);
	double standardDeviationNhietDoCoTheDuongTinh = standardDeviationDT(nhietDoCoThe,n,macBenh);
	
	double meanMachDuongTinh = meanDT(mach,n,macBenh);
	double standardDeviationMachDuongTinh = standardDeviationDT(mach,n,macBenh);
	
	double meanChiSoSpO2DuongTinh = meanDT(chiSoSpO2,n,macBenh);
	double standardDeviationChiSoSpO2DuongTinh = standardDeviationDT(chiSoSpO2,n,macBenh);
	//Tinh toan cho nguoi am tinh
	double meanTuoiAmTinh = meanAT(tuoi,n,macBenh);
	double standardDeviationTuoiAmTinh = standardDeviationAT(tuoi,n,macBenh);
	
	double meanNhipThoAmTinh = meanAT(nhipTho,n,macBenh);
	double standardDeviationNhipThoAmTinh = standardDeviationAT(nhipTho,n,macBenh);
	
	double meanNhietDoCoTheAmTinh = meanAT(nhietDoCoThe,n,macBenh);
	double standardDeviationNhietDoCoTheAmTinh = standardDeviationAT(nhietDoCoThe,n,macBenh);
	
	double meanMachAmTinh = meanAT(mach,n,macBenh);
	double standardDeviationMachAmTinh = standardDeviationAT(mach,n,macBenh);
	
	double meanChiSoSpO2AmTinh = meanAT(chiSoSpO2,n,macBenh);
	double standardDeviationChiSoSpO2AmTinh = standardDeviationAT(chiSoSpO2,n,macBenh);
			//QUA TRINH TESTING
			//Nhap mot du lieu moi de test
	int i;
	do{
		double t,nt,m,ndct,spo2;
		cout<<"Nhap tuoi cua nguoi test: ";cin>>t;
		cout<<"Nhap nhip tho: ";cin>>nt;
		cout<<"Nhap mach: ";cin>>m;
		cout<<"Nhap nhiet do co the: ";cin>>ndct;
		cout<<"Nhap chi so SpO2: ";cin>>spo2;
		
		double calculateProbTuoiDuongTinh = calculateProb(t,meanTuoiDuongTinh,standardDeviationTuoiDuongTinh);
		double calculateProbNhipThoDuongTinh = calculateProb(nt,meanNhipThoDuongTinh,standardDeviationNhipThoDuongTinh);
		double calculateProbMachDuongTinh = calculateProb(m,meanMachDuongTinh,standardDeviationMachDuongTinh);
		double calculateProbNhietDoCoTheDuongTinh = calculateProb(ndct,meanNhietDoCoTheDuongTinh,standardDeviationNhietDoCoTheDuongTinh);
		double calculateProbChiSoSpO2DuongTinh = calculateProb(spo2,meanChiSoSpO2DuongTinh,standardDeviationChiSoSpO2DuongTinh);
		double dt=calculateProbTuoiDuongTinh*calculateProbNhipThoDuongTinh*calculateProbMachDuongTinh*calculateProbNhietDoCoTheDuongTinh*calculateProbChiSoSpO2DuongTinh*pDuongTinh;
	
		double calculateProbTuoiAmTinh = calculateProb(t,meanTuoiAmTinh,standardDeviationTuoiAmTinh);
		double calculateProbNhipThoAmTinh = calculateProb(nt,meanNhipThoAmTinh,standardDeviationNhipThoAmTinh);
		double calculateProbMachAmTinh = calculateProb(m,meanMachAmTinh,standardDeviationMachAmTinh);
		double calculateProbNhietDoCoTheAmTinh = calculateProb(ndct,meanNhietDoCoTheAmTinh,standardDeviationNhietDoCoTheAmTinh);
		double calculateProbChiSoSpO2AmTinh = calculateProb(spo2,meanChiSoSpO2AmTinh,standardDeviationChiSoSpO2AmTinh);
		double at=calculateProbTuoiDuongTinh*calculateProbNhipThoDuongTinh*calculateProbMachAmTinh*calculateProbNhietDoCoTheAmTinh*calculateProbChiSoSpO2AmTinh*pAmTinh;
		
		cout<<"Tich cac chi so sau tinh toan (duong tinh): "<<dt<<endl;
		cout<<"Tich cac chi so sau tinh toan (am tinh): "<<at<<endl;
		if(dt<at) cout<<"Chuan doan nguoi nay am tinh"<<endl;
			else cout<<"Chuan doan nguoi nay duong tinh"<<endl;
		cout<<"Nhap 0 neu muon thoat chuong trinh";
		cin>>i;
		system("cls");
	} while (i!=0);
}
