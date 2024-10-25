# ModPlayer

![GitHub release (latest by date)](https://img.shields.io/github/v/release/realsba/ModPlayer)
![GitHub](https://img.shields.io/github/license/realsba/ModPlayer)
![GitHub issues](https://img.shields.io/github/issues/realsba/ModPlayer)

ModPlayer is a versatile audio playback library designed for MOD files. 
The project aims to provide efficient and high-quality playback of tracker music, leveraging the capabilities of each platform to deliver an optimal user experience.

Features
MOD File Support: Play a wide range of MOD file formats, enabling users to enjoy classic tracker music.
Lightweight and Efficient: Optimized for performance, ensuring smooth playback on resource-constrained devices like ESP32.

Future Plans
In future releases, it aims to introduce customizable options for fine-tuning playback settings and effects to better meet user preferences.
This will include features such as:
- Volume control for adjusting playback levels.
- Various audio effects, including reverb and chorus, that users can enable or modify.
- Speed control for adjusting the playback rate of tracks.
- Sound filters for enhancing audio quality.
These enhancements will empower users to tailor their listening experience according to their individual needs.

## Installation

### Prerequisites

- CMake 3.25 or higher
- SDL2

### Build Instructions

```bash
mkdir cmake-build && cd cmake-build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
````

## Usage
```bash
./ModPlayer <filename>
```

## Project Structure
- src Contains the source code files for the server

## Technologies Used
- C++ (C++23)
- SDL2

## Contributing
Contributions are welcome! Feel free to open an issue or submit a pull request.

## License
This project is licensed under the MIT License - see the [LICENSE](https://github.com/realsba/ModPlayer/blob/main/LICENSE) file for details.

## Author
- Bohdan Sadovyak

## Bugs/Issues
Please report any bugs or issues [here](https://github.com/realsba/ModPlayer/issues).