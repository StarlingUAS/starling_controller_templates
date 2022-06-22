# Starling Controller Generator

This repository contains a number of template repositories for building up your own custom Starling compatible controller. This is designed in a modular way which allows you to mix and match different elements as you need.

The idea is that a base Starling project is generated, but it contains no ROS nodes. Then you add whatever cpp/python or message custom ros packages afterwards.

## Tutorial

This repository is used within the tutorial: [https://starlinguas.github.io/starling_controller_templates/](https://starlinguas.github.io/starling_controller_templates/)

For more detailed explanation of usage, please go to [section 4 of the tutorial](https://starlinguas.github.io/starling_controller_templates/creating/)

## Prerequisits

### Install cookiecutter
The template generation uses the [`cookiecutter`](https://cookiecutter.readthedocs.io/en/stable/README.html) tool for generating custom projects from a template.

Then run:
```sh
python3 -m pip install --user cookiecutter
# or
easy_install --user cookiecutter
```
> See [cookiecutter installation](https://cookiecutter.readthedocs.io/en/stable/installation.html) for further details on different platforms.

This will give you access to the `cookiecutter` command line interface.

### Install Starling Dependencies

Other than that you will need the prerequisits for Starling

### Sign up for Docker Hub and Github

Both are optional but suggested to make the most of the system.

## Constructing your controller

### Generating the base Starling Project

The first step is to build your own Starling project. The following will start the process of using the template to generate a staring project. In your workspace, run the following command.

```bash
cookiecutter https://github.com/StarlingUAS/starling_controller_templates.git --directory starling_template
```

It will follow by asking you to fill in a number of details. The value in the square brackets indicates the default value if you choose not to enter anything. Press Enter to go on to the next one. The inputs include

- Full Name - Your name
- Project Name - The name you have given to this Starling Project
- Github Username - Optionally your github username for filling in the README and metadata
- Docker Username - Optionally your docker hub username which is used for naming the Starling image. Will be used to upload to if you wish to push it online.
- Docker Image Name - The name of the Starling image that this repository produces
- Docker Image Name Full - An autogenerated name based on your username and image name, you can leave as the default unless you really want to change it.

Once complete, the project will be generated into a folder named by your `project_name`. For example, the default project with name `starling_controller` produces a project with the following structure:

```
starling_controller
|-- buildtools
    |-- docker-bake.hcl
|-- deployment
    |-- docker-compose.yml
    |-- kubernetes.yaml
|-- starling_controller
    |-- run.sh
|-- Dockerfile
|-- LICENSE
|-- Makefile
|-- README.md
```

We have the following folders and files.

- *starling_controller* will be populated by user created ros packages. Anything in this folder is directly  copied to the Dockerfile and built.
- *deployment* contains a sample docker-compose file which runs a default simulation stack, and a sample kubernetes file for deployment, both will most definitely need to be edited.
- *buildtools* contains the specification that docker uses to build the container. It contains the naming for the docker image.
- *Dockerfile* contains the dockerfile which specifies the build steps for this project. It already specifies the installation of a number of dependencies, including [libInterpolate](https://github.com/CD3/libInterpolate) interpolation library.

Once generated, the *Makefile* can be used to build and run commands:

```sh
make # Will build the project
make run # Will build and run the container
make run_bash # Will build and run the container, putting you in a bash shell inside it.
make help # Shows the help screen
```

This should successfuly build your project container which you can try and run or inspect. Currently it has no funcionality so nothing can happen. Have a look inside the container using `make run_bash`.

> *Note* On windows you can either use WSL or have a look at some of the solutions [in this link](https://stackoverflow.com/questions/2532234/how-to-run-a-makefile-in-windows)

### Adding Nodes to your project

The generated project has no functionality right now. This repository contains other templates which will generate rosnodes for you. In particular

- *cpp_ros2_node_onboard_template*: Generates a ROS2 node, designed for running onboard the vehicle written in CPP.
- *python_ros2_node_offboard_template*: Generates a ROS2 node, designed for running offboard (central server) written in Python
- *ros2_msgs_template*: Generates a ROS2 msgs package which can be used by any ROS2 package within this container.

These nodes can be added to your project using the following cookiecutter commands. Note that the packages should be generated into the `starling_project_name` directory of the base Starling project. Each of these commands are single line commands.

```sh
# CPP Onboard
cookiecutter https://github.com/StarlingUAS/starling_controller_templates.git --directory cpp_ros2_node_onboard_template -o starling_controller/starling_controller
```

```sh
# Python Offboard
cookiecutter https://github.com/StarlingUAS/starling_controller_templates.git --directory python_ros2_node_offboard_template -o starling_controller/starling_controller
```

```sh
# Messages
cookiecutter https://github.com/StarlingUAS/starling_controller_templates.git --directory ros2_msgs_template -o starling_controller/starling_controller
```

Similar to the generating of the base project, these will ask a number of questions to you during the generation. In particular it will ask what the `package_name` is which will become the name of that particular node package.

> *Note* convention for msg packages is to have a package name of format `<mymessages>_msgs`, e.g. `circle_experiment_msgs`.

> *Note* For those familiar with ROS1, it is ROS2 convention to keep messages in a seperate package to the ros nodes themselves.

> *Note* See below for the default example functionality that these template provide.

This should give you a file tree that looks something like the following (of course with your package names instead)

```tree
starling_controller
|-- buildtools
    |-- docker-bake.hcl
|-- deployment
    |-- docker-compose.yml
    |-- kubernetes.yaml
|-- starling_controller
    |-- template_onboard_controller_cpp
        |-- ...
    |-- template_offboard_controller_python
        |-- ...
    |-- template_msgs
        |-- ...
    |-- run.sh
|-- Dockerfile
|-- LICENSE
|-- Makefile
|-- README.md
```

That being said, the nodes can be run standalone for your own projects, one at a time, or whenever you need a new node within your project.

Once these packages have been placed within the correct directory inside the Starling project, you can simply run `make` to check that they are successfully built.

## Default Example Template Functionality

### The Tutorial Task Scenario

By default, the templates are used to solve the following problem.

You have been asked to prototype a particular scene within a drone display!

In this scene a number of drones take off and automatically fly to starting points equidistant around a circle of a given radius. They then start circling around the edge of the circle attempting to stay equidistant to their neighbours. It is determined that the vehicles have not been well tuned and can end up lagging, therefore a centralised server monitors all the vehicles and notifies them if they are lagging behind.

![task](tutorial/imgs/task.png)

### What is in the templates

The set of node templates above should create you a project which runs the example scenario specifically developed for the purpose of this tutorial. This example has been designed to show the development of an onboard and an offboard container, as well as demonstratee communication between the two. The scenario is as follows:

1. We have \(n\) drones which we would like to fly equidistant around a circle of fixed radius at a initial velocity.
2. A central server will send each drone an id \(i<n\) to determine its start location around the circle.
3. Once received the drones will start flying around the circle and send its current position to the server.
4. The server collates the drones informations to determine if any of the drones are lagging or ahead of where they should be. This ideal position is sent back to each drone.
5. The drone adjusts its velocity to try based on the error to match with the ideal.

With this in mind we can quickly run through what is in each of the ros node templates.

> *Note:* More detail about the actual functionality within these nodes will be in [this tutorial section](cpp_example_dev.md)

### `cpp_ros2_node_onboard_template`

```tree
|-- CMakeLists.txt
|-- include
|   |-- controller.hpp
|   |-- main.hpp
|   `-- state.hpp
|-- launch
|   `-- template_cpp_node.launch.xml
|-- package.xml
`-- src
    |-- controller.cpp
    `-- main.cpp
```

This node runs onboard the vehicle and interfaces with MAVROS. It contains a state machine with functionality to arm, takeoff, land, loiter and takes care of safety functionality.

- `CMakeLists.txt`: contains the instructions to build this rosnode. This includes specifying dependencies and extra libraries (e.g. messages such as `geometry_msgs` or external dependencies). It also specifies the name of the binary containing all of your functionality. By default this is `controller`.
- `include` and `src`: In CPP, your code files are split into header files (specifying object definitions) and source files (specifying object functionality), these are stored here
- `launch`: contains a ROS `launch` file. We use XML notation to describe how your rosnode gets launched, including extra parameters or other changes you want to make at runtime instead of buildtime. This is what gets run to run your rosnode
- `package.xml`: ROS2 Metadata file specifying ros2 dependencies of your project.

As a brief overview of the code files:

- `main.hpp` and `main.cpp`: Contains the program entrypoint function and the core of the ros node. It contains all of the core functionality to fly a vehicle as well as the state machine. It includes the user controller specified in `controller.hpp` to be expected to run during the `execution` phase of the state machine.
- `controller.hpp` and `controller.cpp`: For the majority of simple applications, a user should only need to provide their own version of these files. The controller contains an initialisation and loop function which a user can fill in.
- `state.hpp`: A header only file containing the states of the state machine.

### `python_ros2_node_offboard_template`

```tree
|-- package.xml
|-- resource
|   `-- template_python_node
|-- setup.cfg
|-- setup.py
|-- template_python_node
|   |-- __init__.py
|   `-- main.py
`-- test
    |-- test_copyright.py
    |-- test_flake8.py
    `-- test_pep257.py
```

This node runs offboard on the central server. It is designed to run on its own with no external dependence on anything outside of the application.

- `package.xml`: ROS2 Metadata file specifying ros2 dependencies of your project.
- `resource`: A python ros package special folder, no need to touch
- `setup.cfg`: Configuration file specifying where key resources are
- `setup.py`: The python equivalent of `CMakeLists.txt` and contains the instructions to build this rosnode. It specifies which resources are copied over and available to the rosnode at runtime. Also specifies the name of the binary, and which function it is intended to run. By default this is `controller`
- `<your rosnode name>` e.g. `template_python_node`: The source directory for your python files.
- `test`: A number of testing utilities which can be run with pytest. Currently not used.

As a brief overview of code files:

- `main.py`: Contains a ros node which uses a timer to repeat poll the current state of vehicles on the network at given intervals. It then performs the calculation of ideal vehicle location and sends that to the vehicles.

### `ros2_msgs_template`

```tree
|-- CMakeLists.txt
|-- msg
|   |-- NotifyVehicles.msg
|   `-- TargetAngle.msg
`-- package.xml
```

This node is purely for specifying and building the custom ros messages in our application. Any application which uses these messages need a compiled version of this node.

- `CMakeLists.txt`: contains the instructions to build the messages. Any extra messages or services need to be added to the CMakeLists.
- `msg`: A list of specified custom messages.
- `package.xml`: ROS2 Metadata file specifying ros2 dependencies of your project.

### Dockerfile

As mentioned in the [previous tutorial](docker.md), a Dockerfile is used as a recipe to build your controller docker container.

The Dockerfile in this template contains the command line instructions to build your controller.

By default it will install a number of useful libraries for compatibility.

> If you need any new libraries, you will have to add their installation here.

It then essentially copies in all of the rosnodes specified within the project name directory and runs them through the standard ROS2 build tool named `colcon`.

It also copies over the `run.sh` file which the Dockerfile will run on container startup. Therefore the `run.sh` should have the instructions for running your applications.

Thankfully you do not need to run `docker build` as we have setup an automatic special build system which is wrapped up inside the `Makefile`.

## Running your new project

With your project now constructed, you can now re-run your container with the same `make` commands as earlier.

```sh
cd <Your Application Name> # Go into the your new Starling application directory
make run # Will build and run the container
```

> This will build a container called `<Docker Username>/<Docker Image Name>` with tag latest e.g. `myname/starling_template:latest`

This will build start the onboard controller by default, but it will start complaining that it hasn't received any state or position messages for initialisation. This is normal for now!

If you want to start the offboard controller, you can add the extra option `ENV="-e OFFBOARD=true"` to the make command like so `make run ENV="-e OFFBOARD=true"`. Where it will start trying to identify the number of vehicles on the network, but of course it cannot find any!

You can have a look inside both container using `make run_bash`.

## Initialising Git

Optionally, at this point you can start version controller on your project in order to save your progress. To initalise git and create your first commit, go to the root of your project and run:

```bash
git init
git add -A
git commit -m "Initial Commit"
```

If you want to push this code onto github, you can follow [this tutorial](https://www.digitalocean.com/community/tutorials/how-to-push-an-existing-project-to-github). In short, create an empty github repository of the same name in your github account, then change the remote locally:

```bash
git remote add origin <remote repository URL>
git remote -v
git push origin master
```
