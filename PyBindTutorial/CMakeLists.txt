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
SET(PYTHON_VERSION 3.5)
FIND_PACKAGE( PythonInterp ${PYTHON_VERSION} REQUIRED )
MESSAGE("PYTHONINTERP_FOUND:        " ${PYTHONINTERP_FOUND})
MESSAGE("PYTHON_VERSION_STRING:     " ${PYTHON_VERSION_STRING})
MESSAGE("Include dirs of Python:    " ${PYTHON_INCLUDE_DIRS} )
MESSAGE("Libs of Python:            " ${PYTHON_LIBRARIES} )

IF ( PYTHONINTERP_FOUND )

    # set PYTHON_INSTALL_PREFIX, PYTHON_EXECUTABLE, PYTHON_INCLUDE_DIRS variables using python
	IF( UNIX )
	    EXECUTE_PROCESS(COMMAND python3 -c "import sys; print(sys.prefix)"        OUTPUT_VARIABLE PYTHON_INSTALL_PREFIX       OUTPUT_STRIP_TRAILING_WHITESPACE)
		EXECUTE_PROCESS(COMMAND which python3        OUTPUT_VARIABLE PYTHON_EXECUTABLE           OUTPUT_STRIP_TRAILING_WHITESPACE)
		# set PYTHON_INCLUDE_DIRS variable using python: distutils.sysconfig.get_python_inc()   or  distutils.sysconfig.get_config_var(\"INCLUDEPY\")
		EXECUTE_PROCESS(COMMAND python3 -c "from distutils.sysconfig import get_python_inc; print(get_python_inc())"
			OUTPUT_VARIABLE PYTHON_INCLUDE_DIRS         OUTPUT_STRIP_TRAILING_WHITESPACE)
	ELSE( UNIX )
	    ### Windows: python3 is named python in Anaconda
		EXECUTE_PROCESS(COMMAND python  -c "import sys; print(sys.prefix)"        OUTPUT_VARIABLE PYTHON_INSTALL_PREFIX       OUTPUT_STRIP_TRAILING_WHITESPACE)
		EXECUTE_PROCESS(COMMAND where python         OUTPUT_VARIABLE PYTHON_EXECUTABLE           OUTPUT_STRIP_TRAILING_WHITESPACE)
		# set PYTHON_INCLUDE_DIRS variable using python: distutils.sysconfig.get_python_inc()   or  distutils.sysconfig.get_config_var(\"INCLUDEPY\")
		EXECUTE_PROCESS(COMMAND python  -c "from distutils.sysconfig import get_python_inc; print(get_python_inc())"
			OUTPUT_VARIABLE PYTHON_INCLUDE_DIRS         OUTPUT_STRIP_TRAILING_WHITESPACE)
	ENDIF( UNIX )

	# set PYTHON_LIBRARIES variable using python (works only with Anaconda Python installation)
	IF( UNIX )
	    IF( APPLE )
		    ## for Anaconda installation
			#EXECUTE_PROCESS(COMMAND python3 -c "import sys; from distutils import sysconfig; sys.stdout.write(\"/\".join(map(sysconfig.get_config_var, (\"LIBDIR\", \"LDLIBRARY\"))))"
			#    OUTPUT_VARIABLE PYTHON_LIBRARIES        OUTPUT_STRIP_TRAILING_WHITESPACE)

			## for Homebrew installation
			EXECUTE_PROCESS(COMMAND python3 -c "import sys; from distutils import sysconfig; sys.stdout.write(\"/\".join( [sysconfig.get_config_var(\"LIBDIR\"), \"libpython3.6m.dylib\"] ) )"
				OUTPUT_VARIABLE PYTHON_LIBRARIES        OUTPUT_STRIP_TRAILING_WHITESPACE)
			#SET (PYTHON_LIBRARIES "/usr/local/opt/python3/Frameworks/Python.framework/Versions/3.6/lib/libpython3.6m.dylib")
		ELSE()
		    EXECUTE_PROCESS(COMMAND python3 -c "import sys; from distutils import sysconfig; sys.stdout.write(\"/\".join(map(sysconfig.get_config_var, (\"LIBDIR\", \"INSTSONAME\"))))"
				OUTPUT_VARIABLE PYTHON_LIBRARIES        OUTPUT_STRIP_TRAILING_WHITESPACE)
		ENDIF( APPLE )
	ELSE( UNIX )
	    ### Windows: python3 is named python in Anaconda
		EXECUTE_PROCESS(COMMAND python -c "import sys; from distutils import sysconfig; print(sysconfig.get_config_var(\"VERSION\"))"
			OUTPUT_VARIABLE PYTHON_CONFIG_VERSION        OUTPUT_STRIP_TRAILING_WHITESPACE)
		SET (PYTHON_LIBRARIES "${PYTHON_INSTALL_PREFIX}\\libs\\python${PYTHON_CONFIG_VERSION}.lib")
	ENDIF( UNIX )

	MESSAGE("Install prefix of Python: " ${PYTHON_INSTALL_PREFIX} )
	MESSAGE("Python executable:        " ${PYTHON_EXECUTABLE} )
	MESSAGE("Include dirs of Python:   " ${PYTHON_INCLUDE_DIRS} )
	MESSAGE("Libs of Python:           " ${PYTHON_LIBRARIES} )

	# set path to pybind11 headers
	SET(PYBIND11_INCLUDE_DIRS "./external/pybind11/include/")

	# include paths to python and pybind11 headers
	INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_DIRS} ${PYBIND11_INCLUDE_DIRS})

ENDIF ( PYTHONINTERP_FOUND )

####################################################

ADD_LIBRARY ( ${OUTPUT_NAME} SHARED ${${OUTPUT_UUID}_headers} ${${OUTPUT_UUID}_sources} ${${OUTPUT_UUID}_MOC_GENERATED} ${${OUTPUT_UUID}_UI_GENERATED} ${${OUTPUT_UUID}_RCC_GENERATED} ${${OUTPUT_UUID}_QM} )

IF (PYTHONINTERP_FOUND)

    add_definitions(-DCREATE_PYTHON_BINDINGS) # This define is used in the code to determine whether Python bindings should be created or not

	TARGET_LINK_LIBRARIES (	${OUTPUT_NAME}
		                    ${QT_LIBRARIES}
							${PYTHON_LIBRARIES}
							${OPENGL_LIBRARY}
							${SAMSON_SDK_LIBRARIES}
							)

ELSE (PYTHONINTERP_FOUND)

    TARGET_LINK_LIBRARIES (	${OUTPUT_NAME}
		                    ${QT_LIBRARIES}
							${OPENGL_LIBRARY}
							${SAMSON_SDK_LIBRARIES}
							)

ENDIF (PYTHONINTERP_FOUND)
						
SET_TARGET_PROPERTIES(${OUTPUT_NAME} PROPERTIES OUTPUT_NAME ${OUTPUT_UUID})		
						
IF( UNIX ) 
	SET_TARGET_PROPERTIES ( ${OUTPUT_NAME} PROPERTIES PREFIX "" )
ENDIF( UNIX ) 

SET_PROPERTY ( TARGET ${OUTPUT_NAME} PROPERTY FOLDER "Elements" )

SAMSON_INSTALL_ELEMENT_DIRECTORY( data/ ${OUTPUT_UUID}/Data )
SAMSON_INSTALL_ELEMENT_DIRECTORY( resource/ ${OUTPUT_UUID}/Resource )
SAMSON_INSTALL_ELEMENT_DIRECTORY( doc/ ${OUTPUT_UUID}/Documentation )

SAMSON_INSTALL_ELEMENT ( ${OUTPUT_NAME} ${OUTPUT_UUID} )
