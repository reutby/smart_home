# Smart-Home project
Smart Home is a next generation platform for managing IoT enhanced smart building.
The ability to collect data from environmental sensors such as HVAC, lighting,
fire safety and other sources combined with the ability to extract, aggregate,
analyze, and make decisions based on that data.

The platform serves as the controller and integration hub for modules, devices, controllers and sensors 
that will enable efficient and comfortable operation of the building.

# Description
The central hub is a server application that serves mainly as a host for software
agents representing the devices.
An agent is the software entity loaded by the server to represent an actual device
and will allow the basic interaction between server and devices.
Agents will be loaded at system startup according to a configuration file.

the smart home project will provide the following:
- Provide an efficient mechanism (Multi-threading solution) to receive events from sensors and dispatch these events to relevant controllers.
- Provide a detailed level design.
- Provide an implementation using C++ for a POSIX compliant system.
