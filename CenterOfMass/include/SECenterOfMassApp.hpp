#pragma once 

#include "SBDApp.hpp"
#include "SECenterOfMassAppGUI.hpp"
#include "SBAtom.hpp"
#include "SAMSON.hpp"


/// This class implements the functionality of the app

// SAMSON Element generator pro tip: add non-GUI functionality in this class. The GUI functionality should go in the SECenterOfMassAppGUI class

class SECenterOfMassApp : public SBDApp {

	SB_CLASS

public :

	/// \name Constructors and destructors
	//@{

	SECenterOfMassApp();																													///< Constructs an app
	virtual ~SECenterOfMassApp();																											///< Destructs the app

	//@}

	/// \name GUI
	//@{

	SECenterOfMassAppGUI*											getGUI() const;															///< Returns a pointer to the GUI of the app

	//@}

	void															computeCenterOfMass();

	void															onStructuralEvent(SBStructuralEvent* event);

	SBPointerIndexer<SBAtom>										atomIndexer;

	SBPosition3														centerOfMass;
	SBPosition3*													positionArray;

};


SB_REGISTER_TARGET_TYPE(SECenterOfMassApp, "SECenterOfMassApp", "DD266BCD-9C5F-6187-648B-666702632E4E");
SB_DECLARE_BASE_TYPE(SECenterOfMassApp, SBDApp);
