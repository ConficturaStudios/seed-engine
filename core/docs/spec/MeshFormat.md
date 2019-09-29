# .mesh File Format Specification

The .mesh file format is a binary file format used for storing 3D model data. To generate these files, data can be transferred from other standard formats (.obj, .dae, .fbx, etc.) using the Seed Engine Editor. Within the file, the following vertex data can be stored:

- Vertex Positions
- Vertex Normals
- Vertex UV Coordinates
- Vertex Colors
- Vertex Bone Weights
- Vertex Morph Targets

This data is stored within the file in Big Endian format.

## File Structure

### Header
