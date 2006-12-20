// perturb.cpp
// author:  Frank C. Anderson

// INCLUDE
#include <string>
#include <iostream>
#include <OpenSim/Simulation/Model/LoadModel.h>
#include <OpenSim/Analyses/InvestigationPerturbation.h>

using namespace OpenSim;
using namespace std;

static void PrintUsage(ostream &aOStream);

//_____________________________________________________________________________
/**
 * Main routine for conducting a perturbation analysis.
 */
int main(int argc,char **argv)
{
	//----------------------
	// Surrounding try block
	//----------------------
	try {
	//----------------------

	// PARSE COMMAND LINE
	string option = "";
	string setupFileName = "";
	if(argc<2) {
		PrintUsage(cout);
		return(-1);
	}
	// Load libraries first
	LoadOpenSimLibraries(argc,argv);
	// Parse other command-line options
	for(int i=1;i<argc;i++) {
		option = argv[i];

		// PRINT THE USAGE OPTIONS
		if((option=="-help")||(option=="-h")||(option=="-Help")||(option=="-H")||
		(option=="-usage")||(option=="-u")||(option=="-Usage")||(option=="-U")) {
			PrintUsage(cout);
			return(0);
 
		// PRINT A DEFAULT SETUP FILE FOR THIS INVESTIGATION
		} else if((option=="-PrintSetup")||(option=="-PS")) {
			InvestigationPerturbation *investigation = new InvestigationPerturbation();
			investigation->setName("default");
			Object::setSerializeAllDefaults(true);
			investigation->print("setup_perturb_default.xml");
			Object::setSerializeAllDefaults(false);
			return(0);

		// IDENTIFY SETUP FILE
		} else if((option=="-Setup")||(option=="-S")) {
			if((i+1)<argc) setupFileName = argv[i+1];
			break;
		}
	}

	// ERROR CHECK
	if(setupFileName=="") {
		cout<<"\n\n"<<argv[0]<<": ERROR- A setup file must be specified.\n";
		PrintUsage(cout);
		return(-1);
	}

	// CONSTRUCT
	cout<<"Constructing investigation from setup file "<<setupFileName<<".\n\n";
	InvestigationPerturbation perturb(setupFileName);

	// PRINT MODEL INFORMATION
	AbstractModel *model = perturb.getModel();
	if(model==NULL) {
		cout<<"\nperturb:  ERROR- failed to load model.\n";
		exit(-1);
	}
	cout<<"-----------------------------------------------------------------------\n";
	cout<<"Loaded library\n";
	cout<<"-----------------------------------------------------------------------\n";
	model->printBasicInfo(cout);
	cout<<"-----------------------------------------------------------------------\n\n";

	// RUN
	perturb.run();

	//----------------------------
	// Catch any thrown exceptions
	//----------------------------
	} catch(Exception x) {
		x.print(cout);
		return(-1);
	}
	//----------------------------

	return(0);
}

//_____________________________________________________________________________
/**
 * Print the usage for this application
 */
void PrintUsage(ostream &aOStream)
{
	aOStream<<"\n\nperturb.exe:\n\n";
	aOStream<<"At least one of the following command-line options must be specified.\n\n";
	aOStream<<"Option              Argument         Action / Notes\n";
	aOStream<<"------              --------         --------------\n";
	aOStream<<"-Help, -H                            Print the command-line options for perturb.exe.\n";
	aOStream<<"-PrintSetup, -PS                     Print a default setup file for perturb.exe (setup_perturb_default.xml).\n";
	aOStream<<"-Setup, -S          SetupFileName    Specifies the name of the XML setup file for the perturb investigation.\n";
}
