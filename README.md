# PETAce-Network

## Introduction

PETAce-Network defines abstract network communication interfaces.
It is one of the many components in [the framework PETAce](https://github.com/tiktok-privacy-innovation/PETAce).

Currently, PETAce-Network instantiate the network communication interface using the socket protocol.

## Requirements

| System | Toolchain                                             |
|--------|-------------------------------------------------------|
| Linux  | Clang++ (>= 5.0) or GNU G++ (>= 5.5), CMake (>= 3.15) |

| Optional dependency                                    | Tested version | Use                    |
|--------------------------------------------------------|----------------|------------------------|
| [GoogleTest](https://github.com/google/googletest)     | 1.12.1         | For running tests      |

## Building PETAce-Network

We assume that all commands presented below are executed in the root directory of PETAce-Network.

To build PETAce-Network library (optionally with test and example):

```bash
cmake -S . -B build -DNETWORK_BUILD_TEST=ON -DNETWORK_BUILD_EXAMPLE=ON
cmake --build build
```

Output binaries can be found in `build/lib/` and `build/bin/` directories.

| Compile Options             | Values        | Default | Description                                         |
|-----------------------------|---------------|---------|-----------------------------------------------------|
| `CMAKE_BUILD_TYPE`          | Release/Debug | Release | Debug mode decreases run-time performance.          |
| `NETWORK_BUILD_SHARED_LIBS` | ON/OFF        | OFF     | Build a shared library if set to ON.                |
| `NETWORK_BUILD_EXAMPLE`     | ON/OFF        | ON      | Build C++ example if set to ON.                     |
| `NETWORK_BUILD_TEST`        | ON/OFF        | ON      | Build C++ test if set to ON.                        |
| `NETWORK_BUILD_DEPS`        | ON/OFF        | ON      | Download and build unmet dependencies if set to ON. |

## Running the PETAce-Network protocol

Here we give a simple example to run our protocol.

To run as Party A:

```shell
./build/bin/network_example 127.0.0.1 8899 127.0.0.1 8890
```

To run as Party B:

```shell
./build/bin/network_example 127.0.0.1 8890 127.0.0.1 8899
```

## Contribution

Please check [Contributing](CONTRIBUTING.md) for more details.

## Code of Conduct

Please check [Code of Conduct](CODE_OF_CONDUCT.md) for more details.

## License

This project is licensed under the [Apache-2.0 License](LICENSE).

## Citing PETAce

To cite PETAce in academic papers, please use the following BibTeX entries.

### Version 0.1.0

```tex
    @misc{petace,
        title = {PETAce (release 0.1.0)},
        howpublished = {\url{https://github.com/tiktok-privacy-innovation/PETAce}},
        month = July,
        year = 2023,
        note = {TikTok Pte. Ltd.},
        key = {PETAce}
    }
```
