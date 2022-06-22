# Flying your controllers in the Flying Arena

Now we reach the final step, running your controllers on the real vehicles. By the end of this tutorial you should hopefully be able to understand how to transition from flying with your KinD integration testing stack to the real world - well more specifically the Bristol Robotics Laboratory flight arena.

[TOC]

## Bristol Robotics Laboratory Flight Arena

The Bristol Robotics Lab (BRL) Flight Arena is a large 15.6m x 11.8m x 5m space with a large 10m x 5m x 4m flying volume in the center. 

![flight_arena](flight_arena.png)

### Flight Arena Features

The space is safe to fly vehicles up to 5kg, and multiple smaller vehicles. In the past we've had projects ranging from high speed flight for autonomous drone racing to flying custom drones for cave inspections. 

A key feature of the flight arena is the array of ViCon Motion Capture cameras dotted around the gantries. When calibrated, these give mm level accuracy at detecting the position of reflective balls. These balls are placed in a non-symmetric pattern aroound the UAV. This allows us to have excellent positioning information of our drones and is fed directly to the vehicle. 

For multi-uav work, we have aquired a set of [coex clover](https://coex.tech/clover) multirotor UAVs. These UAVs are comprised of a raspberry pi 4B with 2Gb RAM connected to a modified PixRacer Autopilot running PX4. For sensing, they have your standard set of IMU, magnetometer, compass and barometer, as well as a downwards facing range finder, a camera, and a ring of LEDs. These clovers are the ones we aim to do our application tests on. 

![coex_clover_pictures](clover.png)

In terms of compute, we have 3 recent desktops and 2 laptop hotdesking spaces, and an arena server. For networking, we rely on a strong wifi hub to transmit to and from any active vehicles. 

### Flight Arena System Setup

Currently in the flight arena we have a minature cluster setup using a lightweight variant of kubernetes known as [k3s](https://k3s.io/). We opt to use k3s as it provides many of the core features we require from running kubernetes, without beeing needlessly expensive to run on low-powered edge hardware. 

![arena_architecture](arena.png)

As shown in the diagram, we run a central k8 server on the arena server. Each of the vehicles is then setup as a node with a name of vehicle_11 to vehicle_14. These can be seen by logging onto any of the machines and going to the arena kubernetes dashboard on `https://flyingserver.local:13771`. You will need to run `starling utils get-dashboard-token` to get the access token.

Each of the desktop machines only serve to access the cluster and are not part of the cluster themselves. However due to a quirk of ROS2, each of the desktops can actually natively (and through running a docker container) access the active ROS2 topics. 

A useful side-affect of running the drones as nodes in a cluster is that they do not need reconfiguring on startup. Once a vehicle is turned on it will automatically attempt to reconnect to the cluster and request its deployed containers. 

A key element of indoor flight, especially so with multiple vehicles, is safety. It is absolutely paramount that we are always aware of the safety cases and features of anything we fly - hence the need for this entire testing and integration testing stack in the first place.


## Preparing your controller for real world deployment



## Deploying and Developing on real vehicles





## Next Steps