/*
version: 		0.2
prerequis:
OS:			(Windows 7 SP1) 32bit ou (Windows XP SP3) 32bit *obligatoir*
charger:		CGAPXUTL.DLL
dll:			WINSCARD.DLL
  			AXUTIL.DLL
  			AXIS2_ENGINE.DLL
  			IDOCRYPTO.DLL
EDI:			Visual C++ 2005 ou anterieur

les choses a verifier:
le type de session de OuvrireSession / mettre 1 ou 2 ou 3
le type de session dans LireDonneeAS / mettre 1 ou 2 ou 3 / essaye de mettre les meme partout

les questions qui se posent:
est-ce que LireDonneeAS va copier la valeur voulu vers la variable "valeur" ou non? oui, c'est la cas!
quelle valeur la variable "longueure" dans LireDonneeAS calcule (le label ou la valeur elle meme) ?
*/

#include <windows.h>
#include <iostream>
#include <cstring>
#include <string>

int main() {
  
  // charger la dll CGAPXUTL.DLL
  HMODULE hGetProcIDDLL = LoadLibrary(L"C:\\dllChifa\\cgapxutl.dll");
  
  // verifié si la dll a etait bien importée ou non
  if (hGetProcIDDLL != NULL) {
    std::cout << "la dll a etait importee\n";
	system("pause");
  } else {
    std::cout << "la dll n'a etait importee\n";
	system("pause");
	exit(1);
  }

  typedef int (*OuvrireSess)(int, int);
  OuvrireSess OuvrireSession = (OuvrireSession) GetProcAddress( hGetProcIDDLL, "OuvrireSession");

  if( OuvrireSession != NULL ) {
      std::cout << "la fonction OuvrireSession s'est fait appellee!\n";
      system("pause");
    } else {
      std::cout << "la fonction OuvrireSession ne s'est pas fait appellee!\n";
      system("pause");
      exit(1);
    }

  typedef int (*LireDonnee)(int, char*, char*, int, char*);
  LireDonnee LireDonneeAS = (LireDonnee) GetProcAddress( hGetProcIDDLL, "LireDonneeAS");
  
  if( LireDonneeAS != NULL ) {
	std::cout << "la fonction LireDonneeAS s'est fait appellee!\n";
	system("pause");
  } else {
    std::cout << "la fonction LireDonneeAS ne s'est pas fait appellee!\n";
	system("pause");
	exit(1);
  }

  typedef int (*LireDonneeP)(int, char*, char*, int, char*);
  LireDonneeP LireDonneePS = (LireDonneeP) GetProcAddress( hGetProcIDDLL, "LireDonneePS");
  
  if( LireDonneePS != NULL ) {
	std::cout << "la fonction LireDonneePS s'est fait appellee!\n";
	system("pause");
  } else {
    std::cout << "la fonction LireDonneePS ne s'est pas fait appellee!\n";
	system("pause");
	exit(1);
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
    exit(1);
  }
  
  HANDLE sess;

  // les parametre sont
  // (session, typeSession)
  // type de session est soit l'entier 1 ou 2 ou 3
  int retOuvrireSession = OuvrireSession( sess /*parametre inconnu*/, 1 /*1 ou 2 ou 3*/);  
  std::cout << "OuvrireSession a etait appellee! valeur ret: " << retOuvrireSession << std::endl;
  system("pause");

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

  // les parametre sont
  // (session)
  int retFermerSession = FermerSession(sess /*parametre inconnu*/);
  std::cout << "FermerSession a etait appellee! valeur ret: " << retFermerSession << std::endl;
  system("pause");
    
  return 0;
}
