# Starling Tutorial

[TOC]

## Introduction

### What is Starling

Starling is an end to end, modular, containerised UAV infrastucture  designed to facilitate the local development, testing and deployment of Single and Multi-UAV systems from simulation to the Bristol Robotics Lab Flight Arena (and hopefully beyond). It will hopefully allow for a more approachable development workflow to enable more researchers to fly UAVs in a safe, reproducable and controllable manner.

![simplearch](imgs/SimpleArch.png)

This tutorial is intended to demonstrate how to use Starling to develop and deploy a multi-uav controller.

### What Will I learn In This Tutorial

This tutorial aims to bring you from the basics of software development, to starting your own Starling project, to local testing, to flying your developed controller in the real world.

Through the development of a multi-UAV controller, you will be taught the fundamentals of Starling, and how to use it. This will include learning about UAV Control and ROS2, why we decided to use Docker and Containerisation, and the use of Kubernetes and Container Orchestration for testing. We will be providing both background discussion as well as hands on example to run.

In particular, we follow the Starling development workflow we designed for the development, testing and validation of Starling controllers.

![workflow](imgs/workflow.png)


### The Tutorial Task Scenario

You have been asked to prototype a particular scene within a drone display!

In this scene a number of drones take off and automatically fly to starting points equidistant around a circle of a given radius. They then start circling around the edge of the circle attempting to stay equidistant to their neighbours. It is determined that the vehicles have not been well tuned and can end up lagging, therefore a centralised server monitors all the vehicles and notifies them if they are lagging behind.

![task](imgs/task.png)

## How To Use This Tutorial

This tutorial is split into a set of sequential sections. Each section builds upon the tools and knowledge from previous tutorials, so it is recommended you follow them in sequence.

The tutorials themselves are mostly split between teaching theory, and then applying that theory through running some exercises or commands.

It is important that throughout this tutorial, you consider why you are being asked to run a command with those particular arguments. Don't just copy and paste verbatim!

As mentioned you will be developing a starling application alongside this tutorial. There are some parts where it will be beneficial for you to have the code open side by side.


## Contents

1. [Getting started](getting_started.md)
      - Learn Starling dependencies and how to install them

2. [ROS2 and UAV Control](ros2_uav.md)
      - Learn how UAVs are controlled
      - Learn the theory behind the Robot Operating System

3. [Docker and Containersiation](docker.md)
      - Learn what containerisation is and how its used within Starling
      - Learn basic Docker commands to run Starling containers

4. [Creating your own Starling project](creating.md)
      - Learning how to use a template to create your own Starling project

5. [Simulation and the Digital Double](simulation.md)
      - Learn about how UAVs are simulated
      - Learn how to run the BRL digital double simulator

6. [Developing the example controller with ROS2 in CPP](cpp_example_dev.md)
      - *Exercise:* Building a solution to the example scenario

7. [Local testing with Docker-Compose](testing_with_docker_compose.md)
      - Learn how to develop and test your controller against the simulator

8. [Multi-UAV flight with Kubernetes for container deployment](multiuav_kubernetes.md)
      - Learn about why Starling uses Kubernetes for Integration testing
      - Learn how to run the integration testing stack

9. [Local Integration testing with KinD Digital Double](testing_with_kind.md)
      - Learn how to deploy your application for integration testing

10. [Flying your controllers in the Flying Arena](brl_flight.md)
      - Learn about the BRL flight arena systems
      - Learn about how to develop and deploy your controller to real vehicles safely

11. [Wrapping up and next steps](next_steps.md)
      - Providing useful links and next steps after completing the tutorial