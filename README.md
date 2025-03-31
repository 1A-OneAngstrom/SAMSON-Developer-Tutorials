# SAMSON Developer Tutorials

Sample source code and tutorials for developing SAMSON Extensions - modules for the [SAMSON](https://www.samson-connect.net), open platform for molecular modeling.

See [SAMSON Developer Guide - Tutorials](https://documentation.samson-connect.net/developers/latest/tutorials/) for more information and the description of these samples.

## SAMSON Extension samples

### General

- [EnergyConverter](EnergyConverter) - how to work with SAMSON units through implementing an [app](https://documentation.samson-connect.net/developers/latest/apps/) that performs energy conversion.

### Apps

- [AtomShaker](AtomShaker) - how to create a simple [app](https://documentation.samson-connect.net/developers/latest/apps/) with GUI that shakes atoms.
- [Barycenter](Barycenter) - how to integrate external programs in SAMSON extensions.

### Signals, events, and slots

- [CenterOfMass](CenterOfMass) - how to process signals and events on an example of an interactive computation of the center of mass in an [app](https://documentation.samson-connect.net/developers/latest/apps/).

### Importers

- [EXYZImporter](EXYZImporter) - how to create a simple [importer](https://documentation.samson-connect.net/developers/latest/importers/) for an XYZ format.

### Exporters

- [EXYZExporter](EXYZExporter) - how to create a simple [exporter](https://documentation.samson-connect.net/developers/latest/exporters/) for an XYZ format.

### Visual models

- [VanDerWaals](VanDerWaals) - how to implement a simple van der Waals [visual model](https://documentation.samson-connect.net/developers/latest/modeling-and-simulation/#visual-models).

### Editors

- [AtomPusher](AtomPusher) - how to create a simple [editor](https://documentation.samson-connect.net/developers/latest/editors/) that pushes atoms.
- [PathGenerator](PathGenerator) - how to create an [editor](https://documentation.samson-connect.net/developers/latest/editors/) that allows users to create node paths in the viewport.

### Interaction models and State updaters

- [Springs](Springs) - how to create a simple Bond Springs [interaction model](https://documentation.samson-connect.net/developers/latest/modeling-and-simulation/#interaction-models).
- [SteepestDescent](SteepestDescent) - how to create a [state updater](https://documentation.samson-connect.net/developers/latest/modeling-and-simulation/#state-updaters).
- [MonteCarlo](MonteCarlo) - how to implement a simple exploration method based on a Metropolis Monte Carlo approach.

### Python bindings

- [PyBindTutorial](PyBindTutorial) - how to create python bindings for a SAMSON Extension. **Note:** Python path needs to be specified when building this extension. Due to this prerequisite, it is disabled by default. To enable it, uncomment the `ADD_SUBDIRECTORY( PyBindTutorial )` line in the root `CMakeLists.txt` file. See [PyBindTutorial/README.md](PyBindTutorial/README.md).
