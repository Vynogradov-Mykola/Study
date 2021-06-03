#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

 int main(void)
{
  vector<wstring>foundMP3;
  const wstring FORMAT = L"\\*.mp3";
  wstring pathTofolder;
  setlocale(LC_ALL, "Russian");

  cout <<"Enter the path to the file where .mp3's are saved: ";
  getline(wcin, pathTofolder);

  //WINAPI
  //Type WIN32_FIND_DATA is the structure with fields containing
  //info about file
  //HANDLE is a descriptor
  WIN32_FIND_DATA FindFileData;
  HANDLE hf;

  hf = FindFirstFile(&(pathTofolder + FORMAT)[0], &FindFileData);
  if (hf != INVALID_HANDLE_VALUE)
  {
    do
    {
      wstring ws(FindFileData.cFileName);
      foundMP3.push_back(ws);
    } while (FindNextFile(hf, &FindFileData) != 0);
    FindClose(hf);
  }

  if(foundMP3.size() != 0){
      cout << "Detected: " << endl;
  for(int n = 0; n < foundMP3.size(); n++)
      wcout << foundMP3[n] << endl;
  }
  else if(foundMP3.size() == 0){
      cout << "I did not find mp3's" << endl;
  }
  return 0;
}
