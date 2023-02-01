#include <stdio.h>
#include <math.h>
#include <string.h>

int main (int argc, char* argv[])
{
  int read_char;
  float x, y, z, q, o, t;
  int atomid;
  int chainid;
  char resname[50]; 
  char chainname[50]; 
  char atomname1[50], atomname2[50]; 
  char str[50];  
  int comparison_result1, comparison_result2, comparison_result3;
  
  FILE * pFile;
  FILE * pFile2;  
  
  pFile = fopen (argv[1],"r");
  pFile2 = fopen ("new.pdbqt","w");

  read_char = fscanf (pFile, "%s", str);
  while(read_char>0)
  {
   comparison_result1 = strcmp(str,"ATOM");
   comparison_result2 = strcmp(str,"HETATM");
   comparison_result3 = strcmp(str,"TER");

   if(comparison_result1==0)
   {
    fscanf (pFile, "%d %s %s %s %d %f %f %f %f %f %f %s", &atomid, atomname1, resname, chainname, &chainid, &x, &y, &z, &o, &t, &q, atomname2);
    fprintf (pFile2, "ATOM%7d  %-3.3s %-3.3s %-1.1s%4d%12.3f%8.3f%8.3f%6.2f%6.2f%10.3f %s\n", atomid, atomname1, resname, chainname, chainid, x, y, z, o, t, q, atomname2);
   }

   if(comparison_result2==0)
   {
    fscanf (pFile, "%d %s %s %s %d %f %f %f %f %f %f %s", &atomid, atomname1, resname, chainname, &chainid, &x, &y, &z, &o, &t, &q, atomname2);
    fprintf (pFile2, "HETATM%5d  %-3.3s %-3.3s %-1.1s%4d%12.3f%8.3f%8.3f%6.2f%6.2f%10.3f %s\n", atomid, atomname1, resname, chainname, chainid, x, y, z, o, t, q, atomname2);
   }

   if(comparison_result3==0)
   {
    fscanf (pFile, "%d %s %s %d", &atomid, resname, chainname, &chainid);
    fprintf (pFile2, "TER%8d%9.3s %-1.1s%4d\n", atomid, resname, chainname, chainid);
   }

   read_char = fscanf (pFile, "%s", str);

  }

  fclose (pFile);
  fclose (pFile2); 

  return 0;
}
