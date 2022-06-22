#  Wrapping up and next steps

[TOC]

## Wrapping up the Tutorial

Congratulations on making it to the end of this intense tutorial! 🥳🥳🎉🎉🎉

![cat](imgs/wrapup/kitten-cat.gif)


Through the Starling development workflow, you have sucessfully created your own Starling project and validated against local testing, our integration testing stack and on real vehicles.

In the process, you have hopefully learnt about the basics of UAV Control and ROS2. Why we decided to use docker and containerisation. And finally why we extended to using Kubernetes and container orchestration for software deployment to the real world.

## What Next

Now it's time for you to go do something awesome with your Starling projects! The cookiecutter templates are publically available and should cover most use cases - whether you are doing low level control testing or higher level planning.

Feel free to continue playing around with the example application from this tutorial. The solution we devise is only one of an infinite number of possible solutions. In particular, I feel you could apply some sort of optimisation procedure for the server's method of finding optimal thetas for each vehicle. I would love to see what sort of improvements you all come up with!

Finally, we share some more links for useful places to go to and other useful links. We could only cover so much in this tutorial (I know right...) and there are many nuances and details about all the tools and setups throughout all of Starling.

- For specific information, please visit our docs at [https://docs.starlinguas.dev/](https://docs.starlinguas.dev/). There you will find more detailed information about the images and setup.
- There already exists an ecosystem of applications in our github repository at [https://github.com/StarlingUAS](https://github.com/StarlingUAS). A couple of notable projects include:
    - [Syncrhonous position control](https://github.com/StarlingUAS/synchronous_position_trajectory_controller) which is a multi-vehicle trajectory follower which can follow paths submitted to a web interface. A useful setup for basic multi-vehicle path following.
    - [BRL Flight Arena](https://github.com/StarlingUAS/BRLFlightArenaGazebo) is the source for the flight arena digital double and gives examples for how to create your own gazebo worlds, as well as include custom vehicles into your Starling containers.
    - [Example UI](https://github.com/StarlingUAS/starling_ui_example) is the source for the very basic example user interface we use throughout this tutorial. As Docker cannot really run native GUI applications, a web based interface is the next best thing!
    - And many others!

We would love to hear about the projects you are developing! We would also love to receive contributions and Pull Requests for this project. This is a fully open source project, and in that spirit, if in using it you find issues with the core of Starling, please submit an issue or even fix it and submit a PR! We appreciate as much as help as we can get!

I hope you have enjoyed going through tutorial, and have found it useful. I also hope that Starling becomes the right tool for you to do your research! If you have any questions or queries about this Tutorial or Starling, I will be more than happy to anwser them at [mickey.li@bristol.ac.uk](mailto:mickey.li@bristol.ac.uk).

**Mickey Li**, Bristol Robotics Laboratory, University of Bristol, University of West England

- Website: [https://mickeyhl.li/](https://mickeyhl.li/)
- Email: [mickey.li@bristol.ac.uk](mailto:mickey.li@bristol.ac.uk)
- Github: [https://github.com/mhl787156](https://github.com/mhl787156)
- LinkedIn: [https://www.linkedin.com/in/mickeyhaolinli/](https://www.linkedin.com/in/mickeyhaolinli/)