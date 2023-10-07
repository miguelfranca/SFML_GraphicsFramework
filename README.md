## Installation
1 - Run `apt-get install g++` to install g++ 

2 - Download the SFML SDK from: https://www.sfml-dev.org/download/sfml/2.5.1/,
unpack it and copy the files to your preferred location

3 - Create the following environment variable:

```bash
  SFML_ROOT="<path-to-SFML-folder>"
```

4 - Update your library path with:

```bash
  LD_LIBRARY_PATH=$LD_LIBRARY_PATH:<path-to-SFML-folder>/lib/
```

5 - Download/clone this repository.

### Running

Run the template project in `template/` with:
```bash
run
```
