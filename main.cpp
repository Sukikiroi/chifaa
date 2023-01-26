/*
  version: 		0.2
  prerequis:
  OS:			windows 7 32bit (obligatoir)
  Libraries:		WDK (Windows Driver Kit)
  charger:		cgapxutl.dll
  dll:			OLEAUT32.DLL
  			ADVAPI32.DLL
  			USER32.DLL
  			OLE32.DLL
  			COMCTL32.DLL
  			MSVCRT.DLL
  			SHELL32.DLL
  			CGAPXUTL.DLL
  			WTSAPI32.DLL
  			MSIMG32.DLL
  			WINDOWSCODECS.DLL
  			IMM32.DLL
  			DWMAPI.DLL
  			
  EDI:			Visual C++ 2005 ou anterieur
*/

/*

les choses a verifié:
le handle de OuvrireSession est un simple handle, essaye de mettre le return de OuvrireSession dans LireDoneeAScomme le handle de OuvrireSession
le type de session de OuvrireSession / mettre 1 ou 2 ou 3
le type de session dans LireDonneeAS / mettre 1 ou 2 ou 3 / essaye de mettre les meme partout
essaie de mettre le type de valeur LireDonneeAS comme string

les questions qui se posent:
est-ce que LireDonneeAS va copier la valeur voulu vers la variable valeur ou non? oui, c'est la cas!
quelle veleur variable "longueure" calcule?

*/

#include <windows.h>
#include <iostream>
#include <winscard.h>
#include <cstring>
#include <string>

int main() {
  
  // charger la dll cgapxutl.dll
  HMODULE hGetProcIDDLL = LoadLibrary(L"C:\\dllChifa\\cgapxutl.dll");
  
  // verifié si la dll a etait bien importée ou non
  if (hGetProcIDDLL == NULL) {
    std::cout << "le dll s'est pas importee\n";
	system("pause");
  } else {
    std::cout << "la dll a etait importee\n";
	system("pause");
  }

  // session a l'air d'un integer (toujous inconnu)
  // type de session est soit l'entier 1 ou 2 ou 3
  typedef int (*OuvrireSess)(int, int);
  OuvrireSess OuvrireSession = (OuvrireSession) GetProcAddress( hGetProcIDDLL, "OuvrireSession");

  if( OuvrireSession != NULL ) {
      std::cout << "la fonction OuvrireSession s'est fait appellee!\n";
      system("pause");
    } else {
      std::cout << "la fonction OuvrireSession ne s'est pas fait appellee!\n";
      system("pause");
    }

  typedef int (*LireDonnee)(int, char*, char*, int, char*);
  LireDonnee LireDonneeAS = (LireDonnee) GetProcAddress( hGetProcIDDLL, "LireDonneeAS");
  
  if( LireDonneeAS != NULL ) {
	std::cout << "la fonction LireDonneeAS s'est fait appellee!\n";
	system("pause");
  } else {
    std::cout << "la fonction LireDonneeAS ne s'est pas fait appellee!\n";
	system("pause");
  }

  typedef int (*LireDonneeP)(int, char*, char*, int, char*);
  LireDonneeP LireDonneePS = (LireDonneeP) GetProcAddress( hGetProcIDDLL, "LireDonneePS");
  
  if( LireDonneePS != NULL ) {
	std::cout << "la fonction LireDonneePS s'est fait appellee!\n";
	system("pause");
  } else {
    std::cout << "la fonction LireDonneePS ne s'est pas fait appellee!\n";
	system("pause");
  }


  // le parametre de FermerSession est toujours inconnu
  typedef int (*FermerSess)(int);
  FermerSess FermerSession = (FermerSession) GetProcAddress( hGetProcIDDLL, "FermerSession");

  if( FermerSession != NULL ) {
    std::cout << "la fonction FermerSession s'est fait appellee!\n";
    system("pause");
  } else {
    std::cout << "la fonction FermerSession ne s'est pas fait appellee!\n";
    system("pause");
  }
  
  HANDLE sess;

  int retOuvrireSession = OuvrireSession( sess /*parametre inconnu*/, 1 /*1 ou 2 ou 3*/);  
  std::cout << "OuvrireSession a etait appellee! valeur ret: " << retOuvrireSession << std::endl;
  system("pause");

  // appeller la fonction LireDonneeAS
  // LireDonneeAS(session, label, valeur, longueur, type)
  // type de label
  // "CS.ADMIN.TYPE"
  // "CS.ASSURE.NUMERO"
  // "CS.ASSURANCE.CENTREAFFI"
  // "CS.ASSURE.NOMLA"
  // "CS.ASSURE.PRENOMLA"
  // "CS.ASSURE.DATENAISSANCE"
  // "CS.ASSURE.NOMAR"
  // "CS.ASSURE.PRENOMAR"
  // "CS.BENEFICIAIRE.ADRESSE"
  // "CS.MUTUELLE.PHARMACIES"
  // "CS.DROITS.TAUX"
  // "CS.MUTUELLE.DATEFIN"
  // "CS.MUTUELLE.CODE"
  // "CS.DROITS.DATEFIN"
  // "CS.ASSURANCE.ORGAAFFI"
  // "CS.MUTUELLE.PHARMACIES"
  // "CS.ALD1.NOM"
  // "CS.ALD2.NOM"
  // "CS.ALD3.NOM"
  // "CS.MUTUELLE.PHARMACIES"
  // "CS.ASSURANCE.STATUT"
  // "CS.ASSURANCE.POSITION"


  // La fonction LireDoneeAS
  // les parametre sont
  // (session, label, valeur, longueur, typeDeSession)
  string valeur = "0000000000000000";
  LireDonneeAS(sess /*parametre inconnu*/, "CS.ASSURE.NOMLA", valeur, strlen(valeur), 1 /*1 ou 2 ou 3*/);
  std::cout << "LireDonneeAS a etait appellee!\n";
  system("pause");
  std::cout << "la valeur LireDonneeAS est: " << valeur << std::endl;
  system("pause");

  // La fonction LireDoneePS
  // les parametre sont
  // (session, label, valeur, longueur, typeDeSession)  
  string valeur = "0000000000000000";
  LireDonneePS(sess /*parametre inconnu*/, "CS.ASSURE.NOMLA", valeur, strlen(valeur), 1 /*1 ou 2 ou 3*/);
  std::cout << "LireDonneePS a etait appellee!\n";
  system("pause");
  std::cout << "la valeur LireDonneePS est: " << valeur << std::endl;
  system("pause");


  int retFermerSession = FermerSession(sess /*parametre inconnu*/);
  std::cout << "FermerSession a etait appellee! valeur ret: " << retFermerSession << std::endl;
  system("pause");
  return 0;
}

