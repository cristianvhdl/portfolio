#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int hamming_distance(string& fs, string& ss){
  int hm_distance = 0;

  if((fs.length() == ss.length())){
    for(int i = 0; i < fs.length(); i++){
      if(!(fs[i] == ss[i])){
        hm_distance++;
      }
    }

  }else{
    hm_distance = -1;
  }
  return hm_distance;
}

int main (){
  int x;
  cout << "enter the number of barcodes in the \"ref.txt\" file: ";
  cin >> x;

  cout << "computing hamming distance between barcodes...\n";
  string *s1 = new string[x];
  ifstream infile;
  ofstream outfile;

  infile.open("ref.txt");
  outfile.open("out.txt");

  outfile << "\t";
  for (int i = 0; i < x; i++){
    getline(infile, s1[i]);
    outfile << s1[i] << "\t";
  }
  outfile << endl;
  infile.close();

  for(int i = 0; i < x; i++){
      outfile << s1[i] << "\t";
    for(int j = 0; j < x; j++){
      outfile << hamming_distance(s1[i], s1[j]) << "\t";
      if (j == x-1)
        outfile << endl;
    }
  }
  outfile.close();
  cout << "done. see \"out.txt\" for results.\n";

  return 0;
}
