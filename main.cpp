/*
version: 		0.2
prerequis:
OS:			(Windows 7 SP1) 32bit ou (Windows XP SP3) 32bit *obligatoir*
EDI:			Visual C++ 2010 ou anterieur
dll a charger:		CGAPXUTL.DLL
dll:			WINSCARD.DLL
  			AXUTIL.DLL
  			AXIS2_ENGINE.DLL
  			IDOCRYPTO.DLL
option-Linker:		changer ce parametre "Configuration Properties->Linker->Advanced->Target Machine" vers "MachineX86 (/MACHINE:X86)"
			changer ce parametre "Configuration Properties->Linker->Advanced->RBA" vers "No (/DYNAMICBASE:NO)"
			changer ce parametre "Configuration Properties->Linker->Advanced->DEP" vers "No (/NXCOMPAT:NO)"
option pdb:		activer ce parametre "Tools->Options->Debugging->Symbols and select checkbox - Microsoft Symbol Servers"

les choses a verifier:
le type de session de OuvrireSession / mettre 1 ou 2 ou 3
le type de session dans LireDonneeAS et LireDonneePS / mettre 1 ou 2 ou 3 / essaye de mettre les meme partout

les questions qui se posent:
quelle valeur le parametre "longueure" dans LireDonneeAS et LireDonneePS calcule (le label ou la "valeur output" elle meme) ?
*/

#include <windows.h>
#include <iostream>
#include <string>
#include <cstring>

int main() {
  
  // charger la dll CGAPXUTL.DLL
  HMODULE hGetProcIDDLL = LoadLibrary(L"C:\\dllChifaa\\cgapxutl.dll");
  
  // verifier si la dll a etait bien importée ou non
  if (hGetProcIDDLL != NULL) {
    std::cout << "la dll cgapxutl.dll a etait importee\n";
	system("pause");
  } else {
    std::cout << "la dll cgapxutl.dll n'a pas etait importee\n";
	system("pause");
	return 1;
  }

  typedef int (*OuvrireSess)(HANDLE, int);
  OuvrireSess OuvrireSession = (OuvrireSess) GetProcAddress( hGetProcIDDLL, "OuvrireSession");

  if( OuvrireSession != NULL ) {
      std::cout << "la fonction OuvrireSession s'est fait appellee!\n";
      system("pause");
    } else {
      std::cout << "la fonction OuvrireSession ne s'est pas fait appellee!\n";
      system("pause");
      return 1;
    }

  typedef int (*LireDonnee)(HANDLE, char*, std::string, int, int);
  LireDonnee LireDonneeAS = (LireDonnee) GetProcAddress( hGetProcIDDLL, "LireDonneeAS");
  
  if( LireDonneeAS != NULL ) {
	std::cout << "la fonction LireDonneeAS s'est fait appellee!\n";
	system("pause");
  } else {
    std::cout << "la fonction LireDonneeAS ne s'est pas fait appellee!\n";
	system("pause");
	return 1;
  }

  typedef int (*LireDonneeP)(HANDLE, char*, std::string, int, int);
  LireDonneeP LireDonneePS = (LireDonneeP) GetProcAddress( hGetProcIDDLL, "LireDonneePS");
  
  if( LireDonneePS != NULL ) {
	std::cout << "la fonction LireDonneePS s'est fait appellee!\n";
	system("pause");
  } else {
    std::cout << "la fonction LireDonneePS ne s'est pas fait appellee!\n";
	system("pause");
	return 1;
  }

  typedef int (*FermerSess)(HANDLE);
  FermerSess FermerSession = (FermerSess) GetProcAddress( hGetProcIDDLL, "FermerSession");

  if( FermerSession != NULL ) {
    std::cout << "la fonction FermerSession s'est fait appellee!\n";
    system("pause");
  } else {
    std::cout << "la fonction FermerSession ne s'est pas fait appellee!\n";
    system("pause");
    return 1;
  }
  
  HANDLE sess = NULL;

  // les parametres sont
  // (session, typeSession)
  // type de session est soit l'entier 1 ou 2 ou 3
  int retOuvrireSession = OuvrireSession( sess, 1 /*1 ou 2 ou 3*/);  
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
  // les parametres sont
  // (session, label, valeur, longueur, typeDeSession)
  std::string valeurAS = "0000000000000000";
  LireDonneeAS(sess /*parametre inconnu*/, "CS.ASSURE.NOMLA", valeurAS, sizeof(valeurAS), 1 /*1 ou 2 ou 3*/);
  std::cout << "LireDonneeAS a etait appellee!\n";
  system("pause");
  std::cout << "la valeur LireDonneeAS est: " << valeurAS.c_str() << std::endl;
  system("pause");

  // La fonction LireDoneePS
  // les parametres sont
  // (session, label, valeur, longueur, typeDeSession)
  std::string valeurPS = "0000000000000000";
  LireDonneePS(sess /*parametre inconnu*/, "CS.ASSURE.NOMLA", valeurPS, sizeof(valeurPS), 1 /*1 ou 2 ou 3*/);
  std::cout << "LireDonneePS a etait appellee!\n";
  system("pause");
  std::cout << "la valeur LireDonneePS est: " << valeurPS.c_str() << std::endl;
  system("pause");

  // les parametres sont
  // (session)
  int retFermerSession = FermerSession(sess);
  std::cout << "FermerSession a etait appellee! valeur ret: " << retFermerSession << std::endl;
  system("pause");
    
  return 0;
}
