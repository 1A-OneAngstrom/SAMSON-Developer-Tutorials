#pragma once 

#include "SBDApp.hpp"
#include "SEBarycenterAppGUI.hpp"


/// This class implements the functionality of the app

// SAMSON Extension generator pro tip: add non-GUI functionality in this class. The GUI functionality should go in the SEBarycenterAppGUI class

class SB_EXPORT SEBarycenterApp : public SBDApp {

	SB_CLASS

public:

	/// \name Constructors and destructors
	//@{

	SEBarycenterApp();																													///< Constructs an app
	virtual ~SEBarycenterApp();																											///< Destructs the app

	//@}

	/// \name GUI
	//@{

	SEBarycenterAppGUI*											getGUI() const;															///< Returns a pointer to the GUI of the app

	//@}

	std::string													compute();

};


SB_REGISTER_TARGET_TYPE(SEBarycenterApp, "SEBarycenterApp", "37ED1FB7-BCB1-6DBA-A0B5-30566981528E");
SB_DECLARE_BASE_TYPE(SEBarycenterApp, SBDApp);
