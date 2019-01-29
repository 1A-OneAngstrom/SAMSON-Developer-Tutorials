#pragma once 

#include "SBDApp.hpp"
#include "SEPyBindTutorialAppGUI.hpp"

#include "CustomStructuralGroup.hpp"

#include "SBQuantity.hpp"

/// This class implements the functionality of the app

class SEPyBindTutorialApp : public SBDApp {

	SB_CLASS

public :

	/// \name Constructors and destructors
	//@{

	SEPyBindTutorialApp();																													///< Constructs an app
	virtual ~SEPyBindTutorialApp();																											///< Destructs the app

	//@}

	/// \name GUI
	//@{

	SEPyBindTutorialAppGUI*											getGUI() const;															///< Returns a pointer to the GUI of the app

	//@}

	/// \name Custom functions
	//@{

	void															addCustomStructuralModel();

	//@}

};

SB_REGISTER_TARGET_TYPE(SEPyBindTutorialApp, "SEPyBindTutorialApp", "29049DE1-6EE0-CA2C-2B10-5641ABED7F59");
SB_DECLARE_BASE_TYPE(SEPyBindTutorialApp, SBDApp);
