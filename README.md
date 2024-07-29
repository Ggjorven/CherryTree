# CherryTree

**CherryTree** is a rendering project written in C++20 using the OpenGL and Vulkan API. The name CherryTree reflects the project's purpose: to experiment with various rendering techniques, much like exploring different branches of a tree. This project is in its very early stages.

## Features

- Written in C++20
- Utilizes OpenGL and Vulkan APIs
- Experiment with various rendering techniques.

## Getting Started

### Prerequisites

- C++20 compatible compiler
- Vulkan SDK (In the future I wish to help you install this.)

## Installation

### Windows

1. Clone the repository:
    ```sh
    git clone --recursive https://github.com/ggjorven/CherryTree.git
    cd PuCherryTreelse
    ```

2. Navigate to the scripts folder:
    ```sh
    cd scripts
    ```

3. Choose what you want it build to:
    - Visual Studio 17 2022:
        ```sh
        ./gen-vs2022-windows.bat
        ```
    - MinGW make files:
        ```sh
        ./gen-make-windows.bat
        ```

### Linux

1. Clone the repository:
    ```sh
    git clone --recursive https://github.com/ggjorven/CherryTree.git
    cd CherryTree
    ```

2. Navigate to the scripts folder:
    ```sh
    cd scripts
    ```

3. Generate make files:
    ```sh
    chmod +x gen-make-linux.sh
    ./gen-make-linux.sh
    ```

## Building

### Windows
- Visual Studio 17 2022:
    1. Navigate to the root of the directory
    2. Open the Pulse.sln file
    3. Start building in your desired configuration
    4. Build files can be in the bin/%Config%-windows/ folder.
    5. (Optional) Open a terminal and run the Sandbox project:
    ```sh
    ./Sandbox.exe
    ``` 
- MinGW Make:
    1. Navigate to the root of the directory
    2. Open a terminal.
    3. Call make with desired configuration (debug, release or dist):
    ```sh
    make config=release
    ```
    4. Build files can be in the bin/%Config#-linux/ folder.
    5. (Optional) Open a terminal and run the Sandbox project:
    ```sh
    make config=release
    ```

### Linux
Before you start make sure you have GLFW dependencies installed:

#### Ubuntu/Debian

```sh
sudo apt-get update
sudo apt-get install libx11-dev
sudo apt-get install libxcursor-dev
sudo apt-get install libxrandr-dev
sudo apt-get install libxinerama-dev
sudo apt-get install libxi-dev
```

#### Fedora
```sh
sudo dnf install libX11-devel
sudo dnf install libXcursor-devel
sudo dnf install libXrandr-devel
sudo dnf install libXinerama-devel
sudo dnf install libXi-devel
```

#### CentOS/RHEL
```sh
sudo yum install libX11-devel
sudo yum install libXcursor-devel
sudo yum install libXrandr-devel
sudo yum install libXinerama-devel
sudo yum install libXi-devel
```

#### Arch
```sh
sudo pacman -S libx11
sudo pacman -S libxcursor
sudo pacman -S libxrandr
sudo pacman -S libxinerama
sudo pacman -S libxi
```

#### Actual build:

1. Navigate to the root of the directory
2. Open a terminal
3. Call make with desired configuration (debug, release or dist):
```sh
make config=release
```
4. Build files can be in the bin/%Config#-linux/ folder.
5. (Optional) Open a terminal and run the Sandbox project:
```sh
chmod +x Sandbox
./Sandbox
```

## License
This project is licensed under the Apache 2.0 License. See [LICENSE](LICENSE.txt) for details.

## Contributing
Contributions are welcome! Please fork the repository and create a pull request with your changes.

## Third-Party Libraries
  - `Pulse` [https://github.com/Ggjorven/Pulse](https://github.com/Ggjorven/Pulse)
  - `spdlog` [https://github.com/gabime/spdlog/](https://github.com/gabime/spdlog/)
  - `glad` [https://github.com/Dav1dde/glad/tree/glad2](https://github.com/Dav1dde/glad/tree/glad2)