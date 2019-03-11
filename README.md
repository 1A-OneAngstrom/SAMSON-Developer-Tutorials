# SAMSON-Developer-Tutorials
Sample source code and tutorials for developing SAMSON Elements - modules for the SAMSON open platform for molecular modeling (<https://www.samson-connect.net>).

- **AtomShaker** - this SAMSON Element demonstrates how to create a simple App with GUI that shakes atoms in SAMSON.
- **EXYZImporter** - this SAMSON Element demonstrates how to create a simple Importer for an XYZ format.
- **EXYZExporter** - this SAMSON Element demonstrates how to create a simple Exporter for an XYZ format.
- **Springs** - this SAMSON Element demonstrates how to create a simple Bond Springs Interaction Model.
- **PyBindTutorial** - this SAMSON Element demonstrates how to create python bindings for a SAMSON Element. **Note:** Python and Python Scripting need to be installed (see README of this Element).  Due to this prerequisites, it is disabled by default. To enable it, uncomment the `ADD_SUBDIRECTORY( PyBindTutorial )` line in the root `CMakeLists.txt` file.