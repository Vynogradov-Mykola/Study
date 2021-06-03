
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <dirent.h>
#include <sstream>
#include <windows.h>
#include <locale>
#include <codecvt>
using namespace std;
#define ID3_MAX_SIZE 128
string path;   //PATH TO DIRECTORY
int corrections; // variable of errors
vector<string> LIST_OF_PATH;    // LIST OF PATHS
int num_of_files=0;     //Global int with number of all files in directory
int num_of_file=0;    //Global int, pos number of file
string ganres[148]={"Blues","Classic Rock","Country","Dance","Disco","Funk","Grunge",
                   "Hip-Hop","Jazz","Metal","New Age","Oldies","Other","Pop",
                   "R&B","Rap","Reggae","Rock","Techno","Industrial","Alternative",
                   "Ska","Death Metal","Pranks","Soundtrack","Euro-Techno","Ambient",
                   "Trip-Hop","Vocal","Jazz+Funk","Fusion","Trance","Classical",
                   "Instrumental","Acid","House","Game","Sound Clip","Gospel",
                   "Noise","AlternRock","Bass","Soul","Punk","Space","Meditative",
                   "Instrumental Pop","Instrumental Rock","Ethnic","Gothic",
                   "Darkwave","Techno-Industrial","Electronic","Pop-Folk","Eurodance",
                   "Dream","Southern Rock","Comedy","Cult","Gangsta","Top 40",
                   "Christian Rap","Pop/Funk","Jungle","Native American","Cabaret",
                   "New Wave","Psychedelic","Rave","Showtunes","Trailer","Lo-Fi",
                   "Tribal","Acid Punk","Acid Jazz","Polka","Retro","Musical",
                   "Rock & Roll","Hard Rock",
                    "Folk","Folk/Rock","National Folk","Swing","Fast Fusion",
                   "Bebob","Latin","Revival","Celtic","Bluegrass","Avantgarde",
                   "Gothic Rock","Progressive Rock","Psychedelic Rock",
                   "Symphonic Rock","Slow Rock","Big Band","Chorus","Easy Listening",
                   "Acoustic","Humour","Speech","Chanson","Opera","Chamber Music",
                   "Sonata","Symphony","Booty Bass","Primus","Porn Groove",
                   "Satire","Slow Jam","Club","Tango","Samba","Folklore",
                   "Ballad","Power Ballad","Rhythmic Soul","Freestyle",
                   "Duet","Punk Rock","Drum Solo","Acapella","Euro-House",
                   "Dance Hall", "Goa", "Drum & Bass", "Club-House", "Hardcore",
                   "Terror", "Indie", "BritPop", "Negerpunk", "Polsk Punk", "Beat",
                   "Christian Gangs", "Heavy Metal", "Black Metal", "Crossover",
                   "Contemporary Ch?", "Cristian Rock", "Merengue", "Salsa",
                   "Thrash Metal", "Anime", "JPop", "Synthpop"};
//============================GANRES OF MP3==============================//


typedef struct IDv3Tag      //structure ID3 Tag (128 B)
{
    char signature[3];
    char name[30];
    char artist[30];
    char album[30];
    char year[4];
    char description[30];
    char ganre;

} ID3TAG;
vector<wstring>foundMP3;

long idv3_file_offset(FILE* fp)  //function to find pos of id3
{
    fseek(fp, 0L, SEEK_END);        //find pos
    return ftell(fp) - ID3_MAX_SIZE;  //return pos
}
void filefinder()           //get a list with names of all files in directory
{   cout<<"Enter path to directory:  ";

    cin>>path;
    DIR *directory = opendir(path.c_str());   //open directory
    struct dirent *direntStruct;

    if (directory != NULL) {
        while (direntStruct = readdir(directory))
        {
            LIST_OF_PATH.push_back(direntStruct->d_name); //add name to list LIST_OF_PATH
            num_of_files+=1;
        }
    }
    else {cout<<"Incorrect path to directory, to try again select 1, to exit select 2\n";
        cin>>corrections;
        if(corrections==1)
          { cin>>path;

            filefinder();
          }
         }
    closedir(directory);            //close directory
}

void rewrite(string path_to_f)      //rewrite function
{

}
void print(string path_to_f)
{
    const char *cster=path_to_f.c_str();     //convert STRING path into CHAR path (for fopen())
    FILE* fp;
    if ((fp = fopen(cster,"r")) == NULL)   // open file in read-mode
    printf("Unable to open file %s for reading\n", cster);

    char* buf = new char[ID3_MAX_SIZE];
    memset((void*)buf, 0x00, ID3_MAX_SIZE);

    fseek(fp, idv3_file_offset(fp), SEEK_SET);  //pos of tag
    fread(buf, 1, ID3_MAX_SIZE, fp);  //read tag

    ID3TAG* pId3Tag = NULL;
    if ((pId3Tag = reinterpret_cast<ID3TAG*>(buf)) != NULL)
    {
    int gnr=pId3Tag->ganre;
               printf("Name:        %s\n",pId3Tag->name);
               printf("Artist:      %s\n",pId3Tag->artist);
               printf("Album:       %s\n",pId3Tag->album);
               cout<<"Year:        "<<pId3Tag->year[0]<<pId3Tag->year[1]<<pId3Tag->year[2]<<pId3Tag->year[3];
               printf("\nDescription: %s\n",pId3Tag->description);
               if(gnr>0) cout<<"Ganre:       "<<ganres[gnr];
               else cout<<"Ganre:       Other";
    }
    cout<<"\n";
//===================print TAG==========================//
    fclose(fp);


        delete[] buf;
}
int main()
{   setlocale(LC_ALL, "Russian");
    cout<<"Work with directory or with one file? \n1-directory\n2-file\nEnter: ";
    int changer=0;
    cin>>changer;
    if(changer==1){
    filefinder();
    if (corrections==2) return 0;
    vector<string> path_to_files;
//===================path to directory+name of file========//
    for(int i=2;i<num_of_files;i++)
    {   string rev;
        rev=path+"/"+LIST_OF_PATH[i];
        path_to_files.push_back(rev);
    }
//===================path to directory+name of file========//

       for(int i=0;i<num_of_files-2;i++){
           cout<<"========================================"<<i<<"  Track=="
"===============================================================\n";
            print(path_to_files[i]);  //print all tags in dir
        }
    cout<<"\nChange to rewrite ";
   // int num_of_file = 0;
   while(num_of_file!=-1){
    cin>>num_of_file;
    cout<<"\n";
       rewrite(path_to_files[num_of_file]);         //call rewrite function
        cout<<"If you want to exit enter   -1      else to continue ";
           cin>>num_of_file;

           cout<<"\nEnter LIST  to see all tracks else to continue ";
           string list;
           cin>>list;
           if(list=="LIST")
           {
               for(int i=0;i<num_of_files-2;i++)
               {
                   cout<<"========================================"<<i<<"  Track=="
                   "===============================================================\n";
                   print(path_to_files[i]);  //print all tags in dir
               }
           }
           cout<<"\nChange to rewrite ";
}
    }
    else            //for work with one file
    {   cout<<"Enter path: ";
        cin>>path;          //enter path to file
        print(path);            //print information
        cout<<"Do you want to rewrite?   yes/no\n";
        string change;              //changer
        cin>>change;
        while(change=="yes")        //rewrite cycle
        {
            rewrite(path);
            cout<<"Continue rewritre?   yes/no\n";
            cin>>change;
        }

    }
    _getch();

    return 0;
}


