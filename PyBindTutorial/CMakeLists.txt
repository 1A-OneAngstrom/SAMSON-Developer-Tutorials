SET ( PROJECT_FOLDER_NAME PyBindTutorial )
SET ( PROJECT_PATH ${ELEMENT_NAME} )
SET ( OUTPUT_NAME "SE${PROJECT_FOLDER_NAME}" )
ADD_DEFINITIONS( -DELEMENT_NAME=\"${OUTPUT_NAME}\" )

SET( OUTPUT_UUID F2078F9E-F2CB-BA72-EE86-1E01A10B63D4 )
SET( OUTPUT_UUID-VAR \"${OUTPUT_UUID}\" )
ADD_DEFINITIONS( -DSB_ELEMENT_UUID=${OUTPUT_UUID-VAR} )

MESSAGE ( "-- ++ CREATING PROJECT OR MAKEFILE ---> ${OUTPUT_UUID} : ${OUTPUT_NAME}" )

FILE ( GLOB_RECURSE ${OUTPUT_UUID}_headers include/*.hpp )
FILE ( GLOB_RECURSE ${OUTPUT_UUID}_sources source/*.cpp )
FILE ( GLOB_RECURSE ${OUTPUT_UUID}_resources resource/*.qrc )
FILE ( GLOB_RECURSE ${OUTPUT_UUID}_form form/*.ui )
	
FILE( GLOB_RECURSE ${OUTPUT_UUID}_ts resource/translations/*.ts )

INCLUDE_DIRECTORIES ( include )
INCLUDE_DIRECTORIES ( ${CMAKE_CURRENT_BINARY_DIR} )

IF(QT_WRAP_CPP)

	QT5_WRAP_CPP( ${OUTPUT_UUID}_MOC_GENERATED ${${OUTPUT_UUID}_headersToMOC} )

ENDIF(QT_WRAP_CPP)

QT5_WRAP_UI( ${OUTPUT_UUID}_UI_GENERATED ${${OUTPUT_UUID}_form} )

QT5_ADD_RESOURCES( ${OUTPUT_UUID}_RCC_GENERATED ${${OUTPUT_UUID}_resources} )

QT5_ADD_TRANSLATION( ${OUTPUT_UUID}_QM  ${${OUTPUT_UUID}_ts} )

SOURCE_GROUP ( include FILES ${${OUTPUT_UUID}_headers} )
SOURCE_GROUP ( source FILES ${${OUTPUT_UUID}_sources} )
SOURCE_GROUP ( resource FILES ${${OUTPUT_UUID}_resources} )
SOURCE_GROUP ( form FILES ${${OUTPUT_UUID}_form} )
SOURCE_GROUP ( translationFiles FILES ${${PROJECT_FOLDER_NAME}_QM} ${${OUTPUT_UUID}_ts} )
SOURCE_GROUP ( GeneratedFiles FILES ${${OUTPUT_UUID}_MOC_GENERATED} ${${OUTPUT_UUID}_UI_GENERATED} ${${OUTPUT_UUID}_RCC_GENERATED} )

####################################################
#   Python bindings thanks to pybind11
####################################################
IF( DEBUG )

	# Disable the creation of Python bindings in the Debug mode
	# since Python is not supported in the Debug mode
	SET (Python_LIBRARIES "")
	
ELSE( DEBUG )

    INCLUDE ( PythonVersion )

    MESSAGE("================================  PYTHON VERSION  ====================================")
    MESSAGE("PYTHON_MAJOR_VERSION_NUMBER  = " ${PYTHON_MAJOR_VERSION_NUMBER})
    MESSAGE("PYTHON_MINOR_VERSION_NUMBER  = " ${PYTHON_MINOR_VERSION_NUMBER})
    MESSAGE("PYTHON_PATCH_VERSION_NUMBER  = " ${PYTHON_PATCH_VERSION_NUMBER})
	MESSAGE("======================================================================================")

    SET( PYTHON_VERSION ${PYTHON_MAJOR_VERSION_NUMBER}.${PYTHON_MINOR_VERSION_NUMBER} )

    MESSAGE("                           Searching for Python " ${PYTHON_VERSION})
	MESSAGE("--------------------------------------------------------------------------------------")

    IF( UNIX )

        FIND_PACKAGE(Python3 ${PYTHON_VERSION} EXACT COMPONENTS Interpreter Development REQUIRED)

		SET( Python_FOUND 				${Python3_FOUND} )
		SET( Python_Interpreter_FOUND 	${Python3_Interpreter_FOUND} )
		SET( Python_VERSION 			${Python3_VERSION} )
		SET( Python_EXECUTABLE 			${Python3_EXECUTABLE} )
		SET( Python_LIBRARIES 			${Python3_LIBRARIES} )
		SET( Python_INCLUDE_DIRS 		${Python3_INCLUDE_DIRS} )
		SET( Python_LIBRARY_DIRS 		${Python3_LIBRARY_DIRS} )
		SET( Python_INTERPRETER_ID 		${Python3_INTERPRETER_ID} )
		SET( Python_VERSION 			${Python3_VERSION} )
		SET( Python_VERSION_MAJOR 		${Python3_VERSION_MAJOR} )
		SET( Python_VERSION_MINOR 		${Python3_VERSION_MINOR} )
		SET( Python_VERSION_PATCH 		${Python3_VERSION_PATCH} )
	
    ELSE( UNIX )

        FIND_PACKAGE(Python ${PYTHON_VERSION} EXACT COMPONENTS Interpreter Development REQUIRED)

    ENDIF( UNIX )

	MESSAGE("Python_FOUND:             " ${Python_FOUND} )
	MESSAGE("Python Interpreter found: " ${Python_Interpreter_FOUND})
	MESSAGE("Python version:           " ${Python_VERSION})
	MESSAGE("Python executable:        " ${Python_EXECUTABLE})
	MESSAGE("Python libraries:         " ${Python_LIBRARIES} )
	MESSAGE("Python include dirs:      " ${Python_INCLUDE_DIRS} )
	MESSAGE("Python libraries dirs:    " ${Python_LIBRARY_DIRS} )
	MESSAGE("Python_INTERPRETER_ID:    " ${Python_INTERPRETER_ID} )
	MESSAGE("Python_VERSION:           " ${Python_VERSION} )
	MESSAGE("Python_VERSION_MAJOR:     " ${Python_VERSION_MAJOR} )
	MESSAGE("Python_VERSION_MINOR:     " ${Python_VERSION_MINOR} )
	MESSAGE("Python_VERSION_PATCH:     " ${Python_VERSION_PATCH} )
	MESSAGE("======================================================================================")
	MESSAGE("")

	IF ( ${Python_Interpreter_FOUND} )

	    # This define is used in the code to determine 
		# whether Python bindings should be created or not
	    add_definitions(-DCREATE_PYTHON_BINDINGS)
        
	    # Set path to pybind11 headers
        SET(Pybind11_INCLUDE_DIRS "./external/pybind11/include/")
	    # include paths to python and pybind11 headers
        INCLUDE_DIRECTORIES(${Python_INCLUDE_DIRS} ${Pybind11_INCLUDE_DIRS})

	    # Set path to headers for SAMSON SDK SBQuantity and SBType* wrappers
	    SET(SAMSONSDKWRAPPERS_INCLUDE_DIRS "./external/SAMSON-SDK-wrappers/")
	    INCLUDE_DIRECTORIES(${SAMSONSDKWRAPPERS_INCLUDE_DIRS})

	ENDIF ( ${Python_Interpreter_FOUND} )
   
ENDIF( DEBUG )

####################################################

ADD_LIBRARY ( ${OUTPUT_NAME} SHARED ${${OUTPUT_UUID}_headers} ${${OUTPUT_UUID}_sources} ${${OUTPUT_UUID}_MOC_GENERATED} ${${OUTPUT_UUID}_UI_GENERATED} ${${OUTPUT_UUID}_RCC_GENERATED} ${${OUTPUT_UUID}_QM} )

TARGET_LINK_LIBRARIES (	${OUTPUT_NAME}
	                    ${QT_LIBRARIES}
						${Python_LIBRARIES}
						${OPENGL_LIBRARY}
						${SAMSON_SDK_LIBRARIES}
						)
						
SET_TARGET_PROPERTIES(${OUTPUT_NAME} PROPERTIES OUTPUT_NAME ${OUTPUT_UUID})		
						
IF( UNIX ) 
	SET_TARGET_PROPERTIES ( ${OUTPUT_NAME} PROPERTIES PREFIX "" )
ENDIF( UNIX ) 

SET_PROPERTY ( TARGET ${OUTPUT_NAME} PROPERTY FOLDER "Elements" )

SAMSON_INSTALL_ELEMENT_DIRECTORY( data/ ${OUTPUT_UUID}/Data )
SAMSON_INSTALL_ELEMENT_DIRECTORY( resource/ ${OUTPUT_UUID}/Resource )
SAMSON_INSTALL_ELEMENT_DIRECTORY( doc/ ${OUTPUT_UUID}/Documentation )

SAMSON_INSTALL_ELEMENT ( ${OUTPUT_NAME} ${OUTPUT_UUID} )
