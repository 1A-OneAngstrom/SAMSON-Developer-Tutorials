#pragma once 

#include "SBMInteractionModelParticleSystem.hpp"

#include "SBBaseEvent.hpp"
#include "SBDocumentEvent.hpp"
#include "SBStructuralEvent.hpp"
#include "SBBond.hpp"


/// This class implements an interaction model

class SESpringsInteractionModel : public SBMInteractionModelParticleSystem {

	SB_CLASS

public :

	/// \name Constructors and destructors
	//@{

	SESpringsInteractionModel();																													///< Builds an interaction model					
	SESpringsInteractionModel(SBParticleSystem* particleSystem);																					///< Builds an interaction model 
	virtual ~SESpringsInteractionModel();																											///< Destructs the interaction model

	//@}

	/// \name Serialization
	//@{

	virtual bool												isSerializable() const;													///< Returns true when the class is serializable

	virtual void												serialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer, const SBVersionNumber& sdkVersionNumber = SB_SDK_VERSION_NUMBER, const SBVersionNumber& classVersionNumber = SBVersionNumber(1, 0, 0)) const;		///< Serializes the node
	virtual void												unserialize(SBCSerializer* serializer, const SBNodeIndexer& nodeIndexer, const SBVersionNumber& sdkVersionNumber = SB_SDK_VERSION_NUMBER, const SBVersionNumber& classVersionNumber = SBVersionNumber(1, 0, 0));			///< Unserializes the node

	//@}

	/// \name Topology
	//@{

	virtual	void												eraseImplementation();													///< Erases the interaction model

	//@}

	/// \name Interactions									
	//@{

	virtual void												initializeInteractions();												///< Initializes the interaction model
	virtual void												updateInteractions();													///< Updates the interaction model

	//@}

	/// \name Rendering
	//@{

	virtual void												display();																///< Displays the interaction model
	virtual void												displayForShadow();														///< Displays the interaction model for shadow purposes
	virtual void												displayForSelection();													///< Displays the interaction model for selection purposes

	virtual void												expandBounds(SBIAPosition3& bounds) const;								///< Expands the bounds to make sure the interaction model fits inside them

	virtual void												collectAmbientOcclusion(const SBPosition3& boxOrigin, const SBPosition3& boxSize, unsigned int nCellsX, unsigned int nCellsY, unsigned int nCellsZ, float* ambientOcclusionData);		///< To collect ambient occlusion data

	//@}

	/// \name Events
	//@{

	virtual void												onBaseEvent(SBBaseEvent* baseEvent);									///< Handles base events
	virtual void												onDynamicalEvent(SBDynamicalEvent* dynamicalEvent);						///< Handles dynamical events
	virtual void												onDocumentEvent(SBDocumentEvent* documentEvent);						///< Handles document events
	virtual void												onStructuralEvent(SBStructuralEvent* documentEvent);					///< Handles structural events

	//@}

	unsigned int 												setBondSpringsModel();
	void														setBondSpringStiffness(double stiffness);

private:

	void														computeBondSpringsInteractions();

	SBPointerIndexer<SBStructuralParticle> const*				particleIndex;

	bool														initializeNeeded;
	bool														isSpringModelSet;
	double														bondSpringStiffness;													///< the stiffness of bond springs

	SBQuantity::kJPerMol										energyBondSprings;														///< bond stretch energy

	SBVector<SBQuantity::length>								springLengthVector;														///< the equilibrium length
	SBVector<SBBond*>											springBondVector;														///< vector of all bonds in the selected system

};


SB_REGISTER_TARGET_TYPE(SESpringsInteractionModel, "SESpringsInteractionModel", "33F5E835-A53E-EFC1-EEAA-E94B84B6915D");
SB_DECLARE_BASE_TYPE(SESpringsInteractionModel, SBMInteractionModelParticleSystem);
