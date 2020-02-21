#pragma once 

#include "SBDApp.hpp"
#include "SEEnergyConverterAppGUI.hpp"


/// This class implements the functionality of the app

// SAMSON Element generator pro tip: add non-GUI functionality in this class. The GUI functionality should go in the SEEnergyConverterAppGUI class

class SEEnergyConverterApp : public SBDApp {

	SB_CLASS

public :

	/// \name Constructors and destructors
	//@{

	SEEnergyConverterApp();																													///< Constructs an app
	virtual ~SEEnergyConverterApp();																											///< Destructs the app

	//@}

	/// \name GUI
	//@{

	SEEnergyConverterAppGUI*											getGUI() const;															///< Returns a pointer to the GUI of the app

	//@}

	/// \name Conversion
	//@{

	double																convert(const double sourceEnergy, const int sourceUnit, const int destinationUnit);

	//@}

};


SB_REGISTER_TARGET_TYPE(SEEnergyConverterApp, "SEEnergyConverterApp", "276E2B73-108E-F34E-C1BE-627CB4F6A64B");
SB_DECLARE_BASE_TYPE(SEEnergyConverterApp, SBDApp);
