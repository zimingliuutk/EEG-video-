#include <iostream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <iterator>
#include <tuple>
#include <cstring>

using namespace std;

class EEG_plot {
	public:

	vector<vector <string>> readtxt (string name, int a){

		ifstream file(name);
		vector<string> v;
		string str;
		while (file >> str){
			v.push_back(str);
		}
		v.erase( v.begin(), v.begin()+32);

		vector<vector<string>>matrix (2*50,vector<string>(32));
		for (int i = 0; i< a; i++) {
			for (int j = 0; j < 32; j++){
				matrix[2*(i%50)+1][j] = v[32*i+j];
				string p = std::to_string ((i+1)*0.06);
				matrix[2*(i%50)][j] = p;
			}
		}

		return matrix;
	}

	string vectostring (vector<string> plot){
		ostringstream vts;
		copy(plot.begin(), plot.end(),
			std::ostream_iterator<string> (vts, " "));
			string res = vts.str();
		return res;
	}

	tuple <string,string,string,string> line (vector<vector <string>>matrix){
		vector<string> FP1(matrix.size());
		vector<string> FP2(matrix.size());
		vector<string> F3(matrix.size());
		vector<string> F4(matrix.size());
		for (int i = 0; i< matrix.size();i++){
				FP1[i] = matrix[i][0];
				FP2[i] = matrix[i][1];
				F3[i] = matrix[i][2];
				F4[i] = matrix[i][3];
		}
		string s = "newcurve marktype box linetype solid pts ";
		string fp1 = vectostring (FP1);
		string fp2 = vectostring (FP2);
		string f3 = vectostring (F3);
		string f4 = vectostring (F4);
		fp1 = s+ fp1;
		fp2 = s+ fp2;
		f3 = s+ f3;
		f4 = s+ f4;

		return make_tuple (fp1,fp2,f3,f4);
	}

	string charToStr (char* c_char){
		string tempStr;
		for (int i = 0; c_char[i] != '\0'; i++){
			tempStr +=c_char[i];
		}
		return tempStr;
	}

	void modifyContentInFile(char *fileName,int lineNum,char *content){
		ifstream in;
		char line[1024]={'\0'};
		in.open(fileName);
		int i=0;
		string tempStr;
		while(in.getline(line,sizeof(line))){
			i++;
			if(lineNum!=i){
				tempStr+=charToStr(line);
			}
			else{
	       		tempStr+=charToStr(content);
			}
			tempStr+='\n';
		}
		in.close();
		ofstream out;
		out.open(fileName);
		out.flush();
		out<<tempStr;
		out.close();
	}



};


int main(int argc, char* argv[]) {
	EEG_plot output;
	string file;
	int dur;
	cout<< "inputfile" << endl;
	cin >> file;
	cout<< "duration (min)" << endl;
	cin >> dur;
	for (int i = 0; i< dur/0.06; i++){

		vector<vector<string>> matrix = output.readtxt(file, i);
		if (i<50){
			string axis = "xaxis min 0 max 3 size 7";
			int n = axis.length();
			char char_axis[n+1];
			strcpy(char_axis,axis.c_str());

			output.modifyContentInFile("eeg.jgr", 3, char_axis);
		}
		else {
		string axis1 = "xaxis min ";
		float a = std::atof (matrix[0][0].c_str());
		string x_1 = std::to_string(0.06*i-3);
		string axis2 = " max " ;
		string x_2 = std::to_string(0.06*i);
		string axis3 =" size 7";
		string axis = axis1 + x_1 + axis2 + x_2 + axis3;

		int n = axis.length();
		char char_axis[n+1];
		strcpy(char_axis,axis.c_str());

		output.modifyContentInFile("eeg.jgr", 3, char_axis);
		}


		string fp1, fp2, f3, f4;
		tie(fp1,fp2,f3,f4) = output.line(matrix);
		matrix.clear(); 

		int n1 = fp1.length();
		char char_fp1[n1+1];
		strcpy(char_fp1,fp1.c_str());

		int n2 = fp2.length();
		char char_fp2[n2+1];
		strcpy(char_fp2,fp2.c_str());

		int n3 = f3.length();
		char char_f3[n3+1];
		strcpy(char_f3,f3.c_str());

		int n4 = f4.length();
		char char_f4[n4+1];
		strcpy(char_f4,f4.c_str());

		output.modifyContentInFile("eeg.jgr", 10, char_fp1);
		output.modifyContentInFile("eeg.jgr", 15, char_fp2);
		output.modifyContentInFile("eeg.jgr", 20, char_f3);
		output.modifyContentInFile("eeg.jgr", 25, char_f4);
		string c = std::to_string (i+1);

		string s1 = "jgraph -P eeg.jgr | ps2pdf - | convert -density 300 - -quality 100 image/eeg-"+c+".jpg";

		int n5 = s1.length();
		char char_s1[n5+1];
		strcpy(char_s1,s1.c_str());

		system(char_s1);

		
	}

	file.erase(file.end() -4);

	system("ffmpeg -r 25 -i image/eeg-%d.jpg -pix_fmt yuv420p Output.mp4");



	
	
   
}
