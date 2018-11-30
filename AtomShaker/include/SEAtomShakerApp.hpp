#pragma once 

#include "SBDApp.hpp"
#include "SEAtomShakerAppGUI.hpp"
#include "SBQuantity.hpp"

/// This class implements the functionality of the app

// SAMSON Element generator pro tip: add non-GUI functionality in this class. The GUI functionality should go in the SEAtomShakerAppGUI class

class SEAtomShakerApp : public SBDApp {

	SB_CLASS

public :

	/// \name Constructors and destructors
	//@{

	SEAtomShakerApp();																													///< Constructs an app
	virtual ~SEAtomShakerApp();																											///< Destructs the app

	//@}

	/// \name GUI
	//@{

	SEAtomShakerAppGUI*											getGUI() const;															///< Returns a pointer to the GUI of the app

	//@}

	void														shakeAtoms(const SBQuantity::length& distance);

};


SB_REGISTER_TARGET_TYPE(SEAtomShakerApp, "SEAtomShakerApp", "545A5360-B2DC-67B4-636E-71D243E06AA0");
SB_DECLARE_BASE_TYPE(SEAtomShakerApp, SBDApp);
