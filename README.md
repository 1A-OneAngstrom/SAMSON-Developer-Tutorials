# SAMSON-Developer-Tutorials
Sample source code and tutorials for developing SAMSON Elements - modules for the [SAMSON](<https://www.samson-connect.net>) open platform for molecular modeling (<https://www.samson-connect.net>).

List of SAMSON Element samples:

- **AtomShaker** - a sample demonstrating how to create a simple App with GUI that shakes atoms.
- **AtomPusher** - a sample demonstrating how to create a simple Editor that pushes atoms.
- **CenterOfMass** - a sample demonstrating how to process signals and events on an example of an interactive computation of the center of mass.
- **EnergyConverter** - a sample demonstrating how to work with SAMSON units through implementing an app that performs energy conversion.
- **EXYZImporter** - a sample demonstrating how to create a simple Importer for an XYZ format.
- **EXYZExporter** - a sample demonstrating how to create a simple Exporter for an XYZ format.
- **Springs** - a sample demonstrating how to create a simple Bond Springs Interaction Model.
- **SteepestDescent** - a sample demonstrating how to create a state updater.
- **MonteCarlo** - a sample demonstrating how to implement a simple exploration method based on a Metropolis Monte Carlo approach.
- **PyBindTutorial** - a sample demonstrating how to create python bindings for a SAMSON Element. **Note:** Python and Python Scripting need to be installed (see README of this Element).  Due to this prerequisites, it is disabled by default. To enable it, uncomment the `ADD_SUBDIRECTORY( PyBindTutorial )` line in the root `CMakeLists.txt` file.
