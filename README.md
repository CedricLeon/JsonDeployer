# JsonDeployer

Little soft use to copy a **JSON** file in many directories for video extracts (**Naostage**).

## Build

````bash
git clone https://github.com/Naostage/JsonDeployer.git
mkdir build && cd build
cmake -DCMAKE_PREFIX_PATH=path_to_your_Qt5_package ..
./jsonDeployer -i "source_file_path" -d "target_directory_path"
````

## Help

To use **JsonDeployer** you have to precise your source file and your target directory;

You can use **-h** ou **--help** option to visualize available options : 

````bash
Naostage Json File Deployer

Options:
  -h, --help                            Displays help on commandline options.
  --help-all                            Displays help including Qt specific
                                        options.
  -i, --input <Json file>               Source Json file to copy
  -d, --destination <Target directory>  Target directory where json file will
                                        be copied
  -f, --force                           Overwrite existing files.
````

You can use **--force** option if you want to overwrite a file which already exist.